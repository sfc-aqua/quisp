#include "Condition.h"
#include <memory>
namespace quisp::rules {
void Condition::addClause(std::unique_ptr<Clause> clause) { clauses.push_back(std::move(clause)); }

json Condition::serialize_json() {
  json condition_json;
  condition_json["clauses"] = {};
  for (auto &clause : clauses) {
    condition_json["clauses"].push_back(clause->serialize_json());
  }
  return condition_json;
}

}  // namespace quisp::rules
