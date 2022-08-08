#include "LoggerBase.h"
#include "omnetpp/cmodule.h"

namespace quisp::modules::Logger {
LoggerBase::LoggerBase() {}
LoggerBase::~LoggerBase() {}
void LoggerBase::initializeLogger(utils::ComponentProvider& provider) {
  logger = provider.getLogger();
  logger->setModule(provider.module);
}

void LoggerBase::logPacket(const std::string& event_type, omnetpp::cMessage const* const msg) { logger->logPacket(event_type, msg); }
}  // namespace quisp::modules::Logger
