#include "DoubleSelectionDualActionSecond.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>
#include "base/TransferMessage.cc"

namespace quisp::rules::active::actions {

DoubleSelectionDualActionSecond::DoubleSelectionDualActionSecond(unsigned long ruleset_id, int rule_id, int shared_tag, int partner, QNIC_type qnic_type, int qnic_id, int resource,
                                                                 int trash_resource_x, int trash_resource_z, int ds_trash_resource_x)
    : ActiveAction(ruleset_id, rule_id, shared_tag),
      partner(partner),
      qnic_type(qnic_type),
      qnic_id(qnic_id),
      resource(resource),
      trash_resource_Z(trash_resource_z),
      trash_resource_X(trash_resource_x),
      doubleselection_trash_resource_X(ds_trash_resource_x) {}

// X purification, Z purification to trash_qubit_X Bell pair.
cPacket *DoubleSelectionDualActionSecond::run(cModule *re) {
  auto *qubit = getResource(resource, partner);
  auto *trash_qubit_X = getResource(trash_resource_X, partner);
  auto *trash_qubit_Z = getResource(trash_resource_Z, partner);
  auto *ds_trash_qubit_X = getResource(doubleselection_trash_resource_X, partner);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_X || trash_qubit_X == ds_trash_qubit_X ||
      trash_qubit_Z == ds_trash_qubit_X) {
    return generateError("Qubit and Trash_qubit must be different.");
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_X == nullptr) {
    return generateError("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
  }

  bool meas_X = trash_qubit_X->Xpurify(qubit);
  bool meas_Z = trash_qubit_Z->Zpurify(qubit);
  bool ds_meas_X = ds_trash_qubit_X->Xpurify(trash_qubit_Z);

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_Z->entangled_partner != nullptr) {
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }
  if (trash_qubit_X->entangled_partner != nullptr) {
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;
  }
  if (ds_trash_qubit_X->entangled_partner != nullptr) {
    ds_trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;

    ds_trash_qubit_X->entangled_partner->entangled_partner = nullptr;
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);
  removeResource_fromRule(trash_qubit_Z);
  removeResource_fromRule(ds_trash_qubit_X);

  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_X, qnic_type);

  auto message = base::generateDoubleSelectionDoublePurificationSecondResult(partner, ruleset_id, rule_id, shared_tag, action_index, 7, meas_X, meas_Z, ds_meas_X);
  action_index++;
  return message;
}

DoubleSelectionDualActionSecondInv::DoubleSelectionDualActionSecondInv(unsigned long ruleset_id, int rule_id, int shared_tag, int partner, QNIC_type qnic_type, int qnic_id,
                                                                       int resource, int trash_resource_x, int trash_resource_z, int ds_trash_resource_z)
    : ActiveAction(ruleset_id, rule_id, shared_tag),
      partner(partner),
      qnic_type(qnic_type),
      qnic_id(qnic_id),
      resource(resource),
      trash_resource_Z(trash_resource_z),
      trash_resource_X(trash_resource_x),
      doubleselection_trash_resource_Z(ds_trash_resource_z) {}

// Double selection double error (ZX error) purification
cPacket *DoubleSelectionDualActionSecondInv::run(cModule *re) {
  auto *qubit = getResource(resource, partner);
  auto *trash_qubit_X = getResource(trash_resource_X, partner);
  auto *trash_qubit_Z = getResource(trash_resource_Z, partner);
  auto *ds_trash_qubit_Z = getResource(doubleselection_trash_resource_Z, partner);

  if (qubit == trash_qubit_X || qubit == trash_qubit_Z || trash_qubit_Z == trash_qubit_X || qubit == ds_trash_qubit_Z || trash_qubit_X == ds_trash_qubit_Z ||
      trash_qubit_Z == ds_trash_qubit_Z) {
    return generateError("Qubit and Trash_qubit must be different.");
  }
  if (qubit == nullptr || trash_qubit_Z == nullptr || trash_qubit_X == nullptr || ds_trash_qubit_Z == nullptr) {
    return generateError("Not enough resource (Qubit and Trash_qubit) found. This should have been checked as a condition clause.");
  }

  bool meas_Z = trash_qubit_Z->Zpurify(qubit);
  bool meas_X = trash_qubit_X->Xpurify(qubit);
  bool ds_meas_Z = ds_trash_qubit_Z->Zpurify(trash_qubit_X);

  qubit->Lock(ruleset_id, rule_id, action_index);

  // Trash qubit has been measured. Now, break the entanglement info of the partner. There is no need to overwrite its density matrix since we are only tracking errors.
  if (trash_qubit_Z->entangled_partner != nullptr) {
    trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }
  if (trash_qubit_X->entangled_partner != nullptr) {
    trash_qubit_X->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    trash_qubit_X->entangled_partner->entangled_partner = nullptr;
  }

  if (ds_trash_qubit_Z->entangled_partner != nullptr) {
    ds_trash_qubit_Z->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
    ds_trash_qubit_Z->entangled_partner->entangled_partner = nullptr;
  }
  // Delete measured resource from the tracked list of resources.
  removeResource_fromRule(trash_qubit_X);
  removeResource_fromRule(trash_qubit_Z);
  removeResource_fromRule(ds_trash_qubit_Z);

  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_X, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit_Z, qnic_type);
  rule_engine->freeConsumedResource(qnic_id, ds_trash_qubit_Z, qnic_type);
  // Deleting done

  auto message = base::generateDoubleSelectionDoublePurificationSecondResult(partner, ruleset_id, rule_id, shared_tag, action_index, 7, meas_X, meas_Z, ds_meas_Z);
  action_index++;
  return message;
}

}  // namespace quisp::rules::active::actions
