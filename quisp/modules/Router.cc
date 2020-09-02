/** \file Router.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors takaakimatsuo
 *
 *  \brief Router
 */
#include <classical_messages_m.h>  //Path selection: type = 1, Timing notifier for BMA: type = 4
#include <omnetpp.h>
#include <map>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class Router Router.cc
 *  \todo Documentation of the class header.
 *
 *  \brief Router
 */
class Router : public cSimpleModule {
 private:
  int myAddress;

  typedef std::map<int, int> RoutingTable;  // destaddr -> gateindex
  RoutingTable rtable;

 protected:
  virtual void initialize(int stage) override;
  virtual void handleMessage(cMessage *msg) override;
  virtual int numInitStages() const override { return 1; };
};

Define_Module(Router);

void Router::initialize(int stage) {
  EV << "Routing table initialized \n";
  myAddress = getParentModule()->par("address");

  // Topology creation for routing table
  cTopology *topo = new cTopology("topo");
  cMsgPar *yes = new cMsgPar();
  yes->setStringValue("yes");
  topo->extractByParameter("includeInTopo", yes->str().c_str());  // Any node that has a parameter includeInTopo will be included in routing
  delete (yes);
  if (topo->getNumNodes() == 0 || topo == nullptr) {  // If no node with the parameter & value found, do nothing.
    return;
  }

  cTopology::Node *thisNode = topo->getNodeFor(getParentModule());  // The parent node with this specific router

  int number_of_links_total = 0;

  // Initialize channel weights for all existing links.
  for (int x = 0; x < topo->getNumNodes(); x++) {  // Traverse through all nodes
    // For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
    for (int j = 0; j < topo->getNode(x)->getNumOutLinks(); j++) {  // Traverse through all links from a specific node.
      // thisNode->disable();//You can also disable nodes or channels accordingly to represent broken hardwares
      // EV<<"\n thisNode is "<< topo->getNode(x)->getModule()->getFullName() <<" has "<<topo->getNode(x)->getNumOutLinks()<<" links \n";
      double channel_cost = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("cost");  // Get assigned cost for each channel written in .ned file

      EV << topo->getNode(x)->getLinkOut(j)->getLocalGate()->getFullName() << " =? "
         << "includes quantum?"
         << "\n";
      // if(strcmp(topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->getFullName(),"QuantumChannel")==0){
      if (strstr(topo->getNode(x)->getLinkOut(j)->getLocalGate()->getFullName(), "quantum")) {
        // Ignore quantum link in classical routing table
        // EV<<"\n Disable quantum from topo \n";
        topo->getNode(x)->getLinkOut(j)->disable();
      } else {
        // Otherwise, keep the classical channels and set the weight
        topo->getNode(x)->getLinkOut(j)->setWeight(channel_cost);  // Set channel weight
        // EV<<"\n Including classical channel link cost = "<< topo->getNode(x)->getLinkOut(j)->getWeight()<<":
        // "<<topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->getFullName()<<"\n";
      }
    }
  }

  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all the destinations from the thisNode
    if (topo->getNode(i) == thisNode) continue;    // skip the node that is running this specific router app
    // Apply dijkstra to each node to find all shortest paths.
    topo->calculateWeightedSingleShortestPathsTo(topo->getNode(i));  // Overwrites getNumPaths() and so on.

    // Check the number of shortest paths towards the target node. This may be more than 1 if multiple paths have the same minimum cost.
    if (thisNode->getNumPaths() == 0) continue;  // not connected

    cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();  // Returns the next link/gate in the ith shortest paths towards the target node.
    int gateIndex = parentModuleGate->getIndex();
    int address = topo->getNode(i)->getModule()->par("address");
    rtable[address] = gateIndex;  // Store gate index per destination from this node
    // EV <<"\n  Classical!!!!: Towards address " << address <<"("<< topo->getNode(i)->getModule()->getName() << ")"<<parentModuleGate->getFullName()<<"gateIndex is " << gateIndex
    // << "cost ="<< thisNode->getPath(0)->getWeight() << endl;

    if (strstr(parentModuleGate->getFullName(), "quantum")) {
      error("Classical routing table referring to quantum gates...");
    }
    // EV << "\n  Towards address " << address <<"("<< topo->getNode(i)->getModule()->getName() << ") gateIndex is " << gateIndex << endl;
  }

  delete topo;
}

