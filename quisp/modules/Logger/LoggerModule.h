#pragma once
#include <omnetpp.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <memory>
#include "ILogger.h"

namespace quisp::modules::Logger {
class LoggerModule : public omnetpp::cSimpleModule {
 public:
  LoggerModule();
  ~LoggerModule();
  void initialize() override;
  ILogger* getLogger();

 protected:
  std::shared_ptr<spdlog::logger> logger;

  static std::string trim_quotes(std::string s);
};
Define_Module(LoggerModule);
}  // namespace quisp::modules::Logger
