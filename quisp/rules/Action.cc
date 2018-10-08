/** \file Action.cc
 *
 *  \authors cldurand
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include "Action.h"
//#include "../modules/RuleEngine.h"
#include "tools.h"
#include <omnetpp.h>
#include "classical_messages_m.h"


namespace quisp {
namespace rules {

/*
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
}*/

cPacket* SwappingAction::run(cModule *re, qnicResources* resources) {
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

/*
cPacket* PurifyAction::run(qnicResources* resources) {
    stationaryQubit *qubit = NULL, *trash_qubit = NULL;
    qubit = getQubit(resources,qnic_type,qnic_id,partner,resource);
    trash_qubit = getQubit(resources,qnic_type,qnic_id,partner,trash_resource);
    if ((qubit) && (trash_qubit)) {
        // do purification where trash_qubit is in the measured pair TODO
        return 0;
    }
    // error
}*/

cPacket* PurifyAction::run(cModule *re, qnicResources* resources) {
    stationaryQubit *qubit = NULL, *trash_qubit = NULL;
    qubit = getUnLockedQubit_fromTop(resources,qnic_type,qnic_id,partner,resource);
    trash_qubit = getUnLockedQubit_fromTop(resources,qnic_type,qnic_id,partner,trash_resource);
    if ((qubit) && (trash_qubit)) {
        if(qubit== trash_qubit){
            Error *pk = new Error;
            pk->setError_text("Qubit and Trash qubit are the same for purification. Something must be wrong.");
            return pk;
        }else{
            // do purification where trash_qubit is in the measured pair TODO
            qubit->Lock(static_action_id+purification_count);
            trash_qubit->Lock(static_action_id+purification_count);//You may not need this because this will be trashed soo anyway.
            purification_count++;
            bool measurement_outcome_error = qubit->purify(trash_qubit);//Only error propagation. No density matrix calculation.

            /*Delete measured resource from the tracked list of resources.*/
            RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
            rule_engine->freeConsumedResource(qnic_id, trash_qubit, qnic_type);
            /*Deleting done*/


            return 0;
        }
    }else{
        Error *pk = new Error;
        pk->setError_text("Qubits not found for purification.");
        return pk;
    }
    // error
}


/*
cPacket* PurifyAction::run(cModule *re, qnicResources* resources) {
    stationaryQubit *qubit = NULL, *trash_qubit = NULL;
    qubit = getQubit(resources,qnic_type,qnic_id,partner,resource);
    trash_qubit = getQubit(resources,qnic_type,qnic_id,partner,trash_resource);
    if ((qubit) && (trash_qubit)) {
        // do purification where trash_qubit is in the measured pair TODO
        return 0;
    }
    // error
}*/


/*
cPacket* RandomMeasureAction::run(qnicResources* resources) {
    EV<<"Measuring qubit now.\n";
    stationaryQubit *qubit = NULL;
    qubit = getQubit(resources,qnic_type,qnic_id,partner,resource);

    if(qubit==nullptr){
           Error *pk = new Error;
           pk->setError_text("Qubit not found for measurement.");
           return pk;
    }else{
        measurement_outcome o = qubit->measure_density_independent();
        current_count++;

        //freeConsumedQubit(resources,qnic_type,qnic_id,partner,resource);

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
}*/

cPacket* RandomMeasureAction::run(cModule *re, qnicResources* resources) {
    EV<<"Measuring qubit now.\n";
    stationaryQubit *qubit = NULL;
    qubit = getQubit(/*re,*/ resources,qnic_type,qnic_id,partner,resource);

    if(qubit==nullptr){
        Error *pk = new Error;
        pk->setError_text("Qubit not found for measurement.");
        return pk;
    }else{

        measurement_outcome o = qubit->measure_density_independent();
        current_count++;

        /*Delete measured resource from the tracked list of resources.*/
        RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
        rule_engine->freeConsumedResource(qnic_id, qubit, qnic_type);
        /*Deleting done*/

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
