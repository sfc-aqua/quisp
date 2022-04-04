#include "DoubleSelectionDualAction.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

namespace quisp::rules::actions {
DoubleSelectionDualAction::DoubleSelectionDualAction(unsigned long ruleset_id, unsigned long rule_id, int partner, QNIC_type qnic_type, int qnic_index, int resource,
                                                     int trash_resource_x, int trash_resource_z, int ds_trash_resource_x, int ds_trash_resource_z)
    : Action(ruleset_id, rule_id),
      partner(partner),
      qnic_type(qnic_type),
      qnic_id(qnic_index),
      resource(resource),
      trash_resource_Z(trash_resource_z),
      trash_resource_X(trash_resource_x),
      doubleselection_trash_resource_Z(ds_trash_resource_z),
      doubleselection_trash_resource_X(ds_trash_resource_x){};

// X purification, Z purification to trash_qubit_X Bell pair.
cPacket *DoubleSelectionDualAction::run(cModule *re) {
  auto *qubit = getResource(resource, partner);
  auto *trash_qubit_X = getResource(trash_resource_X, partner);
  auto *trash_qubit_Z = getResource(trash_resource_Z, partner);
  auto *ds_trash_qubit_X = getResource(doubleselection_trash_resource_X, partner);
  auto *ds_trash_qubit_Z = getResource(doubleselection_trash_resource_Z, partner);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || qubit == ds_trash_qubit_Z ||
      trash_qubit_Z == ds_trash_qubit_X || trash_qubit_Z == ds_trash_qubit_Z || trash_qubit_X == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_Z ||
      ds_trash_qubit_Z == ds_trash_qubit_X) {
    return generateError("Qubit and Trash_qubit must be different.");
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X == nullptr || ds_trash_qubit_Z == nullptr) {
    return generateError("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
  }

  bool meas_X = trash_qubit_X->Xpurify(qubit);
  bool ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);
  bool meas_Z = trash_qubit_Z->Zpurify(qubit);
  bool ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);
  removeResource_fromRule(trash_qubit_Z);
  removeResource_fromRule(ds_trash_qubit_X);
  removeResource_fromRule(ds_trash_qubit_Z);
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);

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

DoubleSelectionDualActionInv::DoubleSelectionDualActionInv(unsigned long ruleset_id, unsigned long rule_id, int partner, QNIC_type qnic_type, int qnic_index, int resource,
                                                           int trash_resource_x, int trash_resource_z, int ds_trash_resource_x, int ds_trash_resource_z)
    : Action(ruleset_id, rule_id),
      partner(partner),
      qnic_type(qnic_type),
      qnic_id(qnic_index),
      resource(resource),
      trash_resource_Z(trash_resource_z),
      trash_resource_X(trash_resource_x),
      doubleselection_trash_resource_Z(ds_trash_resource_z),
      doubleselection_trash_resource_X(ds_trash_resource_x){};

// Double selection double error (ZX error) purification
cPacket *DoubleSelectionDualActionInv::run(cModule *re) {
  auto *qubit = getResource(resource, partner);
  auto *trash_qubit_X = getResource(trash_resource_X, partner);
  auto *trash_qubit_Z = getResource(trash_resource_Z, partner);
  auto *ds_trash_qubit_X = getResource(doubleselection_trash_resource_X, partner);
  auto *ds_trash_qubit_Z = getResource(doubleselection_trash_resource_Z, partner);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || qubit == ds_trash_qubit_Z ||
      trash_qubit_Z == ds_trash_qubit_X || trash_qubit_Z == ds_trash_qubit_Z || trash_qubit_X == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_Z ||
      ds_trash_qubit_Z == ds_trash_qubit_X) {
    return generateError("Qubit and Trash_qubit must be different.");
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X == nullptr || ds_trash_qubit_Z == nullptr) {
    return generateError("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
  }

  bool meas_Z = trash_qubit_Z->Zpurify(qubit);
  bool ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);
  bool meas_X = trash_qubit_X->Xpurify(qubit);
  bool ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);
  removeResource_fromRule(trash_qubit_Z);
  removeResource_fromRule(ds_trash_qubit_X);
  removeResource_fromRule(ds_trash_qubit_Z);
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);

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
}  // namespace quisp::rules::actions
