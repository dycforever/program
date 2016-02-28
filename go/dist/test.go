package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
)

var a string

func f() {
	fmt.Fprint(ioutil.Discard, a)
}

func hello(i int) {
	a = "hello, world" + strconv.Itoa(i)
	go f()
}

func main() {
	for i := 0; ; i++ {
		hello(i)
	}
}
