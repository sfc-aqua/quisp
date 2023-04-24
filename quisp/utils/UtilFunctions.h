#include <iostream>
#include <map>
#include "backends/interfaces/IRandomNumberGenerator.h"

namespace quisp::util_functions {
using quisp::backends::abstract::IRandomNumberGenerator;

/*
  Description:
    This is a function that, given a set of labels and weights and a random number, returns a label according to the random number
  Args:
    std::map<Label, double> weights: weight(double) and label are a pair of values and it is a elements of std:map.
    rand: random number(double)
  Return:
    It returns label which previous_label_weight < rand <= label_weight
  Example:
    weight = {{0.3, ErrorLabel::X}, {0.7, ErrorLabel::Z}, {1.0, ErrorLabel::Y}}}
    rand = 0.4

    returns ErrorLabel::Z
 */
template <typename Label>
Label samplingWithWeights(std::map<Label, double> weights, double rand) {
  double sum = 0;
  for (auto &[l, w] : weights) {
    sum += w;
  }
  double ceil = 0;
  for (auto &[l, w] : weights) {
    ceil += w / sum;

    if (rand <= ceil) {
      return l;
    }
  }
}
}  // namespace quisp::util_functions