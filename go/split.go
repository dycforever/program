package main

import (
	"fmt"
	"strings"
)

func main() {
	l := "a#b#c#d#e#f#g"
	fmt.Println(strings.Split(l, "#"))
	fmt.Println(strings.SplitAfter(l, "#"))
	fmt.Println(strings.SplitN(l, "#", 3))
	fmt.Println(strings.SplitAfterN(l, "#", 3))
}
