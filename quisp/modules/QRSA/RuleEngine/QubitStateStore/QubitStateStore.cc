#include "QubitStateStore.h"

namespace quisp::modules::qubit_state_store {
QubitStateStore::QubitStateStore(int num_emitter_qnics, int num_receiver_qnics, int num_passive_receiver_qnics) {}
QubitStateStore::~QubitStateStore() {}
int QubitStateStore::size() { return 0; }
void QubitStateStore::setBusy(int qnic_type, int qnic_index, int qubit_index) {}
void QubitStateStore::setFree(int qnic_type, int qnic_index, int qubit_index) {}

bool QubitStateStore::hasFreeQubitInQNic(int qnic_type, int qnic_index) { return false; }
int QubitStateStore::countFreeQubitsInQNic(int qnic_type, int qnic_index) { return 0; }
int QubitStateStore::getFreeQubitIndexInQNic(int qnic_type, int qnic_index) { return 0; }

}  // namespace quisp::modules::qubit_state_store
