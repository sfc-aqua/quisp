#pragma once

#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

class SimultaneousSwappingAction : public Action {
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
  int initiator_resouce;

  int responder;
  QNIC_type responder_qnic_type;
  int responder_qnic_id;
  int responder_qnic_address;
  int responder_resouce;

  int self_left_qnic_id;
  int self_right_qnic_id;
  QNIC_type self_left_qnic_type;
  QNIC_type self_right_qnic_type;

  int index_in_path;
  int path_length_exclude_IR;

 public:
  // constructor of entanglement swapping
  SimultaneousSwappingAction(unsigned long RuleSet_id, int rule_index, int lp, QNIC_type lqt, int lqi, int lqad, int lr, int rp, QNIC_type rqt, int rqi, int rqad, int rr, int slqi,
                             QNIC_type slqt, int srqi, QNIC_type srqt, int init, QNIC_type initqt, int initqi, int initqad, int initr, int resp, QNIC_type respqt, int respqi,
                             int respqad, int respr, int iip, int pleir);

  cPacket* run(cModule* re) override;
};
}  // namespace actions
}  // namespace rules
}  // namespace quisp
