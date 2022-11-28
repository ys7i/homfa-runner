#include "reverse-graph.hpp"
#include "spdlog/spdlog.h"
#include "tfhe-util.hpp"
#include <cmath>
#include <set>
#include <string>
#include <vector>

using namespace std;

ReverseGraph::ReverseGraph(vector<string> lines, const SecretKey &skey)
    : Graph(lines), trlwelvl1_zero(trivial_TRLWELvl1(0)),
      trlwelvl1_one(trivial_TRLWELvl1(1)) {
  set<string> label_set;
  for (const auto &st : states) {
    if (this->labels.count(st)) {
      label_set.insert(labels.at(st));
    }
  }
  this->bit_num = int(ceil(log2(label_set.size() + 1)));
  vector<string> label_vector(label_set.begin(), label_set.end());

  unordered_map<string, vector<TRLWELvl1>> trlwe_map;

  for (int i = 0; i < label_vector.size() + 1; i++) {
    vector<TRLWELvl1> trlwe_vector;
    if (i == 0) {
      for (int j = 0; j < this->bit_num; j++) {
        trlwe_vector.push_back(trlwelvl1_zero);
      }
      trlwe_map[""] = trlwe_vector;
      continue;
    }
    for (int j = 0; j < this->bit_num; j++) {
      TRLWELvl1 value =
          (i % int(pow(2, j + 1))) == 0 ? trlwelvl1_zero : trlwelvl1_one;
      trlwe_vector.insert(trlwe_vector.begin() + j, value);
    }
    trlwe_map[label_vector.at(i - 1)] = trlwe_vector;
  }
  spdlog::info(to_string(trlwe_map.size()));
}