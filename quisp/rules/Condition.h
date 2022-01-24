#pragma once
#include <memory>
#include <vector>
#include "Clause.h"

namespace quisp::rules {

class Condition {
 public:
  Condition(){};

  std::vector<BaseClause> clauses;
  void addClause(std::unique_ptr<BaseClause> clause);
};
}  // namespace quisp::rules
