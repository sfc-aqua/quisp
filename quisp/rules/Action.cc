/** \file Action.cc
 *
 *  \authors cldurand,takaakimatsuo
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
            //qubit->Lock(ruleset_id, rule_id);
            //trash_qubit->Lock(static_action_id+purification_count);//You may not need this because this will be trashed soon anyway.
            /*purification_count++;
            bool measurement_outcome_error = qubit->purify(trash_qubit);//Only error propagation. No density matrix calculation.

            //Delete measured resource from the tracked list of resources.
            RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
            rule_engine->freeConsumedResource(qnic_id, trash_qubit, qnic_type);
            //Deleting done*/
            return 0;
        }
    }else{
        Error *pk = new Error;
        pk->setError_text("Qubits not found for purification.");
        return pk;
    }
    // error
}



cPacket* RandomMeasureAction::run(cModule *re, qnicResources* resources) {
    EV<<"Measuring qubit now.\n";
    stationaryQubit *qubit = NULL;
    //qubit = getQubit(/*re,*/ resources,qnic_type,qnic_id,partner,resource);
    //qubit = getUnLockedQubit_fromTop(resources,qnic_type,qnic_id,partner,resource);
    qubit = getResource_fromTop(resource);

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
        if(current_count==max_count){
            pk->setFinish(simTime()-start);
        }
        return pk;
    }
}

int Action::checkNumResource(){
    //std::cout << "Num resource = " << (*rule_resources).size()<<"\n";
    return (*rule_resources).size();
}

//required_index: 0 is the top one, 1 is the 2nd top one, and so on.
stationaryQubit* Action::getResource_fromTop(int required_index){
    int resource_index = 0;
    stationaryQubit *pt = nullptr;
    for (auto it=(*rule_resources).begin(); it!=(*rule_resources).end(); ++it) {
        if(it->second->isLocked()){
            //Ignore locked resource
        }else if(resource_index == required_index && !it->second->isLocked()){
            //std::cout<<"Rule: Let's use this qubit!"<<it->second<<", isBusy = "<<it->second->isBusy<<"\n";
            pt = it->second;
            break;
        }else{
            resource_index++;
        }
    }
    return pt;
}

void Action::removeResource_fromRule(stationaryQubit *qubit){
    //std::cout<<"[Action] Before: "<<(*rule_resources).size()<<"\n";
    for (auto it =  (*rule_resources).begin(), next_it =  (*rule_resources).begin(); it !=  (*rule_resources).end(); it = next_it){
          next_it = it; ++next_it;
          if (it->second == qubit){
              //std::cout<<"Rule: Let's delete this qubit!"<<it->second<<", isBusy = "<<it->second->isBusy<<"\n";
              (*rule_resources).erase(it);    // or "it = m.erase(it)" since C++11
              break;
          }
    }
    //std::cout<<"[Action] After: "<<(*rule_resources).size()<<"\n";
}

cPacket* PurifyAction::run(cModule *re) {
    std::cout<<"Purification!\n";
    stationaryQubit *qubit = nullptr;
    stationaryQubit *trash_qubit = nullptr;
    qubit = getResource_fromTop(resource);
    trash_qubit = getResource_fromTop(trash_resource);
    if(qubit == trash_qubit){
        Error *pk = new Error;
        pk->setError_text("Qubit and Trash_qubit must be different.");
        return pk;
    }
    if(qubit==nullptr || trash_qubit == nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
        return pk;
    }
    bool meas = trash_qubit->purify(qubit);//Error propagation only. Not based on density matrix
    qubit->Lock(ruleset_id, rule_id, action_index);
    //std::cout<<"Locked"<<qubit<<", trashed"<<trash_qubit<<"\n";

    //Delete measured resource from the tracked list of resources.
   removeResource_fromRule(trash_qubit);//Remove from resource list in this Rule.
   RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
   rule_engine->freeConsumedResource(qnic_id, trash_qubit, qnic_type);//Remove from entangled resource list.
   //Deleting done



   PurificationResult *pk = new PurificationResult;
   pk->setDestAddr(partner);
   pk->setAction_index(action_index);
   pk->setRule_id(rule_id);
   pk->setRuleset_id(ruleset_id);
   pk->setOutput_is_plus(meas);
   action_index++;
   return pk;
}


cPacket* RandomMeasureAction::run(cModule *re) {

    //std::cout<<"Measuring qubit now.\n";
    stationaryQubit *qubit = nullptr;
    //qubit = getQubit(/*re,*/ resources,qnic_type,qnic_id,partner,resource);
    qubit = getResource_fromTop(resource);



    if(qubit==nullptr){
        Error *pk = new Error;
        pk->setError_text("Qubit not found for measurement.");
        return pk;
    }else{

        measurement_outcome o = qubit->measure_density_independent();
        current_count++;

        //Delete measured resource from the tracked list of resources.
        removeResource_fromRule(qubit);//Remove from resource list in this Rule.
        RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
        rule_engine->freeConsumedResource(qnic_id, qubit, qnic_type);//Remove from entangled resource list.
        //Deleting done

        LinkTomographyResult *pk = new LinkTomographyResult;
        pk->setSrcAddr(src);
        pk->setDestAddr(dst);
        pk->setCount_id(current_count);
        pk->setPartner_address(src);//Partner's partner is self/src
        pk->setKind(6);
        pk->setOutput_is_plus(o.outcome_is_plus);
        pk->setBasis(o.basis);
        if(current_count==max_count){
                    pk->setFinish(simTime()-start);
        }
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
