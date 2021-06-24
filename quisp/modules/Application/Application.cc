/** \file Application.cc
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief Application
 */
#include "Application.h"
#include <vector>
#include "utils/ComponentProvider.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

Application::Application() : provider(utils::ComponentProvider{this}) {}

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

  my_address = provider.getQNode()->par("address");
  is_e2e_connection = par("EndToEndConnection");
  number_of_resources = par("NumberOfResources");
  num_measure = par("NumMeasureApp");
  requiredFidelity = par("RequiredFidelity");

  WATCH_VECTOR(other_end_node_addresses);
  storeEndNodeAddresses();

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
    scheduleAt(simTime() + 0.1 * my_address, pk);
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
    send(msg, "toRouter");
    return;
  }

  delete msg;
  error("Application not recognizing this packet");
}

void Application::storeEndNodeAddresses() {
  cTopology *topo = new cTopology("topo");

  // like topo.extractByParameter("nodeType","EndNode")
  topo->extractByParameter("nodeType", provider.getQNode()->par("nodeType").str().c_str());

  int addr;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    addr = (int)node->getModule()->par("address");

    // ignore myself
    if (addr != my_address) {
      other_end_node_addresses.push_back(addr);
    }
  }
  delete topo;
}

int Application::getOneRandomEndNodeAddress() {
  int random_index = intuniform(0, other_end_node_addresses.size() - 1);
  return other_end_node_addresses[random_index];
}

}  // namespace modules
}  // namespace quisp
