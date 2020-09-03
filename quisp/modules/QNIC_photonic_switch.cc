/** \file QNIC_photonic_switch.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief QNIC_photonic_switch
 */
#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class QNIC_photonic_switch QNIC_photonic_switch.cc
 *  \todo Documentation of the class header.
 *
 *  \brief QNIC_photonic_switch
 */
class QNIC_photonic_switch : public cSimpleModule {
 private:
  int myAddress;
  cMessage *generatePacket;  // Not the actual packet. Local message to invoke Events
  cPar *sendIATime;
  bool isBusy;  // Already requested a path selection for a Quantum app
 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void BubbleText(const char *txt);
  virtual void checkGateNumber();
  virtual void checkQubitNumber();
  virtual void checkAndsetNeighborAddress();
  virtual cModule *getQNode();

 public:
  QNIC_photonic_switch();
  int getAddress();
  virtual void Reserve();
  virtual void ReleaseReservation();
  virtual bool isReserved();
};

Define_Module(QNIC_photonic_switch);

QNIC_photonic_switch::QNIC_photonic_switch() { generatePacket = nullptr; }

void QNIC_photonic_switch::initialize() {
  // Check wether this QNIC's output is connected to a single neighbor for debugging purpose.
  checkGateNumber();
  checkAndsetNeighborAddress();
  ReleaseReservation();
}

void QNIC_photonic_switch::checkAndsetNeighborAddress() {
  // |qnic_quantum_port$o -(next gate)-> quantum_port$i | ---(next gate)---> | quantum_port$i --> fromHoM_quantum_port$i
  cGate *gt = getParentModule()->gate("qnic_quantum_port$o");  // Inner-port of this node in qnic - connected to another qnic in another node
  int neighbor_address = gt->getNextGate()->getNextGate()->getOwnerModule()->par("address");
  getParentModule()->par("neighbor_node_address") = neighbor_address;
  int neighbor_qnodeAddress = gt->getNextGate()->getNextGate()->getOwnerModule()->par("address");
  // EV<<"\n ***********************"<<gt->getNextGate()->getName()<<gt->getNextGate()->getIndex();//Outer-port of the same QNode
  // EV<<"\n ***********************"<<gt->getNextGate()->getNextGate()->getName()<<gt->getNextGate()->getNextGate()->getIndex();//Outer-port of the connected node
  // EV<<"\n ***********************"<<gt->getNextGate()->getNextGate()->getNextGate()->getName()<<gt->getNextGate()->getNextGate()->getNextGate()->getIndex();
  // EV<<"\n
  // ***********************"<<gt->getNextGate()->getNextGate()->getNextGate()->getNextGate()->getName()<<gt->getNextGate()->getNextGate()->getNextGate()->getNextGate()->getIndex();//EV<<gt->getNextGate()->getName()<<gt->getNextGate()->getIndex();
  // cModule *qnicType = module->getModuleByPath("networks.QNode.qnic");
}

void QNIC_photonic_switch::handleMessage(cMessage *msg) {
  // scheduleAt(simTime(),msg);
  send(msg, "toQNIC_quantum_port$o");  // Just send it outside.
  // send(msg, "toqubit_quantum_port$o",0);
  // delete msg;
}

void QNIC_photonic_switch::BubbleText(const char *txt) {
  if (hasGUI()) {
    char text[32];
    sprintf(text, "%s", txt);
    bubble(text);
  }
}

void QNIC_photonic_switch::checkGateNumber() {
  std::vector<const char *> gatesss = getParentModule()->getGateNames();
  int num = gatesss.size();
  /*if(num!=2){//!=2 because it is also conencted to the router if interHoM exists
      error("A single QNIC has more than one connection... Not allowed.");
  }*/
  for (int i = 0; i < num; i++) {
    EV << num << " gates in  " << getParentModule()->getName() << ": " << gatesss[i] << "\n";
  }
}

cModule *QNIC_photonic_switch::getQNode() {
  cModule *currentModule = getParentModule();
  try {
    cModuleType *QNodeType = cModuleType::get("networks.QNode");  // Assumes the node in a network has a type QNode
    while (currentModule->getModuleType() != QNodeType) {
      currentModule = currentModule->getParentModule();
    }
    return currentModule;
  } catch (std::exception &e) {
    error("No module with QNode type found as a parent node of QNIC_photonic_switch. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

void QNIC_photonic_switch::checkQubitNumber() {}

/**
 * At the moment, the only multiplexing scheme supported is circuit switching
 * managed at the QNIC level, so we have put a single reservation boolean
 * here associated with the QNIC.
 * On processing of a ConnectionSetupRequest, this flag is checked and if
 * available set.  If the QNIC is already reserved (e.g., competing
 * reservations are flowing in the network, and part of the path is
 * already reserved), then the ConnectionManager should fail this request
 * and send a RejectConnectionSetupRequest message.
 * \todo extend this to support other muxing styles (long-term research project,
 * but should build on Aparicio)
 */
void QNIC_photonic_switch::Reserve() {
  getParentModule()->par("is_reserved") = true;
  EV << "QNIC reserved!!\n";
}

void QNIC_photonic_switch::ReleaseReservation() {
  getParentModule()->par("is_reserved") = false;
  EV << "QNIC reservation released!!\n";
}

bool QNIC_photonic_switch::isReserved() { return getParentModule()->par("is_reserved"); }

}  // namespace modules
}  // namespace quisp
