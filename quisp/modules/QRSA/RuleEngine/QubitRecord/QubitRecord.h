#pragma once

#include <modules/Logger/ILogger.h>
#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include "IQubitRecord.h"

namespace quisp::modules::qubit_record {

class QubitRecord : public IQubitRecord {
 public:
  QubitRecord(QNIC_type qnic_type, int qnic_index, int qubit_index, Logger::ILogger* logger = nullptr);
  ~QubitRecord();
  bool isBusy() const override;
  void setBusy(bool _is_busy) override;
  bool isAllocated() const override;
  void setAllocated(bool _is_allocated) override;
  int getQubitIndex() const override;
  int getQNicIndex() const override;
  QNIC_type getQNicType() const override;
  bool isRuleApplied(unsigned long rule_id) const override;
  void markRuleApplied(unsigned long rule_id) override;
  void clearAppliedRules() override;

 protected:
  QNIC_type qnic_type;
  int qnic_index;
  int qubit_index;
  bool is_busy = false;
  bool is_allocated = false;
  std::vector<unsigned long> applied_rule_ids;
  Logger::ILogger* logger = nullptr;

  inline void logState();
};

}  // namespace quisp::modules::qubit_record
