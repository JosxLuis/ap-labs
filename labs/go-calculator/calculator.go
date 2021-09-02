package main

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)

import (
	"fmt"
	"os"
	"strconv"
)

func calc(operator int, values []int) int {
	resultado := values[0]
	fmt.Print(resultado)

	for i := 1; i < len(values); i++ {
		if operator == 1 {
			fmt.Print(" + ", values[i])
			resultado += values[i]
		} else if operator == 2 {
			fmt.Print(" - ", values[i])
			resultado -= values[i]
		} else {
			fmt.Print(" * ", values[i])
			resultado *= values[i]
		}
	}

	return resultado
}

func main() {

	if len(os.Args) < 4 {
		fmt.Println("¡Error!, No ingresaste suficientes parametros:")
		fmt.Println("<operador> <numeros separados por espacio>")
		return
	} else {
		operator := 0
		if os.Args[1] == "add" {
			operator = 1
		} else if os.Args[1] == "sub" {
			operator = 2
		} else if os.Args[1] == "mult" {
			operator = 3
		} else {
			fmt.Println("El operador ", os.Args[1], " no es valido")
			return
		}

		slice := make([]int, 0, 100)
		for i := 2; i < len(os.Args); i++ {
			intValue, err := strconv.Atoi(os.Args[i])
			if err == nil {
				slice = append(slice, intValue)
			} else {
				fmt.Println("No ingresaste un numero entero")
				return
			}
		}

		resultado := calc(operator, slice)
		fmt.Print(" = ", resultado)
		fmt.Println("")
	}
}
