package main
import (
	flag "github.com/docker/docker/pkg/mflag"
	"fmt"
	"strings"
//	"io/ioutil"
	"net/http"
	"time"
)

func httpGet(i int) {
	resp, err := http.Get("http://localhost:8714/lua")
	if err != nil {
		// handle error
	}

	defer resp.Body.Close()
//	body, err := ioutil.ReadAll(resp.Body)
//	if err != nil {
//		// handle error
//	}
//	fmt.Println(i, ":", string(body))
}

func bench(qps int) {
	currTime := time.Now()
	for i := 0; i < qps; i++ {
		go httpGet(i)
	}
	timeDiff := time.Since(currTime)
	time.Sleep(1 * time.Second - timeDiff)
}

func main() {
	qps := flag.Int([]string{"r", "-qps"}, 100, "request number per second")
//	reqfile := flag.String([]string{"f", "-file"}, "", "request file")
	flag.Parse()
	fmt.Println(*qps)

	args := flag.Args()
	if len(args) == 1 {
		colonCnt := strings.Count(args[0], ":")
		if colonCnt == 0 {
			fmt.Println("use default port 80")
		} else if colonCnt == 1 {
			// TODO: catch error
			fmt.Println("port: ", args[0][strings.Index(args[0], ":") + 1:])
		}
	} else if len(args) == 2 {
		fmt.Println("spec: ", args[0], ":", args[1])
	} else {
		fmt.Println("invalid spec: ", args)
	}
	for {
		bench(*qps)
	}
}

