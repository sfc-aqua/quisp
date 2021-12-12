#pragma once

#include "../QubitRecord/IQubitRecord.h"
#include "IQNicRecord.h"
#include "modules/QNIC.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::qnic_record {

using quisp::modules::qubit_record::IQubitRecord;

class QNicRecord : public IQNicRecord {
 public:
  QNicRecord(utils::ComponentProvider& provider, int index, QNIC_type type);
  ~QNicRecord(){};

  int countNumFreeQubits() override;
  int takeFreeQubitIndex() override;
  void setQubitBusy(int qubit_index, bool is_busy) override;

  const int index;
  const QNIC_type type;

 protected:
  std::vector<std::unique_ptr<IQubitRecord>> qubits;
};

}  // namespace quisp::modules::qnic_record
