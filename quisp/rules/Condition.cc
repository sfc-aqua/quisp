#include "Condition.h"
#include <memory>
#include "rules/Clause.h"
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

void Condition::deserialize_json(json serialized) {
  // prepare empty clauses
  auto serialized_clauses = serialized["clauses"];
  if (serialized["clauses"] != nullptr) {
    for (auto clause : serialized_clauses) {
      // check clause type
      auto clause_type = clause["type"].get<std::string>();
      if (clause_type == "enough_resource") {
        auto enough_resource = std::make_unique<EnoughResourceConditionClause>(clause);
        clauses.push_back(std::move(enough_resource));
      } else if (clause_type == "measure_count") {
        auto measure_count = std::make_unique<MeasureCountConditionClause>(clause);
        clauses.push_back(std::move(measure_count));
      } else if (clause_type == "fidelity") {
        auto fidelity = std::make_unique<FidelityConditionClause>(clause);
        clauses.push_back(std::move(fidelity));
      } else if (clause_type == "purification_correlation") {
        auto wait = std::make_unique<PurificationCorrelationClause>(clause);
        clauses.push_back(std::move(wait));
      } else if (clause_type == "swapping_correction") {
        auto wait = std::make_unique<SwappingCorrectionClause>(clause);
        clauses.push_back(std::move(wait));
      } else {
        throw omnetpp::cRuntimeError("No matching clause found");
      }
    }
  }
}

}  // namespace quisp::rules
