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
    int resource_index = 0;
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
    bool isSuccess = false

    stationaryQubit *qubit = nullptr;


    SwappingResult *pk = new SwappingResult;
    pk->setDestAddr(left_partner); // FIXME
    pk->setKind(2);
    pk->setAction_index(action_index);
    pk->setRule_id(rule_id);
    pk->setRuleset_id(ruleset_id);
    pk->setIsSuccess();
    action_index++;
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
