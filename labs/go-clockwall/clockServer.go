// Clock Server is a concurrent TCP server that periodically writes the time.
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

func handleConn(c net.Conn, tz string, location *time.Location) {
	defer c.Close()
	for {
		_, err := io.WriteString(c, tz+strings.Repeat(" ", 15-len(tz))+": "+time.Now().In(location).Format("15:04:05\n"))
		if err != nil {
			return // e.g., client disconnected
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {

	if len(os.Args) < 3 || len(os.Args) > 3 {
		fmt.Println("Usage TZ={Timezone} go run clockServer.go -port {Port}")
		os.Exit(1)
	}

	port := os.Args[1:]
	tz := os.Getenv("TZ")

	listener, err := net.Listen("tcp", "localhost:"+port[1])

	location, errt := time.LoadLocation(tz)

	if errt != nil {
		log.Panic(tz + " Is an invalid Timezone")
	}
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn, tz, location) // handle connections concurrently
	}
}
