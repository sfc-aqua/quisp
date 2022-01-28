#include "Condition.h"
#include <memory>
namespace quisp::rules {
void Condition::addClause(std::unique_ptr<Clause> clause) { clauses.push_back(std::move(clause)); }

json Condition::serialize() {
  json condition_json;
  for (auto &clause : clauses) {
    condition_json["type"] = clause->getName();
    condition_json["options"] = clause->serialize();
  }
  return condition_json;
}

}  // namespace quisp::rules
