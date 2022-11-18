#pragma once
#include "ILogger.h"

namespace quisp::modules::Logger {

/**
 * \brief DisabledLogger class is used for
 */
class DisabledLogger : public ILogger {
 public:
  DisabledLogger(){};
  virtual ~DisabledLogger(){};
  void logPacket(const std::string& event_type, omnetpp::cMessage const* const msg) override { return; }
  void logQubitState(quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_busy, bool is_allocated) override { return; }
  void logBellPairInfo(const std::string& event_type, int partner_addr, quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index) override { return; }
  void setModule(omnetpp::cModule const* const mod) override { return; }
  void setQNodeAddress(int addr) override { return; }
};
}  // namespace quisp::modules::Logger