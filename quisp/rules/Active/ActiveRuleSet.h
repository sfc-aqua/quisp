#pragma once
#include <omnetpp.h>
#include "ActiveRule.h"

namespace quisp::rules::active {
/**
 *
 * \brief Set of rules for the RuleEngine.
 */
class ActiveRuleSet {
 public:
  ActiveRuleSet(unsigned long _ruleset_id, int _owner_addr);
  const unsigned long ruleset_id;
  int owner_addr;
  std::vector<std::unique_ptr<ActiveRule>> rules;

  void addRule(std::unique_ptr<ActiveRule> r);  // Add pointers to Rules
  std::unique_ptr<ActiveRule>& getRule(int i);
  int size() const;
  bool empty() const;
  std::vector<std::unique_ptr<ActiveRule>>::const_iterator cbegin() const noexcept;
  std::vector<std::unique_ptr<ActiveRule>>::const_iterator cend() const noexcept;
  std::vector<std::unique_ptr<ActiveRule>>::iterator begin() noexcept;
  std::vector<std::unique_ptr<ActiveRule>>::iterator end() noexcept;
};

}  // namespace quisp::rules::active
