/** \file tools.h
 *
 *  \authors cldurand
 *  \date 2018/09/04
 *
 *  \brief tools
 */
#ifndef QUISP_RULES_TOOLS_H_
#define QUISP_RULES_TOOLS_H_

namespace quisp {
namespace rules {

/** \func static stationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id)*/

static stationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) {
    // assume that qnic type is ok
    std::pair<EntangledPairs::iterator,EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);//Find all resource in qytpe/qid entangled with partner.
    int real_res_id = 0;
    for (EntangledPairs::iterator it=ret.first; it!=ret.second; ++it,++real_res_id) {
        std::cout << real_res_id << '\n';
        if (real_res_id == res_id){
            return it->second;//Returns the top qubit in that list, if res_id = 0
        }
    }
    return NULL;
}

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_TOOLS_H_
