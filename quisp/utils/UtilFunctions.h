#include <iostream>
#include <map>
#include "backends/interfaces/IRandomNumberGenerator.h"

namespace quisp::util_functions {
using quisp::backends::abstract::IRandomNumberGenerator;

/*
  Description:
    This is a function that, given a set of labels and weights and a random number, returns a label according to the random number
  Args:
    std::map<double, Label> weights: weight(double) and label are a pair of values and it is a elements of std:map.
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
  double ceil;
  static bool IsFirst = true;
  for (auto &[l, w] : weights) {
    if (IsFirst) {
      ceil = 1 - w;
      IsFirst = false;
    } else {
      ceil += w;
    }

    if (rand <= ceil) {
      return l;
    }
  }
}
}  // namespace quisp::util_functions