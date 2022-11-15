#ifndef YSHR_FILE_READER
#define YSHR_FILE_READER

#include "graph.hpp"
#include "spdlog/spdlog.h"
#include <iostream>
#include <string>
std::vector<std::string> read_file(const std::string file_name) {
  std::ifstream ifs(file_name);
  std::string line;
  std::vector<std::string> whole_lines;

  if (ifs.fail()) {
    spdlog::error("couldn't load file at {}", file_name);
  }

  while (getline(ifs, line)) {
    whole_lines.push_back(line);
  }
  return whole_lines;
}

std::vector<Sigma> split_to_zero_one(string input) {
  std::vector<Sigma> sigma_vector;
  for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
    if ((*it) == '0') {
      sigma_vector.push_back(Sigma::ZERO);
    } else if ((*it) == '1') {
      sigma_vector.push_back(Sigma::ONE);
    } else {
      spdlog::error("error");
      throw "Syntax error: input";
    }
  }
  return sigma_vector;
}

#endif