package main

import (
	"fmt"
	"os/exec"
)

func main() {
	cmd2 := new(exec.Cmd)
	cmd2.Path = "/usr/local/bin/sh"
	cmd2.Args = []string{"sh", "/home/dingyc/dev/gopath/t.sh"}
	fmt.Println(cmd2)

	//	cmd := exec.Command("/usr/local/bin/sh", "/home/dingyc/dev/gopath/t.sh")
	//	fmt.Println(cmd)
	err := cmd2.Start()
	if err != nil {
		fmt.Println(err)
	}
	err = cmd2.Wait()
	if err != nil {
		fmt.Println(err)
	}

	//	out, err := exec.Command("/bin/bash", "/home/dingyc/dev/gopath/t.sh").Output()
	//	if err != nil {
	//		fmt.Println("error occured")
	//		fmt.Printf("%s", err)
	//	}
	//	fmt.Printf("%s", out)
	fmt.Println("success")
}
