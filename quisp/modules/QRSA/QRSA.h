#pragma once
#include <memory>
#include "RuleEngine/QubitRecord/IQubitRecord.h"
#include "modules/QNIC.h"

namespace quisp::modules::qrsa {

using IQubitRecord = quisp::modules::qubit_record::IQubitRecord;
// points qnode local qubit
struct LocalQubitRef {
  LocalQubitRef(QNIC_type qnic_type, int qnic_index, int qubit_index) : qnic_type(qnic_type), qnic_index(qnic_index), qubit_index(qubit_index) {}
  const QNIC_type qnic_type;
  const int qnic_index;
  const int qubit_index;
};
}  // namespace quisp::modules::qrsa
