// Graph class
#include <list>
#include <string>
#include <fstream>
#include <iterator>

#include "Matrix.hpp"

template <class T>
class Graph{
public:

  // Constructors
  Graph(unsigned, T = 0);
  Graph(unsigned, unsigned, std::vector<T>);
  Graph(std::string);
  Graph(void){}
  //Destructor
  ~Graph();

  // Resize Graph nodes
  void resize(unsigned, T = 0);

  // Graph Methods
  unsigned V();
  unsigned E();
  bool adjacent(const unsigned &, const unsigned &);
  std::vector<unsigned> neighbors(const unsigned &);
  void add(const unsigned &, const unsigned &, std::string = "undirected");
  void del(const unsigned &, const unsigned &);
  unsigned get_node_value(const unsigned &);
  void set_node_value(const unsigned &, const unsigned &);
  T get_edge_value(const unsigned &, const unsigned &);
  void set_edge_value(const unsigned &, const unsigned &, T, std::string = "undirected");

  void print_Graph();

private:
  matrix<T> G;
  unsigned edges = 0;
  unsigned nodes = 0;
};

//Constructors
template <class T>
Graph<T>::Graph(unsigned n, T initial){
  // Graph Initialization
  G.resize(n,n,initial);
  nodes=n;
}
template <class T>
Graph<T>::Graph(unsigned n, unsigned density, std::vector<T> dist_range){
  G.resize(n,n,0);
  nodes=n;
  // Random graph initialization
  for(unsigned i = 0; i < nodes; ++i){
    for(unsigned j = 0; j < nodes; ++j){
      if(i==j) continue;
      else if (rand()%100 < density){
        G(i,j) = G(j,i) = dist_range[rand()%dist_range.size()];
        ++edges;
      }
    }
  }
}
template <class T>
Graph<T>::Graph(std::string file){
  // Read file
  std::ifstream data_file(file);
  std::istream_iterator<T> start(data_file), end;
  std::vector<T> data(start, end);

  // Nodes
  nodes=data[0];
  G.resize(nodes, nodes, 0);
  data.erase(data.begin());

  unsigned i, j, pos = 1;
  for (auto d : data){
    switch (pos) {
      case 1: i = d; ++pos; break;
      case 2: j = d; ++pos; break;
      case 3: set_edge_value(i,j,d); pos=1; break;
    }
  }
}
//Destructor
template <class T>
Graph<T>::~Graph(){}

//Resize
template <class T>
void Graph<T>::resize(unsigned n, T initial){
  G.resize(n,n,initial);
  nodes=n;
}

// Graph Methods
template <class T>
unsigned Graph<T>::V(){return nodes;}
template <class T>
unsigned Graph<T>::E(){return edges;}

template <class T>
bool Graph<T>::adjacent(const unsigned &x, const unsigned &y){
  if (G(x,y))  return true;
  else return false;
}

template <class T>
std::vector<unsigned> Graph<T>::neighbors(const unsigned &x){
  std::vector<unsigned> y;
  for (unsigned i = 0; i < nodes; ++i)
  {
    if (G(x,i)) y.push_back(i);
  }
  return y;
}

template <class T>
void Graph<T>::add(const unsigned &x, const unsigned &y, std::string direction){
  if (G(x,y)==0){
    // Directed graph
    if (direction == "directed"){
      G(x,y) = 1;
    }
    // Undirected graph
    else{
      G(x,y) = G(y,x) = 1;
    }
  }
}

template <class T>
void Graph<T>::del(const unsigned &x, const unsigned &y){
  if (G(x,y))  G(x,y)=G(y,x)=0;
}

template <class T>
unsigned Graph<T>::get_node_value(const unsigned &x){
  unsigned degree = 0;
  for (unsigned i = 0; i < nodes; ++i)
  {
    if (G(x,i)) ++degree;
  }
  return degree;
}

template <class T>
void Graph<T>::set_node_value(const unsigned &x, const unsigned &a){
  if (get_node_value(x)<a){
    do{
      add(x, rand()%nodes);
    }while (get_node_value(x)<a);
  }
  else if (get_node_value(x)>a){
    do{
      del(x, rand()%nodes);
    }while (get_node_value(x)>a);
  }
  else
  {
    std::cout << "Node value is already " << a << std::endl;
  }
}

template <class T>
T Graph<T>::get_edge_value(const unsigned &x, const unsigned &y){return G(x,y);}

template <class T>
void Graph<T>::set_edge_value(const unsigned &x, const unsigned &y, T v, std::string direction){
  if (direction == "directed"){
    G(x,y) = v;
  }
  else{
    G(x,y) = G(y,x) = v;
  }
}

template <class T>
void Graph<T>::print_Graph(){
  std::cout << "\nGraph matrix: \n";
  G.print();
}
