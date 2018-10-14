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

/*
//you also sometimes need to return feedback information for other nodes.
cPacket* Rule::checkrun(qnicResources * resources, int qnic_type, int qnic_index, int resource_entangled_with_address) {

    EntangledPairs temp_resource_list;

    auto ret = resources[qnic_type][qnic_index].equal_range(resource_entangled_with_address);
    for (auto i = ret.first; i != ret.second; ++i) {
        EV<<"Resource: between node "<<i->first<<", "<<i->second<<"\n";
        temp_resource_list.insert(std::make_pair(i->first, i->second));//Copy all related ones to temporary list.
    }

    cPacket *pk = nullptr;
    if (condition->check(resources)){
        EV<<"All conditions met. Running Action. \n";
        pk = action->run(resources);
    }
    return pk;
}*/


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




/*
cPacket* Rule::checkrun(cModule * re, qnicResources * resources, int qnic_type, int qnic_index, int resource_entangled_with_address) {

    EntangledPairs temp_resource_list;

    auto ret = resources[qnic_type][qnic_index].equal_range(resource_entangled_with_address);
    for (auto i = ret.first; i != ret.second; ++i) {
        EV<<"Resource: between node "<<i->first<<", "<<i->second<<"\n";
        temp_resource_list.insert(std::make_pair(i->first, i->second));//Copy all related ones to temporary list.
    }

    cPacket *pk = nullptr;
    if (condition->check(resources)){
        EV<<"All conditions met. Running Action. \n";
        pk = action->run(resources);
    }
    return pk;
}*/

/*
cPacket* Rule::checkrun(EntangledPairs resources, int resource_entangled_with_address) {
    //EntangledPairs temp_resource_list;

    //auto ret = resources.equal_range(resource_entangled_with_address);//Find resources in the qnic entangled with resource_entangled_with_address
    //for (auto i = ret.first; i != ret.second; ++i) {
    //    EV<<"Resource: between node "<<i->first<<", "<<i->second<<"\n";
     //   temp_resource_list.insert(std::make_pair(i->first, i->second));//Copy all related ones to temporary list.
    //}

    cPacket *pk = nullptr;
    //if (condition->check(resources)){
    //    EV<<"All conditions met. Running Action. \n";
    //    pk = action->run(resources);
    //}
    return pk;
}*/

/*
cPacket* Rule::checkrun(qnicResources * resources) {
    cPacket *pk = nullptr;
    EV<<"condition->check(resources) = "<< condition->check(resources);
    if (condition->check(resources)){
        EV<<"All conditions met. Running Action. \n";
        pk = action->run(resources);
    }else{
        EV<<"Condition did not meet.";
        pk = new ConditionNotSatisfied;
    }
    return pk;
}*/

/*
bool Rule::checkTerminate(qnicResources * resources) {
    bool done = false;
    if (condition->checkTerminate(resources)){
        EV<<"Termination conditions met. Delete this RuleSet. \n";
        done = true;
    }else{
        EV<<"Termination conditions not yet fulfilled.\n ";
    }
    return done;
}*/

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



/*
int Rule::test(qnicResources * resources){
    EV<<"Invoked!!!!!!!!\n";
    printf("Test");
    return 0;
}*/

} // namespace rules
} // namespace quisp
