#include "Logger.h"

namespace quisp::modules::Logger {
Logger::Logger(std::shared_ptr<spdlog::logger> logger) : _logger(logger) {
  std::string jsonpattern = {"{\"time\": \"%Y-%m-%dT%H:%M:%S\", \"level\": \"%^%l%$\", %v}"};
  _logger->set_pattern(jsonpattern);
}
Logger::~Logger() {}
void Logger::logPacket(std::string event_type, omnetpp::cMessage* msg) { _logger->info("\"event_type\": \"{}\", {}", event_type, msg); }

}  // namespace quisp::modules::Logger
