/** \file RealTimeController.cc
 *
 *  \brief RealTimeController
 */
#include "RealTimeController.h"

namespace quisp::modules {

Define_Module(RealTimeController);

RealTimeController::RealTimeController() : provider(utils::ComponentProvider{this}) {}
void RealTimeController::initialize() {
  EV << "RealTimeController booted\n";
  myAddress = par("address");
}

void RealTimeController::handleMessage(cMessage *msg) {}

void RealTimeController::EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) {
  Enter_Method("EmitPhoton()");
  auto *q = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);
  q->emitPhoton(pulse);
}

void RealTimeController::ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) {
  auto *q = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);
  q->setFree(consumed);
}
void RealTimeController::ReInitialize_StationaryQubit(qrsa::IQubitRecord *const qubit_record, bool consumed) {
  auto *qubit = provider.getStationaryQubit(qubit_record);
  qubit->setFree(consumed);
}

void RealTimeController::applyXGate(qrsa::IQubitRecord *const qubit_record) {
  auto *qubit = provider.getStationaryQubit(qubit_record);
  qubit->gateX();
}
void RealTimeController::applyZGate(qrsa::IQubitRecord *const qubit_record) {
  auto *qubit = provider.getStationaryQubit(qubit_record);
  qubit->gateZ();
}
void RealTimeController::applyYGate(qrsa::IQubitRecord *const qubit_record) {
  auto *qubit = provider.getStationaryQubit(qubit_record);
  qubit->gateY();
}
}  // namespace quisp::modules
