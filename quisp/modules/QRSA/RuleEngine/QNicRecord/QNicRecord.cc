#include "QNicRecord.h"
#include "modules/QNIC.h"

namespace quisp::modules::qnic_record {
QNicRecord::QNicRecord(int index, QNIC_type type) : index(index), type(type) {}

}  // namespace quisp::modules::qnic_record
