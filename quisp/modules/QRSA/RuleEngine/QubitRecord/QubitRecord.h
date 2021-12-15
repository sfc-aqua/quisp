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
};

}  // namespace quisp::modules::qubit_record
