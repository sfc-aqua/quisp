#pragma once

#include "BaseAction.h"

namespace quisp::rules::actions {

class RandomMeasureAction : public Action {
 public:
  RandomMeasureAction(unsigned long ruleset_id, unsigned long rule_index, int owner_address, int partner, QNIC_type qnic_type, int qnic_id, int resource, int max_count);
  cPacket* run(cModule* re) override;

 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int src;
  int dst;
  int mutable current_count;
  int mutable max_count;
  simtime_t start;
};
}  // namespace quisp::rules::actions
