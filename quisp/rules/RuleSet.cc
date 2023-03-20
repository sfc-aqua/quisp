#include "RuleSet.h"

#include <random>
#include <string>

#include <omnetpp.h>

#include "RuleSetConverter/RuleSetConverter.h"

using json = nlohmann::json;
using quisp::types::QNodeAddr;

namespace quisp::rules {
RuleSet::RuleSet(unsigned long ruleset_id, QNodeAddr owner_address) : ruleset_id(ruleset_id), owner_addr(owner_address) {}

Rule* RuleSet::addRule(std::unique_ptr<Rule> rule) {
  Rule* raw_ptr = rule.get();
  rules.push_back(std::move(rule));
  return raw_ptr;
};

json RuleSet::serialize_json() {
  // inialize json and put metadata
  json ruleset_json;
  ruleset_json["ruleset_id"] = ruleset_id;
  ruleset_json["owner_address"] = owner_addr;
  ruleset_json["num_rules"] = rules.size();
  for (auto& rule : rules) {
    ruleset_json["rules"].push_back(rule->serialize_json());
  }
  return ruleset_json;
};

void RuleSet::deserialize_json(json serialized) {
  // if this function is directly called, check if there is json serialization
  if (serialized == nullptr) {
    throw omnetpp::cRuntimeError("No json serialization found");
  }

  // get properties from json with type conversion
  serialized.at("ruleset_id").get_to(ruleset_id);
  serialized.at("owner_address").get_to(owner_addr);

  // deserialize rules and push them back
  auto serialized_rules = serialized.at("rules");
  for (auto rule : serialized_rules) {
    auto deserialized_rule = std::make_unique<Rule>(rule);
    rules.push_back(std::move(deserialized_rule));
  }
};

runtime::RuleSet RuleSet::construct() const { return rs_converter::RuleSetConverter::construct(*this); }
}  // namespace quisp::rules

namespace std {
std::ostream& operator<<(std::ostream& os, const quisp::rules::RuleSet& rs) {
  os << "RuleSet(" << rs.ruleset_id << ", owner:" << rs.owner_addr << ")\n";
  for (auto& rule : rs.rules) {
    std::cout << rule->name << "\n";
  }

  return os;
}
}  // namespace std
