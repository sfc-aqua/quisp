#pragma once
#include "Rule.h"


namespace quisp::rules {

/**
 * @brief (Inactive) RuleSet class which includes a set of Rule Information
 *
 */
class RuleSet {
 public:
  RuleSet(unsigned long ruleset_id, int owner_address);

  unsigned long ruleset_id;  ///< `ruleset_id` is used for identifying connection
  int owner_addr;  ///< Address of RuleSet owner
  std::vector<BaseRule> rules;

  BaseRule &addRule(const BaseRule rule, std::vector<int> partners);
  void serialize();
  void deserialize();
  unsigned long createUniqueId();
};

}  // namespace quisp::rules
