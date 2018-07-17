/** \file Clause.cc
 *
 *  \authors cldurand
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#include "Clause.h"

namespace quisp {
namespace rules {

static stationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) {
    // assume that qnic type is ok
    std::pair<EntangledPairs::iterator,EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);
    int real_res_id = 0;
    for (EntangledPairs::iterator it=ret.first; it!=ret.second; ++it,++real_res_id) {
        std::cout << real_res_id << '\n';
        if (real_res_id == res_id) return it->second;
    }
    return NULL;
}

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
