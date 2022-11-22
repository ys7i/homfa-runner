#include "CLI/CLI.hpp"
#include "forward-graph.hpp"
#include "reverse-graph.hpp"
#include "spdlog/spdlog.h"
#include "tfhe-util.hpp"
#include "utils.hpp"
#include <iostream>

class GraphTypeValidator : public CLI::Validator {
public:
  GraphTypeValidator() {
    name_ = "GRAPH_TYPE";
    func_ = [](const std::string &str) {
      if (str != "plain" && str != "offline")
        return std::string("graphtype is invalid");
      else
        return std::string();
    };
  }
};
const static GraphTypeValidator graph_type_validator;

int process_plain(vector<string> graph_config, vector<Sigma> sigma_vector) {
  auto graph = new ForwardGraph(graph_config);
  for (auto it = sigma_vector.begin(); it != sigma_vector.end(); ++it) {
    graph->move_next(*it);
    ForwardGraph::State current_state = graph->get_current_state();
    string label = graph->output_label(current_state);
    spdlog::info("state: " + to_string(current_state));
    if (label != "") {
      spdlog::info("label: " + label);
    } else {
      spdlog::info("label: nothing continue");
    }
  }
  return 0;
}

int process_offline(vector<string> graph_config, vector<Sigma> sigma_vector) {
  auto skey = get_skey();
  auto graph = new ReverseGraph(graph_config);
  for (auto it = sigma_vector.begin(); it != sigma_vector.end(); ++it) {
    graph->move_next(*it);
    ForwardGraph::State current_state = graph->get_current_state();
    string label = graph->output_label(current_state);
    spdlog::info("state: " + to_string(current_state));
    if (label != "") {
      spdlog::info("label: " + label);
    } else {
      spdlog::info("label: nothing continue");
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  CLI::App app{"App description"};
  spdlog::set_level(spdlog::level::debug);

  std::string graph_type;
  app.add_option("--type", graph_type, "Require an graph type")
      ->required()
      ->check(graph_type_validator);

  std::string input_file;
  app.add_option("--input-file", input_file, "Require an input file")
      ->required()
      ->check(CLI::ExistingFile);

  std::string graph_file;
  app.add_option("--graph-file", graph_file, "Require an graph file")
      ->required()
      ->check(CLI::ExistingFile);

  CLI11_PARSE(app, argc, argv);
  auto input = read_file(input_file);
  auto graph_config = read_file(graph_file);
  auto sigma_vector = split_to_zero_one(input.at(0));
  if (graph_type == "plain") {
    return process_plain(graph_config, sigma_vector);
  } else if (graph_type == "offline") {
    return process_offline(graph_config, sigma_vector);
  } else {
    throw "graph type error";
  }
}
