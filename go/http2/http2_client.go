package main

import (
	"fmt"
	//	"golang.org/x/net/http2"
	"io/ioutil"
	"log"
	"net/http"
)

func main() {
	client := http.Client{
	// InsecureTLSDial is temporary and will likely be
	// replaced by a different API later.
	}

	// resp, err := client.Get("https://so.m.sm.cn:443/")
	resp, err := client.Get("https://dyc.sm.cn:8082/")

	if err != nil {
		log.Fatal(err)
	}

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(string(body))
}
