/** \file Application.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief Application
 */
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class Application Application.cc
 *
 *  \brief Application
 */
class Application : public cSimpleModule {
 private:
  int myAddress;
  cMessage *generatePacket; /**< Not the actual packet.
                              Local message to invoke Events */
  // cPar *sendIATime;
  // bool isBusy; /**< Already requested a path selection
  //               for a Quantum app */

  int *Addresses_of_other_EndNodes = new int[1];
  int num_of_other_EndNodes;
  bool EndToEndConnection;
  int number_of_resources;

  int num_measure;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void BubbleText(const char *txt);
  virtual int *storeEndNodeAddresses();
  virtual int getOneRandomEndNodeAddress();
  virtual cModule *getQNode();

 public:
  Application();
  int getAddress();
};

Define_Module(Application);

Application::Application() { generatePacket = nullptr; }

/**
 * \brief Initialize module.
 *
 * If we're not in and end node, this module is not necessary.
 */

void Application::initialize() {
  cGate *toRouterGate = gate("toRouter");
  if (!toRouterGate->isConnected()) {
    // Since we only need this module in EndNode, delete it otherwise.
    deleteThisModule *msg = new deleteThisModule;
    scheduleAt(simTime(), msg);
  } else {
    myAddress = getParentModule()->par("address");
    EndToEndConnection = par("EndToEndConnection");
    number_of_resources = par("NumberOfResources");
    num_measure = par("num_measure");

    Addresses_of_other_EndNodes = storeEndNodeAddresses();
    int tp = par("TrafficPattern");

    // cModule *qnode = getQNode();
    // if(myAddress == 1 && EndToEndConnection){//hard-coded for now
    // 20/3/15: upgrade from "exactly one connection" to
    // "let's all mambo!"  Each EndNode makes exactly one connection.
    // that means that some nodes will be receivers of more than
    // one connection, at random.
    // myaddress==1 for debugging
    if (EndToEndConnection) {  // hard-coded for now
      int endnode_destination_address;
      int ia;

      switch (tp) {
        default:
          error("Invalid TrafficPattern specified.");
          break;
        case 0:
          EV << "EndToEndConnection is set. but no traffic pattern specified; proceeding with no traffic\n";
          break;
        case 1:  // just one connection
          ia = par("LoneInitiatorAddress");
          if (myAddress == ia) {
            // while ((endnode_destination_address = getOneRandomEndNodeAddress()) == myAddress);
            endnode_destination_address = getOneRandomEndNodeAddress();
            EV << "Just one lonely connection setup request will be sent from " << myAddress << " to " << endnode_destination_address << "\n";
            ConnectionSetupRequest *pk = new ConnectionSetupRequest();
            pk->setActual_srcAddr(myAddress);
            pk->setActual_destAddr(endnode_destination_address);
            pk->setDestAddr(myAddress);
            pk->setSrcAddr(myAddress);
            pk->setNumber_of_required_Bellpairs(number_of_resources);
            pk->setKind(7);
            scheduleAt(simTime(), pk);
          }
          break;
        case 2:  // let's all mambo!
          // while ((endnode_destination_address = getOneRandomEndNodeAddress()) == myAddress);
          endnode_destination_address = getOneRandomEndNodeAddress();
          EV << "My connection setup request will be sent from " << myAddress << " to " << endnode_destination_address << "\n";
          ConnectionSetupRequest *pk = new ConnectionSetupRequest();
          pk->setActual_srcAddr(myAddress);
          pk->setActual_destAddr(endnode_destination_address);
          pk->setDestAddr(myAddress);
          pk->setSrcAddr(myAddress);
          pk->setNumber_of_required_Bellpairs(number_of_resources);  // required bell pairs
          pk->setKind(7);
          // to avoid conflict
          scheduleAt(simTime() + exponential(0.00001 * myAddress), pk);
          break;
      }
    }
  }
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
  num_of_other_EndNodes = topo->getNumNodes() - 1;
  Addresses_of_other_EndNodes = new int[num_of_other_EndNodes];

  int index = 0;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    EV << "\n\n\nEnd node address is " << node->getModule()->par("address").str() << "\n";
    if ((int)node->getModule()->par("address") != myAddress) {  // ignore self
      Addresses_of_other_EndNodes[index] = (int)node->getModule()->par("address");
      EV << "\n Is it still " << node->getModule()->par("address").str() << "\n";
      index++;
    }
  }

  // Just so that we can see the data from the IDE
  std::stringstream ss;
  for (int i = 0; i < num_of_other_EndNodes; i++) {
    ss << Addresses_of_other_EndNodes[i] << ", ";
  }
  std::string s = ss.str();
  par("Other_endnodes_table") = s;
  delete topo;
  return Addresses_of_other_EndNodes;
}

int Application::getOneRandomEndNodeAddress() {
  int random_index = intuniform(0, num_of_other_EndNodes - 1);
  return Addresses_of_other_EndNodes[random_index];
}

void Application::BubbleText(const char *txt) {
  if (hasGUI()) {
    char text[32];
    sprintf(text, "%s", txt);
    bubble(text);
  }
}

int Application::getAddress() { return myAddress; }

cModule *Application::getQNode() {
  cModule *currentModule = getParentModule();  // We know that Connection manager is not the QNode, so start from the parent.
  try {
    cModuleType *QNodeType = cModuleType::get("networks.QNode");  // Assumes the node in a network has a type QNode
    while (currentModule->getModuleType() != QNodeType) currentModule = currentModule->getParentModule();
  } catch (std::exception &e) {
    error("No module with QNode type found. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

}  // namespace modules
}  // namespace quisp
