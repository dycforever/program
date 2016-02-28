
package main

import (
	"os"
	"fmt"
	"os/signal"
	"syscall"

	psignal "github.com/docker/docker/pkg/signal"
)

func setupDumpStackTrap() {
	c := make(chan os.Signal, 1)
	signal.Notify(c, syscall.SIGUSR1)
	go func() {
		for range c {
			psignal.DumpStacks()
		}
	}()
}

func main() {
	c := make(chan os.Signal, 1)
	signal.Notify(c)
	// signal can be overlapped
	setupDumpStackTrap()
	for sig := range c {
		switch sig {
		default:
			fmt.Println("sig: ", sig)
		}
	}
}
