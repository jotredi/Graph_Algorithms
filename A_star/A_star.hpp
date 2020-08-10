#ifndef A_STAR_HPP
#define A_STAR_HPP

#include "Graph.hpp"

using std::vector;

class A_star{
public:
  // Constructor & Destructor
  A_star();
  virtual ~A_star();

  // Search algorithm
  double search(Graph<double> &graph, vector<vector<double>> &nodes,
                unsigned u, unsigned w);

  // Path
  vector<unsigned> get_path(unsigned start, unsigned goal);

  // Heuristic
  double heuristic(double x, double y, vector<double> goal);

  // Node struct
  struct node{
    unsigned n;
    double g;
    double f;
  };

private:
  vector<unsigned> came_from;
};

#include "A_star.cpp"

#endif
