/** \file RoutingDaemon.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors takaakimatsuo
 *
 *  \brief RoutingDaemon
 */
#include "RoutingDaemon.h"
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace quisp {
namespace modules {

Define_Module(RoutingDaemon);

/**
 *  \todo Documentation of the class header.
 *
 *  \brief RoutingDaemon
 *
 * The RoutingDaemon is one of the five key modules in the
 * software for a quantum repeater/router (qrsa).  It will be responsible for
 * running dynamic routing protocols, such as qOSPF, qBGP, etc.
 *
 * It communicates with other RoutingDaemons, in other nodes on the network,
 * as in the classical Internet.  Internally, its role is to keep track of the
 * QNICs and the links by communicating with the HardwareMonitor, and to provide
 * information to the ConnectionManager when requested.  (There is also one
 * place where the RuleEngine needs access to information maintained by the RD.)
 *
 * The above is the intended design.
 *
 * \todo In fact, the RoutingDaemon as it exists today uses special, internal
 * OMNeT++ magic to directly access the network topology, as stored in the
 * simulator, rather than dynamically discovering it.  That should be corrected.
 *
 * At the moment, the RD is independent of the end-to-end reservation of resources,
 * as dictated by the multiplexing (muxing) discpline in use.  This means that
 * it always returns a single, best path to connect to the requested node.  A
 * consequence is that ConnectionSetupRequest can fail if the resource management
 * discipline is fully blocking, as in circuit switching, which is the first
 * discipline we are implementing.
 *
 * \todo Also, this code is built as a Module, via the Define_Module call;
 * the other important modules are classes.  That distinction needs to be
 * addressed.
 */
void RoutingDaemon::initialize(int stage) {
  EV << "Routing Daemon booted\n";

  EV << "Routing table initialized \n";
  myAddress = getParentModule()->par("address");
  // Topology creation for routing table
  cTopology *topo = new cTopology("topo");
  // veryfication?
  cMsgPar *yes = new cMsgPar();
  yes->setStringValue("yes");
  topo->extractByParameter("includeInTopo", yes->str().c_str());  // Any node that has a parameter includeInTopo will be included in routing
  delete (yes);
  // EV << "cTopology found " << topo->getNumNodes() << " nodes\n";
  if (topo->getNumNodes() == 0 || topo == nullptr) {  // If no node with the parameter & value found, do nothing.
    return;
  }

  cTopology::Node *thisNode = topo->getNodeFor(getParentModule()->getParentModule());  // The parent node with this specific router

  // Initialize channel weights for all existing links.
  for (int x = 0; x < topo->getNumNodes(); x++) {  // Traverse through all nodes
    // For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
    for (int j = 0; j < topo->getNode(x)->getNumOutLinks(); j++) {  // Traverse through all links from a specific node.
      // thisNode->disable();//You can also disable nodes or channels accordingly to represent broken hardwares
      // EV<<"\n thisNode is "<< topo->getNode(x)->getModule()->getFullName() <<" has "<<topo->getNode(x)->getNumOutLinks()<<" links \n";

      // Calculate bell pair generation rate to use it as channel cost
      // The cost metric is taken from https://arxiv.org/abs/1206.5655
      double speed_of_light_in_fiber = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("Speed_of_light_in_fiber");
      double channel_length = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("distance");
      double emission_prob = 0.46 * 0.49;
      // Emission success probability needs to be read from the .ini file or StationaryQubit.cc residing inside qnic module
      // cTopology::Node *currNode = topo->getNodeFor(getParentModule()->getParentModule());
      // double emission_prob = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("emission_success_probability");
      EV_DEBUG << "\n Channel length is " << channel_length;
      EV_DEBUG << "\n Speed of light in the channel is " << speed_of_light_in_fiber;
      // cTopology::Node *currNode = topo->getNodeFor(getParentModule()->getParentModule());
      // double emission_prob = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("emission_success_probability");
      double seconds_per_bell_pair_generation = (channel_length / speed_of_light_in_fiber) * emission_prob;
      EV_DEBUG << "\n BellGenT metric for the channel is " << seconds_per_bell_pair_generation;

      // EV<<topo->getNode(x)->getLinkOut(j)->getLocalGate()->getFullName()<<" =? "<<"QuantumChannel"<<"\n";
      // if(strcmp(topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->getFullName(),"QuantumChannel")==0){
      if (strstr(topo->getNode(x)->getLinkOut(j)->getLocalGate()->getFullName(), "quantum")) {
        // Otherwise, keep the quantum channels and set the weight
        // EV<<"\n Quantum Channel!!!!!! cost is"<<channel_cost<<"\n";
        topo->getNode(x)->getLinkOut(j)->setWeight(seconds_per_bell_pair_generation);  // Set channel weight
      } else {
        // Ignore classical link in quantum routing table
        topo->getNode(x)->getLinkOut(j)->disable();
      }
    }
  }

  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all the destinations from the thisNode
    if (topo->getNode(i) == thisNode) continue;  // skip the node that is running this specific router app
    // Apply dijkstra to each node to find all shortest paths.
    topo->calculateWeightedSingleShortestPathsTo(topo->getNode(i));  // Overwrites getNumPaths() and so on.

    // Check the number of shortest paths towards the target node. This may be more than 1 if multiple paths have the same minimum cost.
    // EV<<"\n Quantum....\n";
    if (thisNode->getNumPaths() == 0) {
      error("Path not found. This means that a node is completely separated...Probably not what you want now");
      continue;  // not connected
    }
    // Returns the next link/gate in the ith shortest paths towards the target node.
    cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();
    QNIC thisqnic;
    int destAddr = topo->getNode(i)->getModule()->par("address");
    thisqnic.address = parentModuleGate->getPreviousGate()->getOwnerModule()->par("self_qnic_address");
    thisqnic.type = (QNIC_type)(int)parentModuleGate->getPreviousGate()->getOwnerModule()->par("self_qnic_type");
    thisqnic.index = parentModuleGate->getPreviousGate()->getOwnerModule()->getIndex();
    ;
    thisqnic.pointer = parentModuleGate->getPreviousGate()->getOwnerModule();

    qrtable[destAddr] = thisqnic;  // Store gate index per destination from this node
    // EV<<"\n Quantum: "<<topo->getNode(i)->getModule()->getFullName()<<"\n";
    // EV <<"\n  Quantum: Towards node address " << destAddr << " use qnic with address = "<<parentModuleGate->getPreviousGate()->getOwnerModule()->getFullName()<<"\n";
    if (!strstr(parentModuleGate->getFullName(), "quantum")) {
      error("Quantum routing table referring to classical gates...");
    }
  }
  delete topo;
}

/**
 * This is the only routine, at the moment, with any outside contact.
 * Rather than exchanging a message with those who need this information (ConnectionManager, mainly,
 * and in one case RuleEngine), this is a direct call that they make.
 *
 * \todo Decide if this is really the right way to do this.  Likely also
 * hooked up in the issue of module v. class.
 */
int RoutingDaemon::return_QNIC_address_to_destAddr(int destAddr) {
  Enter_Method("return_QNIC_address_to_destAddr");
  RoutingTable::iterator it = qrtable.find(destAddr);
  if (it == qrtable.end()) {
    EV << "Quantum: address " << destAddr << " unreachable from this node \n";
    return -1;
  }
  return it->second.address;
}

int RoutingDaemon::returnNumEndNodes() {
  cTopology *topo = new cTopology("topo");
  cMsgPar *yes = new cMsgPar();
  yes->setStringValue("yes");
  topo->extractByParameter("includeInTopo", yes->str().c_str());
  int index = 0;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    std::string node_type = node->getModule()->par("nodeType");
    if (node_type == "EndNode") {  // ignore myself
      index++;
    }
  }
  delete topo;
  return index;
};

/**
 * Once we begin using dynamic routing protocols, this is where the messages
 * will be handled.  This perhaps will also be how we communicate with the
 * other important daemons in the qrsa.
 * \todo Handle dynamic routing protocol messages.
 **/
void RoutingDaemon::handleMessage(cMessage *msg) {}

}  // namespace modules
}  // namespace quisp
