#include "QNode.h"
#include "ModuleType.h"
#include "UtilFunctions.h"

namespace quisp_test {
namespace qnode {

using quisp_test::module_type::TestModuleType;
using quisp_test::utils::getTestSimulation;
using quisp_test::utils::setParBool;
using quisp_test::utils::setParInt;
using quisp_test::utils::setParStr;

TestQNode::TestQNode(int addr) : omnetpp::cModule(), address(addr) {
  setParInt(this, "address", addr);
  setParStr(this, "nodeType", "qnode");
  setComponentType(new TestModuleType("test qnode"));
  finalizeParameters();
  auto *sim = getTestSimulation();
  sim->registerComponent(this);
}

}  // namespace qnode
}  // namespace quisp_test
