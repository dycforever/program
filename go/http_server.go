package main

import (
	"fmt"
	"path"
	"io"
	"log"
	"net/http"
	"os"
)

func recvMetric(w http.ResponseWriter, r *http.Request) {
	body := r.Body
	buf := make([]byte, 1024)
	for {
		count, err := body.Read(buf)
		if count == 0 && (err == io.EOF || err == nil) {
			fmt.Println("read eof")
			return
		} else if count == 0 {
			fmt.Println("detect error")
			return
		} else {
			fmt.Println("recv body:", string(buf))
		}
	}
}

func chart(w http.ResponseWriter, r *http.Request) {
	url := r.URL.EscapedPath()
	file := path.Join("/home/dyc/github/dycforever/program/js/highcharts", url)
	fmt.Println("output file:", file)
	fin, _ := os.Open(file)
	defer fin.Close()
	io.Copy(w, fin)
}

func saveFile(w http.ResponseWriter, r *http.Request) {
	err := r.ParseMultipartForm(1e8)
	if err != nil {
		fmt.Fprintf(w, "error!\n")
		fmt.Println(err)
		return
	}
	fmt.Println(r.Form)
	fmt.Println("url", r.URL)
	fmt.Println("path", r.URL.Path)
	fmt.Println("scheme", r.URL.Scheme)

	fileContent, headers, err := r.FormFile("UpLoadFile")
	if err != nil {
		fmt.Println("get r.FormFile['UpLoadFile'] failed:")
		return
	}

	filename := headers.Filename
	if filename == "" {
		fmt.Println("get filename failed:")
		return
	}

	fout, err := os.Create(filename)
	defer fout.Close()
	if err != nil {
		fmt.Println("open file failed:", filename, err)
		return
	}

	buf := make([]byte, 5*1024*1024)
	for {
		n, err := fileContent.Read(buf)
		if n == 0 && err == io.EOF {
			break
		} else if n > 0 {
			fout.Write(buf[:n])
		} else {
			fmt.Println("read failed")
			break
		}
	}
	//    _, err = io.Copy(fout, fileContent)
	//    if err != nil {
	//	    fmt.Fprintf(w, "write failed!\n")
	//        return
	//    }

	fmt.Fprintf(w, "received!\n")
}

func HelloServer(w http.ResponseWriter, r *http.Request) {
	//r.ParseForm()
	val := r.FormValue("username")
	println("HelloServer1", val)
	w.Write([]byte(val))
}

func main() {
	http.HandleFunc("/upload", saveFile)
	http.HandleFunc("/report", recvMetric)
	http.HandleFunc("/hello", HelloServer)
	http.HandleFunc("/", chart)
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
