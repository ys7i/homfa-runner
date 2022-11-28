#ifndef YSHR_REVERSE_GRAPH
#define YSHR_REVERSE_GRAPH

#include "graph.hpp"
#include "tfhe-util.hpp"

class ReverseGraph : public Graph {
protected:
  State current_state;
  int bit_num;
  TRLWELvl1 trlwelvl1_zero;
  TRLWELvl1 trlwelvl1_one;
  unordered_map<string, vector<TRLWELvl1>> trlwe_map;

public:
  ReverseGraph(vector<string> lines, const SecretKey &skey);

private:
};

#endif