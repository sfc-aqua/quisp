#pragma once
#include <modules/Logger/ILogger.h>
#include <iostream>
namespace quisp_test::Logger {
using quisp::modules::Logger::ILogger;
class TestLogger : public ILogger {
 public:
  TestLogger() {}
  ~TestLogger() {}
  void logPacket(const std::string& event_type, omnetpp::cMessage const* const msg) override { std::cout << "logPacket: " << event_type << std::endl; };
  void logQubitState(quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_busy, bool is_allocated) override {
    std::cout << "logQubitState: " << qnic_index << ", " << qubit_index << ", busy: " << is_busy << ", allocated: " << is_allocated << std::endl;
  };

  void setModule(omnetpp::cModule const* const mod) override {}
  void setQNodeAddress(int addr) override {}
};
}  // namespace quisp_test::Logger
