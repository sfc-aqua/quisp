#pragma once
#include <omnetpp.h>
#include "Rule.h"

namespace quisp {
namespace rules {

/** \class RuleSet RuleSet.h
 *
 * \brief Set of rules for the RuleEngine.
 */
class ActiveRuleSet {
 public:
  ActiveRuleSet(unsigned long _ruleset_id, int _owner_addr);
  unsigned long ruleset_id;
  int owner_addr;
  simtime_t started_at;  // first time stamp of this ruleset get executed
  std::vector<std::unique_ptr<Rule>> rules;

  void addRule(std::unique_ptr<Rule> r);  // Add pointers to Rules
  std::unique_ptr<Rule>& getRule(int i);
  int size() const;
  bool empty() const;
  std::vector<std::unique_ptr<Rule>>::const_iterator cbegin();
  std::vector<std::unique_ptr<Rule>>::const_iterator cend();
};

}  // namespace rules
}  // namespace quisp
