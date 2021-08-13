#pragma once

#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

class SwappingAction : public Action {
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

 public:
  // constructor of entanglement swapping
  SwappingAction(unsigned long RuleSet_id, unsigned long rule_index, int lp, QNIC_type lqt, int lqi, int lqad, int lr, int rp, QNIC_type rqt, int rqi, int rqad, int rr, int slqi,
                 QNIC_type slqt, int srqi, QNIC_type srqt);
  // cPacket* run(qnicResources *resources) override;
  // cPacket* run(cModule *re, qnicResources *resources) override;
  cPacket* run(cModule* re) override;
};

}  // namespace actions
}  // namespace rules
}  // namespace quisp
