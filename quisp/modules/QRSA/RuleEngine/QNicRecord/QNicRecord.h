#pragma once

#include <memory>

#include <modules/Logger/ILogger.h>
#include <modules/QNIC.h>
#include <utils/ComponentProvider.h>
#include "../QubitRecord/IQubitRecord.h"
#include "IQNicRecord.h"

namespace quisp::modules::qnic_record {

using quisp::modules::qubit_record::IQubitRecord;

class QNicRecord : public IQNicRecord {
 public:
  QNicRecord(utils::ComponentProvider& provider, int index, QNIC_type type, Logger::ILogger* logger = nullptr);
  ~QNicRecord(){};

  int countNumFreeQubits() override;
  int takeFreeQubitIndex() override;
  void setQubitBusy(int qubit_index, bool is_busy) override;
  qrsa::IQubitRecord* getQubit(int qubit_index) override;

  const int index;
  const QNIC_type type;

 protected:
  // QNicRecord class has the ownership of the QubitRecords.
  // if QNicRecord is destroyed, all QubitRecords will be destroyed automatically.
  std::vector<std::unique_ptr<IQubitRecord>> qubits;
};

}  // namespace quisp::modules::qnic_record
