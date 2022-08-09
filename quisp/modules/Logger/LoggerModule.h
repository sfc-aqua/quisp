#pragma once
#include <omnetpp.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <memory>
#include "ILogger.h"

namespace quisp::modules::Logger {

enum class LoggerType {
  Unknown,
  JsonLogger,
};

class LoggerModule : public omnetpp::cSimpleModule {
 public:
  LoggerModule();
  ~LoggerModule();
  void initialize() override;
  void finish() override;
  ILogger* getLogger();

 protected:
  std::shared_ptr<spdlog::logger> logger;
  LoggerType logger_type = LoggerType::Unknown;

  static std::string trimQuotes(std::string s);
  static LoggerType toLoggerType(const std::string& s);
};
Define_Module(LoggerModule);
}  // namespace quisp::modules::Logger
