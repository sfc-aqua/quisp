#pragma once

namespace quisp::modules::qubit_record {

/**
 * @brief The QubitRecord interface.
 *
 * This interface is used to represent a qubit on a software layer.
 * StationaryQubit is the representaiton of a physical qubit, not for a software layer.
 * The subclass of this interface should contain the state of the qubit like busy or not, allocation.
 * If you want to add more state to StationaryQubit, you should consider to do it for the subclass.
 * This class is used by mainly QNicRecord.
 */
class IQubitRecord {
 public:
  virtual ~IQubitRecord() {}
  virtual bool isBusy() const = 0;
  virtual void setBusy(bool _is_busy) = 0;
  virtual int getIndex() const = 0;
};

}  // namespace quisp::modules::qubit_record
