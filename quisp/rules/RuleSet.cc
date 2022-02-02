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
  json ruleset;
  ruleset["ruleset_id"] = ruleset_id;
  ruleset["owner_address"] = owner_addr;
  ruleset["num_rules"] = rules.size();
  for (auto &rule : rules) {
    ruleset["rules"].push_back(rule->serialize());
  }
  out.json = ruleset;
};

void RuleSet::serialize_protobuf() { throw omnetpp::cRuntimeError("Protobuf serialization is not yet implemented"); }

void RuleSet::deserialize(){};

}  // namespace quisp::rules
