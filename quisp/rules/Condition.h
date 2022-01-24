#pragma once
#include <memory>
#include <vector>
#include "Clause.h"

namespace quisp::rules {

class Condition {
 public:
  Condition(){};

  std::vector<std::unique_ptr<Clause>> clauses;
  void addClause(std::unique_ptr<Clause> clause);
};
}  // namespace quisp::rules
