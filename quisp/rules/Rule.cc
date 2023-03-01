#include "Rule.h"
#include <omnetpp.h>
#include "Action.h"
#include "Condition.h"

namespace quisp::rules {

Rule::Rule(int partner_address, int send_tag, int receive_tag) : send_tag(send_tag), receive_tag(receive_tag) { qnic_interfaces.push_back({partner_address}); };

Rule::Rule(std::vector<int> partner_address, int send_tag, int receive_tag) : send_tag(send_tag), receive_tag(receive_tag) {
  for (int addr : partner_address) {
    qnic_interfaces.push_back({addr});
  }
}

void Rule::setCondition(std::unique_ptr<Condition> cond) { condition = std::move(cond); }

void Rule::setAction(std::unique_ptr<Action> act) { action = std::move(act); }

json Rule::serialize_json() {
  json rule_json;
  rule_json["name"] = name;
  rule_json["interface"] = qnic_interfaces;
  rule_json["send_tag"] = send_tag;
  rule_json["receive_tag"] = receive_tag;
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
  serialized["name"].get_to(name);
  serialized["interface"].get_to(qnic_interfaces);
  serialized["send_tag"].get_to(send_tag);
  serialized["receive_tag"].get_to(receive_tag);

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
    } else if (action_name == "swapping_correction") {
      auto wait_swapping_action = std::make_unique<SwappingCorrection>(serialized_action);
      setAction(std::move(wait_swapping_action));
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
