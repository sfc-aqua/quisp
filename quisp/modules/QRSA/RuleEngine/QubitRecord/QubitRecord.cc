#include "QubitRecord.h"

#include <omnetpp/cexception.h>

#include "modules/Logger/ILogger.h"

namespace quisp::modules::qubit_record {

QubitRecord::QubitRecord(QNIC_type qnic_type, int qnic_index, int qubit_index, Logger::ILogger* logger)
    : qnic_type(qnic_type), qnic_index(qnic_index), qubit_index(qubit_index), logger(logger) {}

QubitRecord::~QubitRecord() {}

bool QubitRecord::isBusy() const { return is_busy; }

void QubitRecord::setBusy(bool _is_busy) {
  if (is_busy == _is_busy) {
    throw omnetpp::cRuntimeError("QubitRecord::setBusy: is_busy is already set to the same value. Qubit(%s, %d, %d)", QNIC_names[qnic_type], qnic_index, qubit_index);
  }
  is_busy = _is_busy;
  logState();
}

bool QubitRecord::isAllocated() const { return is_allocated; }

void QubitRecord::setAllocated(bool _is_allocated) {
  if (is_allocated == _is_allocated) {
    throw omnetpp::cRuntimeError("QubitRecord::setAllocated: is_allocated is already set to the same value. Qubit(%s, %d, %d)", QNIC_names[qnic_type], qnic_index, qubit_index);
  }
  is_allocated = _is_allocated;
  logState();
}

int QubitRecord::getQubitIndex() const { return qubit_index; }
int QubitRecord::getQNicIndex() const { return qnic_index; }
QNIC_type QubitRecord::getQNicType() const { return qnic_type; }

void QubitRecord::logState() { logger->logQubitState(qnic_type, qnic_index, qubit_index, is_busy, is_allocated); }

}  // namespace quisp::modules::qubit_record
