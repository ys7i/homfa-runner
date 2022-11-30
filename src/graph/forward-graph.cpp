#include "spdlog/spdlog.h"
#include <iostream>
#include <istream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "forward-graph.hpp"

using namespace std;

ForwardGraph::ForwardGraph(vector<string> lines) : Graph(lines) {
  current_state = initial_state;
}

void ForwardGraph::move_next(Sigma sigma) {
  spdlog::info("read:" + to_string(int(sigma)));
  auto next_state = sigma == Sigma::ZERO ? transitions.at(current_state).first
                                         : transitions.at(current_state).second;
  current_state = next_state;
}

ForwardGraph::State ForwardGraph::get_current_state() { return current_state; }