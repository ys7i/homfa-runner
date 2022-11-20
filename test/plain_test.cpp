#include "graph.hpp"
#include "utils.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

struct test_case {
  vector<string> config;
  string input;
  vector<int> traces;
};

struct test_case cases[] = {
    {{">0 0 1", "1 2 3", "2reject 2 2", "3accept 3 3"},
     "1010",
     {0, 1, 2, 2, 2}},
    {{">0 1 3", "1 2 0", "2 3 1", "3 2 0"}, "110010", {0, 3, 0, 1, 2, 1, 2}}};

TEST(plain, table) {
  for (test_case &elm : cases) {
    auto graph = new Graph(elm.config);
    auto input = split_to_zero_one(elm.input);
    EXPECT_EQ(graph->get_current_state(), *(elm.traces.begin()));
    for (int index = 0; index < input.size(); ++index) {
      graph->move_next(input.at(index));
      EXPECT_EQ(graph->get_current_state(), elm.traces.at(index + 1));
    }
  }
}
