package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	args := os.Args[1:]
	if len(args) != 2 {
		fmt.Println("Error in inputs")
		fmt.Println("USAGE: ./earthqueake peopleQuantity secondsToFinish")
	} else {
		n, errN := strconv.Atoi(args[0])
		TO, errTO := strconv.Atoi(args[1])
		if errTO != nil || errN != nil {
			fmt.Println("Error in inputs")
			fmt.Println("USAGE: ./earthqueake peopleQuantity secondsToFinish")
		} else {
			file := "finalMap.csv"
			tmpMap := newMap(10, file, 16, 12)
			tmpMap.initMap()
			sim := newSimulation(n, TO, tmpMap)

			if sim == nil {
				fmt.Println("Can't run Simulation")
			} else {
				sim.startSim()
				sim.report()
			}
		}
	}
}
