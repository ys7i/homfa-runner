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

enum RunningState {
  Running = 0,
  Terminated = 1,
};

class Graph {
public:
  using State = int;
  using States = unordered_set<int>;
  using Transitions = unordered_map<State, pair<States, States>>;
  using Labels = unordered_map<State, string>;

private:
  Transitions transitions;
  Labels labels;
  unordered_set<State> initial_states;
  unordered_set<State> states;
  unordered_set<State> current_states;

public:
  Graph(vector<string> lines);
  void process_offline(vector<Sigma> input);

private:
  void load_config(vector<string> lines);
  States split_destinations(string line);
  RunningState move_next(Sigma sigma);
};

#endif