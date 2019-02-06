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
            //std::cout<<"node["<<it->second->node_address<<"] Rule: Let's use this qubit!"<<it->second<<", isLocked = "<<it->second->isLocked()<<"\n";
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

//Either Z or X purification.
cPacket* PurifyAction::run(cModule *re) {
    //std::cout<<"Purification!\n";
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
    bool meas = false;
    if(X && !Z)
        meas = trash_qubit->Xpurify(qubit);//Error propagation only. Not based on density matrix
    else if (!X && Z)
        meas = trash_qubit->Zpurify(qubit);//Error propagation only. Not based on density matrix

    //std::cout<<"node["<<qubit->node_address<<"][before]Kept "<<qubit<<" locked="<<qubit->isLocked()<<", trashed"<<trash_qubit<<" locked="<<trash_qubit->isLocked()<<"\n";
    qubit->Lock(ruleset_id, rule_id, action_index);
    //std::cout<<"node["<<qubit->node_address<<"]after]Kept "<<qubit<<" locked="<<qubit->isLocked()<<", trashed"<<trash_qubit<<" locked="<<trash_qubit->isLocked()<<"\n";

    if(trash_qubit->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit);//Remove from resource list in this Rule.
    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    //std::cout<<"node["<<qubit->node_address<<"]Purification calling freeConsumedResource"<<trash_qubit<<"\n";
    rule_engine->freeConsumedResource(qnic_id, trash_qubit, qnic_type);//Remove from entangled resource list.
    //Deleting done

    PurificationResult *pk = new PurificationResult;
    pk->setDestAddr(partner);
    pk->setKind(7);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setOutput_is_plus(meas);
    pk->setEntangled_with(qubit);
    action_index++;
    return pk;
}



//X and Z purification, simultaneously.
cPacket* DoublePurifyAction::run(cModule *re) {

    //std::cout<<"DoublePurification!\n";
    stationaryQubit *qubit = nullptr;
    stationaryQubit *trash_qubit_Z, *trash_qubit_X = nullptr;

    qubit = getResource_fromTop(resource);
    trash_qubit_X = getResource_fromTop(trash_resource_X);
    trash_qubit_Z = getResource_fromTop(trash_resource_Z);

    if(qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X){
        Error *pk = new Error;
        pk->setError_text("Qubit and Trash_qubit must be different.");
        return pk;
    }
    if(qubit==nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
        return pk;
    }
    bool meas_X, meas_Z = false;

    meas_X = trash_qubit_X->Xpurify(qubit);//Error propagation only. Not based on density matrix
    meas_Z = trash_qubit_Z->Zpurify(qubit);//Error propagation only. Not based on density matrix

    //std::cout<<"node["<<qubit->node_address<<"][before]Kept "<<qubit<<" locked="<<qubit->isLocked()<<", trashed"<<trash_qubit<<" locked="<<trash_qubit->isLocked()<<"\n";
    qubit->Lock(ruleset_id, rule_id, action_index);
    //std::cout<<"node["<<qubit->node_address<<"]after]Kept "<<qubit<<" locked="<<qubit->isLocked()<<", trashed"<<trash_qubit<<" locked="<<trash_qubit->isLocked()<<"\n";

    if(trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
		
        trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
	}
    if(trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
	    
        trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
	}
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(trash_qubit_Z);//Remove from resource list in this Rule.
    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    //std::cout<<"node["<<qubit->node_address<<"]Purification calling freeConsumedResource"<<trash_qubit<<"\n";
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
    //Deleting done

    DoublePurificationResult *pk = new DoublePurificationResult;
    pk->setDestAddr(partner);
    pk->setKind(7);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setXOutput_is_plus(meas_X);
    pk->setZOutput_is_plus(meas_Z);
    pk->setEntangled_with(qubit);
    action_index++;
    return pk;
}




