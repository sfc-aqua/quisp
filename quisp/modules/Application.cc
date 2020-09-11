/** \file Application.cc
 *  \todo clean Clean code when it is simple.
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

Application::Application() { generatePacket = nullptr; }

/**
 * \brief Initialize module.
 *
 * If we're not in and end node, this module is not necessary.
 */

void Application::initialize() {
  cGate *toRouterGate = gate("toRouter");

  // Since we only need this module in EndNode, delete it otherwise.
  if (!toRouterGate->isConnected()) {
    deleteThisModule *msg = new deleteThisModule;
    scheduleAt(simTime(), msg);
    return;
  }

  myAddress = getParentModule()->par("address");
  is_e2e_connection = par("EndToEndConnection");
  number_of_resources = par("NumberOfResources");
  num_measure = par("num_measure");

  other_end_node_addresses = storeEndNodeAddresses();

  if (!is_e2e_connection) {
    return;
  }

  int traffic_pattern = par("TrafficPattern");

  if (traffic_pattern == 0) {
    EV << "EndToEndConnection is set true. but no traffic pattern specified; proceeding with no traffic\n";
    return;
  }

  // just one connection
  if (traffic_pattern == 1) {
    int initiator_address = par("LoneInitiatorAddress");
    if (myAddress == initiator_address) {
      int endnode_dest_addr = getOneRandomEndNodeAddress();
      EV << "Just one lonely connection setup request will be sent from " << myAddress << " to " << endnode_dest_addr << "\n";
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
    EV << "My connection setup request will be sent from " << myAddress << " to " << endnode_dest_addr << "\n";
    ConnectionSetupRequest *pk = createConnectionSetupRequest(endnode_dest_addr, number_of_resources);
    // delay to avoid conflict
    scheduleAt(simTime() + exponential(0.00001 * myAddress), pk);
    return;
  }

  error("Invalid TrafficPattern specified.");
}

ConnectionSetupRequest *Application::createConnectionSetupRequest(int dest_addr, int num_of_required_resources) {
  ConnectionSetupRequest *pk = new ConnectionSetupRequest();
  pk->setActual_srcAddr(myAddress);
  pk->setActual_destAddr(dest_addr);
  pk->setDestAddr(myAddress);
  pk->setSrcAddr(myAddress);
  pk->setNumber_of_required_Bellpairs(num_of_required_resources);
  pk->setKind(7);
  return pk;
}

void Application::handleMessage(cMessage *msg) {
  if (dynamic_cast<deleteThisModule *>(msg) != nullptr) {
    deleteModule();
    delete msg;
  } else if (dynamic_cast<ConnectionSetupRequest *>(msg) != nullptr) {
    send(msg, "toRouter");
  } else if (dynamic_cast<ConnectionSetupResponse *>(msg) != nullptr) {
    send(msg, "toRouter");
  } else if (dynamic_cast<RejectConnectionSetupRequest *>(msg) != nullptr) {
    RejectConnectionSetupRequest *pk = check_and_cast<RejectConnectionSetupRequest *>(msg);
    int actual_src = pk->getActual_srcAddr();
    if (actual_src == myAddress) {
      float recon_try = std::rand() / RAND_MAX;
      int reject_node = pk->getSrcAddr();
      EV << "Connection was rejected by " << reject_node << "at" << myAddress << "\n";
      // this might be better handled in application
      ConnectionSetupRequest *pkt = new ConnectionSetupRequest;
      pkt->setActual_srcAddr(myAddress);
      pkt->setActual_destAddr(pk->getActual_destAddr());  // This might not good way
      pkt->setDestAddr(myAddress);
      pkt->setSrcAddr(myAddress);
      pkt->setNumber_of_required_Bellpairs(number_of_resources);
      pkt->setKind(7);
      scheduleAt(simTime(), pkt);
    }
  } else if (dynamic_cast<InternalRuleSetForwarding *>(msg) != nullptr) {
    bubble("internal rulesetforwarding packet arrived to application!");
    send(msg, "toRouter");
  } else {
    delete msg;
    error("Application not recognizing this packet");
  }

  /*if(msg == generatePacket){
      header *pk = new header("PathRequest");
      pk->setSrcAddr(1);//packet source setting
      pk->setDestAddr(3);//packet destination setting
      pk->setKind(1);
      send(pk, "toRouter");//send to port out. connected to local routing module (routing.localIn).
      scheduleAt(simTime() + sendIATime->doubleValue(), generatePacket);
      //scheduleAt(simTime() + 10, generatePacket);//In 10 seconds, another msg send gets invoked
  }
  else if(msg->getKind()==1 && strcmp("PathRequest", msg->getName())==0){
      BubbleText("Path Request received!");

      EV << "Deleting path request\n";
  }
  else{//A message was reached from another node to here
      delete msg;
      //cModule *mod = getSimulation()->getModule(4);
      //int ad = mod->par("address");
      //QNode *aa = check_and_cast<QNode*>(mod);//Cast not working
      //EV<<"------------------------------"<<mod->getModuleType()<<"\n";

      EV << "Deleting msg\n";
  }*/
}

int *Application::storeEndNodeAddresses() {
  cTopology *topo = new cTopology("topo");
  topo->extractByParameter("nodeType", getParentModule()->par("nodeType").str().c_str());  // like topo.extractByParameter("nodeType","EndNode")
  num_of_other_end_nodes = topo->getNumNodes() - 1;
  other_end_node_addresses = new int[num_of_other_end_nodes];

  int index = 0;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    EV << "\n\n\nEnd node address is " << node->getModule()->par("address").str() << "\n";
    if ((int)node->getModule()->par("address") != myAddress) {  // ignore self
      other_end_node_addresses[index] = (int)node->getModule()->par("address");
      EV << "\n Is it still " << node->getModule()->par("address").str() << "\n";
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

void Application::bubbleText(const char *txt) {
  if (hasGUI()) {
    char text[32];
    sprintf(text, "%s", txt);
    bubble(text);
  }
}

int Application::getAddress() { return myAddress; }

cModule *Application::getQNode() {
  // We know that Connection manager is not the QNode, so start from the parent.
  cModule *currentModule = getParentModule();
  try {
    // Assumes the node in a network has a type QNode
    cModuleType *QNodeType = cModuleType::get("networks.QNode");
    while (currentModule->getModuleType() != QNodeType) currentModule = currentModule->getParentModule();
  } catch (std::exception &e) {
    error("No module with QNode type found. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

}  // namespace modules
}  // namespace quisp
