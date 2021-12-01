package main

import (
	"fmt"
	"sync"
	"time"
)

type Person struct {
	speed   float32
	id      int
	isDeath bool
	pos     *Node
}

func (p *Person) setPos(MyNode *Node) {
	p.pos = MyNode
	p.pos.mut.Lock()
}

func (p *Person) move(waitGroup *sync.WaitGroup, exit chan int) {
	fmt.Printf("Person %d has started to run\n", p.id)
	for {
		select {
		case <-exit:
			fmt.Printf("Person %d is dead\n", p.id)
			defer waitGroup.Done()
			return

		default:
			if !p.pos.isExit {
				p.pos.nextStep.mut.Lock()
				time.Sleep(time.Duration(p.speed) * time.Second)
				p.pos.mut.Unlock()
				p.pos = p.pos.nextStep
			} else {
				fmt.Printf("Person %d is out of the building\n", p.id)
				p.pos.mut.Unlock()
				p.isDeath = false
				defer waitGroup.Done()
				return
			}
		}
	}
}
