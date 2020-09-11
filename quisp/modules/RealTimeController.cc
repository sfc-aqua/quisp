/** \file RealTimeController.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief RealTimeController
 */
#include "RealTimeController.h"
#include <modules/stationaryQubit.h>

namespace quisp {
namespace modules {

Define_Module(RealTimeController);

void RealTimeController::initialize() {
  EV << "RealTimeController booted\n";
  myAddress = par("address");
}

void RealTimeController::handleMessage(cMessage *msg) {}

void RealTimeController::EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) {
  Enter_Method("EmitPhoton()");
  cModule *qnode = getQNode();  // Get the parent QNode that runs this RC.

  try {
    // EV<<"EmitPhoton for qnic["<<qnic_index<<"] and qubit["<<qubit_index<<"]\n\n\n";
    cModule *qubit = nullptr;
    if (qnic_type >= QNIC_N) error("Only 3 qnic types are currently recognized....");  // avoid segfaults <3
    qubit = qnode->getSubmodule(QNIC_names[qnic_type], qnic_index)->getSubmodule("statQubit", qubit_index);
    StationaryQubit *q = check_and_cast<StationaryQubit *>(qubit);
    q->emitPhoton(pulse);
  } catch (std::exception &e) {
    error("Some error occurred in RealTimeController. Here!. Maybe the qnic/statQubit couldnt be found. Have you changed the namings?");
  }
}

cModule *RealTimeController::getQNode() {
  // We know that Connection manager is not the QNode, so start from the parent.
  cModule *currentModule = getParentModule();
  try {
    // Assumes the node in a network has a type QNode
    cModuleType *QNodeType = cModuleType::get("networks.QNode");
    while (currentModule->getModuleType() != QNodeType) {
      currentModule = currentModule->getParentModule();
    }
    return currentModule;
  } catch (std::exception &e) {
    error("No module with QNode type found. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

void RealTimeController::ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) {
  bool success;
  cModule *qnode = getQNode();  // Get the parent QNode that runs this RC.
  try {
    cModule *qubit = nullptr;
    if (qnic_type >= QNIC_N) error("Only 3 qnic types are currently recognized....");  // avoid segfaults <3
    qubit = qnode->getSubmodule(QNIC_names[qnic_type], qnic_index)->getSubmodule("statQubit", qubit_index);
    StationaryQubit *q = check_and_cast<StationaryQubit *>(qubit);
    q->setFree(consumed);
  } catch (std::exception &e) {
    error("Some error occured in RealTimeController. Maybe the qnic/statQubit couldnt be found. Have you changed the namings?");
  }
}

}  // namespace modules
}  // namespace quisp
