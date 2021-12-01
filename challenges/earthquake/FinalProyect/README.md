
### Earthquake Simulator Architecture

This project consist in the implementation of an multithreaded earquake simulator; It simulates a map of a building with a n number of people there, it create random exits in every run and creates a timer when people start running to the exits, afte the timing is done it calculates how many people made it 

## main.go
This file handles the input and calls the simulation
 
## Queue.go
A personalized queue for this problem, used in the map implementation od the people running

## Node.go
A node object that is later used in the creation of the map

## Person.go
This class defines the person object

## map.go
Map consist in taking a layout from a csv and creating a map consisting of nodes

## Simulation.go
This part is in charge of create a n number of persons, handling the simulation and initializing the persons in their initial spot

## Final notes
Just in case its important, running the proyect on gitpod causes some trouble so I recommend runnin on local


# video
https://youtu.be/yusYfTftj1g