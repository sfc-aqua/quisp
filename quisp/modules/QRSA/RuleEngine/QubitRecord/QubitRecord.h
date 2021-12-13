#pragma once

#include "IQubitRecord.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"

namespace quisp::modules::qubit_record {

class QubitRecord : public IQubitRecord {
 public:
  QubitRecord(int qnic_index, QNIC_type qnic_type, int qubit_index);
  ~QubitRecord();
  bool isBusy() const override;
  void setBusy(bool _is_busy) override;
  int getIndex() const override;

 protected:
  QNIC_type qnic_type;
  int qnic_index;
  int qubit_index;
  bool is_busy = false;
};

}  // namespace quisp::modules::qubit_record
