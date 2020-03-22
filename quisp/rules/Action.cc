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
    return (*rule_resources).size();
}

//required_index: 0 is the top one, 1 is the 2nd top one, and so on.
stationaryQubit* Action::getResource_fromTop(int required_index){
    stationaryQubit *pt = nullptr;

    for (auto it=(*rule_resources).begin(); it!=(*rule_resources).end(); ++it) {
        if(it->second->isLocked()){
            //Ignore locked resource
        }else if(resource_index == required_index && !it->second->isLocked()){
            pt = it->second;
            break;
        }else{
            resource_index++;
        }
    }
    return pt;
}

void Action::removeResource_fromRule(stationaryQubit *qubit){
    for (auto it =  (*rule_resources).begin(), next_it = (*rule_resources).begin(); it != (*rule_resources).end(); it = next_it){
          next_it = it; ++next_it;
          if (it->second == qubit){
              (*rule_resources).erase(it);
              break;
          }
    }
}

cPacket* SwappingAction::run(cModule *re){
    float success_probability = 1.0;

    stationaryQubit *left_qubit = nullptr;
    stationaryQubit *right_qubit = nullptr;

    left_qubit = getResource_fromTop(left_resource);
    right_qubit = getResource_fromTop(right_resource);

    if(left_qubit == nullptr|| right_qubit==nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource found!");
        return pk;
    }
    if(left_qnic_id < 0 || right_qnic_id < 0){
        Error *pk = new Error;
        pk->setError_text("QNICs are not found!");
        return pk;
    }

    // actual swapping operations
    stationaryQubit *right_partner_qubit = right_qubit->entangled_partner;
    stationaryQubit *left_partner_qubit = left_qubit->entangled_partner;
    // just swapping pointer.
    // swapper have no way to know this swapping is success or not.
    if(std::rand()/RAND_MAX < success_probability){
        right_partner_qubit->setEntangledPartnerInfo(left_partner_qubit);
        left_partner_qubit->setEntangledPartnerInfo(right_partner_qubit);

        removeResource_fromRule(left_qubit);
        removeResource_fromRule(right_qubit);
    }else{
        removeResource_fromRule(right_qubit);
        removeResource_fromRule(right_partner_qubit);
        removeResource_fromRule(right_qubit);
        removeResource_fromRule(right_partner_qubit);
    }
    // Currently, this function is able to return only one packet, but this action have to return 
    //  two nodes (left partner and right partner). once return information to rule engine, then, duplicate it.
    SwappingResult *pk = new SwappingResult;
    // no destination here. In RuleEngine, it's set.
    pk->setKind(4);
    pk->setRuleSet_id(ruleset_id);
    pk->setRule_id(rule_id);
    pk->setAction_index(action_index);

    // FIXME: These operations are corresponds to the result of operation.
    pk->setOperation_type_left(1); // operation type for left node
    pk->setOperation_type_right(1); // operation type for right node
    // These information are cropped in the RuleEngine.
    pk->setLeft_Dest(left_partner); // this might not require but just in case
    pk->setRight_Dest(right_partner);

    pk->setNew_partner_left(right_partner);
    pk->setNew_partner_qnic_index_left(right_qnic_id);
    pk->setNew_partner_qnic_type_left(right_qnic_type);
    pk->setNew_partner_qnic_address_left(right_qnic_address);
    pk->setMeasured_qubit_index_left(resource_index); // here is wrong;

    pk->setNew_partner_right(left_partner);
    pk->setNew_partner_qnic_index_right(left_qnic_id);
    pk->setNew_partner_qnic_type_right(left_qnic_type);
    pk->setNew_partner_qnic_address_right(left_qnic_address);
    pk->setMeasured_qubit_index_right(resource_index);
    return pk;
}

