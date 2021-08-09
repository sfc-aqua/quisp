#include "PurifyAction.h"
#include <classical_messages_m.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

namespace quisp {
namespace rules {
namespace actions {

PurifyAction::PurifyAction() {}

PurifyAction::PurifyAction(int part, QNIC_type qt, int qi, int res, int tres, int rs_id, int r_id) {
  partner = part;
  qnic_type = qt;
  qnic_id = qi;
  resource = res; /*The one to purify. Index from top to bottom.*/
  trash_resource = tres; /*The one to consume to purify*/
  purification_count = 0;
  rule_id = r_id;
  ruleset_id = rs_id;
  // action_index++;
  action_indices.insert(std::make_pair(part, 0));
}

PurifyAction::PurifyAction(unsigned long RuleSet_id, int rule_index, bool X_purification, bool Z_purification, int num_purification, int part, QNIC_type qt, int qi, int res,
                           int tres) {
  partner = part;
  qnic_type = qt;
  qnic_id = qi;
  resource = res;
  trash_resource = tres;
  purification_count = num_purification;
  rule_id = rule_index;
  ruleset_id = RuleSet_id;
  num_purify = num_purification;
  X = X_purification;
  Z = Z_purification;
  // action_index++;
  action_indices.insert(std::make_pair(part, 0));
}

// Either Z or X purification.
cPacket *PurifyAction::run(cModule *re) {
  EV << "purification start\n";
  StationaryQubit *qubit = nullptr;
  StationaryQubit *trash_qubit = nullptr;

  qubit = getResourceFromTopWithPartner(resource, partner);
  trash_qubit = getResourceFromTopWithPartner(trash_resource, partner);

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

  qubit->Lock(ruleset_id, rule_id, action_indices.at(partner));
  EV << "qubit: " << qubit << " trash qubit: " << trash_qubit << "\n";

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
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  rule_engine->freeConsumedResource(qnic_id, trash_qubit, qnic_type);  // Remove from entangled resource list.

  PurificationResult *pk = new PurificationResult;
  pk->setDestAddr(partner);
  // This result is sent to partner address and my address.
  // To keep the information who is the purifcation partner, this variable is used.
  pk->setPurification_partner(partner);
  pk->setKind(7);
  pk->setAction_index(action_indices.at(partner));
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setOutput_is_plus(meas);
  pk->setEntangled_with(qubit);
  action_indices.at(partner)++;
  return pk;
}
}  // namespace actions
}  // namespace rules
}  // namespace quisp
