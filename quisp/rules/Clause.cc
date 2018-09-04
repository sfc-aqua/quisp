/** \file Clause.cc
 *
 *  \authors cldurand
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#include "Clause.h"
#include "tools.h"

namespace quisp {
namespace rules {

int FidelityClause::check(qnicResources* resources) const {
    stationaryQubit* qubit = NULL;
    checkQnic();
    if (qubit = getQubit(resources, qnic_type, qnic_id, partner, resource))
        return (qubit->getFidelity() >= threshold);
    return 0;
}

Clause *EXAMPLE_CLAUSE = new FidelityClause(0,0,.6);

} // namespace rules
} // namespace quisp
