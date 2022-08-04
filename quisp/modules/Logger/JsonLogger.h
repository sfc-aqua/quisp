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
  void logPacket(std::string event_type, omnetpp::cMessage* msg) override;
  void setModule(omnetpp::cModule* mod) override;

 protected:
  std::shared_ptr<spdlog::logger> _logger;
  static std::string format(omnetpp::cMessage* msg);

  std::string module_path;
  omnetpp::cModule* module;
};
}  // namespace quisp::modules::Logger
