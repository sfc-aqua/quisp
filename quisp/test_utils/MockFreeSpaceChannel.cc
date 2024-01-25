#include "MockFreeSpaceChannel.h"
#include "ChannelType.h"
#include "TestUtilFunctions.h"
#include "omnetpp/cchannel.h"
#include "omnetpp/ccomponent.h"
#include "Configuration.h"

namespace quisp_test::FSChannel {

using quisp_test::channel_type::TestChannelType;
using utils::getTestSimulation;

MockFreeSpaceChannel::MockFreeSpaceChannel(const char* channel_name) : omnetpp::cIdealChannel(channel_name) {
  setComponentType(new TestChannelType("test channel"));
  setName(channel_name);

  cfg = new quisp_test::configuration::Configuration;
  props = new cProperties;

  auto *sim = getTestSimulation();
  sim->registerComponent(this);
};

MockFreeSpaceChannel::~MockFreeSpaceChannel() {
  this->getSourceGate()->disconnect();
};

void MockFreeSpaceChannel::setNext_check_time(SimTime next_check) {
    next_check_time = next_check;
}

SimTime MockFreeSpaceChannel::getNext_check_time() {
    return next_check_time;
}
}
