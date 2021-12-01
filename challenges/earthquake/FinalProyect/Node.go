package main

import (
	"sync"
)

type Node struct {
	left     *Node
	right    *Node
	back     *Node
	front    *Node
	nextStep *Node
	isExit   bool
	isBorder bool
	STE      int
	mut      *sync.Mutex
}

func NewNode(isExit bool, isBorder bool, STE int) *Node {
	newNode := &Node{}
	newNode.left = nil
	newNode.right = nil
	newNode.back = nil
	newNode.front = nil
	newNode.nextStep = nil
	newNode.isExit = isExit
	newNode.isBorder = isBorder
	newNode.STE = STE
	newNode.mut = new(sync.Mutex)
	return newNode
}

func (n *Node) getNext() []*Node {
	array := make([]*Node, 4)
	array[0] = n.front
	array[1] = n.right
	array[2] = n.back
	array[3] = n.left
	return array
}
