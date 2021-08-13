#include "SwappingAction.h"
#include <classical_messages_m.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

using quisp::types::MeasureZResult;

namespace quisp {
namespace rules {
namespace actions {

SwappingAction::SwappingAction(unsigned long RuleSet_id, unsigned long rule_index, int lp, QNIC_type lqt, int lqi, int lqad, int lr, int rp, QNIC_type rqt, int rqi, int rqad, int rr,
                               int slqi, QNIC_type slqt, int srqi, QNIC_type srqt) {
  ruleset_id = RuleSet_id;
  rule_id = rule_index;

  left_partner = lp;
  left_qnic_type = lqt;
  left_qnic_id = lqi;
  left_qnic_address = lqad;
  left_resource = lr;
  right_partner = rp;
  right_qnic_type = rqt;
  right_qnic_id = rqi;
  right_qnic_address = rqad;
  right_resource = rr;

  self_left_qnic_id = slqi;
  self_right_qnic_id = srqi;
  self_left_qnic_type = slqt;
  self_right_qnic_type = srqt;
}

// TODO: completely mixed
cPacket *SwappingAction::run(cModule *re) {
  float success_probability = 1.0;

  StationaryQubit *left_qubit = nullptr;
  StationaryQubit *right_qubit = nullptr;

  // FIXME: left_resource is misleading name. This is just an index.
  left_qubit = getResourceFromTopWithPartner(left_resource, left_partner);
  right_qubit = getResourceFromTopWithPartner(right_resource, right_partner);

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
  right_qubit->CNOT_gate(left_qubit);
  left_qubit->Hadamard_gate();

  // TODO This is a little bit cheating. This must be tracked!
  int lindex = left_partner_qubit->stationaryQubit_address;
  int rindex = right_partner_qubit->stationaryQubit_address;

  auto left_measure = left_qubit->measure_Z();
  auto right_measure = right_qubit->measure_Z();

  // RuleEngine::updateResources_EntanglementSwapping handles the operation type.
  int operation_type_left, operation_type_right;
  // operation_type: 0 = I, 1 = X, 2 = Z
  if (left_measure == MeasureZResult::NO_ERROR && right_measure == MeasureZResult::NO_ERROR) {
    EV << "operation type 0, operation left I, operation right I\n";
    operation_type_left = 0;
    operation_type_right = 0;
  } else if (left_measure == MeasureZResult::NO_ERROR && right_measure == MeasureZResult::HAS_X_ERROR) {
    EV << "operation type 1, operation left I, operation right X\n";
    operation_type_left = 0;
    operation_type_right = 1;
  } else if (left_measure == MeasureZResult::HAS_X_ERROR && right_measure == MeasureZResult::NO_ERROR) {
    EV << "operation type 2, operation left Z, operation right I\n";
    operation_type_left = 2;
    operation_type_right = 0;
  } else {
    // left_measure == HAS_X_ERROR && right_measure == HAS_X_ERROR
    EV << "operation type 3, operation left Z, operation right X\n";
    operation_type_left = 2;
    operation_type_right = 1;
  }
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  if ((std::rand() / RAND_MAX) < success_probability) {
    right_partner_qubit->setEntangledPartnerInfo(left_partner_qubit);
    left_partner_qubit->setEntangledPartnerInfo(right_partner_qubit);
  } else {  // this might be wrong
    removeResource_fromRule(left_partner_qubit);
    removeResource_fromRule(right_partner_qubit);
    // TODO CHECK is this correct?
    // This node can't manipulate partner's qubit
  }
  removeResource_fromRule(left_qubit);
  removeResource_fromRule(right_qubit);
  // free consumed
  rule_engine->freeConsumedResource(self_left_qnic_id, left_qubit, self_left_qnic_type);  // free left
  rule_engine->freeConsumedResource(self_right_qnic_id, right_qubit, self_right_qnic_type);  // free right

  // result packet
  SwappingResult *pk = new SwappingResult;
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

}  // namespace actions
}  // namespace rules
}  // namespace quisp
