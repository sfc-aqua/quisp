#include "QubitRecord.h"
#include "omnetpp/cexception.h"

namespace quisp::modules::qubit_record {

QubitRecord::QubitRecord(int qnic_index, QNIC_type qnic_type, int qubit_index) : qnic_type(qnic_type), qnic_index(qnic_index), qubit_index(qubit_index) {}

QubitRecord::~QubitRecord() {}

bool QubitRecord::isBusy() const { return is_busy; }

void QubitRecord::setBusy(bool _is_busy) {
  if (is_busy == _is_busy) {
    throw omnetpp::cRuntimeError("QubitRecord::setBusy: is_busy is already set to the same value. Qubit(%s, %d, %d)", QNIC_names[qnic_type], qnic_index, qubit_index);
  }
  is_busy = _is_busy;
}

int QubitRecord::getIndex() const { return qubit_index; }

}  // namespace quisp::modules::qubit_record
