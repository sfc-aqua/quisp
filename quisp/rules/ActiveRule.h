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
#include "Action.h"
#include "Condition.h"

namespace quisp::rules {

class ActiveRule {
 public:
  const unsigned long ruleset_id;
  const unsigned long rule_id;
  unsigned long next_rule_id = 0;
  std::string name;
  std::unique_ptr<Condition> condition;
  std::unique_ptr<Action> action;
  std::multimap<int, IStationaryQubit *> resources;
  std::vector<int> action_partners;
  std::vector<int> next_action_partners;  // if this rule extends the entanglement

  ActiveRule(unsigned long ruleset_id, unsigned long rule_id, std::string rule_name = "", std::vector<int> action_partners = {});

  void addResource(int address_entangled_with, IStationaryQubit *qubit);
  void setCondition(Condition *c);
  void setAction(Action *a);

  cPacket *checkrun(cModule *re);
  bool checkTerminate();
};

}  // namespace quisp::rules
