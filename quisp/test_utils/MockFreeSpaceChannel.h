#pragma once

#include <omnetpp.h>
#include "channels/FSChannel.h"

namespace quisp_test::FSChannel {

class MockFreeSpaceChannel : public channels::FSChannel {
public:
    explicit MockFreeSpaceChannel(const char* channel_name);
    ~MockFreeSpaceChannel();
    void initialize() override {};
    void setNext_check_time(SimTime next_check);
    virtual cProperties* getProperties() const override {return props;};
    SimTime getNext_check_time() override;
    void addResultRecorders() override {};
    virtual simtime_t getTransmissionFinishTime() const override {return simTime();};
private:
    SimTime next_check_time;
    cProperties *props;
    cConfiguration *cfg;
};
}
