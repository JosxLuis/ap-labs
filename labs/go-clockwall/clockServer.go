// Clock Server is a concurrent TCP server that periodically writes the time.
package main

import (
	"flag"
	"io"
	"log"
	"net"
	"strconv"
	"time"
)

func handleConn(c net.Conn, port string) {
	defer c.Close()

	var loc *time.Location
	switch port {
	case "8010":
		loc, _ = time.LoadLocation("US/Eastern")
	case "8020":
		loc, _ = time.LoadLocation("Asia/Tokyo")
	case "8030":
		loc, _ = time.LoadLocation("Europe/London")
	}

	for {
		_, err := io.WriteString(c, loc.String()+" : "+time.Now().In(loc).Format("15:04:05\n"))
		if err != nil {
			return // e.g., client disconnected
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {
	port := flag.Int("port", 8000, "The port of the clock server")
	flag.Parse()

	listener, err := net.Listen("tcp", "localhost:"+strconv.Itoa(*port))

	if err != nil {
		log.Fatal(err)
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn, strconv.Itoa(*port)) // handle connections concurrently
	}
}