//X and Z purification, simultaneously.
cPacket* DoublePurifyAction_inv::run(cModule *re) {

    //std::cout<<"DoublePurification!\n";
    stationaryQubit *qubit = nullptr;
    stationaryQubit *trash_qubit_Z, *trash_qubit_X = nullptr;

    qubit = getResource_fromTop(resource);
    trash_qubit_X = getResource_fromTop(trash_resource_X);
    trash_qubit_Z = getResource_fromTop(trash_resource_Z);

    if(qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X){
        Error *pk = new Error;
        pk->setError_text("Qubit and Trash_qubit must be different.");
        return pk;
    }
    if(qubit==nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
        return pk;
    }
    bool meas_X, meas_Z = false;


    meas_Z = trash_qubit_Z->Zpurify(qubit);//Error propagation only. Not based on density matrix
    meas_X = trash_qubit_X->Xpurify(qubit);//Error propagation only. Not based on density matrix

    //std::cout<<"node["<<qubit->node_address<<"][before]Kept "<<qubit<<" locked="<<qubit->isLocked()<<", trashed"<<trash_qubit<<" locked="<<trash_qubit->isLocked()<<"\n";
    qubit->Lock(ruleset_id, rule_id, action_index);
    //std::cout<<"node["<<qubit->node_address<<"]after]Kept "<<qubit<<" locked="<<qubit->isLocked()<<", trashed"<<trash_qubit<<" locked="<<trash_qubit->isLocked()<<"\n";

    if(trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.

        trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.

        trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(trash_qubit_Z);//Remove from resource list in this Rule.
    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    //std::cout<<"node["<<qubit->node_address<<"]Purification calling freeConsumedResource"<<trash_qubit<<"\n";
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
    //Deleting done

    DoublePurificationResult *pk = new DoublePurificationResult;
    pk->setDestAddr(partner);
    pk->setKind(7);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setXOutput_is_plus(meas_X);
    pk->setZOutput_is_plus(meas_Z);
    pk->setEntangled_with(qubit);
    action_index++;
    return pk;
}


cPacket* RandomMeasureAction::run(cModule *re) {

    //std::cout<<"Measuring qubit now.\n";
    stationaryQubit *qubit = nullptr;
    //qubit = getQubit(/*re,*/ resources,qnic_type,qnic_id,partner,resource);

    /*for (auto it=(*rule_resources).begin(); it!=(*rule_resources).end(); ++it) {
            if(it->second->node_address==2 || it->second->node_address == 1){
               if(it->second->isLocked())
                   std::cout<<"Measurement: node["<<it->second->node_address<<"]"<<ruleset_id<<"[*resources] = "<<it->second<<"\n";
               else
                   std::cout<<"Measurement: node["<<it->second->node_address<<"]"<<ruleset_id<<"[resources] = "<<it->second<<"\n";
            }
           }
    */


    qubit = getResource_fromTop(resource);
	

    if(qubit==nullptr){
        Error *pk = new Error;
        pk->setError_text("Qubit not found for measurement.");
        return pk;
    }else{

        measurement_outcome o = qubit->measure_density_independent();
        current_count++;

        //EV<<"Measuring "<<qubit<<" in node["<<qubit->node_address<<"] qnic["<<qubit->qnic_index<<"] qnic_type["<<qubit->qnic_type<<"] \n";
        //Delete measured resource from the tracked list of resources.
        removeResource_fromRule(qubit);//Remove from resource list in this Rule.
        RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
        //std::cout<<"Measure calling freeConsumedResource"<<qubit<<"\n";
        rule_engine->freeConsumedResource(qnic_id, qubit, qnic_type);//Remove from entangled resource list.
        //Deleting done



       /* for (auto it=(*rule_resources).begin(); it!=(*rule_resources).end(); ++it) {
                if(it->second->node_address==2 || it->second->node_address == 1){
                   if(it->second->isLocked())
                       std::cout<<"Measurement: node["<<it->second->node_address<<"]"<<ruleset_id<<"[*resources] = "<<it->second<<"\n";
                   else
                       std::cout<<"Measurement: node["<<it->second->node_address<<"]"<<ruleset_id<<"[resources] = "<<it->second<<"\n";
                }
               }
        */


        LinkTomographyResult *pk = new LinkTomographyResult;
        pk->setSrcAddr(src);
        pk->setDestAddr(dst);
        pk->setCount_id(current_count);
        pk->setPartner_address(src);//Partner's partner is self/src
        pk->setKind(6);
        pk->setOutput_is_plus(o.outcome_is_plus);
        pk->setBasis(o.basis);
        pk->setGOD_clean(o.GOD_clean);
        if(current_count==max_count){
                    pk->setFinish(simTime()-start);
                    pk->setMax_count(max_count);
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
