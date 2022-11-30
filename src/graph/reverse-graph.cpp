#include "reverse-graph.hpp"
#include "spdlog/spdlog.h"
#include "tfhe-util.hpp"
#include <cmath>
#include <execution>
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
  std::vector<TRLWELvl1> weight(states.size());
  this->bit_num = int(ceil(log2(label_set.size() + 1)));
  vector<string> label_vector(label_set.begin(), label_set.end());
  this->label_vector = label_vector;

  unordered_map<string, TRLWELvl1> trlwe_map;

  for (int i = 0; i < label_vector.size() + 1; i++) {
    if (i == 0) {
      trlwe_map[""] = trivial_TRLWELvl1(0);
      continue;
    }
    trlwe_map[label_vector.at(i - 1)] = trivial_TRLWELvl1(i);
  }

  for (auto it = states.begin(); it != states.end(); ++it) {
    if (labels.count(*it) == 0) {
      weight.at(*it) = trlwe_map[""];
    } else {
      auto label = labels.at(*it);
      weight.at(*it) = trlwe_map[label];
    }
  }
  this->weight = weight;
}

void ReverseGraph::run(const TRGSWLvl1FFT &input) {
  std::vector<TRLWELvl1> next_weight(states.size());
  for_each(states.begin(), states.end(), [&](ReverseGraph::State q) {
    ReverseGraph::State q0 = this->get_next_state(q, Sigma::ZERO),
                        q1 = this->get_next_state(q, Sigma::ONE);
    const TRLWELvl1 &w0 = weight.at(q0), &w1 = weight.at(q1);
    TFHEpp::CMUXFFT<Lvl1>(next_weight.at(q), input, w1, w0);
  });
  swap(weight, next_weight);
}

ReverseGraph::State ReverseGraph::get_next_state(ReverseGraph::State q,
                                                 Sigma sigma) {
  return sigma == Sigma::ZERO ? transitions.at(q).first
                              : transitions.at(q).second;
}

vector<TLWELvl1> ReverseGraph::output_result() {
  vector<TLWELvl1> rets(this->bit_num);
  for (int i = 0; i < this->bit_num; i++) {
    TFHEpp::SampleExtractIndex<Lvl1>(rets[i], weight.at(this->initial_state),
                                     i);
  }
  return rets;
}

// i番目がi桁目
string ReverseGraph::output_label(vector<TLWELvl1> results,
                                  const SecretKey &skey) {
  int num = 0;
  for (int i = 0; i < results.size(); i++) {
    if (decrypt_TLWELvl1_to_bool(results.at(i), skey)) {
      num += int(pow(2, i));
    }
  }
  if (num == 0) {
    return "";
  }
  return this->label_vector.at(num - 1);
};