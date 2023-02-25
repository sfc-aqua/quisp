/** \file Rule.h
 *
 *  \brief Rule
 */
#pragma once
#include <omnetpp.h>
#include <stdio.h>
#include <memory>

#include <nlohmann/json.hpp>

#include "Action.h"
#include "Condition.h"

using json = nlohmann::json;

namespace quisp::rules {
class Rule {
 public:
  Rule(){};
  Rule(int partner_address, int send_tag, int receive_tag);
  Rule(std::vector<int> partner_address, int send_tag, int receive_tag);
  Rule(json serialized) { deserialize_json(serialized); };
  unsigned long parent_ruleset_id;
  int send_tag;  ///< used to denote which rules should receive this message
  int receive_tag;  ///< RuleEngine will assign a message with this tag to this rule.
  std::vector<QnicInterface> qnic_interfaces;
  std::string name;
  std::unique_ptr<Condition> condition;  ///< Condition includes a set of clauses
  std::unique_ptr<Action> action;

  void setCondition(std::unique_ptr<Condition> condition);
  void setAction(std::unique_ptr<Action> action);
  void setName(std::string rule_name) { name = rule_name; };
  json serialize_json();
  void deserialize_json(json serialized);
};

}  // namespace quisp::rules
