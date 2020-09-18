/** \file PhotonicSwitch.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief PhotonicSwitch
 */
#include "PhotonicSwitch.h"

namespace quisp {
namespace modules {

PhotonicSwitch::PhotonicSwitch() { generatePacket = nullptr; }

void PhotonicSwitch::initialize() {
  // Check wether this QNIC's output is connected to a single neighbor for debugging purpose.
  checkGateNumber();
  checkAndsetNeighborAddress();
  ReleaseReservation();
}

void PhotonicSwitch::checkAndsetNeighborAddress() {
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

void PhotonicSwitch::handleMessage(cMessage *msg) {
  // scheduleAt(simTime(),msg);
  send(msg, "toQNIC_quantum_port$o");  // Just send it outside.
  // send(msg, "toqubit_quantum_port$o",0);
  // delete msg;
}

void PhotonicSwitch::BubbleText(const char *txt) {
  if (hasGUI()) {
    char text[32];
    sprintf(text, "%s", txt);
    bubble(text);
  }
}

void PhotonicSwitch::checkGateNumber() {
  std::vector<const char *> gatesss = getParentModule()->getGateNames();
  int num = gatesss.size();
  /*if(num!=2){//!=2 because it is also conencted to the router if interHoM exists
      error("A single QNIC has more than one connection... Not allowed.");
  }*/
  for (int i = 0; i < num; i++) {
    EV << num << " gates in  " << getParentModule()->getName() << ": " << gatesss[i] << "\n";
  }
}

cModule *PhotonicSwitch::getQNode() {
  cModule *currentModule = getParentModule();
  try {
    cModuleType *QNodeType = cModuleType::get("networks.QNode");  // Assumes the node in a network has a type QNode
    while (currentModule->getModuleType() != QNodeType) {
      currentModule = currentModule->getParentModule();
    }
    return currentModule;
  } catch (std::exception &e) {
    error("No module with QNode type found as a parent node of PhotonicSwitch. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

void PhotonicSwitch::checkQubitNumber() {}

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
void PhotonicSwitch::Reserve() {
  getParentModule()->par("is_reserved") = true;
  EV << "QNIC reserved!!\n";
}

void PhotonicSwitch::ReleaseReservation() {
  getParentModule()->par("is_reserved") = false;
  EV << "QNIC reservation released!!\n";
}

bool PhotonicSwitch::isReserved() { return getParentModule()->par("is_reserved"); }

}  // namespace modules
}  // namespace quisp
