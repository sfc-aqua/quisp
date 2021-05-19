/** \file RealTimeController.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief RealTimeController
 */
#include "RealTimeController.h"

#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/Utils/ComponentProvider.h"

namespace quisp {
namespace modules {

Define_Module(RealTimeController);
RealTimeController::RealTimeController() : provider(ComponentProvider{this}) {}
void RealTimeController::initialize() {
  EV << "RealTimeController booted\n";
  myAddress = par("address");
}

void RealTimeController::handleMessage(cMessage *msg) {}

void RealTimeController::EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) {
  Enter_Method("EmitPhoton()");
  try {
    auto *q = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);
    q->emitPhoton(pulse);
  } catch (std::exception &e) {
    error("Some error occurred in RealTimeController. Here!. Maybe the qnic/statQubit couldnt be found. Have you changed the namings?");
  }
}

void RealTimeController::ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) {
  try {
    auto *q = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);
    q->setFree(consumed);
  } catch (std::exception &e) {
    error("Some error occured in RealTimeController. Maybe the qnic/statQubit couldnt be found. Have you changed the namings?");
  }
}
}  // namespace modules
}  // namespace quisp
