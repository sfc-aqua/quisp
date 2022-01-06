/** \file RuleSet.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief RuleSet
 */
#include "RuleSet.h"

namespace quisp {
namespace rules {

RuleSet::RuleSet(unsigned long _ruleset_id, int _owner_addr) {
  ruleset_id = _ruleset_id;
  owner_addr = _owner_addr;
  started_at = simTime();
}

void RuleSet::addRule(std::unique_ptr<Rule> r) { rules.emplace_back(std::move(r)); };
std::unique_ptr<Rule>& RuleSet::getRule(int i) { return rules[i]; };
void serialize();
void desrialize();
int RuleSet::size() const { return rules.size(); };
bool RuleSet::empty() const { return rules.empty(); }
std::vector<std::unique_ptr<Rule>>::const_iterator RuleSet::cbegin() { return rules.cbegin(); }
std::vector<std::unique_ptr<Rule>>::const_iterator RuleSet::cend() { return rules.cend(); }

}  // namespace rules
}  // namespace quisp
