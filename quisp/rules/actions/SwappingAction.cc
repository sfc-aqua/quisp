#include "SwappingAction.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

using quisp::types::EigenvalueResult;

namespace quisp::rules::actions {

SwappingAction::SwappingAction(unsigned long ruleset_id, unsigned long rule_id, int left_partner, QNIC_type left_qnic_type, int left_qnic_id, int left_qnic_address,
                               int left_resource, int right_partner, QNIC_type right_qnic_type, int right_qnic_id, int right_qnic_address, int right_resource,
                               int self_left_qnic_id, QNIC_type self_left_qnic_type, int self_right_qnic_id, QNIC_type self_right_qnic_type)
    : Action(ruleset_id, rule_id),
      left_partner(left_partner),
      left_qnic_type(left_qnic_type),
      left_qnic_id(left_qnic_id),
      left_qnic_address(left_qnic_address),
      left_resource(left_resource),
      right_partner(right_partner),
      right_qnic_type(right_qnic_type),
      right_qnic_id(right_qnic_id),
      right_qnic_address(right_qnic_address),
      right_resource(right_resource),
      self_left_qnic_id(self_left_qnic_id),
      self_right_qnic_id(self_right_qnic_id),
      self_left_qnic_type(self_left_qnic_type),
      self_right_qnic_type(self_right_qnic_type) {}

// TODO: completely mixed
cPacket *SwappingAction::run(cModule *re) {
  // FIXME: left_resource is misleading name. This is just an index.
  auto *left_qubit = getResource(left_resource, left_partner);
  auto *right_qubit = getResource(right_resource, right_partner);

  if (left_qubit == nullptr || right_qubit == nullptr) {
    return generateError("Not enough resource found! This shouldn't happen!");
  }

  if (left_qubit == right_qubit) {
    return generateError("Left and right qubits are the same. ");
  }

  if (left_qnic_id < 0 || right_qnic_id < 0) {
    return generateError("QNICs are not found!");
  }

  // actual swapping operations
  auto *right_partner_qubit = right_qubit->entangled_partner;
  auto *left_partner_qubit = left_qubit->entangled_partner;

  if (right_partner_qubit == nullptr || left_partner_qubit == nullptr) {
    return generateError("Partner qubits are null");
  }
  // just swapping pointer.
  // swapper have no way to know this swapping is success or not.
  // bell measurement
  right_qubit->CNOT_gate(left_qubit);

  // TODO This is a little bit cheating. This must be tracked!
  int lindex = left_partner_qubit->stationaryQubit_address;
  int rindex = right_partner_qubit->stationaryQubit_address;

  auto left_measure = left_qubit->local_measure_X();
  auto right_measure = right_qubit->local_measure_Z();

  // RuleEngine::updateResources_EntanglementSwapping handles the operation type.
  // operation_type: 0 = I, 1 = X, 2 = Z
  int operation_type_left = left_measure == EigenvalueResult::PLUS_ONE ? 0 : 2;
  int operation_type_right = right_measure == EigenvalueResult::PLUS_ONE ? 0 : 1;

  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  right_partner_qubit->setEntangledPartnerInfo(left_partner_qubit);
  left_partner_qubit->setEntangledPartnerInfo(right_partner_qubit);
  removeResource_fromRule(left_qubit);
  removeResource_fromRule(right_qubit);
  rule_engine->freeConsumedResource(self_left_qnic_id, left_qubit, self_left_qnic_type);  // free left
  rule_engine->freeConsumedResource(self_right_qnic_id, right_qubit, self_right_qnic_type);  // free right

  auto *pk = new SwappingResult;
  // no destination here. In RuleEngine, it's set.
  // this setKind() doesn't seem to have any effect; set instead in void RuleEngine::traverseThroughAllProcesses2()
  pk->setKind(5);
  pk->setRuleSet_id(ruleset_id);
  pk->setRule_id(rule_id);
  pk->setAction_index(action_index);
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

}  // namespace quisp::rules::actions
