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

static void getQubit(qnicResources* resources, int partner, QNIC_type qtype, int qid, QubitAddr * result) {
    // assume that qnic type is ok
    std::pair<EntangledPairs::iterator,EntangledPairs::iterator> ret = resources[qtype]->equal_range(partner);
    int real_qid = 0;
    *result = { .node_address=-1, .qnic_index=-1, .qubit_index=-1 };
    for (EntangledPairs::iterator it=ret.first; it!=ret.second; ++it,++real_qid) {
        std::cout << real_qid << '\n';
        if (real_qid == qid) {
            *result = it->second;
            break;
        }
    }
}

int FidelityClause::check(qnicResources* resources) const {
    checkQnic();
    return 0;
}

Clause *EXAMPLE_CLAUSE = new FidelityClause(0,0,.6);

} // namespace rules
} // namespace quisp
