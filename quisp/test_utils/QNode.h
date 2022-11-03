#pragma once

#include <omnetpp.h>

namespace quisp_test {
namespace qnode {

class TestQNode : public omnetpp::cModule {
 public:
  explicit TestQNode(int addr, int mass, bool is_initiator);
  int address;
  int mass;
  bool is_initiator;
};
}  // namespace qnode
}  // namespace quisp_test