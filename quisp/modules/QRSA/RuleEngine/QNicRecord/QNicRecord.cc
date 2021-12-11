#include "QNicRecord.h"
#include "../QubitRecord/QubitRecord.h"
#include "modules/QNIC.h"

namespace quisp::modules::qnic_record {
using quisp::modules::qubit_record::QubitRecord;

QNicRecord::QNicRecord(utils::ComponentProvider& provider, int index, QNIC_type type) : index(index), type(type) {
  int num_qubits = provider.getNumQubits(index, type);
  for (int i = 0; i < num_qubits; i++) {
    auto* qubit = provider.getStationaryQubit(index, i, type);
    qubits.emplace_back(std::make_unique<QubitRecord>(index, type, i));
  }
}

}  // namespace quisp::modules::qnic_record
