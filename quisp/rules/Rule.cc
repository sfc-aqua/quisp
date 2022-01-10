#include "Rule.h"
#include "Action.h"
#include "Condition.h"
#include <omnetpp.h>

namespace quisp::rules {

void BaseRule::addCondition(Condition condition) {}

void BaseRule::addAction(Action action) {}

void BaseRule::setNextRule(unsigned long next_rule_id) {
	if (to != 0){
		throw omnetpp::cRuntimeError("next_rule_id has already been set");
	}else{
		to = next_rule_id;
	}
}

PurificationRule::PurificationRule(PurType purification_type) : purification_type(purification_type) {}

SwappingRule::SwappingRule(SwapType swap_type) : swapping_type(swap_type) {}

WaitRule::WaitRule() {}

RandomMeasurementRule::RandomMeasurementRule(int total_measurement) : total_measurement(total_measurement) {}
}  // namespace quisp::rules
