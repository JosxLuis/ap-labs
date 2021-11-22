package main

import (
	"flag"
	"io"
	"log"
	"net"
	"os"
)

func main() {

	newyork := flag.String("NewYork", "localhost:8010", "Addres for NewYork timezone clock")
	tokyo := flag.String("Tokyo", "localhost:8020", "Addres for Tokyo timezone clock")
	london := flag.String("London", "localhost:8030", "Addres for London timezone clock")
	flag.Parse()

	cities := make(chan *string, 3) //buffered channel of integer, change if we have more citites
	go func() {
		cities <- newyork
		cities <- tokyo
		cities <- london
	}()
	for destination := range cities {
		conn := subscribe(*destination)
		defer conn.Close()
		go mustCopy(os.Stdout, conn)
	}

}

func subscribe(destination string) net.Conn {
	conn, err := net.Dial("tcp", destination)
	if err != nil {
		log.Fatal(err)
	}
	return conn
}

func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}
