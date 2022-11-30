#ifndef YSHR_UTIL
#define YSHR_UTIL

#include "graph.hpp"
#include <string>
#include <vector>

std::vector<std::string> read_file(const std::string file_name);
std::vector<Sigma> split_to_zero_one(string input);

#endif