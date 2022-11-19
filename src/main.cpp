#include "CLI/CLI.hpp"
#include "graph.hpp"
#include "spdlog/spdlog.h"
#include "utils.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  CLI::App app{"App description"};
  spdlog::set_level(spdlog::level::debug);
  // Define options
  int p = 0;

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
  auto graph = new Graph(graph_config);
  for (auto it = sigma_vector.begin(); it != sigma_vector.end(); ++it) {
    graph->move_next(*it);
    Graph::State current_state = graph->get_current_state();
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