package main

import (
	"flag"
	"fmt"
)

func main() {
	var port = flag.Int("port", 1234, "listen port")
	var ip = ""
	flag.StringVar(&ip, "ip", "", "listen ip")
	flag.Parse()
	fmt.Println(*port)
	fmt.Println(ip)
}
