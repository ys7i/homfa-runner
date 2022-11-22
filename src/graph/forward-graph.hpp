#ifndef YSHR_FORWARD_GRAPH
#define YSHR_FORWARD_GRAPH

#include "graph.hpp"

class ForwardGraph : public Graph {
protected:
  State current_state;

public:
  ForwardGraph(vector<string> lines);
  void process_offline(vector<Sigma> input);
  void move_next(Sigma sigma);
  State get_current_state();
};

#endif