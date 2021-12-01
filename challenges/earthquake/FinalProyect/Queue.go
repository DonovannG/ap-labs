package main

type Queue struct {
	queue  []*Node
	antPos int
	curr   int
}

func NewQueue(size, antPos int, curr int) *Queue {
	queue := make([]*Node, size)
	return &Queue{queue: queue, antPos: antPos, curr: curr}
}

func (q *Queue) add(node *Node) {
	q.queue[q.antPos] = node
	q.antPos++
}

func (q *Queue) pop() *Node {
	q.curr++
	return q.queue[q.curr-1]
}