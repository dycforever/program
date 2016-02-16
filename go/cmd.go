package main
import (
	"log"
	"io"
	"syscall"
	"os"
	"path"
	"os/exec"
	"path/filepath"
)

func newConsole() (Console, error) {
	master, err := os.OpenFile("/dev/ptmx", syscall.O_RDWR|syscall.O_NOCTTY|syscall.O_CLOEXEC, 0)
	if err != nil {
		return nil, err
	}
	console, err := ptsname(master)
	if err != nil {
		return nil, err
	}
	if err := unlockpt(master); err != nil {
		return nil, err
	}
	if err := os.Chmod(console, 0600); err != nil {
		return nil, err
	}

	return &linuxConsole{
		slavePath: console,
		master:    master,
	}, nil
}

//  func createStdioPipes(p *libcontainer.Process, rootuid int) (*tty, error) {
//  	var (
//  		t   = &tty{}
//  		fds []int
//  	)
//  	r, w, err := os.Pipe()
//  	if err != nil {
//  		return nil, err
//  	}
//  	fds = append(fds, int(r.Fd()), int(w.Fd()))
//  	go io.Copy(w, os.Stdin)
//  	t.closers = append(t.closers, w)
//  	p.Stdin = r
//  	if r, w, err = os.Pipe(); err != nil {
//  		return nil, err
//  	}
//  	fds = append(fds, int(r.Fd()), int(w.Fd()))
//  	go io.Copy(os.Stdout, r)
//  	p.Stdout = w
//  	t.closers = append(t.closers, r)
//  	if r, w, err = os.Pipe(); err != nil {
//  		return nil, err
//  	}
//  	fds = append(fds, int(r.Fd()), int(w.Fd()))
//  	go io.Copy(os.Stderr, r)
//  	p.Stderr = w
//  	t.closers = append(t.closers, r)
//  	// change the ownership of the pipe fds incase we are in a user namespace.
//  	for _, fd := range fds {
//  		if err := syscall.Fchown(fd, rootuid, rootuid); err != nil {
//  			return nil, err
//  		}
//  	}
//  	return t, nil
//  }

func main() {
	dir, err := filepath.Abs(filepath.Dir(os.Args[0]))
	if err != nil {
		log.Fatal(err)
	}


	execFile := path.Join(dir, "child")
	cmd := &exec.Cmd{
		Path: execFile,
		Args: []string {execFile},
	}

	r, w, err := os.Pipe()
	if err != nil {
		return
	}
	go io.Copy(w, os.Stdin)
	cmd.Stdin = r
	cmd.Stdin = os.Stdin

	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	cmd.Dir = "/tmp"
	cmd.SysProcAttr = &syscall.SysProcAttr{}
	cmd.Run()
//	cmd.ExtraFiles = append(p.ExtraFiles, childPipe)
//	cmd.Env = append(cmd.Env, fmt.Sprintf("_LIBCONTAINER_INITPIPE=%d", 3+len(cmd.ExtraFiles)-1))
}

