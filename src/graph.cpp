#include "graph.hpp"
#include "spdlog/spdlog.h"
#include <iostream>
#include <istream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

Graph::Graph(vector<string> lines) { this->load_config(lines); }

void Graph::load_config(vector<string> lines) {
  regex re(
      R"(^(\>?)(\d+)([^\d]*)[\s\t]+(\d+(?:,\d+)*)[\s\t]+(\d+(?:,\d+)*)[\s\t]*$)");
  for (auto it = lines.begin(); it != lines.end(); ++it) {
    smatch match;
    regex_match(*it, match, re);
    if (match.empty()) {
      spdlog::error("Syntax error: graph config");
      throw "Sytax error: graph config";
    }

    Graph::State state = stoi(match[2].str());
    if (match[1].str() == ">") {
      initial_states.insert(state);
      current_states.insert(state);
    }
    states.insert(state);
    if (match[3].str() != "") {
      labels[state] = match[3].str();
    }

    auto zero_destinations = this->split_destinations(match[4].str());
    auto one_destinations = this->split_destinations(match[5].str());
    transitions[state] = {zero_destinations, one_destinations};
  }
}

void Graph::process_offline(vector<Sigma> input) {
  for (auto it = input.begin(); it != input.end(); ++it) {
    auto running_state = this->move_next(*it);
    if (running_state == RunningState::Terminated) {
      break;
    }
  }
};

Graph::States Graph::split_destinations(string line) {
  stringstream ss{line};
  string buf;
  unordered_set<Graph::State> destinations;
  while (getline(ss, buf, ',')) {
    destinations.insert(stoi(buf));
  }
  return destinations;
}

RunningState Graph::move_next(Sigma sigma) {
  spdlog::info("read:" + to_string(int(sigma)));
  unordered_set<Graph::State> next_states;
  for (auto st : current_states) {
    auto next_states_subset = sigma == Sigma::ZERO ? transitions.at(st).first
                                                   : transitions.at(st).second;
    next_states.insert(next_states_subset.begin(), next_states_subset.end());
  }
  for (auto st : next_states) {
    if (labels.count(st)) {
      spdlog::info("output - state:" + to_string(st) + " - " + labels.at(st));
      return RunningState::Terminated;
    }
  }
  spdlog::info("continue");
  current_states = next_states;
  return RunningState::Running;
}