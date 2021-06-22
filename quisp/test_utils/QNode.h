#pragma once

#include <omnetpp.h>

namespace quisp_test {
namespace qnode {

class TestQNode : public omnetpp::cModule {
 public:
  explicit TestQNode(int addr);
  int address;
};
}  // namespace qnode
}  // namespace quisp_test