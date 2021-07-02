#include "SimultaneousSwappingAction.h"
#include <classical_messages_m.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

namespace quisp {
namespace rules {
namespace actions {
SimultaneousSwappingAction::SimultaneousSwappingAction(unsigned long RuleSet_id, int rule_index, int lp, QNIC_type lqt, int lqi, int lqad, int lr, int rp, QNIC_type rqt, int rqi,
                                                       int rqad, int rr, int slqi, QNIC_type slqt, int srqi, QNIC_type srqt, int init, QNIC_type initqt, int initqi, int initqad,
                                                       int initr, int resp, QNIC_type respqt, int respqi, int respqad, int respr, int iip, int pleir) {
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

  // initiator and responder
  initiator = init;
  initiator_qnic_type = initqt;
  initiator_qnic_id = initqi;
  initiator_qnic_address = initqad;
  initiator_resouce = initr;

  responder = resp;
  responder_qnic_type = respqt;
  responder_qnic_id = respqi;
  responder_qnic_address = respqad;
  responder_resouce = respr;

  self_left_qnic_id = slqi;
  self_right_qnic_id = srqi;
  self_left_qnic_type = slqt;
  self_right_qnic_type = srqt;

  index_in_path = iip;
  path_length_exclude_IR = pleir;
}

cPacket *SimultaneousSwappingAction::run(cModule *re) {
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

  StationaryQubit *right_partner_qubit = right_qubit->entangled_partner;
  StationaryQubit *left_partner_qubit = left_qubit->entangled_partner;

  left_qubit->Hadamard_gate();
  right_qubit->CNOT_gate(left_qubit);

  int lindex = left_partner_qubit->stationaryQubit_address;
  int rindex = right_partner_qubit->stationaryQubit_address;

  bool left_measure = left_qubit->measure_Z();
  bool right_measure = right_qubit->measure_Z();

  int operation_type_left, operation_type_right;

  if (!left_measure && !right_measure) {  // 0 0
    EV << "operation type 0, operation left I, operation right I\n";
    operation_type_left = 0;
    operation_type_right = 0;
  } else if (!left_measure && right_measure) {  // 0 1
    EV << "operation type 1, operation left I, operation right X\n";
    operation_type_left = 0;
    operation_type_right = 1;
  } else if (left_measure && !right_measure) {  // 1 0
    EV << "operation type 2, operation left Z, operation right I\n";
    operation_type_left = 0;
    operation_type_right = 2;
  } else if (left_measure && right_measure) {  // 1 1
    EV << "operation type 3, operation left Z, operation right X\n";
    operation_type_left = 0;
    operation_type_right = 3;
  }
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  if (std::rand() / RAND_MAX < success_probability) {
    right_partner_qubit->setEntangledPartnerInfo(left_partner_qubit);
    left_partner_qubit->setEntangledPartnerInfo(right_partner_qubit);

  } else {
    left_partner_qubit->isBusy = false;
    right_partner_qubit->isBusy = false;
  }
  removeResource_fromRule(left_qubit);
  removeResource_fromRule(right_qubit);

  // free consumed
  rule_engine->freeConsumedResource(self_left_qnic_id, left_qubit, self_left_qnic_type);  // free left
  rule_engine->freeConsumedResource(self_right_qnic_id, right_qubit, self_right_qnic_type);  // free right

  left_qubit->isBusy = false;
  right_qubit->isBusy = false;

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

}  // namespace actions
}  // namespace rules
}  // namespace quisp
