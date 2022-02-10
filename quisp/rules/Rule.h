/** \file Rule.h
 *  \authors cldurand, takaakimatsuo
 *  \date 2018/06/25
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
  Rule(json serialized) { deserialize_json(serialized); };
  unsigned long parent_ruleset_id;
  int rule_id;
  int to = 0;
  std::string name;
  std::vector<int> partners;
  std::unique_ptr<Condition> condition;  ///< Condition includes a set of clauses
  std::unique_ptr<Action> action;

  void setCondition(std::unique_ptr<Condition> condition);
  void setAction(std::unique_ptr<Action> action);
  void setNextRule(unsigned long next_rule_id);
  void setName(std::string rule_name) { name = rule_name; };
  json serialize_json();
  void deserialize_json(json serialized);
};

}  // namespace quisp::rules
