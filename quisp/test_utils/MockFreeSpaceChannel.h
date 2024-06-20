#pragma once

#include <omnetpp.h>
#include "channels/FreeSpaceChannel.h"

namespace quisp_test::FreeSpaceChannel {

class MockFreeSpaceChannel : public channels::FreeSpaceChannel {
 public:
  explicit MockFreeSpaceChannel(const char* channel_name);
  ~MockFreeSpaceChannel();
  void initialize() override{};
  void setNextCheckTime(SimTime next_check);
  virtual cProperties* getProperties() const override { return props; };
  SimTime getNextCheckTime() override;
  void addResultRecorders() override{};
  virtual simtime_t getTransmissionFinishTime() const override { return simTime(); };

 private:
  SimTime next_check_time;
  cProperties* props;
  cConfiguration* cfg;
};
}  // namespace quisp_test::FreeSpaceChannel
