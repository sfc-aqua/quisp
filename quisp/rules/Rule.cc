#include "Rule.h"
#include <omnetpp.h>
#include "Action.h"
#include "Condition.h"

namespace quisp::rules {

Rule::Rule(int partner_address, QNIC_type qnic_type, int qnic_id, int shared_tag, bool is_finalized) : shared_tag(shared_tag), is_finalized(is_finalized) {
  QnicInterface interface { partner_address, qnic_type, qnic_id };
  qnic_interfaces.push_back(interface);
};

Rule::Rule(std::vector<int> partner_address, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id, int shared_tag, bool is_finalized)
    : shared_tag(shared_tag), is_finalized(is_finalized) {
  for (int i = 0; i < partner_address.size(); i++) {
    QnicInterface interface { partner_address.at(i), qnic_type.at(i), qnic_id.at(i) };
    qnic_interfaces.push_back(interface);
  }
}

void Rule::setCondition(std::unique_ptr<Condition> cond) { condition = std::move(cond); }

void Rule::setAction(std::unique_ptr<Action> act) { action = std::move(act); }

void Rule::setNextRule(int next_rule_id) {
  if (to != -1) {
    throw omnetpp::cRuntimeError("next_rule_id has already been set");
  } else {
    to = next_rule_id;
  }
}

json Rule::serialize_json() {
  json rule_json;
  rule_json["rule_id"] = rule_id;
  rule_json["next_rule_id"] = to;
  rule_json["name"] = name;
  rule_json["interface"] = qnic_interfaces;
  rule_json["shared_tag"] = shared_tag;
  if (condition != nullptr) {
    rule_json["condition"] = condition->serialize_json();
  }
  if (action != nullptr) {
    rule_json["action"] = action->serialize_json();
  }
  return rule_json;
}

void Rule::deserialize_json(json serialized) {
  // deserialize rule meta data
  serialized["rule_id"].get_to(rule_id);
  serialized["next_rule_id"].get_to(to);
  serialized["name"].get_to(name);
  serialized["interface"].get_to(qnic_interfaces);
  serialized["shared_tag"].get_to(shared_tag);

  // deserialize actions
  if (serialized["action"] != nullptr) {  // action found
    auto serialized_action = serialized.at("action");
    auto action_name = serialized_action.at("type").get<std::string>();
    // check which action to be initialized
    if (action_name == "purification") {
      auto purification_action = std::make_unique<Purification>(serialized_action);
      setAction(std::move(purification_action));
    } else if (action_name == "swapping") {
      auto swapping_action = std::make_unique<EntanglementSwapping>(serialized_action);
      setAction(std::move(swapping_action));
    } else if (action_name == "wait") {
      auto wait_action = std::make_unique<Wait>(serialized_action);
      setAction(std::move(wait_action));
    } else if (action_name == "tomography") {
      auto tomography_action = std::make_unique<Tomography>(serialized_action);
      setAction(std::move(tomography_action));
    } else {
      throw omnetpp::cRuntimeError("No action type found");
    }
  }

  // deserialize conditions
  if (serialized["condition"] != nullptr) {  // condition found
    // empty condition
    auto empty_condition = std::make_unique<Condition>(serialized.at("condition"));
    setCondition(std::move(empty_condition));
  }
}

}  // namespace quisp::rules
