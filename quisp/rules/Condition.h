#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>
#include "Clause.h"

using json = nlohmann::json;
namespace quisp::rules {

class Condition {
 public:
  Condition(){};

  std::vector<std::unique_ptr<Clause>> clauses;
  void addClause(std::unique_ptr<Clause> clause);
  json serialize();
};
}  // namespace quisp::rules
