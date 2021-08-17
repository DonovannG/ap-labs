package main

import (
	"fmt"
	"os"
)


func main() {
	
	//name := os.Args[1]
	n := len(os.Args)
	
	if(n>1){
		if n == 1{ 
			name := os.Args[1]
			fmt.Printf("Hello %v, Welcome to the jungle \n", name)
		}else{
			name := os.Args[1]
			for i := 2; i < n; i++{
				name += " " + os.Args[i]
			}
			fmt.Printf("Hello %v, Welcome to the jungle \n", name)	
		}
	}else{
		fmt.Println("Error, No name was entered")
	}	
}
