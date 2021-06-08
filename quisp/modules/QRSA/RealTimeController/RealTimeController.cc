/** \file RealTimeController.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief RealTimeController
 */
#include "RealTimeController.h"
#include <utils/ComponentProvider.h>

namespace quisp {
namespace modules {

Define_Module(RealTimeController);
RealTimeController::RealTimeController() : provider(utils::ComponentProvider{this}) {}
void RealTimeController::initialize() {
  EV << "RealTimeController booted\n";
  std::cout<<"RealTimeController booted"<<std::endl;
  myAddress = par("address");
}

void RealTimeController::handleMessage(cMessage *msg) {}

void RealTimeController::EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) {
  Enter_Method("EmitPhoton()");
  auto *q = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);
  q->emitPhoton(pulse);
}

cModule *RealTimeController::getRGSsource() {
  // We know that Connection manager is not the QNode, so start from the parent.
  cModule *currentModule = getParentModule();
  try {
    // Assumes the node in a network has a type QNode
    cModuleType *RGSsourceType = cModuleType::get("modules.RGS_source");
    while (currentModule->getModuleType() != RGSsourceType) {
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
  auto *q = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);
  q->setFree(consumed);
}
}  // namespace modules
}  // namespace quisp
