#pragma once

#include "BaseAction.h"

namespace quisp::rules::actions {

class PurifyAction : public ActiveAction {
 public:
  PurifyAction(unsigned long ruleset_id, unsigned long rule_id, bool x_purification, bool z_purification, int num_purification, int partner, QNIC_type qnic_type, int qnic_id,
               int resource, int trash_resource);

  cPacket* run(cModule* re) override;

 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
};

}  // namespace quisp::rules::actions