//Either Z or X purification.
cPacket* PurifyAction::run(cModule *re) {
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

    qubit->Lock(ruleset_id, rule_id, action_index);

    if(trash_qubit->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit);//Remove from resource list in this Rule.
    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
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



//Double error purification
cPacket* DoublePurifyAction::run(cModule *re) {
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

    qubit->Lock(ruleset_id, rule_id, action_index);

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




//Inveerted double error purification.
cPacket* DoublePurifyAction_inv::run(cModule *re) {
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

    qubit->Lock(ruleset_id, rule_id, action_index);

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




//Double selection single error (X error) purification.
cPacket* DoubleSelectionAction::run(cModule *re) {

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
    meas_Z = trash_qubit_Z->Zpurify(trash_qubit_X);//Error propagation only. Not based on density matrix

    qubit->Lock(ruleset_id, rule_id, action_index);

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


//Double selection single error (Z error) purification
cPacket* DoubleSelectionAction_inv::run(cModule *re) {

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
    meas_X = trash_qubit_X->Xpurify(trash_qubit_Z);//Error propagation only. Not based on density matrix

    qubit->Lock(ruleset_id, rule_id, action_index);

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

    stationaryQubit *qubit = nullptr;

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
        pk->setGOD_clean(o.GOD_clean);
        if(current_count==max_count){
                    pk->setFinish(simTime()-start);
                    pk->setMax_count(max_count);
        }
        return pk;
    }
}



//X purification, Z purification to trash_qubit_X Bell pair.
cPacket* DoubleSelectionDualAction::run(cModule *re) {

    stationaryQubit *qubit = nullptr;
    stationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_Z, *ds_trash_qubit_X = nullptr;

    qubit = getResource_fromTop(resource);
    trash_qubit_X = getResource_fromTop(trash_resource_X);
    trash_qubit_Z = getResource_fromTop(trash_resource_Z);
    ds_trash_qubit_X = getResource_fromTop(doubleselection_trash_resource_X);
    ds_trash_qubit_Z = getResource_fromTop(doubleselection_trash_resource_Z);

    if(qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || qubit == ds_trash_qubit_Z || trash_qubit_Z == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_X ||  ds_trash_qubit_Z == ds_trash_qubit_X){
        Error *pk = new Error;
        pk->setError_text("Qubit and Trash_qubit must be different.");
        return pk;
    }
    if(qubit==nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X==nullptr || ds_trash_qubit_Z==nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
        return pk;
    }
    bool meas_X, meas_Z, ds_meas_X, ds_meas_Z = false;

    meas_X = trash_qubit_X->Xpurify(qubit);//Error propagation only. Not based on density matrix
    ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

    meas_Z = trash_qubit_Z->Zpurify(qubit);//Error propagation only. Not based on density matrix
    ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

    qubit->Lock(ruleset_id, rule_id, action_index);

    if(trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(ds_trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        ds_trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        ds_trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(ds_trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        ds_trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        ds_trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
     }
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(trash_qubit_Z);//Remove from resource list in this Rule.
    removeResource_fromRule(ds_trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(ds_trash_qubit_Z);//Remove from resource list in this Rule.
    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
    rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);
    //Deleting done

    DS_DoublePurificationResult *pk = new DS_DoublePurificationResult;
    pk->setDestAddr(partner);
    pk->setKind(7);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setXOutput_is_plus(meas_X);
    pk->setZOutput_is_plus(meas_Z);
    pk->setDS_XOutput_is_plus(ds_meas_X);
    pk->setDS_ZOutput_is_plus(ds_meas_Z);
    pk->setEntangled_with(qubit);
    action_index++;
    return pk;
}





//Double selection double error (ZX error) purification
cPacket* DoubleSelectionDualAction_inv::run(cModule *re) {

    stationaryQubit *qubit = nullptr;
    stationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_Z, *ds_trash_qubit_X = nullptr;

    qubit = getResource_fromTop(resource);
    trash_qubit_X = getResource_fromTop(trash_resource_X);
    trash_qubit_Z = getResource_fromTop(trash_resource_Z);
    ds_trash_qubit_X = getResource_fromTop(doubleselection_trash_resource_X);
    ds_trash_qubit_Z = getResource_fromTop(doubleselection_trash_resource_Z);

    if(qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || qubit == ds_trash_qubit_Z || trash_qubit_Z == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_X ||  ds_trash_qubit_Z == ds_trash_qubit_X){
        Error *pk = new Error;
        pk->setError_text("Qubit and Trash_qubit must be different.");
        return pk;
    }
    if(qubit==nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X==nullptr || ds_trash_qubit_Z==nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
        return pk;
    }
    bool meas_X, meas_Z, ds_meas_X, ds_meas_Z = false;


    meas_Z = trash_qubit_Z->Zpurify(qubit);//Error propagation only. Not based on density matrix
    ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

    meas_X = trash_qubit_X->Xpurify(qubit);//Error propagation only. Not based on density matrix
    ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

    qubit->Lock(ruleset_id, rule_id, action_index);

    if(trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(ds_trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        ds_trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        ds_trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(ds_trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        ds_trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        ds_trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
     }
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(trash_qubit_Z);//Remove from resource list in this Rule.
    removeResource_fromRule(ds_trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(ds_trash_qubit_Z);//Remove from resource list in this Rule.
    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
    rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);
    //Deleting done

    DS_DoublePurificationResult *pk = new DS_DoublePurificationResult;
    pk->setDestAddr(partner);
    pk->setKind(7);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setXOutput_is_plus(meas_X);
    pk->setZOutput_is_plus(meas_Z);
    pk->setDS_XOutput_is_plus(ds_meas_X);
    pk->setDS_ZOutput_is_plus(ds_meas_Z);
    pk->setEntangled_with(qubit);
    action_index++;
    return pk;
}





//X purification, Z purification to trash_qubit_X Bell pair.
cPacket* DoubleSelectionDualActionSecond::run(cModule *re) {

    stationaryQubit *qubit = nullptr;
    stationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_X = nullptr;

    qubit = getResource_fromTop(resource);
    trash_qubit_X = getResource_fromTop(trash_resource_X);
    trash_qubit_Z = getResource_fromTop(trash_resource_Z);
    ds_trash_qubit_X = getResource_fromTop(doubleselection_trash_resource_X);

    if(qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_X){
        Error *pk = new Error;
        pk->setError_text("Qubit and Trash_qubit must be different.");
        return pk;
    }
    if(qubit==nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X==nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
        return pk;
    }
    bool meas_X, meas_Z, ds_meas_X = false;

    meas_X = trash_qubit_X->Xpurify(qubit);//Error propagation only. Not based on density matrix

    meas_Z = trash_qubit_Z->Zpurify(qubit);//Error propagation only. Not based on density matrix
    ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

    qubit->Lock(ruleset_id, rule_id, action_index);

    if(trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(ds_trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        ds_trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        ds_trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
     }
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(trash_qubit_Z);//Remove from resource list in this Rule.
    removeResource_fromRule(ds_trash_qubit_X);//Remove from resource list in this Rule.

    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
    rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);
    //Deleting done

    DS_DoublePurificationSecondResult *pk = new DS_DoublePurificationSecondResult;
    pk->setDestAddr(partner);
    pk->setKind(7);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setXOutput_is_plus(meas_X);
    pk->setZOutput_is_plus(meas_Z);
    pk->setDS_Output_is_plus(ds_meas_X);

    pk->setEntangled_with(qubit);
    action_index++;
    return pk;
}







//Double selection double error (ZX error) purification
cPacket* DoubleSelectionDualActionSecond_inv::run(cModule *re) {

    stationaryQubit *qubit = nullptr;
    stationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_Z = nullptr;

    qubit = getResource_fromTop(resource);
    trash_qubit_X = getResource_fromTop(trash_resource_X);
    trash_qubit_Z = getResource_fromTop(trash_resource_Z);
    ds_trash_qubit_Z = getResource_fromTop(doubleselection_trash_resource_Z);

    if(qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_Z){
        Error *pk = new Error;
        pk->setError_text("Qubit and Trash_qubit must be different.");
        return pk;
    }
    if(qubit==nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr  || ds_trash_qubit_Z==nullptr){
        Error *pk = new Error;
        pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
        return pk;
    }
    bool meas_X, meas_Z, ds_meas_Z = false;


    meas_Z = trash_qubit_Z->Zpurify(qubit);//Error propagation only. Not based on density matrix

    meas_X = trash_qubit_X->Xpurify(qubit);//Error propagation only. Not based on density matrix
    ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

    qubit->Lock(ruleset_id, rule_id, action_index);

    if(trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }
    if(trash_qubit_X->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        trash_qubit_X->entangled_partner->entangled_partner=nullptr;//Break entanglement.
    }

    if(ds_trash_qubit_Z->entangled_partner!=nullptr){//Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
        ds_trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true; //For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
        ds_trash_qubit_Z->entangled_partner->entangled_partner=nullptr;//Break entanglement.
     }
    //Delete measured resource from the tracked list of resources.
    removeResource_fromRule(trash_qubit_X);//Remove from resource list in this Rule.
    removeResource_fromRule(trash_qubit_Z);//Remove from resource list in this Rule.
    removeResource_fromRule(ds_trash_qubit_Z);//Remove from resource list in this Rule.

    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);//Remove from entangled resource list.
    rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
    rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);
    //Deleting done

    DS_DoublePurificationSecondResult *pk = new DS_DoublePurificationSecondResult;
    pk->setDestAddr(partner);
    pk->setKind(7);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setXOutput_is_plus(meas_X);
    pk->setZOutput_is_plus(meas_Z);
    pk->setDS_Output_is_plus(ds_meas_Z);
    pk->setEntangled_with(qubit);
    action_index++;
    return pk;
}







} // namespace rules
} // namespace quisp
