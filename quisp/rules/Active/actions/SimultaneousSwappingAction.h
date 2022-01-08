#pragma once

#include "BaseAction.h"

namespace quisp::rules::actions {

class SimultaneousSwappingAction : public ActiveAction {
 public:
  SimultaneousSwappingAction(unsigned long ruleset_id, unsigned long rule_id, int left_partner, QNIC_type left_qnic_type, int left_qnic_index, int left_qnic_address,
                             int left_resource, int right_partner, QNIC_type right_qnic_type, int right_qnic_index, int right_qnic_address, int right_resource,
                             int self_left_qnic_id, QNIC_type self_left_qnic_type, int self_right_qnic_id, QNIC_type self_right_qnic_type, int initiator,
                             QNIC_type initiator_qnic_type, int initiator_qnic_id, int initiator_qnic_address, int initiator_resource, int responder, QNIC_type responder_qnic_type,
                             int responder_qnic_id, int responder_qnic_address, int responder_resource, int index_in_path, int path_length_exclude_ir);

  cPacket* run(cModule* re) override;

 protected:
  // First partner
  int left_partner;
  QNIC_type left_qnic_type;
  int left_qnic_id;
  int left_qnic_address;
  int left_resource;
  // Second partner
  int right_partner;
  QNIC_type right_qnic_type;
  int right_qnic_id;
  int right_qnic_address;
  int right_resource;
  int action_index = 0;

  int initiator;
  QNIC_type initiator_qnic_type;
  int initiator_qnic_id;
  int initiator_qnic_address;
  int initiator_resource;

  int responder;
  QNIC_type responder_qnic_type;
  int responder_qnic_id;
  int responder_qnic_address;
  int responder_resource;

  int self_left_qnic_id;
  int self_right_qnic_id;
  QNIC_type self_left_qnic_type;
  QNIC_type self_right_qnic_type;

  int index_in_path;
  int path_length_exclude_IR;
};
}  // namespace quisp::rules::actions
