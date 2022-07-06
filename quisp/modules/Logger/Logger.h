#pragma once
#include <messages/classical_messages.h>
#include <spdlog/spdlog.h>
#include <memory>
#include "ILogger.h"

namespace quisp::modules::Logger {

/**
 * \brief Default Logger class using spdlog library
 *

 */
class Logger : public ILogger {
 public:
  Logger(std::shared_ptr<spdlog::logger> logger);
  virtual ~Logger();
  void logPacket(std::string event_type, omnetpp::cMessage* msg);

 protected:
  std::shared_ptr<spdlog::logger> _logger;
};
}  // namespace quisp::modules::Logger

std::ostream& operator<<(std::ostream& os, const quisp::messages::ConnectionSetupRequest& pk) {
  return os << "\"actual_dest_addr\": " << pk.getActual_destAddr() << ", \"actual_src_addr\": " << pk.getActual_srcAddr() << ", \"num_measure\": " << pk.getNum_measure()
            << ", \"num_required_bell_pairs\": " << pk.getNumber_of_required_Bellpairs();
}

std::ostream& operator<<(std::ostream& os, const omnetpp::cMessage*& pk) { return os << "\"cmessage test\": "; }
