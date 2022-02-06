#include "RuleSet.h"
#include <omnetpp.h>
#include <memory>
#include <random>
#include <string>

using json = nlohmann::json;

namespace quisp::rules {
RuleSet::RuleSet(unsigned long ruleset_id, int owner_address) : ruleset_id(ruleset_id), owner_addr(owner_address) {}

Rule *RuleSet::addRule(std::unique_ptr<Rule> rule, std::vector<int> partners) {
  for (int partner : partners) {
    rule->partners.push_back(partner);
  }
  rule->rule_id = current_rule_id;
  current_rule_id++;
  rule->parent_ruleset_id = ruleset_id;
  Rule *raw_ptr = rule.get();
  rules.push_back(std::move(rule));
  return raw_ptr;
};

void RuleSet::serialize_json() {
  // inialize json and put metadata
  json ruleset_json;
  ruleset_json["ruleset_id"] = ruleset_id;
  ruleset_json["owner_address"] = owner_addr;
  ruleset_json["num_rules"] = rules.size();
  for (auto &rule : rules) {
    ruleset_json["rules"].push_back(rule->serialize_json());
  }
  // store serialized ruleset json
  out.json = ruleset_json;

  // reinitialize member variables
  ruleset_id = 0;
  owner_addr = -1;
  rules.clear();
};

void RuleSet::deserialize() {
  // check which serialization format
  if (out.json != nullptr) {
    // json deserialization
    deserialize_json();
  } else {
    throw omnetpp::cRuntimeError("No serialization found");
  }
};

void RuleSet::deserialize_json() {
  auto serialized = out.json;
  // if this function is directly called, check if there is json serialization
  if (serialized == nullptr) {
    throw omnetpp::cRuntimeError("No json serialization found");
  }

  // get properties from json with type conversion
  ruleset_id = serialized.at("ruleset_id").get<unsigned long>();
  owner_addr = serialized.at("owner_address").get<int>();

  // deserialize rules and push them back
  auto serialized_rules = serialized.at("rules");
  for (auto rule : serialized_rules) {
    auto deserialized_rule = std::make_unique<Rule>();
    deserialized_rule->deserialize_json(rule);
    rules.push_back(std::move(deserialized_rule));
  }
};

}  // namespace quisp::rules
