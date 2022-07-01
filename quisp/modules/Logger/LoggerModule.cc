#include "LoggerModule.h"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

namespace quisp::modules::Logger {
LoggerModule::LoggerModule() {}
LoggerModule::~LoggerModule() {}
void LoggerModule::initialize() { logger = spdlog::basic_logger_mt<spdlog::async_factory>("default_sim_result_logger", "results/sim_result.log"); }

}  // namespace quisp::modules::Logger
