package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) == 1 {
		fmt.Println("¡Error!, Sorry :o you must insert a parameter like a name")
		return
	} else {
		name := ""
		for i := 1; i < len(os.Args); i++ {
			name += os.Args[i] + " "
		}
		fmt.Printf("Hello %v, Welcome to the jungle\n", name)
	}
}
