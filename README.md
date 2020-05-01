# Graph_Algorithms
Implementation of algorithms on Graph data structures in C++

## Table of contents
* [Dijkstra's Algorithm](#dijkstras-algorithm)
* [Minimum Spanning Tree](#minimum-spanning-tree)

## Dijkstra's Algorithm
Implementation of a Monte Carlo simulation that calculates the average shortest path in a graph.

### Description
The program includes a Graph class for representing the graph
and another class for implementing the Dijkstra's algorithm.

Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph, which may represent, for example, road networks.

### Details
The graph is an undirected graph generated randomly. The edges of the graph have a positive cost and represent the distance. 
The initialization of the graph has edge density as a parameter and distance range as a parameter. So a graph whose density is 0.1 would have 10% of its edges picked at random and its edge distance would be selected at random from the distance 
range.

The program computes an average path length for a randomly generated graph. Concretely, it uses a density of 25% on a graph of 50 nodes with a distance range from 1.0 to 10.0, but this can be modified.

To get an average path length, 49 paths are computed:

1 to 2, 1 to 3, 1 to 4, …, 1 to 50.

### Graph Class
The Graph is represented using connectivity matrices but it could also be represented using edge lists. Here are the Graph methods:

* `V()`: return the number of vertices in the graph.
* `E()`: return the number of edges in the graph.
* `adjacent(x, y)`: test whether there is an edge from node x to node y.
* `neighbors(x)`: list all nodes y such that there is an edge from x to y.
* `add(x, y)`: add to G the edge from x to y, if it is not there.
* `delete(x, y)`: remove the edge from x to y, if it is there.
* `get_node_value(x)`: return the value associated with the node x (number of nodes connected to x).
* `set_node_value(x, a)`: set the value associated with the node x to a (a nodes connected to x).
* `get_edge_value(x, y)`: return the value associated to the edge (x,y).
* `set_edge_value(x, y, v)`: set the value associated to the edge (x,y) to v.
* `print_Graph()`: print the graph on the screen.

### ShortestPath Class
This class contains the implementation of the Dijkstra's Algorithm. It makes use of a min priority queue to always have access to the vertex with the next shortest link in the shortest path calculation at the top of the queue.

* `path(u, w)`: find shortest path between u-w and return the sequence of vertices representing shorest path u-v1-v2-…-vn-w.
* `path_size()`: return the path cost associated with the shortest path.

## Minimum Spanning Tree
Implementation of a minimum spanning tree (MST) algorithm for a weighted undirected graph. Concretely, I make use of the Prim's Algorithm, which is faster in dense Graphs.

### Description
A spanning tree for a Graph `G` is a tree that reaches all the nodes of the graph. The cost for such a spanning tree is the sum of all the edge costs (weights) in the spanning tree’s edge set. Over all possible spanning trees, the MST is the one with the least total cost (it may not be unique).

### Details
The program reads the graph from a file which contains 20 nodes with their respective edge values.

The `Prim` Class computes the Prim's Algorithm and returns the total cost as well as the final Tree (edges).

### Extension to the problem (MST with colors)
An interesting and more challenging extension to the MST problem is to give each edge one of three colors (eg. Red, Green or Blue). This is to consider that a road may be a local street or a highway or a turnpike. Many route finding algorithms find a least costly path constrained by what type of road to take.

To implement this, we should compute the MST where the edge colors are a constraint, eg. all edges must be green.

The function `MST_color()` inside the Prim class computes the Prim's Algorithm constrained by a selected color.

## Sources
* These problems are proposed by the course [C++ For C Programmers](https://www.coursera.org/learn/c-plus-plus-a?) from the University of California, Santa Cruz.
* https://en.wikipedia.org/wiki/Dijkstra's_algorithm
* https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
* https://en.wikipedia.org/wiki/Prim%27s_algorithm
* https://en.wikipedia.org/wiki/Minimum_spanning_tree
* [Matrix Class](https://github.com/jotredi/Matrix_Class)
