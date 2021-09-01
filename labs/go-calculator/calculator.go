package main

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array(?)
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)

import (
	"fmt"
	"os"
	"strconv"
)

func calc(operator int, values []int) int {
	r := values[0]
	if operator==1{
		fmt.Printf("%d",r)
		for i := 1;i<len(values);i++{
			fmt.Printf(" + %d",values[i])
			r += values[i]
		}
	}else if operator == 2{
		fmt.Printf("%d",r)
		for i := 1;i<len(values);i++{
			fmt.Printf(" - %d",values[i])
			r -= values[i]
		}
	}else if operator == 3{
		fmt.Printf("%d",r)
		for i := 1;i<len(values);i++{
			fmt.Printf(" * %d",values[i])
			r *= values[i]
		}
	}
	return r
}

func main() {
	var arr [256]int
	var oper int
	op := os.Args[1]
	if op == "add"{
		oper = 1
	}else if op == "sub"{
		oper = 2
	} else if op == "mult"{
		oper = 3
	}else{
		fmt.Println("Need to put add, sum or mult as the operator")
		os.Exit(1)
	}
	for i:= 2; i<len(os.Args) ;i++{
		f,err := strconv.Atoi(os.Args[i])
		if err != nil{
			fmt.Println("Only integers accepted")
			os.Exit(3)
		}
		arr[i-2] = f
	}
	slice := arr[0:len(os.Args)-2]
	result := calc(oper, slice)
	fmt.Printf(" = %d\n", result)
}