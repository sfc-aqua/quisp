#include "LoggerBase.h"
#include <cstddef>
#include "omnetpp/cmodule.h"

namespace quisp::modules::Logger {
LoggerBase::LoggerBase() {}
LoggerBase::~LoggerBase() {}
void LoggerBase::initializeLogger(utils::ComponentProvider& provider) {
  logger = provider.getLogger();
  logger->setModule(provider.module);
  auto* qnode = provider.getQNode();
  if (qnode != nullptr) logger->setQNodeAddress(qnode->par("address").intValue());
}
}  // namespace quisp::modules::Logger
