package main

import (
	"os"
	"io"
	"log"
	"runtime"
	"os/signal"
	"fmt"
	"syscall"

	"github.com/Sirupsen/logrus"
	"github.com/opencontainers/runc/libcontainer"
	"github.com/opencontainers/runc/libcontainer/utils"
	"github.com/docker/docker/pkg/term"
)

func init() {
	if len(os.Args) > 1 && os.Args[1] == "init" {
		runtime.GOMAXPROCS(1)
		runtime.LockOSThread()
		factory, _ := libcontainer.New("")
		if err := factory.StartInitialization(); err != nil {
			log.Fatal(err)
		}
		panic("--this line should have never been executed, congratulations--")
	}
}

type tty struct {
	console libcontainer.Console
	state   *term.State
	closers []io.Closer
}

func (t *tty) Close() error {
	for _, c := range t.closers {
		c.Close()
	}
	if t.state != nil {
		term.RestoreTerminal(os.Stdin.Fd(), t.state)
	}
	return nil
}

func (t *tty) resize() error {
	if t.console == nil {
		return nil
	}
	ws, err := term.GetWinsize(os.Stdin.Fd())
	if err != nil {
		return err
	}
	return term.SetWinsize(t.console.Fd(), ws)
}

func createTty(p *libcontainer.Process, rootuid int) (*tty, error) {
	console, err := p.NewConsole(rootuid)
	if err != nil {
		return nil, err
	}
	go io.Copy(console, os.Stdin)
	go io.Copy(os.Stdout, console)
	state, err := term.SetRawTerminal(os.Stdin.Fd())
	if err != nil {
		return nil, fmt.Errorf("failed to set the terminal from the stdin: %v", err)
	}
	t := &tty{
		console: console,
		state:   state,
		closers: []io.Closer{
			console,
		},
	}
	p.Stderr = nil
	p.Stdout = nil
	p.Stdin = nil
	return t, nil
}


// exit models a process exit status with the pid and
// exit status.
type exit struct {
	pid    int
	status int
}

type signalHandler struct {
	signals chan os.Signal
	tty     *tty
}

// forward handles the main signal event loop forwarding, resizing, or reaping depending
// on the signal received.
func (h *signalHandler) forward(process *libcontainer.Process) (int, error) {
	// make sure we know the pid of our main process so that we can return
	// after it dies.
	pid1, err := process.Pid()
	if err != nil {
		return -1, err
	}
	// perform the initial tty resize.
	h.tty.resize()
	for s := range h.signals {
		switch s {
		case syscall.SIGWINCH:
			h.tty.resize()
		case syscall.SIGCHLD:
			exits, err := h.reap()
			if err != nil {
				logrus.Error(err)
			}
			for _, e := range exits {
				logrus.WithFields(logrus.Fields{
					"pid":    e.pid,
					"status": e.status,
				}).Debug("process exited")
				if e.pid == pid1 {
					// call Wait() on the process even though we already have the exit
					// status because we must ensure that any of the go specific process
					// fun such as flushing pipes are complete before we return.
					process.Wait()
					return e.status, nil
				}
			}
		default:
			logrus.Debugf("sending signal to process %s", s)
			if err := syscall.Kill(pid1, s.(syscall.Signal)); err != nil {
				logrus.Error(err)
			}
		}
	}
	return -1, nil
}

// reap runs wait4 in a loop until we have finished processing any existing exits
// then returns all exits to the main event loop for further processing.
func (h *signalHandler) reap() (exits []exit, err error) {
	var (
		ws  syscall.WaitStatus
		rus syscall.Rusage
	)
	for {
		pid, err := syscall.Wait4(-1, &ws, syscall.WNOHANG, &rus)
		if err != nil {
			if err == syscall.ECHILD {
				return exits, nil
			}
			return nil, err
		}
		if pid <= 0 {
			return exits, nil
		}
		exits = append(exits, exit{
			pid:    pid,
			status: utils.ExitStatus(ws),
		})
	}
}

func (h *signalHandler) Close() error {
	return h.tty.Close()
}

func main() {
	spec, rspec, err := loadSpec("/home/dingyc/dev/containers/config.json", "/home/dingyc/dev/containers/runtime.json")
	if err != nil {
		fatal(err)
	}

	abs := "/home/dingyc/dev/containers/runc_cont_test"

	factory, err := libcontainer.New(abs, libcontainer.Cgroupfs, func(l *libcontainer.LinuxFactory) error {
		return nil
	})

	config, err := createLibcontainerConfig("container_id", spec, rspec)
	if err != nil {
		fmt.Println(err)
		return
	}

	container, err := factory.Create("container_id", config)
	if err != nil {
		fmt.Println(err)
		return
	}

	process := &libcontainer.Process{
		Args: spec.Process.Args,
		Env:  spec.Process.Env,
		// TODO: fix libcontainer's API to better support uid/gid in a typesafe way.
		User:   fmt.Sprintf("%d:%d", spec.Process.User.UID, spec.Process.User.GID),
		Cwd:    spec.Process.Cwd,
		Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}

	rootuid, err := config.HostUID()
	if err != nil {
		fmt.Println(err)
		return
	}

	tty, err := createTty(process, rootuid)
	if err != nil {
		fmt.Println(err)
		return
	}

	s := make(chan os.Signal, 1024)

	signal.Notify(s)
	handler := &signalHandler{
		tty:     tty,
		signals: s,
	}

	defer handler.Close()

	if err := container.Start(process); err != nil {
		fmt.Println(err)
	}

	status, err := process.Wait()
	if err != nil {
		fmt.Println(err)
		fmt.Println(status)
	}

//	handler.forward(process)
	return
}



