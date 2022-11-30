#include "reverse-graph.hpp"
#include "spdlog/spdlog.h"
#include "tfhe-util.hpp"
#include "utils.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

struct offline_case {
  vector<string> config;
  string input;
  string label;
};

struct offline_case offline_cases[] = {
    {{">0 0 1", "1 2 3", "2reject 2 2", "3accept 3 3"}, "1010", "reject"},
    {{">0 1 3", "1 2 0", "2reject 2 2", "3accept 3 3"}, "010010", "reject"},
    {{">0 1 1", "1 3 0", "2 2 3", "3 4 5", "4four 4 4", "5five 5 5"},
     "0101101101001",
     "five"}};

TEST(offline, table) {
  for (offline_case &elm : offline_cases) {
    const SecretKey &skey = SecretKey();
    const BKey &bkey = BKey(skey);
    auto graph = new ReverseGraph(elm.config, skey);
    auto sigma_vector = split_to_zero_one(elm.input);
    for (auto it = sigma_vector.rbegin(); it != sigma_vector.rend(); ++it) {
      auto enc_input = encrypt_to_TRGSWLvl1FFT(*it, skey);
      graph->run(enc_input);
    }
    auto results = graph->output_result();
    auto value = graph->output_label(results, skey);
    spdlog::info("value: " + value);
    EXPECT_EQ(value, elm.label);
  }
}
