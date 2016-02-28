package main

import (
	"bufio"
	"encoding/json"
	"errors"
	"flag"
	"fmt"
	"io"
	"net"
	"net/http"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"strings"
	//"runtime"
	"syscall"
	//	"io/ioutil"
	//"log"
	//	"syscall"
	"time"
)

const (
	MARK_NAME  = "_GO_DAEMON"
	MARK_VALUE = "1"
)

func handleConnection(conn net.Conn) {
}

func listen(line string) {
	ln, err := net.Listen("tcp", line)
	if err != nil {
		fmt.Print(err)
		return
	}
	for {
		conn, err := ln.Accept()
		if err != nil {
			return
			// handle error
		}
		go handleConnection(conn)
	}
}

type StatusServer struct {
	id        int
	statusMap map[string]bool
}

func (server *StatusServer) handleHeartBeat(w http.ResponseWriter, r *http.Request) {
	params := r.URL.RawQuery
	if len(params) < 4 || params[0:3] != "id=" {
		fmt.Println("invalid request", params)
		return
	}
	id := params[3:]
	fmt.Println(server.id, ":", os.Getpid(), " receive from ", id)
	fmt.Fprintf(w, "OK!")
}

func (server *StatusServer) handleReq(w http.ResponseWriter, r *http.Request) {
	encoder := json.NewEncoder(w)
	err := encoder.Encode(server.statusMap)
	if err != nil {
		fmt.Println("encode status map failed: ", err)
	}
}

func httpListen(server *StatusServer, spec string) {
	hbHandler := server.handleHeartBeat
	http.HandleFunc("/hb", hbHandler)

	reqHandler := server.handleReq
	http.HandleFunc("/get", reqHandler)

	err := http.ListenAndServe(spec, nil)
	if err != nil {
		fmt.Println("listen error:", err)
	}
	fmt.Println("listen " + spec)
}

func fork(iplist *string, i int) error {
	mark := fmt.Sprintf("%s=%s", MARK_NAME, MARK_VALUE)
	attr := &os.ProcAttr{
		Dir: "./",
		Env: append(os.Environ(), mark),
		Files: []*os.File{
			os.Stdin,
			os.Stdout,
			os.Stderr,
		},
		Sys: &syscall.SysProcAttr{
			//Chroot:     d.Chroot,
			//Credential: d.Credential,
			Setsid: true,
		},
	}

	args := []string{
		"main",
		"-iplist",
		*iplist,
		"-index",
		fmt.Sprintf("%d", i),
	}

	// _, filename, _, _ := runtime.Caller(0)
	absDir, _ := filepath.Abs(filepath.Dir(os.Args[0]))
	execName := filepath.Join(absDir, filepath.Base(os.Args[0]))

	if _, err := os.StartProcess(execName, args, attr); err != nil {
		fmt.Println(err)
		return err
	}

	//	state, err := c.Process.Wait()
	//	if err != nil {
	//		return err
	//	} else if !state.Success() {
	//		return &ExitError{state}
	//	}
	return nil
}

func createFile(i int, line string) error {
	filename := fmt.Sprintf("%d.out", i)
	fp, err := os.OpenFile(filename, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0666)
	if err != nil {
		fmt.Println(err)
		return err
	}
	defer fp.Close()

	cnt, err := fmt.Fprintf(fp, "%d: %s\npid: %d  ppid: %d", i, line, os.Getpid(), os.Getppid())
	if err != nil {
		fmt.Println(cnt)
		fmt.Println(err)
		return err
	}
	return nil
}

func child() error {
	fmt.Println(os.Args)
	iplistFileName := flag.String("iplist", "iplist", "iplist")
	index := flag.Int("index", -1, "ip index in list")
	flag.Parse()

	fp, _ := os.Open(*iplistFileName)
	defer fp.Close()
	reader := bufio.NewReader(fp)

	iplist := []string{}
	for i := 0; ; i++ {
		line, err := reader.ReadString('\n')

		if err == io.EOF {
			break
		}
		if len(line) == 0 {
			return errors.New("empty line in iplist")
		}
		if line[len(line)-1] == '\n' {
			line = line[0 : len(line)-1]
		}
		iplist = append(iplist, line)
	}
	server := new(StatusServer)
	server.statusMap = make(map[string]bool, 10)
	server.id = *index
	// barrier()
	for i := 0; i < len(iplist); i++ {
		server.statusMap[string(i)] = true
		// createFile(i, line)
		//listen(line)
	}
	line := iplist[*index]
	go httpListen(server, line)

	for {
		fmt.Println("here fmt")
		for i := 0; i < len(iplist); i++ {
			if i != *index {
				line := iplist[i]
				// request update status
				reqLine := "http://" + line + "/hb?id=" + strconv.Itoa(i) + "_" + strconv.Itoa(os.Getpid())
				resp, err := http.Get(reqLine)
				if err != nil {
					server.statusMap[string(i)] = false
					continue
				}
				defer resp.Body.Close()
				body := resp.Body
				buf := make([]byte, 3)
				failed := false
				count, err := body.Read(buf)
				if err != nil && err != io.EOF {
					fmt.Println("invalid http resp:", err)
					failed = true
				}
				if count != 3 {
					fmt.Println("invalid http buf:", buf)
					failed = true
				}
				if failed {
					server.statusMap[string(i)] = false
				} else {
					server.statusMap[string(i)] = true
				}
			}
			time.Sleep(time.Second)
		}
	}
	return nil
}

func parent() {
	var (
		cmdOut  []byte
		cmdName string
		cmdArgs []string
		count   int
		err     error
	)
	iplist := flag.String("iplist", "iplist", "iplist")
	flag.Int("index", -1, "ip index in list")
	flag.Parse()

	cmdName = "wc"
	cmdArgs = []string{"-l", "iplist"}
	cmdOut, err = exec.Command(cmdName, cmdArgs...).Output()
	if err != nil {
		fmt.Println(os.Stderr, "There was an error running command: ", err)
		os.Exit(1)
	}
	count, err = strconv.Atoi(strings.Split(string(cmdOut), " ")[0])

	for i := 0; i < count; i++ {
		err = fork(iplist, i)
		if err != nil {
			fmt.Println(err)
		}
	}
	//	for {
	//		time.Sleep(time.Second)
	//	}
}

func main() {
	v, exist := syscall.Getenv(MARK_NAME)
	_, debug := syscall.Getenv("DEBUG")
	if (exist && v == MARK_VALUE) || debug {
		fmt.Println("run child()")
		child()
	} else {
		fmt.Println("run parent()")
		parent()
	}
}
