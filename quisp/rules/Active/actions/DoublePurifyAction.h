#pragma once

#include "ActiveAction.h"

namespace quisp::rules::active::actions {

class DoublePurifyAction : public ActiveAction {
 public:
  DoublePurifyAction(unsigned long ruleset_id, int rule_id, int shared_tag, int partner, QNIC_type qnic_type, int qnic_id, int resource, int trash_resource_x,
                     int trash_resource_z);
  cPacket* run(cModule* re) override;

 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
};

class DoublePurifyActionInv : public ActiveAction {
 public:
  DoublePurifyActionInv(unsigned long ruleset_id, int rule_id, int shared_tag, int partner, QNIC_type qnic_type, int qnic_id, int resource, int trash_resource_x,
                        int trash_resource_z);
  cPacket* run(cModule* re) override;

 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
};
}  // namespace quisp::rules::active::actions
