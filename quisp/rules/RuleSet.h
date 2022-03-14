#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include "Rule.h"

using json = nlohmann::json;
namespace quisp::rules {
/**
 * @brief RuleSet class which includes a set of Rule Information
 *
 */
class RuleSet {
 public:
  RuleSet(){};
  RuleSet(unsigned long ruleset_id, int owner_address);

  unsigned long ruleset_id;  ///< `ruleset_id` is used for identifying connection
  int owner_addr;  ///< Address of RuleSet owner
  int current_rule_id = 0;
  std::vector<std::unique_ptr<Rule>> rules;

  Rule *addRule(std::unique_ptr<Rule> rule);
  json serialize_json();
  void deserialize_json(json serialized);
  unsigned long createUniqueId();
};

}  // namespace quisp::rules
