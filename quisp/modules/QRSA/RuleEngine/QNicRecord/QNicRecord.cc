#include "QNicRecord.h"
#include "../QubitRecord/QubitRecord.h"
#include "modules/QNIC.h"

namespace quisp::modules::qnic_record {
using quisp::modules::qubit_record::QubitRecord;

QNicRecord::QNicRecord(utils::ComponentProvider& provider, int index, QNIC_type type, Logger::ILogger* logger) : index(index), type(type) {
  int num_qubits = provider.getNumQubits(index, type);
  for (int i = 0; i < num_qubits; i++) {
    qubits.emplace_back(std::make_unique<QubitRecord>(type, index, i, logger));
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
      return qubit->getQubitIndex();
    }
  }
  return -1;
}
qrsa::IQubitRecord* QNicRecord::getQubit(int qubit_index) {
  if (qubits.size() <= qubit_index) {
    throw omnetpp::cRuntimeError("QNicRecord::getQubit: Qubit index:%d out of range. QNIC{%s, %d}, qubits.size(): %lu", qubit_index, QNIC_names[type], index, qubits.size());
  }
  return qubits.at(qubit_index).get();
}

void QNicRecord::setQubitBusy(int qubit_index, bool is_busy) {
  auto* qubit = getQubit(qubit_index);
  qubit->setBusy(is_busy);
}

}  // namespace quisp::modules::qnic_record
