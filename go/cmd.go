package main
import (
	"log"
	"syscall"
	"os"
	"path"
	"os/exec"
	"path/filepath"
)

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
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	cmd.Dir = "/tmp"
	cmd.SysProcAttr = &syscall.SysProcAttr{}
	cmd.Run()
//	cmd.ExtraFiles = append(p.ExtraFiles, childPipe)
//	cmd.Env = append(cmd.Env, fmt.Sprintf("_LIBCONTAINER_INITPIPE=%d", 3+len(cmd.ExtraFiles)-1))
}

