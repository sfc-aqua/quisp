/** \file Application.cc
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief Application
 */
#include "Application.h"
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

Application::Application() {}

/**
 * \brief Initialize module.
 *
 * If we're not in and end node, this module is not necessary.
 */

void Application::initialize() {
  // Since we only need this module in EndNode, delete it otherwise.
  if (!gate("toRouter")->isConnected()) {
    deleteThisModule *msg = new deleteThisModule("DeleteThisModule");
    scheduleAt(simTime(), msg);
    return;
  }

  my_address = getParentModule()->par("address");
  is_e2e_connection = par("EndToEndConnection");
  number_of_resources = par("NumberOfResources");
  num_measure = par("NumMeasureApp");
  requiredFidelity = par("RequiredFidelity");

  other_end_node_addresses = storeEndNodeAddresses();

  if (!is_e2e_connection) {
    return;
  }

  int traffic_pattern = par("TrafficPattern");

  if (traffic_pattern == 0) {
    EV_INFO << "EndToEndConnection is set true. but no traffic pattern specified; proceeding with no traffic\n";
    return;
  }

  // just one connection
  if (traffic_pattern == 1) {
    int initiator_address = par("LoneInitiatorAddress");
    if (my_address == initiator_address) {
      int endnode_dest_addr = getOneRandomEndNodeAddress();
      EV_INFO << "Just one lonely connection setup request will be sent from " << my_address << " to " << endnode_dest_addr << "\n";
      ConnectionSetupRequest *pk = createConnectionSetupRequest(endnode_dest_addr, number_of_resources);
      scheduleAt(simTime(), pk);
    }
    return;
  }

  // let's all mambo!
  // Each EndNode makes exactly one connection.
  // this means that some nodes will be receivers of more than one connection, at random.
  if (traffic_pattern == 2) {
    int endnode_dest_addr = getOneRandomEndNodeAddress();
    EV_INFO << "My connection setup request will be sent from " << my_address << " to " << endnode_dest_addr << "\n";
    ConnectionSetupRequest *pk = createConnectionSetupRequest(endnode_dest_addr, number_of_resources);
    scheduleAt(simTime() + exponential(0.00001 * my_address), pk);
    // delay to avoid conflict
    return;
  }

  error("Invalid TrafficPattern specified.");
}

ConnectionSetupRequest *Application::createConnectionSetupRequest(int dest_addr, int num_of_required_resources) {
  ConnectionSetupRequest *pk = new ConnectionSetupRequest("ConnSetupRequest");
  pk->setActual_srcAddr(my_address);
  pk->setActual_destAddr(dest_addr);
  pk->setDestAddr(my_address);
  pk->setSrcAddr(my_address);
  pk->setNumber_of_required_Bellpairs(num_of_required_resources);
  pk->setRequiredFidelity(requiredFidelity);
  pk->setNum_measure(num_measure);
  pk->setKind(7);
  return pk;
}

void Application::handleMessage(cMessage *msg) {
  if (dynamic_cast<deleteThisModule *>(msg) != nullptr) {
    deleteModule();
    delete msg;
    return;
  }

  if (dynamic_cast<ConnectionSetupRequest *>(msg) != nullptr || dynamic_cast<ConnectionSetupResponse *>(msg) != nullptr) {
    send(msg, "toRouter");
    return;
  }

  if (dynamic_cast<InternalRuleSetForwarding *>(msg) != nullptr) {
    bubble("InternalRuleSetForwarding packet arrived to application!");
    send(msg, "toRouter");
    return;
  }

  delete msg;
  error("Application not recognizing this packet");
}

int *Application::storeEndNodeAddresses() {
  cTopology *topo = new cTopology("topo");

  // like topo.extractByParameter("nodeType","EndNode")
  topo->extractByParameter("nodeType", getParentModule()->par("nodeType").str().c_str());

  num_of_other_end_nodes = topo->getNumNodes() - 1;
  other_end_node_addresses = new int[num_of_other_end_nodes];

  int index = 0;
  int addr;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    addr = (int)node->getModule()->par("address");
    EV_DEBUG << "End node address is " << addr << "\n";

    if (addr != my_address) {  // ignore myself
      other_end_node_addresses[index] = addr;
      index++;
    }
  }

  // Just so that we can see the data from the IDE
  std::stringstream ss;
  for (int i = 0; i < num_of_other_end_nodes; i++) {
    ss << other_end_node_addresses[i] << ", ";
  }
  std::string s = ss.str();
  par("Other_endnodes_table") = s;
  delete topo;
  return other_end_node_addresses;
}

int Application::getOneRandomEndNodeAddress() {
  int random_index = intuniform(0, num_of_other_end_nodes - 1);
  return other_end_node_addresses[random_index];
}

int Application::getAddress() { return my_address; }

cModule *Application::getQNode() {
  // We know that Application is not the QNode, so start from the parent.
  cModule *current_module = getParentModule();
  try {
    // Assumes the node in a network has a type QNode
    const cModuleType *qnode_type = cModuleType::get("modules.QNode");
    while (current_module->getModuleType() != qnode_type) {
      current_module = current_module->getParentModule();
    }
  } catch (std::exception &e) {
    error("No module with QNode type found. Have you changed the type name in ned file?");
    endSimulation();
  }
  return current_module;
}

}  // namespace modules
}  // namespace quisp
