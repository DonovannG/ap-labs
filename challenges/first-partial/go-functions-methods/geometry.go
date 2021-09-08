// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"math"
	"fmt"
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

func orientation(p Point, q Point, r Point) int {
	value := (q.Y()-p.Y())*(r.X()-q.X()) - (q.X()-p.X())*(r.Y()-q.Y())
	if value == 0 {
		return 0
	}else if value > 0 {
		return 1
	}else{
		return 2
	}
}

func segment(p Point, q Point, r Point) bool {
	if q.X() <= math.Max(p.X(), r.X()) && q.X() >= math.Min(p.X(), r.X()) && q.Y() <= math.Max(p.Y(), r.Y()) && q.Y() >= math.Min(p.Y(), r.Y()) {
		return true
	}
	return false
}

func intersect(p1 Point, q1 Point, p2 Point, q2 Point) bool {
	o1 := orientation(p1, q1, p2)
	o2 := orientation(p1, q1, q2)
	o3 := orientation(p2, q2, p1)
	o4 := orientation(p2, q2, q1)
	if o1 != o2 && o3 != o4 {
		return true
	}else if o1 == 0 && segment(p1, p2, q1) {
		return true
	}else if o2 == 0 && segment(p1, q2, q1) {
		return true
	}else if o3 == 0 && segment(p2, p1, q2) {
		return true
	}else if o4 == 0 && segment(p2, q1, q2) {
		return true
	}else{
		return false
	}
	
}

func generator(pointArr Path, sides int) []Point {
	s := rand.NewSource(time.Now().UnixNano())
	random := rand.New(s)
	for i := 0; i < sides-1; i++ {
		symbolX := random.Intn(2)
		if symbolX == 0 {
			pointArr[i].x = random.Float64() * 100
		} else {
			pointArr[i].x = random.Float64() * -100
		}
		symbolY := random.Intn(2)
		if symbolY == 0 {
			pointArr[i].y = random.Float64() * 100
		} else {
			pointArr[i].y = random.Float64() * -100
		}
	}
	pointArr[sides-1] = pointArr[0]
	return pointArr
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Please input number of sides")
		os.Exit(1)
	}
	if len(os.Args) > 2 {
		fmt.Println("Only one input (number of sides) is allowed")
		os.Exit(2)
	}
	sides, err := strconv.Atoi(os.Args[1])
	if sides <= 2 {
		fmt.Println("Cannot create a figure with 2 or fewer sides")
		os.Exit(3)
	}  
	if err == nil {
		fmt.Printf("- Generating a [%d] sides figure\n", sides)
		fmt.Println("- Figure's vertices")
		pointArr := make(Path, sides+1)
		pointArr = generator(pointArr, sides+1)
		for i := 0; i < sides-3; i++ {
			if intersect(pointArr[i], pointArr[i+1], pointArr[i+2], pointArr[i+3]) == true {
				println("An interseccion was detected, try again")
				os.Exit(4)
			} 
		}
		for j := 0; j < sides; j++ {
			fmt.Printf(" - (  %f,   %f)\n", pointArr[j].X(), pointArr[j].Y())
		}
		fmt.Println("- Figure's Perimeter")
		fmt.Printf(" - %f", Distance(pointArr[0], pointArr[1]))
		for k := 1; k < sides; k++{
			fmt.Printf(" + %f", Distance(pointArr[k], pointArr[k+1]))
		}
		fmt.Printf(" = %f\n", pointArr.Distance())
	}
}

//!-path
