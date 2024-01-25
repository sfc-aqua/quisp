#pragma once

#include <omnetpp.h>
#include "channels/FSChannel.h"

namespace quisp_test::FSChannel {

class MockFreeSpaceChannel : public omnetpp::cIdealChannel {
public:
    explicit MockFreeSpaceChannel(const char* channel_name);
    ~MockFreeSpaceChannel();
    void setNext_check_time(SimTime next_check);
    const cProperties* getProperties() {return props;};
    SimTime getNext_check_time();
    void addResultRecorders() override {};
private:
    SimTime next_check_time;
    cProperties *props;
    cConfiguration *cfg;
};
}
