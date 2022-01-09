#include "SimultaneousSwappingAction.h"
#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

using quisp::types::MeasureZResult;
namespace quisp::rules::active::actions {
SimultaneousSwappingAction::SimultaneousSwappingAction(unsigned long ruleset_id, unsigned long rule_id, int left_partner, QNIC_type left_qnic_type, int left_qnic_index,
                                                       int left_qnic_address, int left_resource, int right_partner, QNIC_type right_qnic_type, int right_qnic_index,
                                                       int right_qnic_address, int right_resource, int self_left_qnic_id, QNIC_type self_left_qnic_type, int self_right_qnic_id,
                                                       QNIC_type self_right_qnic_type, int initiator, QNIC_type initiator_qnic_type, int initiator_qnic_id,
                                                       int initiator_qnic_address, int initiator_resource, int responder, QNIC_type responder_qnic_type, int responder_qnic_id,
                                                       int responder_qnic_address, int responder_resource, int index_in_path, int path_length_exclude_ir)
    : ActiveAction(ruleset_id, rule_id),
      left_partner(),
      left_qnic_type(left_qnic_type),
      left_qnic_id(left_qnic_index),
      left_qnic_address(left_qnic_address),
      left_resource(left_resource),
      right_partner(right_partner),
      right_qnic_type(right_qnic_type),
      right_qnic_id(right_qnic_index),
      right_qnic_address(right_qnic_address),
      right_resource(right_resource),
      initiator(initiator),
      initiator_qnic_type(initiator_qnic_type),
      initiator_qnic_id(initiator_qnic_id),
      initiator_qnic_address(initiator_qnic_address),
      initiator_resource(initiator_resource),
      responder(responder),
      responder_qnic_type(responder_qnic_type),
      responder_qnic_id(responder_qnic_id),
      responder_qnic_address(responder_qnic_address),
      self_left_qnic_id(self_left_qnic_id),
      self_right_qnic_id(self_right_qnic_id),
      self_left_qnic_type(self_left_qnic_type),
      self_right_qnic_type(self_right_qnic_type),
      index_in_path(index_in_path),
      path_length_exclude_IR(path_length_exclude_ir) {}

cPacket *SimultaneousSwappingAction::run(cModule *re) {
  float success_probability = 1.0;

  IStationaryQubit *left_qubit = nullptr;
  IStationaryQubit *right_qubit = nullptr;

  left_qubit = getResource(left_resource, left_partner);
  right_qubit = getResource(right_resource, right_partner);

  if (left_qubit == nullptr || right_qubit == nullptr) {
    return generateError("Not enough resource found! This shouldn't happen!");
  }
  if (left_qnic_id < 0 || right_qnic_id < 0) {
    return generateError("QNICs are not found!");
  }

  auto *right_partner_qubit = right_qubit->entangled_partner;
  auto *left_partner_qubit = left_qubit->entangled_partner;

  right_qubit->CNOT_gate(left_qubit);
  left_qubit->Hadamard_gate();

  auto left_measure = left_qubit->measure_Z();
  auto right_measure = right_qubit->measure_Z();

  int operation_type_left, operation_type_right;

  if (left_measure == MeasureZResult::NO_X_ERROR && right_measure == MeasureZResult::NO_X_ERROR) {  // 0 0
    EV << "operation type 0, operation left I, operation right I\n";
    operation_type_left = 0;
    operation_type_right = 0;
  } else if (left_measure == MeasureZResult::NO_X_ERROR && right_measure == MeasureZResult::HAS_X_ERROR) {  // 0 1
    EV << "operation type 1, operation left I, operation right X\n";
    operation_type_left = 0;
    operation_type_right = 1;
  } else if (left_measure == MeasureZResult::HAS_X_ERROR && right_measure == MeasureZResult::NO_X_ERROR) {  // 1 0
    EV << "operation type 2, operation left Z, operation right I\n";
    operation_type_left = 0;
    operation_type_right = 2;
  } else {
    // left_measure == HAS_X_ERROR && right_measure == HAS_X_ERROR
    EV << "operation type 3, operation left Z, operation right X\n";
    operation_type_left = 0;
    operation_type_right = 3;
  }
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  if (std::rand() / RAND_MAX < success_probability) {
    right_partner_qubit->setEntangledPartnerInfo(left_partner_qubit);
    left_partner_qubit->setEntangledPartnerInfo(right_partner_qubit);
  }
  removeResource_fromRule(left_qubit);
  removeResource_fromRule(right_qubit);

  // free consumed
  rule_engine->freeConsumedResource(self_left_qnic_id, left_qubit, self_left_qnic_type);  // free left
  rule_engine->freeConsumedResource(self_right_qnic_id, right_qubit, self_right_qnic_type);  // free right

  auto *pk = new SimultaneousSwappingResult;

  pk->setKind(5);
  pk->setRuleSet_id(ruleset_id);
  pk->setRule_id(rule_id);
  pk->setAction_index(action_index);

  pk->setIndex_in_path(index_in_path);
  pk->setPath_length_exclude_IR(path_length_exclude_IR);

  // FIXME: These operations are corresponds to the result of operation.
  pk->setOperation_type_left(operation_type_left);  // operation type for left node
  pk->setOperation_type_right(operation_type_right);  // operation type for right node
  // These information are cropped in the RuleEngine.

  // Change the destination to end nodes instead.
  pk->setInitiator_Dest(initiator);
  pk->setResponder_Dest(responder);

  pk->setNew_partner_left(responder);
  pk->setNew_partner_qnic_index_left(responder_qnic_id);
  pk->setNew_partner_qnic_type_left(responder_qnic_type);
  pk->setNew_partner_qnic_address_left(responder_qnic_address);

  pk->setNew_partner_right(initiator);
  pk->setNew_partner_qnic_index_right(initiator_qnic_id);
  pk->setNew_partner_qnic_type_right(initiator_qnic_type);
  pk->setNew_partner_qnic_address_right(initiator_qnic_address);

  return pk;
}

}  // namespace quisp::rules::active::actions
