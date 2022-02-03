#include "Condition.h"
#include <memory>
namespace quisp::rules {
void Condition::addClause(std::unique_ptr<Clause> clause) { clauses.push_back(std::move(clause)); }

json Condition::serialize_json() {
  json condition_json;
  for (auto &clause : clauses) {
    condition_json["type"] = clause->getName();
    condition_json["options"] = clause->serialize_json();
  }
  return condition_json;
}

}  // namespace quisp::rules
