#pragma once

#include <omnetpp.h>
#include "types/QNodeAddr.h"

namespace quisp_test {
namespace qnode {
using quisp::types::QNodeAddr;

class TestQNode : public omnetpp::cModule {
 public:
  explicit TestQNode(int addr, int mass, bool is_initiator);
  explicit TestQNode(QNodeAddr addr, int mass, bool is_initiator);
  QNodeAddr address;
  int mass;
  bool is_initiator;
};
}  // namespace qnode
}  // namespace quisp_test
