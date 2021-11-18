#pragma once

#include <memory>
#include <vector>
#include "modules/QRSA/RuleEngine/IRuleEngine.h"
#include "rules/RuleSet.h"

namespace quisp::modules::qubit_state_store {
using quisp::modules::PhotonTransmissionConfig;
class QubitStateStore {
 public:
  QubitStateStore(int num_emitter_qnics, int num_receiver_qnics, int num_passive_receiver_qnics);
  ~QubitStateStore();
  int size();
  void setBusy(int qnic_type, int qnic_index, int qubit_index);
  void setFree(int qnic_type, int qnic_index, int qubit_index);

  bool hasFreeQubitInQNic(int qnic_type, int qnic_index);
  int countFreeQubitsInQNic(PhotonTransmissionConfig config);
  int countFreeQubitsInQNic(int qnic_type, int qnic_index);
  int getFreeQubitIndexInQNic(int qnic_type, int qnic_index);

 protected:
};
}  // namespace quisp::modules::qubit_state_store
