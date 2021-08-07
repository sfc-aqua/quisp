#pragma once

#include "BaseAction.h"

namespace quisp {
namespace rules {
namespace actions {

class RandomMeasureAction : public Action {
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

 public:
  RandomMeasureAction(int owner_address, int part, QNIC_type qt, int qi, int res, int max);

  // cPacket* run(qnicResources *resources) override;
  // cPacket* run(cModule *re, qnicResources *resources) override;
  cPacket* run(cModule* re) override;
};
}  // namespace actions
}  // namespace rules
}  // namespace quisp
