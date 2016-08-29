package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"

//	"golang.org/x/net/http2"
)

func main() {
	client := http.Client{
		// InsecureTLSDial is temporary and will likely be
		// replaced by a different API later.
		// Transport: &http2.Transport{},
	}

	// resp, err := client.Get("https://so.m.sm.cn:443/")
	resp, err := client.Get("https://so.m.sm.cn:12345/")

	if err != nil {
		log.Fatal(err)
	}

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(string(body))
}