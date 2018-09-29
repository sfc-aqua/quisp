/** \file Action.cc
 *
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include "Action.h"
#//include "../modules/RuleEngine.h"
#include "tools.h"
#include <omnetpp.h>
#//include "classical_messages_m.h"


namespace quisp {
namespace rules {

cPacket* SwappingAction::run(qnicResources* resources) {
        stationaryQubit *lqubit = NULL, *rqubit = NULL;
        lqubit = getQubit(resources,
                left_qnic_type, left_qnic_id, left_partner, left_resource);
        rqubit = getQubit(resources,
                right_qnic_type, right_qnic_id, right_partner, right_resource);
        if ((lqubit) && (rqubit)) {
            // do swapping on lqubit and rqubit TODO
            return 0;
        }
        // error
    }

cPacket* PurifyAction::run(qnicResources* resources) {
    stationaryQubit *qubit = NULL, *trash_qubit = NULL;
    qubit = getQubit(resources,qnic_type,qnic_id,partner,resource);
    trash_qubit = getQubit(resources,qnic_type,qnic_id,partner,trash_resource);
    if ((qubit) && (trash_qubit)) {
        // do purification where trash_qubit is in the measured pair TODO
        return 0;
    }
    // error
}

cPacket* RandomMeasureAction::run(qnicResources* resources) {
    EV<<"Measuring qubit now.\n";
    stationaryQubit *qubit = NULL;
    qubit = getQubit(resources,qnic_type,qnic_id,partner,resource);

    measurement_outcome o = qubit->measure_density_independent();
    current_count++;


    LinkTomographyResult *pk = new LinkTomographyResult;
    pk->setSrcAddr(src);
    pk->setDestAddr(dst);
    pk->setCount_id(current_count);
    pk->setPartner_address(src);//Partner's partner is self/src
    pk->setKind(6);
    pk->setOutput_is_plus(o.outcome_is_plus);
    pk->setBasis(o.basis);
    return pk;
}

/*
stationaryQubit* Action::getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) {
    // assume that qnic type is ok
    std::pair<EntangledPairs::iterator,EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);//Find all resource in qytpe/qid entangled with partner.
    int real_res_id = 0;
    stationaryQubit* use_this = nullptr;
    for (auto it=ret.first; it!=ret.second;) {
        std::cout << real_res_id << '\n';
        if (real_res_id == res_id){
            //resources[qtype][qid].erase(it);
            //realtime_controller->ReInitialize_StationaryQubit(it->second.qnic_index ,it->second.qubit_index, qnic_type);
            //Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], it->second.qnic_index, it->second.qubit_index);
            use_this = it->second;//Returns the top qubit in that list, if res_id = 0
            break;
        }else{
            ++it,++real_res_id;
        }
    }
    return use_this;
}*/


} // namespace rules
} // namespace quisp
