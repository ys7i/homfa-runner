#ifndef YSHR_GRAPH
#define YSHR_GRAPH

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

enum Sigma {
  ZERO = 0,
  ONE = 1,
};

class Graph {
public:
  using State = int;
  using Transitions = unordered_map<State, pair<State, State>>;
  using Labels = unordered_map<State, string>;

private:
  Transitions transitions;
  Labels labels;
  State initial_state;
  unordered_set<State> states;
  State current_state;

public:
  Graph(vector<string> lines);
  void process_offline(vector<Sigma> input);

private:
  void load_config(vector<string> lines);
  void move_next(Sigma sigma);
};

#endif