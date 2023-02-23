/** \file Rule.h
 *  \authors cldurand, takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Rule
 */
#pragma once
#include <omnetpp.h>
#include <stdio.h>
#include <types/QNodeAddr.h>
#include <memory>
#include <nlohmann/json.hpp>
#include "Action.h"
#include "Condition.h"

using json = nlohmann::json;

namespace quisp::rules {
class Rule {
 public:
  Rule(){};
  Rule(types::QNodeAddr partner_address, int shared_tag, bool is_finalized);
  Rule(std::vector<types::QNodeAddr> partner_address, int shared_tag, bool is_finalized);
  Rule(json serialized) { deserialize_json(serialized); };
  unsigned long parent_ruleset_id;
  int rule_id = -1;
  int to = -1;
  int shared_tag;  // Used to identify the partner Rule
  bool is_finalized;
  std::string name;
  std::vector<QnicInterface> qnic_interfaces;
  std::vector<types::QNodeAddr> next_partner_addresses;
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
