#include "ActiveRule.h"
#include <messages/classical_messages.h>

using quisp::messages::ConditionNotSatisfied;

namespace quisp::rules::active {

ActiveRule::ActiveRule(unsigned long ruleset_id, unsigned long rule_id, std::string rule_name, std::vector<int> action_partners)
    : ruleset_id(ruleset_id), rule_id(rule_id), name(rule_name), action_partners(action_partners){};

void ActiveRule::addResource(int address_entangled_with, IStationaryQubit *qubit) { resources.insert(std::make_pair(address_entangled_with, qubit)); }

void ActiveRule::setCondition(ActiveCondition *c) { condition.reset(c); }

void ActiveRule::setAction(ActiveAction *a) {
  a->rule_resources = &resources;
  action.reset(a);
}

cPacket *ActiveRule::checkrun(cModule *re) {
  if (condition->check(resources)) {
    return action->run(re);
  }
  return nullptr;
}

bool ActiveRule::checkTerminate() { return condition->checkTerminate(resources); }
}  // namespace quisp::rules::active
