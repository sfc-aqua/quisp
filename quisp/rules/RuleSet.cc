#include "RuleSet.h"
#include <omnetpp.h>
#include <memory>
#include <random>
#include <string>

namespace quisp::rules {
RuleSet::RuleSet(unsigned long ruleset_id, int owner_address) : ruleset_id(ruleset_id), owner_addr(owner_address) {}

Rule *RuleSet::addRule(std::unique_ptr<Rule> rule, std::vector<int> partners) {
  for (int partner : partners) {
    rule->partners.push_back(partner);
  }
  rule->rule_id = createUniqueId();
  rule->parent_ruleset_id = ruleset_id;
  Rule *raw_ptr = rule.get();
  rules.push_back(std::move(rule));
  return raw_ptr;
};

void RuleSet::serialize(){};

void RuleSet::deserialize(){};

unsigned long RuleSet::createUniqueId() {
  std::string time = omnetpp::SimTime().str();
  std::string address = std::to_string(owner_addr);
  std::string random = std::to_string(std::rand() % 10000000);
  std::string hash_seed = address + time + random;
  std::hash<std::string> hash_fn;
  size_t t = hash_fn(hash_seed);
  unsigned long id = static_cast<long>(t);
  return id;
}

}  // namespace quisp::rules
