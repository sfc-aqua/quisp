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
