#include "LoggerBase.h"

namespace quisp::modules::Logger {
LoggerBase::LoggerBase() {}
LoggerBase::~LoggerBase() {}
void LoggerBase::initializeLogger(utils::ComponentProvider& provider) { logger = provider.getLogger(); }

}  // namespace quisp::modules::Logger
