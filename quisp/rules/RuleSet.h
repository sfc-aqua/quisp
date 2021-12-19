/** \file RuleSet.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief RuleSet
 */
#ifndef QUISP_RULES_RULESET_H_
#define QUISP_RULES_RULESET_H_

#include <omnetpp.h>
#include "Rule.h"

namespace quisp {
namespace rules {

/** \class RuleSet RuleSet.h
 *
 * \brief Set of rules for the RuleEngine.
 */
class RuleSet {
 public:
  RuleSet(long _ruleset_id, int _owner_addr, int partner_addr);
  RuleSet(long _ruleset_id, int _owner_addr, std::vector<int> partner_addrs);
  void addRule(std::unique_ptr<Rule> r);
  std::unique_ptr<Rule>& getRule(int i);
  int size() const;
  bool empty() const;
  std::vector<std::unique_ptr<Rule>>::const_iterator cbegin();
  std::vector<std::unique_ptr<Rule>>::const_iterator cend();

  int owner_addr;
  std::vector<int> entangled_partners;
  std::vector<std::unique_ptr<Rule>> rules;
  simtime_t started_at;
  unsigned long ruleset_id;
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_RULESET_H_
