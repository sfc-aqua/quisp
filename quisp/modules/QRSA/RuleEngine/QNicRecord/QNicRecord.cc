#include "QNicRecord.h"
#include "../QubitRecord/QubitRecord.h"
#include "modules/QNIC.h"

namespace quisp::modules::qnic_record {
using quisp::modules::qubit_record::QubitRecord;

QNicRecord::QNicRecord(utils::ComponentProvider& provider, int index, QNIC_type type) : index(index), type(type) {
  int num_qubits = provider.getNumQubits(index, type);
  for (int i = 0; i < num_qubits; i++) {
    qubits.emplace_back(std::make_unique<QubitRecord>(index, type, i));
  }
}

int QNicRecord::countNumFreeQubits() {
  int num_free = 0;
  for (auto& qubit : qubits) {
    if (!qubit->isBusy()) {
      num_free++;
    }
  }
  return num_free;
}

int QNicRecord::takeFreeQubitIndex() {
  for (auto& qubit : qubits) {
    if (!qubit->isBusy()) {
      qubit->setBusy(true);
      return qubit->getIndex();
    }
  }
  return -1;
}

void QNicRecord::setQubitBusy(int qubit_index, bool is_busy) {
  if (qubits.size() <= qubit_index) {
    throw std::runtime_error("QNicRecord::setQubitBusy: Qubit index out of range");
  }
  qubits.at(qubit_index)->setBusy(is_busy);
}

}  // namespace quisp::modules::qnic_record
