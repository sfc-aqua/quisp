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

int Rule::checkrun(qnicResources * resources) {
    int res = 0;
    if (res = condition->check(resources)) action->run(resources);
    return res;
}

} // namespace rules
} // namespace quisp
