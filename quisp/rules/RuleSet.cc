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

RuleSet::RuleSet(long _ruleset_id, int _owner_addr, std::vector<int> partner_addrs) {
  ruleset_id = _ruleset_id;
  owner_addr = _owner_addr;
  entangled_partners = partner_addrs;
  started_at = simTime();
}

RuleSet::RuleSet(long _ruleset_id, int _owner_addr, int partner_addr) {
  ruleset_id = _ruleset_id;
  owner_addr = _owner_addr;
  entangled_partners.push_back(partner_addr);
  started_at = simTime();
}

void RuleSet::addRule(Rule* r) { rules.push_back(r); };
Rule* RuleSet::getRule(int i) { return rules.at(i); };
int RuleSet::size() { return rules.size(); };
bool RuleSet::empty() { return rules.empty(); }
std::vector<Rule*>::const_iterator RuleSet::cbegin() { return rules.cbegin(); }
std::vector<Rule*>::const_iterator RuleSet::cend() { return rules.cend(); }

}  // namespace rules
}  // namespace quisp
