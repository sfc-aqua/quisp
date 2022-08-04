#pragma once
#include <modules/Logger/ILogger.h>
#include <iostream>
namespace quisp_test::Logger {
using quisp::modules::Logger::ILogger;
class TestLogger : public ILogger {
 public:
  TestLogger() {}
  ~TestLogger() {}
  void logPacket(std::string event_type, omnetpp::cMessage* msg) override { std::cout << "logPacket: " << event_type << std::endl; };
  void setModule(omnetpp::cModule* mod) override {}
};
}  // namespace quisp_test::Logger
