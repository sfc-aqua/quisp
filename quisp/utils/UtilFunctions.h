#include <iostream>
#include <map>
#include "backends/interfaces/IRandomNumberGenerator.h"

namespace quisp::utilFunctions {
using quisp::backends::abstract::IRandomNumberGenerator;

template <typename Label>
Label sample(std::map<double, Label> weights, double rand) {
  Label label;

  for (auto &[w, l] : weights) {
    if (rand <= w) {
      break;
    }
    label = l;
  }
  return label;
}
}  // namespace quisp::utilFunctions