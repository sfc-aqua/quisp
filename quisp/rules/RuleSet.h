#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include "Rule.h"

using json = nlohmann::json;
namespace quisp::rules {

struct Serialized {
  json json;
};
/**
 * @brief RuleSet class which includes a set of Rule Information
 *
 */
class RuleSet {
 public:
  RuleSet(unsigned long ruleset_id, int owner_address);

  unsigned long ruleset_id;  ///< `ruleset_id` is used for identifying connection
  int owner_addr;  ///< Address of RuleSet owner
  int current_rule_id = 0;
  std::vector<std::unique_ptr<Rule>> rules;
  Serialized out;

  Rule *addRule(std::unique_ptr<Rule> rule, std::vector<int> partners);
  void serialize_json();
  void serialize_protobuf();
  void deserialize();
  unsigned long createUniqueId();
};

}  // namespace quisp::rules
