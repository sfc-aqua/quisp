#include "Rule.h"
#include <omnetpp.h>
#include "Action.h"
#include "Condition.h"

namespace quisp::rules {

void Rule::setCondition(std::unique_ptr<Condition> cond) { condition = std::move(cond); }

void Rule::setAction(std::unique_ptr<Action> act) { action = std::move(act); }

void Rule::setNextRule(unsigned long next_rule_id) {
  if (to != 0) {
    throw omnetpp::cRuntimeError("next_rule_id has already been set");
  } else {
    to = next_rule_id;
  }
}

json Rule::serialize() {
  json rule_json;
  rule_json["rule_id"] = rule_id;
  rule_json["next_rule_id"] = to;
  rule_json["name"] = name;
  rule_json["partners"] = partners;
  if (condition != nullptr) {
    rule_json["condition"] = condition->serialize();
  }
  if (action != nullptr) {
    rule_json["action"] = action->serialize();
  }
  return rule_json;
}

}  // namespace quisp::rules
