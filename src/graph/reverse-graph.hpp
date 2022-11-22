#ifndef YSHR_REVERSE_GRAPH
#define YSHR_REVERSE_GRAPH

#include "graph.hpp"

class ReverseGraph : public Graph {
protected:
  State current_state;

public:
  ReverseGraph(vector<string> lines);
};

#endif