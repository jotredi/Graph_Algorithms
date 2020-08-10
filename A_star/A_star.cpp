#ifndef A_STAR_CPP
#define A_STAR_CPP

#include <queue>
#include <algorithm>
#include <limits>

#include "A_star.hpp"

// Compare function for priority queue
// It returns minimum f value (cost)
struct compare{
  bool operator()(A_star::node const& n1, A_star::node const& n2)
  {
    return n1.f > n2.f;
  }
};

// Constructor
A_star::A_star(){}

// Destructor
A_star::~A_star(){};

// A star algorithm
double A_star::search(Graph<double> &graph, vector<vector<double>> &nodes,
                      unsigned u, unsigned w){
  // Number of nodes
  unsigned N = nodes.size();

  // Define init & goal nodes
  vector<double> init = nodes[u];
  vector<double> goal = nodes[w];

  // dist (for keeping track of g values)
  // Initialized with infinity (not visited)
  vector<double> dist (N, std::numeric_limits<double>::infinity());

  // Previous node
  came_from.resize(N);

  // Initialize first node
  node start;
  start.n = u;
  start.g = 0;
  start.f = heuristic(init[0], init[1], goal);

  // Set initial position as visited
  dist[u] = 0;
  // Set came_from
  came_from[u] = u;

  // Priority queue (open set)
  std::priority_queue< node, vector<node>, compare > Q;
  Q.push(start);

  while(!Q.empty()){
    // Take element with lowest f
    node current = Q.top();
    Q.pop();

    unsigned current_node = current.n;
    double g = current.g;

    // if goal is reached
    if (current_node == w){
      std::cout << "Found a path to the goal" << std::endl;
      // return final cost
      return g;
    }

    // for next nodes
    for(const unsigned &n : graph.neighbors(current_node)){
      // Get next node position
      double x2 = nodes[n][0];
      double y2 = nodes[n][1];

      // g cost
      double g2 = g + graph.get_edge_value(current_node, n);

      // if not visited or lower cost
      if(g2 < dist[n]){
        // f cost
        double f2 = g2 + heuristic(x2,y2,goal);

        // next node
        node next;
        next.n = n;
        next.g = g2;
        next.f = f2;
        // add queue
        Q.push(next);

        // Update distance
        dist[n] = g2;
        // Set prev node
        came_from[n] = current_node;
      }
    }
  }

  std::cout << "No path found." << std::endl;
  return 0;
}

// Heuristic
double A_star::heuristic(double x, double y, vector<double> goal){
  // Euclidean distance from current position (x,y) to the goal
  return sqrt(pow(x-goal[0], 2) + pow(y-goal[1],2));
}

// Get final path
vector<unsigned> A_star::get_path(unsigned start, unsigned goal){
  vector<unsigned> path;

  path.push_back(goal);

  unsigned current = came_from[goal];

  // Go back until start
  while(current != start){
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());

  return path;
}

#endif
