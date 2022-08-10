#include "LoggerModule.h"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include "JsonLogger.h"

namespace quisp::modules::Logger {

LoggerModule::LoggerModule() {}

LoggerModule::~LoggerModule() {
  if (logger != nullptr) {
    spdlog::shutdown();
  }
}

void LoggerModule::initialize() {
  logger_type = toLoggerType(par("logger"));
  if (logger != nullptr) return;
  if (logger_type == LoggerType::JsonLogger) {
    logger = spdlog::basic_logger_mt<spdlog::async_factory>("default_sim_result_logger", trimQuotes(par("log_filename").str()));
    return;
  }
  error("unknown logger specified: %s", par("logger").str().c_str());
}

void LoggerModule::finish() { logger->flush(); }

ILogger* LoggerModule::getLogger() { return new JsonLogger(logger); }

std::string LoggerModule::trimQuotes(std::string s) {
  if (s.length() == 0) return s;
  if (s[0] == '\"') s = s.substr(1);
  if (s[s.length() - 1] == '\"') s = s.substr(0, s.length() - 1);
  return s;
}

LoggerType LoggerModule::toLoggerType(const std::string& s) {
  if (s == "JsonLogger") return LoggerType::JsonLogger;
  return LoggerType::Unknown;
}

}  // namespace quisp::modules::Logger
