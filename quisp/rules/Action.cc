/** \file Action.cc
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#include "Action.h"
//#include "../modules/RuleEngine.h"
#include <omnetpp.h>
#include "classical_messages_m.h"
#include "tools.h"
#include "../modules/QNIC/StationaryQubit/StationaryQubit.h"
#include <tuple>
#include <map>
#include <iostream>
#include "bits/stdc++.h"
using namespace std;
#include <vector>
using std::begin;
using std::end;

namespace quisp {
namespace rules {

int Action::checkNumResource() { return (*rule_resources).size(); }

// required_index: 0 is the top one, 1 is the 2nd top one, and so on.
StationaryQubit *Action::getResource_fromTop(int required_index) {
  int resource_index = 0;
  StationaryQubit *pt = nullptr;

  for (auto it = (*rule_resources).begin(); it != (*rule_resources).end(); ++it) {
    if (it->second->isLocked()) {
      // Ignore locked resource
    } else if (resource_index == required_index && !it->second->isLocked()) {
      pt = it->second;
      break;
    } else {
      resource_index++;
    }
  }
  return pt;
}

StationaryQubit *Action::getResource_fromTop_with_partner(int required_index, int partner) {
  // here
  int resource_index = 0;
  StationaryQubit *pt = nullptr;
  // EV<<"===========================================\n";
  // for (auto it=(*rule_resources).begin(); it!=(*rule_resources).end(); ++it) {
  //     EV<<"hey!"<<it->first<<"\n";
  // }
  // EV<<"===========================================\n";

  for (auto it = (*rule_resources).begin(); it != (*rule_resources).end(); ++it) {
    if (it->second->isLocked()) {
      // Ignore locked resource
    } else if (it->first == partner && !it->second->isLocked()) {
      pt = it->second;
      break;
    } else {
      resource_index++;
    }
  }
  return pt;
}

void Action::removeResource_fromRule(StationaryQubit *qubit) {
  for (auto it = (*rule_resources).begin(), next_it = (*rule_resources).begin(); it != (*rule_resources).end(); it = next_it) {
    next_it = it;
    ++next_it;
    if (it->second == qubit) {
      (*rule_resources).erase(it);
      break;
    }
  }
}

// TODO: completely mixed
cPacket *SwappingAction::run(cModule *re) {
  float success_probability = 1.0;

  StationaryQubit *left_qubit = nullptr;
  StationaryQubit *right_qubit = nullptr;

  left_qubit = getResource_fromTop_with_partner(left_resource, left_partner);
  right_qubit = getResource_fromTop_with_partner(right_resource, right_partner);

  if (left_qubit == nullptr || right_qubit == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource found! This shouldn't happen!");
    return pk;
  }
  if (left_qnic_id < 0 || right_qnic_id < 0) {
    Error *pk = new Error;
    pk->setError_text("QNICs are not found!");
    return pk;
  }

  // actual swapping operations
  StationaryQubit *right_partner_qubit = right_qubit->entangled_partner;
  StationaryQubit *left_partner_qubit = left_qubit->entangled_partner;
  // just swapping pointer.
  // swapper have no way to know this swapping is success or not.
  // bell measurement
  left_qubit->Hadamard_gate();
  right_qubit->CNOT_gate(left_qubit);

  // TODO This is a little bit cheating. This must be tracked!
  int lindex = left_partner_qubit->stationaryQubit_address;
  int rindex = right_partner_qubit->stationaryQubit_address;

  bool left_measure = left_qubit->measure_Z();
  bool right_measure = right_qubit->measure_Z();

  int operation_type_left, operation_type_right;

  if (!left_measure && !right_measure) {
    EV << "operation type 0, operation left I, operation right I\n";
    operation_type_left = 0;
    operation_type_right = 0;
  } else if (!left_measure && right_measure) {
    EV << "operation type 1, operation left I, operation right X\n";
    operation_type_left = 0;
    operation_type_right = 1;
  } else if (left_measure && !right_measure) {
    EV << "operation type 2, operation left Z, operation right I\n";
    operation_type_left = 2;
    operation_type_right = 0;
  } else if (left_measure && right_measure) {
    EV << "operation type 3, operation left Z, operation right X\n";
    operation_type_left = 2;
    operation_type_right = 1;
  }
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  if (std::rand() / RAND_MAX < success_probability) {
    right_partner_qubit->setEntangledPartnerInfo(left_partner_qubit);
    left_partner_qubit->setEntangledPartnerInfo(right_partner_qubit);

  } else {  // this might be wrong
    // removeResource_fromRule(left_partner_qubit);
    // removeResource_fromRule(right_partner_qubit);
    // TODO CHECK is this correct?
    // rule_engine->freeConsumedResource(left_qnic_id, right_partner_qubit, right_qnic_type);
    // rule_engine->freeConsumedResource(right_qnic_id, left_partner_qubit, left_qnic_type);
    left_partner_qubit->isBusy = false;
    right_partner_qubit->isBusy = false;
  }
  removeResource_fromRule(left_qubit);
  removeResource_fromRule(right_qubit);
  // This might not be good
  left_qubit->isBusy = false;
  right_qubit->isBusy = false;
  // rule_engine->freeConsumedResource(self_left_qnic_id, right_qubit, self_left_qnic_type);
  // rule_engine->freeConsumedResource(self_right_qnic_id, left_qubit, self_right_qnic_type);
  // Currently, this function is able to return only one packet, but this action have to return
  //  two nodes (left partner and right partner). once return information to rule engine, then, duplicate it.
  SwappingResult *pk = new SwappingResult;
  // no destination here. In RuleEngine, it's set.
  // this setKind() doesn't seem to have any effect; set instead in void RuleEngine::traverseThroughAllProcesses2()
  pk->setKind(5);
  pk->setRuleSet_id(ruleset_id);
  pk->setRule_id(rule_id);
  pk->setAction_index(action_index);

  // FIXME: These operations are corresponds to the result of operation.
  pk->setOperation_type_left(operation_type_left);  // operation type for left node
  pk->setOperation_type_right(operation_type_right);  // operation type for right node
  // These information are cropped in the RuleEngine.
  pk->setLeft_Dest(left_partner);  // this might not require but just in case
  pk->setRight_Dest(right_partner);

  pk->setNew_partner_left(right_partner);
  pk->setNew_partner_qnic_index_left(right_qnic_id);
  pk->setNew_partner_qnic_type_left(right_qnic_type);
  pk->setNew_partner_qnic_address_left(right_qnic_address);
  pk->setMeasured_qubit_index_left(lindex);  // here is wrong;

  pk->setNew_partner_right(left_partner);
  pk->setNew_partner_qnic_index_right(left_qnic_id);
  pk->setNew_partner_qnic_type_right(left_qnic_type);
  pk->setNew_partner_qnic_address_right(left_qnic_address);
  pk->setMeasured_qubit_index_right(rindex);
  return pk;
}

// Either Z or X purification.
cPacket *PurifyAction::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit = getResource_fromTop(trash_resource);

  if (qubit == trash_qubit) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas = false;
  if (X && !Z)
    meas = trash_qubit->Xpurify(qubit);  // Error propagation only. Not based on density matrix
  else if (!X && Z)
    meas = trash_qubit->Zpurify(qubit);  // Error propagation only. Not based on density matrix

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;

    // Break entanglement.
    trash_qubit->entangled_partner->entangled_partner = nullptr;
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit);  // Remove from resource list in this Rule.
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit, qnic_type);  // Remove from entangled resource list.
  // Deleting done

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

// Double error purification
cPacket *DoublePurifyAction::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z = false;

  meas_X = trash_qubit_X->Xpurify(qubit);  // Error propagation only. Not based on density matrix
  meas_Z = trash_qubit_Z->Zpurify(qubit);  // Error propagation only. Not based on density matrix

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_Z->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_X->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }

  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  // Deleting done

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

// Inveerted double error purification.
cPacket *DoublePurifyActionInv::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z = false;

  meas_Z = trash_qubit_Z->Zpurify(qubit);  // Error propagation only. Not based on density matrix
  meas_X = trash_qubit_X->Xpurify(qubit);  // Error propagation only. Not based on density matrix

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_Z->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_X->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }

  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  // Deleting done

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

// Double selection single error (X error) purification.
cPacket *DoubleSelectionAction::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z = false;

  meas_X = trash_qubit_X->Xpurify(qubit);  // Error propagation only. Not based on density matrix
  meas_Z = trash_qubit_Z->Zpurify(trash_qubit_X);  // Error propagation only. Not based on density matrix

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_Z->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_X->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  // Deleting done

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

// Double selection single error (Z error) purification
cPacket *DoubleSelectionActionInv::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z = false;

  meas_Z = trash_qubit_Z->Zpurify(qubit);  // Error propagation only. Not based on density matrix
  meas_X = trash_qubit_X->Xpurify(trash_qubit_Z);  // Error propagation only. Not based on density matrix

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_Z->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }

  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_X->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  // Deleting done

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

cPacket *RandomMeasureAction::run(cModule *re) {
  StationaryQubit *qubit = nullptr;

  qubit = getResource_fromTop_with_partner(resource, partner);

  if (qubit == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Qubit not found for measurement.");
    return pk;
  } else {
    measurement_outcome o = qubit->measure_density_independent();
    current_count++;

    // Delete measured resource from the tracked list of resources.
    removeResource_fromRule(qubit);  // Remove from resource list in this Rule.
    RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
    rule_engine->freeConsumedResource(qnic_id, qubit, qnic_type);  // Remove from entangled resource list.
    // Deleting done

    LinkTomographyResult *pk = new LinkTomographyResult;
    pk->setSrcAddr(src);
    pk->setDestAddr(dst);
    pk->setCount_id(current_count);
    pk->setPartner_address(src);  // Partner's partner is self/src
    pk->setKind(6);
    pk->setOutput_is_plus(o.outcome_is_plus);
    pk->setBasis(o.basis);
    pk->setGOD_clean(o.GOD_clean);
    if (current_count == max_count) {
      pk->setFinish(simTime() - start);
      pk->setMax_count(max_count);
    }
    return pk;
  }
}

// X purification, Z purification to trash_qubit_X Bell pair.
cPacket *DoubleSelectionDualAction::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_Z, *ds_trash_qubit_X = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);
  ds_trash_qubit_X = getResource_fromTop(doubleselection_trash_resource_X);
  ds_trash_qubit_Z = getResource_fromTop(doubleselection_trash_resource_Z);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || qubit == ds_trash_qubit_Z ||
      trash_qubit_Z == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_X || ds_trash_qubit_Z == ds_trash_qubit_X) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X == nullptr || ds_trash_qubit_Z == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z, ds_meas_X, ds_meas_Z = false;

  meas_X = trash_qubit_X->Xpurify(qubit);  // Error propagation only. Not based on density matrix
  ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

  meas_Z = trash_qubit_Z->Zpurify(qubit);  // Error propagation only. Not based on density matrix
  ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

  qubit->Lock(ruleset_id, rule_id, action_index);
  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_Z->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }
  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_X->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;
  }
  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (ds_trash_qubit_X->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    ds_trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    ds_trash_qubit_X->entangled_partner->entangled_partner = nullptr;
  }
  // Trash qubit has been measured. Now, break the entanglement info of the partner.
  // There is no need to overwrite its density matrix since we are only tracking errors.
  if (ds_trash_qubit_Z->entangled_partner != nullptr) {
    // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored.
    // This is not true if the partner did a purification, because this does not update the densitymatrix as all we do is track error.
    ds_trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    // Break entanglement.
    ds_trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  removeResource_fromRule(ds_trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(ds_trash_qubit_Z);  // Remove from resource list in this Rule.
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);
  // Deleting done

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

// Double selection double error (ZX error) purification
cPacket *DoubleSelectionDualActionInv::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_Z, *ds_trash_qubit_X = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);
  ds_trash_qubit_X = getResource_fromTop(doubleselection_trash_resource_X);
  ds_trash_qubit_Z = getResource_fromTop(doubleselection_trash_resource_Z);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || qubit == ds_trash_qubit_Z ||
      trash_qubit_Z == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_X || ds_trash_qubit_Z == ds_trash_qubit_X) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X == nullptr || ds_trash_qubit_Z == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z, ds_meas_X, ds_meas_Z = false;

  meas_Z = trash_qubit_Z->Zpurify(qubit);  // Error propagation only. Not based on density matrix
  ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

  meas_X = trash_qubit_X->Xpurify(qubit);  // Error propagation only. Not based on density matrix
  ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

  qubit->Lock(ruleset_id, rule_id, action_index);

  if (trash_qubit_Z->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density
                                                      // matrix since we are only tracking errors.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  if (trash_qubit_X->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density
                                                      // matrix since we are only tracking errors.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  if (ds_trash_qubit_X->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its
                                                         // density matrix since we are only tracking errors.
    ds_trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    ds_trash_qubit_X->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  if (ds_trash_qubit_Z->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its
                                                         // density matrix since we are only tracking errors.
    ds_trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    ds_trash_qubit_Z->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  removeResource_fromRule(ds_trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(ds_trash_qubit_Z);  // Remove from resource list in this Rule.
  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);
  // Deleting done

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

// X purification, Z purification to trash_qubit_X Bell pair.
cPacket *DoubleSelectionDualActionSecond::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_X = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);
  ds_trash_qubit_X = getResource_fromTop(doubleselection_trash_resource_X);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_X) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z, ds_meas_X = false;

  meas_X = trash_qubit_X->Xpurify(qubit);  // Error propagation only. Not based on density matrix

  meas_Z = trash_qubit_Z->Zpurify(qubit);  // Error propagation only. Not based on density matrix
  ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

  qubit->Lock(ruleset_id, rule_id, action_index);

  if (trash_qubit_Z->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density
                                                      // matrix since we are only tracking errors.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  if (trash_qubit_X->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density
                                                      // matrix since we are only tracking errors.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  if (ds_trash_qubit_X->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its
                                                         // density matrix since we are only tracking errors.
    ds_trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    ds_trash_qubit_X->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  removeResource_fromRule(ds_trash_qubit_X);  // Remove from resource list in this Rule.

  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);
  // Deleting done

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

// Double selection double error (ZX error) purification
cPacket *DoubleSelectionDualActionSecondInv::run(cModule *re) {
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit_Z, *trash_qubit_X, *ds_trash_qubit_Z = nullptr;

  qubit = getResource_fromTop(resource);
  trash_qubit_X = getResource_fromTop(trash_resource_X);
  trash_qubit_Z = getResource_fromTop(trash_resource_Z);
  ds_trash_qubit_Z = getResource_fromTop(doubleselection_trash_resource_Z);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_Z) {
    Error *pk = new Error;
    pk->setError_text("Qubit and Trash_qubit must be different.");
    return pk;
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_Z == nullptr) {
    Error *pk = new Error;
    pk->setError_text("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
    return pk;
  }
  bool meas_X, meas_Z, ds_meas_Z = false;

  meas_Z = trash_qubit_Z->Zpurify(qubit);  // Error propagation only. Not based on density matrix

  meas_X = trash_qubit_X->Xpurify(qubit);  // Error propagation only. Not based on density matrix
  ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

  qubit->Lock(ruleset_id, rule_id, action_index);

  if (trash_qubit_Z->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density
                                                      // matrix since we are only tracking errors.
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  if (trash_qubit_X->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density
                                                      // matrix since we are only tracking errors.
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }

  if (ds_trash_qubit_Z->entangled_partner != nullptr) {  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its
                                                         // density matrix since we are only tracking errors.
    ds_trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok =
        true;  // For debugging. Code in RuleEngine makes sure that any new resource is either entangled or has a density matrix stored. This is not true if the partner did a
               // purification, because this does not update the densitymatrix as all we do is track error.
    ds_trash_qubit_Z->entangled_partner->entangled_partner = nullptr;  // Break entanglement.
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);  // Remove from resource list in this Rule.
  removeResource_fromRule(trash_qubit_Z);  // Remove from resource list in this Rule.
  removeResource_fromRule(ds_trash_qubit_Z);  // Remove from resource list in this Rule.

  RuleEngine *rule_engine = check_and_cast<RuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);  // Remove from entangled resource list.
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);
  // Deleting done

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



// //ABSA actions starts here 
// vector<int> slicing(vector<int>& arr, int X, int Y)
// {

//     // Starting and Ending iterators
//     auto start = arr.begin() + X;
//     auto end = arr.begin() + Y + 1;

//     // To store the sliced vector
//     vector<int> result(Y - X + 1);

//     // Copy vector using copy function()
//     copy(start, end, result.begin());

//     // Return the final sliced vector
//     return result;
// }


// //Action 2A for the basis
// int initializeBasisAction() {
//   int basis = 3; //bell
//   return basis;
// }

// //Action 2B for the bell
// bool initializeBellAction() {
//   bool successBell  = false;
//   return successBell;
// }

// //Action 2C for the encodes
// //std::outcomeList<int*, std::successBell<bool
// //encode is like m?
// std::map<int, vector<int>> initializeEncode(int encode,int* bv){
//   //case encodex
//   //int arr[] = { 2,3,2 };
//   //int encode = 1;
//   int e[2];
//   if(encode == 1){
//      e[0] = 1;
//      e[1] = 2;
//   }
//   else{
//       e[0] = 2;
//       e[1] = 1;
//   }
//   std::vector < int > vecOfint(bv, bv + sizeof(bv) / sizeof(int));
//     //for (int str: vecOfStr){
//     //  std::cout << str << std::endl;}
//   std::map<int, vector<int>> encodedTree;
//   std::vector<int> vec(0);
//   for (int i=0; i<vecOfint.size(); i++){
//     if (i == 0){
//       int s = vecOfint[0];
//       std::cout << e[0];
// //      std::vector<int> vec(s, e[0]);
//       vec.resize(s, e[0]);
//     }

//     else if (i%2 == 0){
//       std::vector<int> temp = slicing(vecOfint, 0, i+1);
//       auto multi = std::accumulate(begin(temp), end(temp), 1, std::multiplies<int>());
//       //std::vector<int> vec(multi, e[0]);
//       vec.resize(multi, e[0]);
//     }

//     else{
//       std::vector<int> temp = slicing(vecOfint, 0, i+1);
//       auto multi = std::accumulate(begin(temp), end(temp), 1, std::multiplies<int>());
//       //std:vector<int> vec(multi, e[1]);
//       vec.resize(multi, e[1]);
//     }

//     encodedTree.insert(std::make_pair(i+1, vec));
//   }
//   return encodedTree;
// }

// //Action 2D for the msg
// bool initializeMsgAction(){
//   bool msgSent = false;
//   return msgSent;
// }


// //Action 5
// std::map<int, tuple<int, bool, bool>> measureAction(int* basis){
//   StationaryQubit* left_qubit = nullptr;
//   StationaryQubit* right_qubit = nullptr;
//   //the key is the name of qubit while the values are the basis and outcomes
//   std::map<int, tuple<int, bool, bool>> outcomeList;
//   for(int i=0; i<sizeof(basis);i++){
//     left_qubit = getResource_fromTop_with_partner(left_resource, left_partner);
//     right_qubit = getResource_fromTop_with_partner(right_resource, right_partner);
//     bool outcome_right, outcome_left;
//     if (basis[i] == 1){
//       outcome_right = right_qubit -> measure_X();
//       outcome_left = left_qubit -> measure_X();
//     } else if (basis[i] == 2){
//       outcome_right = right_qubit -> measure_Z();
//       outcome_left = left_qubit -> measure_Z();
//     } else if (basis[i] == 3){
//       left_qubit->Hadamard_gate();
//       right_qubit->CNOT_gate(left_qubit);
//       outcome_left = left_qubit->measure_Z();
//       outcome_right = right_qubit->measure_Z();
//     }
//     tuple<int,bool,bool> item;
//     item = make_tuple(basis[i], outcome_right, outcome_left);
//     outcomeList.insert(pair<int, tuple<int, bool, bool>>(i, item));
//     outcomeList.insert(std::make_pair(i, item));
//   }
//   return outcomeList;
// }

// //Action 7
// int* finalizeAction(std::map<int, tuple<int, bool, bool>> outcomeList){
//   //int absaAdd = left_partner_qubit->stationaryQubit_address;
//   //int endnodeAdd = right_partner_qubit->stationaryQubit_address;
//   int size = outcomeList.size();
//   int msg[size]; //snce we only need a list of basis used
//   //std::map<int, tuple<int, bool, bool>::iterator it = outcomeList.begin();
//   int i = 0;
//   for(auto it= outcomeList.begin(); it != outcomeList.end(); ++it){
//       tuple <int, int, int> val = it->second;
//           msg[i] = std::get<0>(val);
//           i++;
//       }
//   bool msgSent = true;
//   return msg;
// }


// //Action 9
// int* qkdInitializeAction(int m){
//   int* basisList;
//   bool msgNeeded = true;
//   for(int i=0; i<m; i++){
//      int randBasis = rand()%3+1; //if 1 >X, 2>Z, 3 > bell
//      basisList[i] = randBasis;
//     }
//   return basisList;
// }


// //Action 11
// std::map<int, tuple<int, bool, bool>> qkdMeasureAction(int* basis, std::map<int, tuple<int, bool, bool>> outcomeList){
//   //StationaryQubit *incomeQubit = nullptr;
//   StationaryQubit* left_qubit = nullptr;
//   StationaryQubit* right_qubit = nullptr;
//   for(int i=0; i<sizeof(basis);i++){
//       left_qubit = getResource_fromTop_with_partner(left_resource, left_partner);
//       right_qubit = getResource_fromTop_with_partner(right_resource, right_partner);
//           bool outcome_right, outcome_left;
//           if (basis[i] == 1){
//             outcome_right = right_qubit -> measure_X();
//             outcome_left = left_qubit -> measure_X();
//           } else if (basis[i] == 2){
//             outcome_right = right_qubit -> measure_Z();
//             outcome_left = left_qubit -> measure_Z();
//           } else if (basis[i] == 3){
//             left_qubit->Hadamard_gate();
//             right_qubit->CNOT_gate(left_qubit);
//             outcome_left = left_qubit->measure_Z();
//             outcome_right = right_qubit->measure_Z();
//           }
//           tuple<int,bool,bool> item;
//           item = make_tuple(basis[i], outcome_right, outcome_left);
//           outcomeList.insert(pair<int, tuple<int, bool, bool>>(i, item));
//           //outcomeList.insert(std::make_pair(i, item));
//   }
//   return outcomeList;
// }

// //Action 13
// int* qkdFinalizeAction(int* basis){
//   //int absaAdd = left_partner_qubit->stationaryQubit_address;
//   //int endnodeAdd = right_partner_qubit->stationaryQubit_address;
//   //int* msg = *basisList; //this syntax is invalid
//   bool msgNeeded = false;
//   return basis;
// }

}  // namespace rules
}  // namespace quisp
