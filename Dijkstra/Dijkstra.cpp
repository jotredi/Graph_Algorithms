/**************************************
Dijkstra's Shortest Path Algorithm
----------------------------------
This program computes the Dijkstra's
Shortest Path algorithm with the use
of a Graph class for representing
the graph, and a ShortestPath
class for computing the Shortest Path
algorithm.

Connectivity matrices are used to
represent the graphs (with Matrix class)
***************************************/
#include <iostream>

#include "Graph.hpp"
#include "ShortestPath.hpp"

using namespace std;

//Function to print out the path
inline void print_path(list<auto> path){
  for (auto i : path){
    (i==path.back()) ? cout << i <<"\n" : cout << i << " -> ";
  }
}

int main(){
  //Random seed
  srand(time(NULL));

  //Create distance range([1.0, 10.0])
  //91 elements between 1.0 and 10.0
  //taking a 0.1 step
  vector<double> distance(91);
  double d = 1.0;
  for (unsigned i = 0; i < distance.size(); ++i){
    distance[i] = d;
    d += 0.1;
  }

  unsigned density = 25; //Density (0 - 100)%
  unsigned nodes = 50; // Number of nodes
  Graph<double> G (nodes, density, distance);
  ShortestPath<double> path (G);

  //Uncomment to print the graph(matrix)
  //G.print_Graph();
  cout << "\n";

  //Compute of 49 paths
  double sum = 0;
  unsigned n_paths = 0;
  double avg_path_length = 0;

  for (unsigned i = 1; i<G.V(); ++i)
  {
    cout << "Path between nodes 0 and " << i << ":\n";
    print_path(path.path(0,i));

    //Add path size to the average calculation
    //if exists a path:
    if (path.path_size()){
      sum += path.path_size();
      ++n_paths;
    }
  }

  if(n_paths) avg_path_length = sum / n_paths;

  cout << "\nAverage path length = " << avg_path_length <<endl;

  return 0;
}
