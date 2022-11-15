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
  graph->process_offline(sigma_vector);
  return 0;
}