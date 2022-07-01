#pragma once
#include <omnetpp.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <memory>

namespace quisp::modules::Logger {
class LoggerModule : public omnetpp::cSimpleModule {
 public:
  LoggerModule();
  ~LoggerModule();
  void initialize() override;
  std::shared_ptr<spdlog::logger> logger;
};
Define_Module(LoggerModule);
}  // namespace quisp::modules::Logger
