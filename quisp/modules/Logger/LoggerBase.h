#pragma once
#include "ILogger.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::Logger {

/**
 * \brief LoggerBase class integrate abilities to log simulation results into
 * your components.
 */
class LoggerBase {
 public:
  LoggerBase();
  ~LoggerBase();
  void initializeLogger(utils::ComponentProvider& provider);
  void logPacket(std::string event_type, omnetpp::cMessage* msg);

 protected:
  ILogger* logger = nullptr;
};

}  // namespace quisp::modules::Logger
