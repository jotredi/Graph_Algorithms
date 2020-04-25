// ShortestPath class
#include <queue>
#include <limits>

template <class T>
class ShortestPath{
public:
  //Constructor
  ShortestPath(const Graph<T> G): G(G){}
  //Destructor
  ~ShortestPath(){}

  //Functions of ShortestPath
  std::list<unsigned> path(unsigned u, unsigned w);
  T path_size(){return final_size;}

private:
  Graph<T> G;
  std::vector<T> dist;
  std::vector<unsigned> prev;
  T final_size;
};

//ShortestPath Algorithm
template <class T>
std::list<unsigned> ShortestPath<T>::path(unsigned u, unsigned w){
  // u source, w destination
  unsigned s = u;

  // Initialization
  dist.reserve(G.V());
  prev.reserve(G.V());
  dist[u] = 0;

  //Sequence of vertices that represents the shortest path
  std::list<unsigned> sequence;

  //Definition of priority queue wich stores {distance, node}
  std::priority_queue< std::pair<T, unsigned>,
  std::vector <std::pair<T, unsigned>>,
  std::greater<std::pair<T, unsigned>> > Q;

  for (unsigned v = 0; v < G.V(); ++v){
    if (v != u){
      dist[v] = std::numeric_limits<T>::infinity(); //Set all as non visited
    }
  }

  Q.push(std::make_pair(dist[u], u)); //Only source in queue

  //main loop (while the queue is not empty):
  while (!Q.empty())
  {
    //Extract min and remove it from queue
    u = Q.top().second;
    Q.pop();

    //For every neighbor v in u
    for (unsigned v : G.neighbors(u)){
      // Node distance
      T alt = dist[u] + G.get_edge_value(u,v);

      if (alt < dist[v]){
        // Update distance
        dist[v]=alt;
        prev[v]=u;
        Q.push(std::make_pair(alt, v));
      }
    }
  }

  // Check if w (destination) is reached
  if(dist[w]==std::numeric_limits<T>::infinity()){
    // If w not visited
    final_size = 0;
    std::cout << "No path between " << s << " and " << w << std::endl;
  }
  else{
    //This loop takes the path backwards
    //until the source(dist=0)
    unsigned n = w;
    while(dist[n])
    {
      sequence.push_back(n);
      n = prev[n];
    }
    sequence.push_back(n);
    sequence.reverse(); //Reverse the path(from u to w)

    final_size = dist[w];
  }

  return sequence;
}
