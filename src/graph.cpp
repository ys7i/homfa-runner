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
  regex re(R"(^(\>?)(\d+)([^\d]*)[\s\t]+(\d+)[\s\t]+(\d+)[\s\t]*$)");
  for (auto it = lines.begin(); it != lines.end(); ++it) {
    smatch match;
    regex_match(*it, match, re);
    if (match.empty()) {
      spdlog::error("Syntax error: graph config");
      throw "Sytax error: graph config";
    }

    Graph::State state = stoi(match[2].str());
    if (match[1].str() == ">") {
      initial_state = state;
      current_state = state;
    }
    states.insert(state);
    if (match[3].str() != "") {
      labels[state] = match[3].str();
    }

    auto zero_destination = stoi(match[4].str());
    auto one_destination = stoi(match[5].str());
    transitions[state] = {zero_destination, one_destination};
  }
}

void Graph::move_next(Sigma sigma) {
  spdlog::info("read:" + to_string(int(sigma)));
  auto next_state = sigma == Sigma::ZERO ? transitions.at(current_state).first
                                         : transitions.at(current_state).second;
  current_state = next_state;
}

string Graph::output_label(Graph::State st) {
  if (labels.count(st)) {
    return labels.at(st);
  } else {
    return "";
  }
}

Graph::State Graph::get_current_state() { return current_state; }