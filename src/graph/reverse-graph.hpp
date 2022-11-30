#ifndef YSHR_REVERSE_GRAPH
#define YSHR_REVERSE_GRAPH

#include "graph.hpp"
#include "string"
#include "tfhe-util.hpp"

class ReverseGraph : public Graph {
protected:
  State current_state;
  int bit_num;
  TRLWELvl1 trlwelvl1_zero;
  TRLWELvl1 trlwelvl1_one;
  unordered_map<string, vector<TRLWELvl1>> trlwe_map;
  std::vector<TRLWELvl1> weight;
  vector<string> label_vector;

public:
  ReverseGraph(vector<string> lines, const SecretKey &skey);
  void run(const TRGSWLvl1FFT &input);
  State get_next_state(State q, Sigma sigma);
  vector<TLWELvl1> output_result();
  // 本来はグラフ内関数でないべき
  string output_label(vector<TLWELvl1> results, const SecretKey &skey);
};

#endif