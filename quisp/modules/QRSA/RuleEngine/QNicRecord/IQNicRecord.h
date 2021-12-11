#pragma once
#include "utils/ComponentProvider.h"

namespace quisp::modules::qnic_record {
class IQNicRecord {
 public:
  virtual ~IQNicRecord(){};
  virtual int countNumFreeQubits() = 0;
  virtual int takeFreeQubitIndex() = 0;
  virtual void setQubitBusy(int qubit_index, bool is_busy) = 0;
};
}  // namespace quisp::modules::qnic_record
