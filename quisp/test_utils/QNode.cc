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

TestQNode::TestQNode(int addr, int mass, bool is_initiator) : omnetpp::cModule(), address(addr), mass(mass), is_initiator(is_initiator) {
  setParInt(this, "address", addr);
  setParInt(this, "mass", mass);
  setParStr(this, "nodeType", "qnode");
  setParBool(this, "isInitiator", is_initiator);
  setComponentType(new TestModuleType("test qnode"));
  setName("TestQNode");
  auto *sim = getTestSimulation();
  sim->registerComponent(this);
  finalizeParameters();
}

}  // namespace qnode
}  // namespace quisp_test