void Router::handleMessage(cMessage *msg) {
  // check the header of the received package
  header *pk = check_and_cast<header *>(msg);
  int destAddr = pk->getDestAddr();  // read destination from the packet
  int who_are_you = pk->getKind();   // read the type of packet // This might be better fixed
  // bubble("Message kind "<<message_type<<" received");
  EV << "destAddr ==== " << destAddr;
  if (destAddr == myAddress && who_are_you == 1) {  // If destination is this node: Path selection
    send(pk, "toApp");                              // send to Application locally
    return;
  } else if (destAddr == myAddress && dynamic_cast<BSMtimingNotifier *>(msg) != nullptr) {  // Timing for BSM
    bubble("Timing Notifier from HoM (stand-alone or internal) received");
    send(pk, "rePort$o");  // send to Application locally
    return;
  } else if (destAddr == myAddress && dynamic_cast<EPPStimingNotifier *>(msg) != nullptr) {  // Timing for BSM
    bubble("Timing Notifier from EPPS received");
    send(pk, "rePort$o");  // send to Application locally
    return;
  } else if (destAddr == myAddress && dynamic_cast<ConnectionSetupRequest *>(msg) != nullptr) {
    bubble("Connection setup request received");
    send(pk, "cmPort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<ConnectionSetupResponse *>(msg) != nullptr) {
    bubble("Connection setup response received");
    send(pk, "cmPort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<RejectConnectionSetupRequest *>(msg) != nullptr) {
    bubble("Reject connection setup response received");
    send(pk, "cmPort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<InternalRuleSetForwarding *>(msg) != nullptr) {
    bubble("Internal RuleSet Forwarding packet received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<InternalRuleSetForwarding_Application *>(msg) != nullptr) {
    bubble("Internal RuleSet Forwarding Application packet received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<SwappingResult *>(msg) != nullptr) {
    bubble("Swapping Result packet received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<LinkTomographyRequest *>(msg) != nullptr) {
    bubble("Link tomography request received");
    send(pk, "hmPort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<LinkTomographyAck *>(msg) != nullptr) {
    bubble("Link tomography ack received");
    send(pk, "hmPort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<LinkTomographyRuleSet *>(msg) != nullptr) {
    bubble("Link tomography rule set received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<LinkTomographyResult *>(msg) != nullptr) {
    bubble("Link tomography result received");
    send(pk, "hmPort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<PurificationResult *>(msg) != nullptr) {
    bubble("Purification result received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<DoublePurificationResult *>(msg) != nullptr) {
    bubble("DoublePurification result received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<DS_DoublePurificationResult *>(msg) != nullptr) {
    bubble("DS_DoublePurification result received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<DS_DoublePurificationSecondResult *>(msg) != nullptr) {
    bubble("DS_DoublePurificationSecond result received");
    send(pk, "rePort$o");
    return;
  } else if (destAddr == myAddress && dynamic_cast<StopEmitting *>(msg) != nullptr) {
    send(pk, "rePort$o");
    return;
  }

  // Check if packet is reachable
  RoutingTable::iterator it = rtable.find(destAddr);
  if (it == rtable.end()) {
    std::cout << "In Node[" << myAddress << "]Address... " << destAddr << " unreachable, discarding packet " << pk->getName() << endl;
    delete pk;
    error("Router couldn't find the path. Shoudn't happen. Or maybe the router does not understand the packet.");
    return;
  }

  int outGateIndex = (*it).second;
  EV << "forwarding packet " << pk->getName() << " on gate index " << outGateIndex << endl;
  pk->setHopCount(pk->getHopCount() + 1);
  send(pk, "toQueue", outGateIndex);
}

}  // namespace modules
}  // namespace quisp
