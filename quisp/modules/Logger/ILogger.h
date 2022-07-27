#pragma once
#include <omnetpp.h>
#include "omnetpp/csimplemodule.h"

namespace quisp::modules::Logger {

/**
 * \brief Interface of Logger class. Logger class that inherits ILogger is
 * responsible for logging simulation results.
 *
 * Components should not know the detail of Logger class implementation for
 * testability, maintainability, and expandability.
 * The logger class that inherits ILogger class contains QNode informations
 * and component information, and also provides basic functions to log
 * simulation results. Components use a logger instance to log their
 * information. LoggerModule instantiate Logger class and hold it.
 * Components use the Logger instance via ComponentProvider.
 *
 * \see Logger
 * \see ComponentProvider
 */
class ILogger {
 public:
  virtual ~ILogger(){};
  virtual void logPacket(std::string event_type, omnetpp::cMessage* msg) = 0;
  virtual void setModule(omnetpp::cModule* mod) = 0;
};
}  // namespace quisp::modules::Logger
