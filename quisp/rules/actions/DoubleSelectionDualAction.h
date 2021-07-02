#pragma once

#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualAction : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_Z;
  int doubleselection_trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionDualAction(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_X, int ds_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    doubleselection_trash_resource_Z = ds_Z;
    doubleselection_trash_resource_X = ds_X;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoubleSelectionDualAction(){

  };
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualActionInv : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_Z;
  int doubleselection_trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionDualActionInv();
  DoubleSelectionDualActionInv(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_X, int ds_Z);
  cPacket* run(cModule* re) override;
};
}  // namespace actions
}  // namespace rules
}  // namespace quisp
