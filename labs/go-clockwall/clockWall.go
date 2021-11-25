package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
	"strings"
)

func printTime(str string) {
	arr := strings.Split(str, "=")
	conn, err := net.Dial("tcp", arr[1])
	if err != nil {
		log.Fatal(err)
	}
	done := make(chan int)
	go func() {
		scanner := bufio.NewScanner(conn)
		for scanner.Scan() {
			fmt.Println(scanner.Text()) //arr[0]+"\t"+":",
		}
		done <- 2
	}()

	close(done)

}

func main() {
	wait := make(chan int)
	ports := os.Args[1:]
	for _, i := range ports {
		go printTime(i)
	}

	for range ports {
		<-wait
	}

	close(wait)

}
