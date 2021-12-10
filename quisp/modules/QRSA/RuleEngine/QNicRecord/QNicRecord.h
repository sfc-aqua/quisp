#pragma once
#include "IQNicRecord.h"
#include "modules/QNIC.h"
namespace quisp::modules::qnic_record {

class QNicRecord : public IQNicRecord {
 public:
  QNicRecord(int index, QNIC_type type);
  ~QNicRecord(){};

  const int index;
  const QNIC_type type;
};
}  // namespace quisp::modules::qnic_record
