#include "QNode.h"
#include "ModuleType.h"
#include "UtilFunctions.h"

namespace quisp_test {
namespace qnode {

using quisp_test::module_type::TestModuleType;
using quisp_test::utils::getTestSimulation;
using quisp_test::utils::setParBool;
using quisp_test::utils::setParInt;
using quisp_test::utils::setParObject;
using quisp_test::utils::setParStr;

TestQNode::TestQNode(int addr, int mass, bool is_initiator) : TestQNode(QNodeAddr{addr}, mass, is_initiator) {}
TestQNode::TestQNode(QNodeAddr addr, int mass, bool is_initiator) : omnetpp::cModule(), address(addr), mass(mass), is_initiator(is_initiator) {
  setParStr(this, "address", std::to_string(addr).c_str());
  setParInt(this, "mass", mass);
  setParStr(this, "node_type", "qnode");
  setParBool(this, "is_initiator", is_initiator);
  setParObject(this, "possible_recipients", new cObject());
  setComponentType(new TestModuleType("test qnode"));
  setName("TestQNode");
  auto *sim = getTestSimulation();
  sim->registerComponent(this);
  finalizeParameters();
}

}  // namespace qnode
}  // namespace quisp_test
