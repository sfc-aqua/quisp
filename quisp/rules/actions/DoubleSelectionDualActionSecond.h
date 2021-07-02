#pragma once

#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualActionSecond : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.

 public:
  DoubleSelectionDualActionSecond();
  DoubleSelectionDualActionSecond(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_X);
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualActionSecondInv : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_Z;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.

 public:
  DoubleSelectionDualActionSecondInv();
  DoubleSelectionDualActionSecondInv(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_Z);
  cPacket* run(cModule* re) override;
};

}  // namespace actions
}  // namespace rules
}  // namespace quisp
