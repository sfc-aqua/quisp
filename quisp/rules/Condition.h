#pragma once
#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include "Clause.h"

using json = nlohmann::json;
namespace quisp::rules {

class Condition {
 public:
  Condition() {}
  Condition(json serialized) { deserialize_json(serialized); }

  std::vector<std::unique_ptr<Clause>> clauses;
  void addClause(std::unique_ptr<Clause> clause);
  json serialize_json();
  void deserialize_json(json serialized);
};
}  // namespace quisp::rules
