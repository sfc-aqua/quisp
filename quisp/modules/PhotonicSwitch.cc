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

void PhotonicSwitch::initialize() {
  ensureCorrespondingNeighborAddress();
  release();
}

/**
 * this method finds the corresponding neighbor node and save its address to the QNIC parameter.
 */
void PhotonicSwitch::ensureCorrespondingNeighborAddress() {
  // |qnic_quantum_port$o -(next gate)-> quantum_port$i | ---(next gate)---> | quantum_port$i --> fromHoM_quantum_port$i
  // Inner-port of this node in qnic - connected to another qnic in another node
  cGate *gate = getParentModule()->gate("qnic_quantum_port$o");
  int neighbor_address = gate->getNextGate()->getNextGate()->getOwnerModule()->par("address");
  getParentModule()->par("neighbor_node_address") = neighbor_address;
}

void PhotonicSwitch::handleMessage(cMessage *msg) { send(msg, "toQNIC_quantum_port$o"); }

cModule *PhotonicSwitch::getQNode() {
  cModule *module = getParentModule();
  try {
    // Assumes the node in a network has a type QNode
    cModuleType *QNodeType = cModuleType::get("networks.QNode");
    while (module->getModuleType() != QNodeType) {
      module = module->getParentModule();
    }
  } catch (std::exception &e) {
    error("No QNode module found as a parent node of PhotonicSwitch. Have you changed the type name in ned file?");
    endSimulation();
  }
  return module;
}

/**
 * At the moment, the only multiplexing scheme supported is circuit switching
 * managed at the QNIC level, so we have put a single reservation boolean here associated with the QNIC.
 * On processing of a ConnectionSetupRequest, this flag is checked and if available set.
 * If the QNIC is already reserved
 * (e.g., competing reservations are flowing in the network, and part of the path is already reserved),
 * then the ConnectionManager should fail this request and send a RejectConnectionSetupRequest message.
 * \todo extend this to support other muxing styles (long-term research project,
 * but should build on Aparicio)
 */
void PhotonicSwitch::reserve() {
  getParentModule()->par("is_reserved") = true;
  EV_INFO << "QNIC reserved!\n";
}

void PhotonicSwitch::release() {
  getParentModule()->par("is_reserved") = false;
  EV_INFO << "QNIC reservation released!\n";
}

bool PhotonicSwitch::isReserved() { return getParentModule()->par("is_reserved"); }

}  // namespace modules
}  // namespace quisp
