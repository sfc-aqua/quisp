/** \file Rule.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Rule
 */

#include "Rule.h"
#include <messages/classical_messages.h>

using quisp::messages::ConditionNotSatisfied;

namespace quisp::rules {

Rule::Rule(unsigned long ruleset_id, unsigned long rule_index, std::string rule_name, std::vector<int> action_partners)
    : ruleset_id(ruleset_id), rule_index(rule_index), name(rule_name), action_partners(action_partners){};

void Rule::addResource(int address_entangled_with, IStationaryQubit *qubit) { resources.insert(std::make_pair(address_entangled_with, qubit)); }

void Rule::setCondition(Condition *c) { condition.reset(c); }

void Rule::setAction(Action *a) {
  a->rule_resources = &resources;
  action.reset(a);
}

cPacket *Rule::checkrun(cModule *re) {
  if (condition->check(resources)) {
    return action->run(re);
  }
  return new ConditionNotSatisfied;
}

bool Rule::checkTerminate() { return condition->checkTerminate(resources); }
}  // namespace quisp::rules
