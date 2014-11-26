Travelling Salesman Problem
===========================

C programming to solve TSP using backtracking

_The travelling salesman problem (TSP) is an NP-hard problem in combinatorial optimization studied in operations research and theoretical computer science._ [Wikipedia](http://en.wikipedia.org/wiki/Travelling_salesman_problem)

---

##The algorithm

An decision problem using the backtracking technique to solve the best path. The input problem must have the same distance between city A and B in both directions. The graph of the cities must be only numbers. 

##The code

The algorithm decides whether there is a path smaller (or equal) than the argument passed as parameter.

Compile \*.c files and run the algorithm with:


`./a.out <input> <maxLength>`


##Input format:

	<number of vertices>
	<number of edges>
	<origin city> <destination city> <weight of the edge>

For example, a valid input:

	4
	5
	0 1 10
	0 3 8
	0 2 8
	1 2 5
	2 3 4
