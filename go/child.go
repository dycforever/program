package main
import (
	"fmt"
	"os"
)

func Info(format string, a... interface{}) {
	fmt.Print("[", os.Getpid(), "] ")
	fmt.Printf(format, a...)
	fmt.Print("\n")
}

func main() {
	cwd , _ := os.Getwd()
	Info("child at %s", cwd)

	fmt.Println("Enter text: ")
	text := ""
	count , _ := fmt.Scanln(&text)
	Info("read %d bytes: %s", count, text)
}


