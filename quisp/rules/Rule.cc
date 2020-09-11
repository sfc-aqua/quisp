/** \file Rule.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Rule
 */

#include "Rule.h"
#include "classical_messages_m.h"

//#include <modules/RuleEngine.h>

namespace quisp {
namespace rules {

void Rule::addResource(int address_entangled_with, StationaryQubit *qubit) {
  // int index = number_of_resources_allocated_in_total;
  // this index must be entangled partner (this must be updated)
  resources.insert(std::make_pair(address_entangled_with, qubit));  // Assign resource to the 1st Rule.
  // number_of_resources_allocated_in_total++;
  // EV<<"This is current resource!"
}

void Rule::setCondition(Condition *c) { condition.reset(c); }

void Rule::setAction(Action *a) {
  a->rule_resources = &resources;
  action.reset(a);
}
cPacket *Rule::checkrun(cModule *re) {
  cPacket *pk = nullptr;
  if (condition->check(resources)) {
    // std::cout<<"Condition met!.\n";
    // std::cout<<"before: check num = "<<action->checkNumResource()<<"\n";
    pk = action->run(re);
    // std::cout<<"after: check num = "<<action->checkNumResource()<<"\n";
  } else {
    // std::cout<<"Condition did not meet \n";
    pk = new ConditionNotSatisfied;
  }
  // std::cout<<"After: "<<resources.size()<<"\n";
  return pk;
}

bool Rule::checkTerminate() {
  bool done = false;
  if (condition->checkTerminate(resources)) {
    done = true;
    // std::cout<<"Termination conditions met. Delete this RuleSet. done = "<<done<<"\n";
  } else {
    // std::cout<<"Termination conditions not yet fulfilled.\n ";
  }
  return done;
}

/*
cPacket* Rule::checkrun(cModule *re, qnicResources * resources, int qnic_type, int qnic_index, int resource_entangled_with_address) {
    EntangledPairs temp_resource_list;

    auto ret = resources[qnic_type][qnic_index].equal_range(resource_entangled_with_address);
    for (auto i = ret.first; i != ret.second; ++i) {
        EV<<"Resource: between node "<<i->first<<", "<<i->second<<"\n";
        temp_resource_list.insert(std::make_pair(i->first, i->second));//Copy all related ones to temporary list.
    }

    cPacket *pk = nullptr;
    if (condition->check(resources)){
        EV<<"All conditions met. Running Action. \n";
        pk = action->run(re, resources);
    }
    return pk;
}
*/

/*
bool Rule::checkTerminate(qnicResources * resources, int qnic_type, int qnic_index, int resource_entangled_with_address) {
    bool done = false;
    if (condition->checkTerminate(resources)){
        done = true;
        EV<<"Termination conditions met. Delete this RuleSet. done = "<<done<<"\n";
    }else{
        EV<<"Termination conditions not yet fulfilled.\n ";
    }
       return done;
}
*/

}  // namespace rules
}  // namespace quisp
