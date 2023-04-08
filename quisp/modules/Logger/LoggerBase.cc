#include "LoggerBase.h"
#include "omnetpp/cmodule.h"

namespace quisp::modules::Logger {
LoggerBase::LoggerBase() {}
LoggerBase::~LoggerBase() {}
void LoggerBase::initializeLogger(utils::ComponentProvider& provider) {
  logger = provider.getLogger();
  logger->setModule(provider.module);
  auto* qnode = provider.getQNode();
  if (qnode != nullptr) logger->setQNodeAddress(provider.getNodeAddr());
}
}  // namespace quisp::modules::Logger
