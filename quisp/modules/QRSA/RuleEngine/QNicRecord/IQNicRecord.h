#pragma once

#include <modules/QRSA/QRSA.h>
#include <utils/ComponentProvider.h>

namespace quisp::modules::qnic_record {

/** IQNicRecord
 * @brief Interface for QNIC record.
 *
 * This interface is used to access the QNIC record.
 * you can add more states to the QNIC record if its lifecycle is related to QNIC.
 */
class IQNicRecord {
 public:
  virtual ~IQNicRecord(){};
  virtual int countNumFreeQubits() = 0;
  virtual int takeFreeQubitIndex() = 0;
  virtual void setQubitBusy(int qubit_index, bool is_busy) = 0;
  virtual qrsa::IQubitRecord* getQubit(int qubit_index) = 0;
};

}  // namespace quisp::modules::qnic_record
