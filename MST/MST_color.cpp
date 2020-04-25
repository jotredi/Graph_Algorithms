/***********************************************
Minimum Spanning Tree algorithm with colors
--------------------------------------------
I implement Prim's algorithm with the constrain
that each edge has a color and the program
computes a MST with a selected color.
***********************************************/
#include <iostream>

#include "Graph.hpp"
#include "Prim.hpp"

using namespace std;

//Function that returns a random color (Red, Green or Blue)
inline char get_random_color(){
  int n = rand()%3 + 1; //Number between 1 and 3
  switch (n) {
    case 1: return 'R';
    case 2: return 'G';
    case 3: return 'B';
  }
}

int main(){

  //Random seed
  srand(time(NULL));

  // Data file
  std::string file = "data.txt";

  Graph<int> G(file);
  unsigned c;

  // Set colors
  Graph<char> C(G.V(), '0');

  ifstream data_file(file);
  istream_iterator<int> start(data_file), end;
  vector<int> data(start, end);
  data.erase(data.begin());

  unsigned i, j, pos = 1;
  for (auto d : data){
    switch (pos) {
      case 1: i = d; pos++; break;
      case 2: j = d; pos++; break;
      case 3: C.set_edge_value(i,j,get_random_color()); pos=1; break;
    }
  }

  cout << "\nOriginal Graph nodes: \n";
  G.print_Graph();
  cout << "\nColors of each node: \n";
  C.print_Graph();

  Prim<int> tree;

  cout << "\nSelect a method for computing the tree:";
  cout << "\n0: MST without colors";
  cout << "\n1: Red MST";
  cout << "\n2: Green MST";
  cout << "\n3: Blue MST\n";
  do{
    cout << "\nInsert number: ";
    cin >> c;
    switch (c) {
      case 0: cout << "\nCost = " << tree.MST(G) << endl;  break;
      case 1: cout << "\nCost = " << tree.MST_color(G,C,'R') << endl; break;
      case 2: cout << "\nCost = " << tree.MST_color(G,C,'G') << endl; break;
      case 3: cout << "\nCost = " << tree.MST_color(G,C,'B') << endl; break;
      default:cout << "\nError. Please enter a correct number";
    }
  }while(c!=0 && c!=1 && c!=2 && c!=3);

  //Uncomment to print final Tree
  cout << "\nFinal tree nodes: \n";
  tree.get_tree().print_Graph();
  cout << "\nFinal color map: \n";
  tree.get_color_tree().print_Graph();

  return 0;
}
