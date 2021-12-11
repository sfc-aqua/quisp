#pragma once
namespace quisp::modules::qubit_record {
class IQubitRecord {
 public:
  virtual ~IQubitRecord() {}
  virtual bool isBusy() const = 0;
  virtual void setBusy(bool _is_busy) = 0;
  virtual int getIndex() const = 0;
};
}  // namespace quisp::modules::qubit_record
