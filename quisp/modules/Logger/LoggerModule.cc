#include "LoggerModule.h"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include "JsonLogger.h"

namespace quisp::modules::Logger {

LoggerModule::LoggerModule() {}

LoggerModule::~LoggerModule() {
  if (logger_type == LoggerType::JsonLogger) {
    if (spdlog_logger != nullptr) spdlog::shutdown();
    return;
  }
}

void LoggerModule::initialize() {
  if (!par("enable_log").boolValue()) return;
  logger_type = toLoggerType(par("logger"));
  if (logger_type == LoggerType::JsonLogger) {
    if (spdlog_logger != nullptr) return;

#ifndef __EMSCRIPTEN__
    spdlog_logger = spdlog::basic_logger_mt<spdlog::async_factory>("default_sim_result_logger", trimQuotes(par("log_filename").str()));
#else
    // if the platform is WebAssembly, use single thread logger
    spdlog_logger = spdlog::basic_logger_st("default_sim_result_logger", trimQuotes(par("log_filename").str()));
#endif

    return;
  }
  error("unknown logger specified: %s", par("logger").str().c_str());
}

void LoggerModule::finish() {
  if (logger_type == LoggerType::JsonLogger) {
    if (spdlog_logger != nullptr) spdlog_logger->flush();
  }
}

ILogger* LoggerModule::getLogger() {
  if (logger_type == LoggerType::JsonLogger) {
    if (spdlog_logger == nullptr) error("failed to instantiate logger. spdlog is not initialized.");
    return new JsonLogger(spdlog_logger);
  }
  return nullptr;
}

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
