/*************************************************
Minimum Spanning Tree algorithm
-------------------------------
I implement Prim's algorithm with the use of a
min priority queue to always take the next edge
with least cost.

The graph class uses connectivity matrices
(Matrix class).

I use the graph class to represent the Graph
and the final tree.
************************************************/
#include <iostream>

#include "Graph.hpp"
#include "Prim.hpp"

using namespace std;

int main(){

  // Read Graph from file "data.txt"
  Graph<int> G("data.txt");

  cout << "\nOriginal Graph: " << endl;
  G.print_Graph();

  // Prim class
  Prim<int> tree;

  cout << "\nCost of MST = " << tree.MST(G) << endl;

  // Final Tree
  cout << "\nFinal tree: \n";
  tree.get_tree().print_Graph();

  return 0;
}
