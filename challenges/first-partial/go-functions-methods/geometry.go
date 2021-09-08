// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

type Point struct{ x, y float64 }

func (p Point) X() float64 {
	return p.x
}

func (p Point) Y() float64 {
	return p.y
}

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

//!-point

//!+path

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

func randFloat(min, max float64) float64 {
	return min + rand.Float64()*(max-min)
}

func newPoint(x, y float64) Point {
	p := Point{x, y}
	return p
}

func onSegment(p, q, r Point) bool {
	if q.X() <= math.Max(p.X(), r.X()) && q.X() >= math.Min(p.X(), r.X()) && q.Y() <= math.Max(p.Y(), r.Y()) && q.Y() >= math.Min(p.Y(), r.Y()) {
		return true
	} else {
		return false
	}
}

func orientation(p, q, r Point) int {
	val := (q.Y()-p.Y())*(r.X()-q.X()) - (q.X()-p.X())*(r.Y()-q.Y())
	if val == 0 {
		return 0
	}

	if val > 0 {
		return 1
	} else {
		return 2
	}
}

func verifyIntersect(p1, q1, p2, q2 Point) bool {

	o1 := orientation(p1, q1, p2)
	o2 := orientation(p1, q1, q2)
	o3 := orientation(p2, q2, p1)
	o4 := orientation(p2, q2, q1)

	if o1 != o2 && o3 != o4 {
		return true
	}

	if o1 == 0 && onSegment(p1, p2, q1) {
		return true
	}

	if o2 == 0 && onSegment(p1, q2, q1) {
		return true
	}

	if o3 == 0 && onSegment(p2, p1, q2) {
		return true
	}

	if o4 == 0 && onSegment(p2, q1, q2) {
		return true
	}

	return false
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("¡Error!, No ingresaste suficientes parametros:")
		fmt.Println("<number_of_sides>")
		return
	} else {
		intValue, err := strconv.Atoi(os.Args[1])
		if err != nil {
			fmt.Println("No ingresaste un valor entero")
			return
		}

		if intValue >= 3 {
			rand.Seed(time.Now().UTC().UnixNano()) //Semilla

			var slice Path

			puntos := make([]Point, 0, 5)
			segmentos := make([]Point, 0, 5)

			for i := 0; i < intValue; i++ {
				puntos = append(puntos, newPoint(math.Floor((randFloat(-100, 100))*100)/100, math.Floor((randFloat(-100, 100))*100)/100))
			}

			segmentos = append(segmentos, newPoint(puntos[0].X(), puntos[0].Y()))

			for i := 1; i < intValue; i++ {
				segmentos = append(segmentos, newPoint(puntos[i].X(), puntos[i].Y()))
				segmentos = append(segmentos, newPoint(puntos[i].X(), puntos[i].Y()))
			}

			segmentos = append(segmentos, newPoint(puntos[0].X(), puntos[0].Y()))

			flag := false
			var i, j int
			for i = 0; i < (intValue*2)+1; i++ {
				for j = i + 2; j < intValue*2-1; j++ {
					//time.Sleep(2 * time.Second)
					//fmt.Println("Comparar", segmentos[i], segmentos[i+1], "con: ", segmentos[j], segmentos[j+1])
					if segmentos[i+1] == segmentos[j] || segmentos[j+1] == segmentos[i] {
						flag = false
					} else {
						for verifyIntersect(segmentos[i], segmentos[i+1], segmentos[j], segmentos[j+1]) == true {
							q := newPoint(math.Floor((randFloat(-100, 100))*100)/100, math.Floor((randFloat(-100, 100))*100)/100)
							for h := 0; h < len(puntos); h++ {
								if puntos[h] == segmentos[j] {
									puntos[h] = q
								}
							}

							for k := 0; k < len(segmentos); k++ {
								if segmentos[k] == segmentos[j] {
									segmentos[k] = q
								}
							}

							flag = true
							i = 0
							break

						}
					}
					if flag == true {
						j = 0
					} else {
						j++
					}
				}
				i++
			}

			puntos = append(puntos, puntos[0])
			slice = puntos

			fmt.Println(" - Generating a [", intValue, "] sides figure")
			fmt.Println(" - Figure's vertices")
			for i := 0; i < len(slice)-1; i++ {
				fmt.Print("\t")
				fmt.Print(" - ( ")
				fmt.Print(slice[i])
				fmt.Println(" ) ")
			}

			fmt.Println(" - Figure's Perimeter")
			fmt.Print("\t")
			fmt.Print(" - ")
			for i := 0; i < len(slice)-1; i++ {
				fmt.Printf("%.3f", slice[i].Distance(slice[i+1]))
				if i < len(slice)-2 {
					fmt.Printf(" + ")
				}
			}

			fmt.Printf(" =  %.3f", slice.Distance())
			fmt.Println("")

		} else {
			fmt.Println("No ingresaste un numero mayor de 2 puntos")
		}
	}
}

//!-path
