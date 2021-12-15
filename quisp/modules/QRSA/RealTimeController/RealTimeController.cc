/** \file RealTimeController.cc
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

void RealTimeController::applyXGate(qrsa::UniqueQubitRecord &qubit_record) {}
void RealTimeController::applyZGate(qrsa::UniqueQubitRecord &qubit_record) {}
void RealTimeController::assertNoEntanglement(qrsa::UniqueQubitRecord &qubit_record) {
  auto *qubit = provider.getStationaryQubit(qubit_record);
  if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok) {
    error("something went wrong");
  }
  if (qubit->entangled_partner != nullptr) {
    if (qubit->entangled_partner->entangled_partner == nullptr) {
      error("1. Entanglement tracking is not doing its job. in update resource E.S.");
    }
    if (qubit->entangled_partner->entangled_partner != qubit) {
      error("2. Entanglement tracking is not doing its job. in update resource E.S.");
    }
  }
}
}  // namespace modules
}  // namespace quisp
