#include "Rule.h"
#include <omnetpp.h>
#include "Action.h"
#include "Condition.h"

namespace quisp::rules {

void Rule::setCondition(Condition *cond) { condition.reset(cond); }

void Rule::setAction(Action *act) { action.reset(act); }

void Rule::setNextRule(unsigned long next_rule_id) {
  if (to != 0) {
    throw omnetpp::cRuntimeError("next_rule_id has already been set");
  } else {
    to = next_rule_id;
  }
}

void Rule::serialize() {}

}  // namespace quisp::rules
