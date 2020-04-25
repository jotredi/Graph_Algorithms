// Prim Class
#include <queue>
#include <tuple>

//Function that finds n in a vector v
template <typename T>
inline bool find(std::vector<T> &v, T &n){
  for (T k : v){
    if (k == n)  return true;
  }
  return false;
}

template <class T>
class Prim{
public:
  //Constructor & Destructor
  Prim(){}
  ~Prim(){}

  //MST algorithm that returns final cost
  T MST(Graph<T> &G);

  //MST with colors
  T MST_color(Graph<T> &G, Graph<char> &C, char color);

  //Functions that return the final tree & color tree
  Graph<T> get_tree(){return Tree;}
  Graph<char> get_color_tree(){return ColorTree;}

private:
  Graph<T> Tree;
  Graph<char> ColorTree;
  std::vector<unsigned> T_nodes;
  T Cost = 0;
};

// MST algorithm with no colors (no constrains)
template <class T>
T Prim<T>::MST(Graph<T> &G){
  // New tree
  Tree.resize(G.V());

  //Vector of nodes in the tree
  T_nodes.reserve(G.V());

  //PQ Definition wich stores {edge value, i, j}
  std::priority_queue< std::tuple<T, unsigned, unsigned>,
  std::vector <std::tuple<T, unsigned, unsigned>>,
  std::greater<std::tuple<T, unsigned, unsigned>> > Q;

  //First node of the tree (0)
  T_nodes.push_back(0);

  //Get edges from first node
  for (unsigned j : G.neighbors(0)){
    Q.push(std::make_tuple(G.get_edge_value(0,j), 0, j));
  }

  //Main loop
  while(!Q.empty()){

    unsigned i = std::get<1>(Q.top()); //Actual node
    unsigned j = std::get<2>(Q.top()); //Next node
    T        d = std::get<0>(Q.top()); //Edge value

    //If next node is not in the Tree:
    if (!find(T_nodes, j)){
      T_nodes.push_back(j);

      Cost += d; //Update the cost
      Tree.set_edge_value(i, j, d); //Add to the tree

      Q.pop();

      //Get new edges
      for (unsigned n : G.neighbors(j)){
        if (!find(T_nodes, n)){
          Q.push(std::make_tuple(G.get_edge_value(j,n), j, n));
        }
      }
    }
    else{Q.pop();}
  }

  return Cost;
}

//MST with colors
template <class T>
T Prim<T>::MST_color(Graph<T> &G, Graph<char> &C, char color){
  // New tree
  Tree.resize(G.V());
  ColorTree.resize(C.V(), '0');

  //Vector of nodes in the tree
  T_nodes.reserve(G.V());

  //PQ Definition wich stores {edge value, i, j}
  std::priority_queue< std::tuple<T, unsigned, unsigned>,
  std::vector <std::tuple<T, unsigned, unsigned>>,
  std::greater<std::tuple<T, unsigned, unsigned>> > Q;

  //First node of the tree (0)
  T_nodes.push_back(0);

  //Get edges from first node
  for (unsigned j : G.neighbors(0)){
    if (C.get_edge_value(0,j)==color){
      Q.push(std::make_tuple(G.get_edge_value(0,j), 0, j));
    }
  }

  //Main loop
  while(!Q.empty()){

    unsigned i = std::get<1>(Q.top()); //Actual node
    unsigned j = std::get<2>(Q.top()); //Next node
    T        d = std::get<0>(Q.top()); //Edge value

    //If next node is not in the Tree:
    if (!find(T_nodes, j)){
      T_nodes.push_back(j);

      Cost += d; //Update the cost

      //Add edge value with its color to the tree:
      Tree.set_edge_value(i, j, d);
      ColorTree.set_edge_value(i, j, color);

      Q.pop();

      //Get new edges
      for (unsigned n : G.neighbors(j)){
        if (!find(T_nodes, n) && C.get_edge_value(j,n)==color)
        {
          Q.push(std::make_tuple(G.get_edge_value(j,n), j, n));
        }
      }
    }
    else{Q.pop();}
  }

  return Cost;
}
