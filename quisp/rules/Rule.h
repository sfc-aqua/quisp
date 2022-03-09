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
  Rule(int partner_address, QNIC_type qnic_type, int qnic_id, bool is_finalized);
  Rule(std::vector<int> partner_addresses, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id, bool is_finalized)
      : partners(partner_addresses), qnic_types(qnic_type), qnic_ids(qnic_id), is_finalized(is_finalized){};
  Rule(json serialized) { deserialize_json(serialized); };
  unsigned long parent_ruleset_id;
  int rule_id = -1;
  int to = -1;
  bool is_finalized;
  std::string name;
  std::vector<int> partners;
  std::vector<QNIC_type> qnic_types;
  std::vector<int> qnic_ids;
  std::unique_ptr<Condition> condition;  ///< Condition includes a set of clauses
  std::unique_ptr<Action> action;

  void setCondition(std::unique_ptr<Condition> condition);
  void setAction(std::unique_ptr<Action> action);
  void setNextRule(int next_rule_id);
  void setName(std::string rule_name) { name = rule_name; };
  json serialize_json();
  void deserialize_json(json serialized);
};

}  // namespace quisp::rules
