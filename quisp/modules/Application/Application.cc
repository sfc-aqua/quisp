/** \file Application.cc
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
 * If the node type is not EndNode, this module is automatically deleted in this function.
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
  num_measure = par("distant_measure_count");

  WATCH_VECTOR(other_end_node_addresses);
  storeEndNodeAddresses();


  if (!is_e2e_connection) {
    return;
  }

  traffic_pattern = par("TrafficPattern");

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
    // delay to avoid conflict
    scheduleAt(simTime() + 0.00001 * my_address, pk);
    return;
  }
  /*
    Simple GHZ distribution setup, not logic to have number_of_clients sent by clients.
    The Lone initiator should send a message to itself to define the number of clients,
    clients should send a setup request with a bool (and not a int) specifying the connection
    is multipartite. This is to ensure, QNIC are locked not in the setup phase but on the response phase.
  */
  if (traffic_pattern == 3) {
      int initiator_adress = par("LoneInitiatorAddress");
      int number_of_clients = par("NumberOfClients");
      if (my_address != initiator_adress) {

        EV_INFO << "My multipartite connection setup request will be sent from " << my_address << " to " << initiator_adress << "\n";
        EV_INFO << number_of_clients;
        ConnectionSetupRequest *pk = createMultiConnectionSetupRequest(initiator_adress, number_of_resources, number_of_clients);
        // delay to avoid conflict
        scheduleAt(simTime() + 0.00001 * my_address, pk);
      } else {
        EV_INFO << "Initiator setup" << "\n";
        ConnectionSetupRequest *pk = createMultiConnectionSetupRequest(initiator_adress, number_of_resources, number_of_clients);
        // delay to avoid conflict
        scheduleAt(simTime() + 0.00001 * my_address, pk);
      }
      return;
  }
  error("Invalid TrafficPattern specified.");
}

/**
 * \brief Generate connection setup response packet
 * @param dest_addr Destination address of this request
 */
ConnectionSetupRequest *Application::createConnectionSetupRequest(int dest_addr, int num_of_required_resources) {
  ConnectionSetupRequest *pk = new ConnectionSetupRequest("ConnSetupRequest");
  pk->setActual_srcAddr(my_address);
  pk->setActual_destAddr(dest_addr);
  pk->setDestAddr(my_address);
  pk->setSrcAddr(my_address);
  pk->setNum_measure(num_measure);
  pk->setKind(7);
  pk->setNumber_of_clients(1); //CM
  return pk;
}

//CM
ConnectionSetupRequest *Application::createMultiConnectionSetupRequest(int dest_addr, int num_of_required_resources, int number_of_clients) {
  ConnectionSetupRequest *pk = new ConnectionSetupRequest("ConnSetupRequest");
  pk->setActual_srcAddr(my_address);
  pk->setActual_destAddr(dest_addr);
  pk->setDestAddr(my_address);
  pk->setSrcAddr(my_address);
  pk->setNum_measure(num_measure);
  pk->setKind(7);
  pk->setNumber_of_clients(number_of_clients);  // CM
  return pk;
}
/**
 * \brief Message handler
 *
 * @param msg OMNeT++ cMessage
 */
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

/**
 * \brief Store communicatable EndNode addresses
 */
void Application::storeEndNodeAddresses() {
  cTopology *topo = new cTopology("topo");

  // like topo.extractByParameter("nodeType","EndNode")
  topo->extractByParameter("nodeType", provider.getQNode()->par("nodeType").str().c_str());

  int addr;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    addr = node->getModule()->par("address").intValue();

    // ignore myself
    if (addr != my_address) {
      other_end_node_addresses.push_back(addr);
    }
  }
  delete topo;
}

/**
 * \brief Return one randome EndNode address
 */
int Application::getOneRandomEndNodeAddress() {
  int random_index = intuniform(0, other_end_node_addresses.size() - 1);
  return other_end_node_addresses[random_index];
}

}  // namespace modules
}  // namespace quisp
