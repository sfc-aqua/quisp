#pragma once

#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

class DoublePurifyAction : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoublePurifyAction();
  DoublePurifyAction(unsigned long RuleSet_id, unsigned long rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z);
  cPacket* run(cModule* re) override;
};

class DoublePurifyActionInv : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoublePurifyActionInv(unsigned long RuleSet_id, unsigned long rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoublePurifyActionInv(){

  };
  cPacket* run(cModule* re) override;
};
}  // namespace actions
}  // namespace rules
}  // namespace quisp
