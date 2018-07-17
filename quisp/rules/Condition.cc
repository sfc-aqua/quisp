/** \file Condition.cc
 *
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief Condition
 */
#include "Condition.h"

namespace quisp {
namespace rules {

int Condition::check(qnicResources *resources) const {
    for (std::list<Clause*>::const_iterator clause = clauses.cbegin(), end = clauses.cend(); clause != end; clause++)
        if ((*clause)->check(resources)) return 1;
    return 0;
}

} // namespace rules
} // namespace quisp
