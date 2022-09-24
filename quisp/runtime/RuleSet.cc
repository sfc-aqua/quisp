#include "RuleSet.h"

namespace quisp::runtime {
void Rule::finalize() {}

void RuleSet::finalize() {
  // set index for each rule
  for (int i = 0; i < rules.size(); ++i) {
    rules[i].id = i;
  }
}
}  // namespace quisp::runtime
