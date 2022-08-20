#pragma once
#include <messages/classical_messages.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <memory>
#include "ILogger.h"

namespace quisp::modules::Logger {

/**
 * \brief JsonLogger class uses spdlog library and yields jsonl format log
 */
class JsonLogger : public ILogger {
 public:
  JsonLogger(std::shared_ptr<spdlog::logger> logger);
  virtual ~JsonLogger();
  void logPacket(const std::string& event_type, omnetpp::cMessage const* const msg) override;
  void logQubitState(quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_busy, bool is_allocated) override;
  void logBellPairInfo(const std::string& event_type, int partner_addr, quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index) override;
  void setModule(omnetpp::cModule const* const mod) override;
  void setQNodeAddress(int addr) override;

 protected:
  std::shared_ptr<spdlog::logger> _logger;
  static std::string format(omnetpp::cMessage const* const msg);

  std::string module_path;
  int qnode_address = -1;
  omnetpp::cModule const* module;
};
}  // namespace quisp::modules::Logger
