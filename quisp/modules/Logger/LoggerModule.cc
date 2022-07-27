#include "LoggerModule.h"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include "Logger.h"

namespace quisp::modules::Logger {

LoggerModule::LoggerModule() {}

LoggerModule::~LoggerModule() {}

void LoggerModule::initialize() {
  if (logger != nullptr) return;
  logger = spdlog::basic_logger_mt<spdlog::async_factory>("default_sim_result_logger", trim_quotes(par("log_filename").str()));
}

ILogger* LoggerModule::getLogger() { return new Logger(logger); }

std::string LoggerModule::trim_quotes(std::string s) {
  if (s.length() == 0) return s;
  if (s[0] == '\"') s = s.substr(1);
  if (s[s.length() - 1] == '\"') s = s.substr(0, s.length() - 1);
  return s;
}

}  // namespace quisp::modules::Logger
