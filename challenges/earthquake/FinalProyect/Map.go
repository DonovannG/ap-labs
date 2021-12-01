package main

import (
	"bufio"
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"math/rand"
	"os"
	"strconv"
	"time"
)

type Map struct {
	nodes         [][]*Node
	height, width int
	exitDoors     int
	path          string
}

func newMap(exitDoors int, path string, height int, width int) *Map {
	return &Map{
		height:    height,
		width:     width,
		exitDoors: exitDoors,
		path:      path,
	}
}

func (m *Map) initMap() {
	fmt.Println("Starting...")
	dobArr := readFile(m.path, m.width, m.height)
	m.nodes = MatToNode(dobArr, m.exitDoors, m.width, m.height)

	for i := 0; i < len(m.nodes); i++ {
		for j := 0; j < len(m.nodes[i]); j++ {
			if m.nodes[i][j] == nil {
				fmt.Print("--", 0, "-")
			} else if m.nodes[i][j].isExit {
				fmt.Print("--E-")
			} else {
				if m.nodes[i][j].STE < 10 {
					fmt.Print("--", m.nodes[i][j].STE, "-")
				} else {
					fmt.Print("-", m.nodes[i][j].STE, "-")
				}
			}
		}
		fmt.Println()
	}
	fmt.Print("\n\n")
}

func readFile(path string, width int, height int) [][]int {
	dobArr := make([][]int, height)
	for i := range dobArr {
		dobArr[i] = make([]int, width)
	}
	mapFile, err := os.Open(path)
	if err != nil {
		log.Fatalln("Couldn't open the csv file", err)
	}
	buffer := csv.NewReader(bufio.NewReader(mapFile))
	for i := 0; i < height; i++ {
		line, err := buffer.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatal(err)
		}
		for j := 0; j < width; j++ {
			dobArr[i][j], err = strconv.Atoi(line[j])
		}
	}
	return dobArr
}

func MatToNode(dobArr [][]int, nExits int, width int, height int) [][]*Node {
	eNodes := make([][]*Node, len(dobArr))
	for i := range dobArr {
		eNodes[i] = make([]*Node, len(dobArr[i]))
	}
	for i := 0; i < len(dobArr); i++ {
		for j := 0; j < len(dobArr[i]); j++ {
			if dobArr[i][j] == 0 {
				eNodes[i][j] = nil
				continue
			}
			if i == 0 || j == 0 || i == len(dobArr)-1 || j == len(dobArr[i])-1 {
				eNodes[i][j] = NewNode(false, true, 1000)
			} else {
				eNodes[i][j] = NewNode(false, false, 1000)
			}
		}
	}
	for i := range eNodes {
		for j := range eNodes[i] {
			if eNodes[i][j] == nil {
				continue
			}
			if i-1 >= 0 {
				eNodes[i][j].front = eNodes[i-1][j]
			} else {
				eNodes[i][j].front = nil
			}
			if i+1 < len(eNodes) {
				eNodes[i][j].back = eNodes[i+1][j]
			} else {
				eNodes[i][j].back = nil
			}
			if j-1 >= 0 {
				eNodes[i][j].left = eNodes[i][j-1]
			} else {
				eNodes[i][j].left = nil
			}
			if j+1 < len(eNodes[i]) {
				eNodes[i][j].right = eNodes[i][j+1]
			} else {
				eNodes[i][j].right = nil
			}
		}
	}
	createExits(nExits, width, height, eNodes)
	return eNodes
}

func exitDists(ext *Node, eNodes [][]*Node) {
	q := NewQueue(10000, 0, 0)
	currentDist := 0
	ext.STE = currentDist
	q.add(ext)
	for q.curr < q.antPos {
		currentNode := q.pop()
		if currentDist < currentNode.STE {
			currentDist++
		}
		nextNodes := currentNode.getNext()
		for i := 0; i < 4; i++ {
			if nextNodes[i] == nil {
				continue
			}
			if currentDist < nextNodes[i].STE {
				nextNodes[i].STE = currentDist + 1
				nextNodes[i].nextStep = currentNode
				q.add(nextNodes[i])
			}
		}
	}
}

func createExits(nExits int, width int, height int, nodes [][]*Node) {
	if nExits > width*height-height {
		fmt.Println("Too many exits")
		os.Exit(1)
	}
	var numRand int = nExits
	for i := 0; i < nExits; i++ {
		rand.Seed(time.Now().UTC().UnixNano())
		numRand = rand.Int()
		if numRand%4 == 0 {
			numRand = rand.Intn(len(nodes[i]))
			if nodes[0][numRand] != nil {
				nodes[0][numRand].isExit = true
				exitDists(nodes[0][numRand], nodes)
			} else {
				i--
				continue
			}
		} else if numRand%4 == 1 {
			numRand = rand.Intn(len(nodes[i]))
			if nodes[len(nodes)-1][numRand] != nil {
				nodes[len(nodes)-1][numRand].isExit = true
				exitDists(nodes[len(nodes)-1][numRand], nodes)
			} else {
				i--
				continue
			}
		} else if numRand%4 == 2 {
			numRand = rand.Intn(len(nodes))
			if nodes[numRand][0] != nil {
				nodes[numRand][0].isExit = true
				exitDists(nodes[numRand][0], nodes)
			} else {
				i--
				continue
			}
		} else {
			numRand = rand.Intn(len(nodes))
			if nodes[numRand][len(nodes[i])-1] != nil {
				nodes[numRand][len(nodes[i])-1].isExit = true
				exitDists(nodes[numRand][len(nodes[i])-1], nodes)
			} else {
				i--
				continue
			}
		}
	}
}

func (m *Map) getActualNode() []*Node {
	vNod := make([]*Node, m.height*m.width)
	nNodes := 0
	for i := 0; i < m.height; i++ {
		for j := 0; j < m.width; j++ {
			if m.nodes[i][j] == nil {
				continue
			} else if m.nodes[i][j].isExit {
				continue
			} else {
				vNod[nNodes] = m.nodes[i][j]
				nNodes++
			}
		}
	}
	realNodes := make([]*Node, nNodes-1)
	for i := 0; i < len(realNodes); i++ {
		realNodes[i] = vNod[i]
	}
	return realNodes
}
