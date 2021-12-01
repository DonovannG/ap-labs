package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Simulation struct {
	waitGroup *sync.WaitGroup
	PMap      *Map
	people    []Person
	seconds   int
	exit      chan int
}

func (pm *Simulation) createPerson() {
	for i := 0; i < len(pm.people); i++ {
		pm.people[i] = Person{float32(i / 2), i, true, nil}
	}
}

func (pm *Simulation) setPP() {
	availableNode := pm.PMap.getActualNode()
	for i := 0; i < len(pm.people); i++ {
		rand.Seed(time.Now().UnixNano())
		pos := rand.Intn(len(availableNode)-0) + 0
		pm.people[i].setPos(availableNode[pos])
		availableNode[pos] = availableNode[len(availableNode)-1]
		availableNode[len(availableNode)-1] = nil
		availableNode = availableNode[:len(availableNode)-1]
	}
}

func (pm *Simulation) initTime(timeLeft int) {
	pm.waitGroup.Add(1)
	SW := time.NewTimer(time.Duration(timeLeft) * time.Second)
	<-SW.C
	fmt.Println("Time!")
	close(pm.exit)
	defer pm.waitGroup.Done()
}

func (pm *Simulation) initMove() {
	for i := 0; i < len(pm.people); i++ {
		go pm.people[i].move(pm.waitGroup, pm.exit)
		pm.waitGroup.Add(1)
	}
}

func (pm *Simulation) startSim() {
	pm.createPerson()
	pm.setPP()
	go pm.initTime(pm.seconds)
	pm.initMove()
	pm.waitGroup.Wait()
}

func newSimulation(Quantity int, seconds int, PMap *Map) *Simulation {
	if len(PMap.getActualNode()) < Quantity {
		return nil
	}
	return &Simulation{
		waitGroup: new(sync.WaitGroup),
		PMap:      PMap,
		seconds:   seconds,
		people:    make([]Person, Quantity),
		exit:      make(chan int),
	}

}

func (pm *Simulation) report() {
	deceased := 0
	remaining := 0
	for i := 0; i < len(pm.people); i++ {
		if pm.people[i].isDeath {
			deceased++
		}
	}
	remaining = len(pm.people) - deceased
	fmt.Printf("\n\nSimulation was successfull with: %d people in %d sec\n", len(pm.people), pm.seconds)
	fmt.Printf("%d people have survived and %d have died\n", remaining, deceased)

}
