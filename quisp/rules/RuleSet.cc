#include "RuleSet.h"
#include <omnetpp.h>
#include <random>
#include <string>

namespace quisp::rules {
RuleSet::RuleSet(unsigned long ruleset_id, int owner_address) : ruleset_id(ruleset_id), owner_addr(owner_address) {}

BaseRule& RuleSet::addRule(BaseRule rule, std::vector<int> partners) {
  for (int partner : partners) {
    rule.partners.push_back(partner);
  }
  rule.rule_id = createUniqueId();
  rules.push_back(rule);
  BaseRule& rule_ref = rules.at(rules.size() - 1);
  return rule_ref;
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
