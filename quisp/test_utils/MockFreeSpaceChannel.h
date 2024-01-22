#pragma once

#include <omnetpp.h>
#include "channels/FSChannel.h"

namespace quisp_test::FSChannel {

class MockFreeSpaceChannel : public omnetpp::cIdealChannel {
public:
    explicit MockFreeSpaceChannel(const char* channel_name);
    ~MockFreeSpaceChannel();
    void setNext_check_time(SimTime next_check);
    SimTime getNext_check_time();
private:
    SimTime next_check_time;
};
}
