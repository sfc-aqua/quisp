#pragma once

#include "BaseAction.h"

namespace quisp::rules::actions {

class SwappingAction : public ActiveAction {
 public:
  SwappingAction(unsigned long ruleset_id, unsigned long rule_id, int left_partner, QNIC_type left_qnic_type, int left_qnic_id, int left_qnic_address, int left_resource,
                 int right_partner, QNIC_type right_qnic_type, int right_qnic_id, int right_qnic_address, int right_resource, int self_left_qnic_id, QNIC_type self_left_qnic_type,
                 int self_right_qnic_id, QNIC_type self_right_qnic_type);
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

  int self_left_qnic_id;
  int self_right_qnic_id;
  QNIC_type self_left_qnic_type;
  QNIC_type self_right_qnic_type;
};

}  // namespace quisp::rules::actions
