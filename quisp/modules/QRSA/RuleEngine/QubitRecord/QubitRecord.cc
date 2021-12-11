#include "QubitRecord.h"
namespace quisp::modules::qubit_record {
QubitRecord::QubitRecord(int qnic_index, QNIC_type qnic_type, int qubit_index) : qnic_type(qnic_type), qnic_index(qnic_index), qubit_index(qubit_index) {}

}  // namespace quisp::modules::qubit_record
