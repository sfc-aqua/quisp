#pragma once

#include "IQubitRecord.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
namespace quisp::modules::qubit_record {
class QubitRecord : public IQubitRecord {
  ~QubitRecord();

 public:
  QubitRecord(int qnic_index, QNIC_type qnic_type, int qubit_index);

 protected:
  QNIC_type qnic_type;
  int qnic_index;
  int qubit_index;
};
}  // namespace quisp::modules::qubit_record
