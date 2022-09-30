Andrew Wu
CSE13s
Alex Rudnick
Design hw4

In this lab, we are given:
Graphsearch.c
Graphsearch.h (do not change)
Hw4.c (do not change)
Makefile (do not change)

The purpose of this assignment is to open a text file with a number of vertices and connections between each of the vertices, then search vertices for the shortest or the longest path either using breadth first search or depth first search. Breadth first search uses a queue to keep track of vertices while Depth First search uses a stack. At the very end of the code, we need to free the memory associated with each of the searches (queue for breadth, stack for depth-first). 

In graphsearch.c:

Enqueue:
Takes a pointer with a LLpath struct and a path. It'll return the LLPath with an added path to the queue. We will implement this in the same way we did queue in class, but instead of queueing an int, we take a path. We will allocate memory to a LLPath struct and set a pointer to it’s head while iterating through the second struct.

LLPath *enqueue_path(LLPath *q, Path path) {
  // YOUR CODE HERE
	Allocate memory to LLpath called newnode
	Newpath value = path
	If q is null
		Return newpath
	Llpath pointer cur set to q
	While cur next not null
		Cur next
	Cur next = newpath
	Return q 
	
  return NULL;
}





DeQueue:
Takes a LLpath struct and stores the path in the *ret pointer, and also remove the path from the LLPath struct queue. DeQueue is also similar to the one we did in class. We will take a LLpath and a return pointer that’ll store the value we “popped” from the stack. This function will free memory allocated to the stack because it does not return a LLpath struct. 

bool dequeue_path(LLPath **q, Path *ret) {
  // YOUR CODE HERE
	If q is null
		Return false
	Ret = q val
	Freethis pointer set to q
	Q next
	Free freethis
	Return true
}

BFS takes 2 ints and a graph. It runs the “breadth first search” algorithm on a graph. We want to keep track of two lists in the form of a queue. We will use enqueue and dequeue functions for this algorithm. It takes a graph object and two ints to check for the shortest path between the ints i and j. It will explore paths that can be traversed through 1 edge, 2 edges, etc. and return the shortest one. 

Pseudocode:
Path graph_find_path_bfs(Graph *g, int i, int j) {
	Set of vertices visited
	Set of vertices to visit (both of LLint)
	Queue i
	If to_visit is not null
		Int curr
		Dequeue into curr
		If curr = j
			Free memory from llint list for to visit
Free memory from llint list for visited
			Path extend j
			Return path
		For n = 0, n< g vertices, n++
			If graph has edge and vertices visited does not have n,
				Enqueue n
				If path vertices last value in array is not current
					Path extend current
Free memory from llint list for to visit
Free memory from llint list for visited
  Path empty = {0, {0}};
  return empty;
}

DFS is similar to BFS except it uses a stack instead of a queue. This will return the longest path from i to j of graph g. For this reason, we would have to implement a stack struct. Assuming the stack struct of node stack is implemented with a top and an array, and push and pop functions work, we can implement the DFS algorithm. We also need to free memory associated with each alloc. 

Path graph_find_path_dfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.
	Set of vertices visited (llint)
	Set of vertices to visit (stack)
	push i onto stack
	If stack empty is not 0
		Int curr = pop
		If curr = j
			Free memory from stack
			Free memory from llint list for visited
			Path extend j
			Return path
		For n = 0, n< g vertices, n++
			If graph has edge and vertices visited does not have n,
				push n onto stack
				If path vertices last value in array is not current
					Path extend current
Free memory from stack
Free memory from llint list for visited
  Path empty = {0, {0}};
  return empty;
}

MAIN:
In main, we have the code to open the file and read through the txt to create the graph. In the end, however, we want to free memory for the graph and close the file.
Psuedocode:
Graph *delete to g
Int pointer to graph matrix
For each i in g->vertices
	Free gmatrix[i]
Free graph matrix
Free graph
Close file.


