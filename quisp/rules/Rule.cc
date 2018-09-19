/** \file Rule.cc
 *
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief Rule
 */
#include "Rule.h"

namespace quisp {
namespace rules {

//you also sometimes need to return feedback information for other nodes.
int Rule::checkrun(qnicResources * resources, int qnic_type, int qnic_index, int resource_entangled_with_address) {

    EntangledPairs temp_resource_list;

    auto ret = resources[qnic_type][qnic_index].equal_range(resource_entangled_with_address);
    for (auto i = ret.first; i != ret.second; ++i) {
        EV<<"Resource: between node "<<i->first<<", "<<i->second<<"\n";
        temp_resource_list.insert(std::make_pair(i->first, i->second));//Copy all related ones to temporary list.
    }

    int res = 0;
    if (condition->check(resources)){
        EV<<"All conditions meet. Running Action. \n";
        res = action->run(resources);
    }
    return res;
}

int Rule::checkrun(qnicResources * resources) {
    int res = 0;
    if (condition->check(resources)){
        EV<<"All conditions meet. Running Action. \n";
        res = action->run(resources);
    }
    return res;
}

int Rule::test(qnicResources * resources){
    EV<<"Invoked!!!!!!!!\n";
    printf("Test");
    return 0;
}

} // namespace rules
} // namespace quisp
