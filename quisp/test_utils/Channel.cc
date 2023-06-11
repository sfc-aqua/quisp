#include "Channel.h"

namespace quisp_test {
namespace channel {

TestDatarateChannel::TestDatarateChannel() : cDatarateChannel() { setCost(); }

void TestDatarateChannel::setCost(double cost) {
  auto *p = new cDoubleParImpl();
  p->setName("cost");
  p->setDoubleValue(cost);
  p->setIsMutable(true);
  addPar(p);
}

}  // namespace channel
}  // namespace quisp_test
