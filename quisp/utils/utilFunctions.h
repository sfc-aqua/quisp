#include <iostream>
#include <map>
#include "backends/interfaces/IRandomNumberGenerator.h"

namespace quisp {
namespace utilFunctions {
using quisp::backends::abstract::IRandomNumberGenerator;

template <typename Label>
Label sample(std::map<double, Label> weights) {
  // Gives a random double between 0.0 ~ 1.0
  std::unique_ptr<IRandomNumberGenerator> rng;
  double rand = rng->doubleRandom();
  Label label;

  for (auto &[w, l] : weights) {
    if (rand <= w) {
      break;
    }
    label = l;
  }
  return label;
}
}  // namespace utilFunctions
}  // namespace quisp