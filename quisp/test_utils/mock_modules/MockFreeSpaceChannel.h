/*
 * MockFreeSpaceChannel.h
 *
 *  Created on: Jan 18, 2024
 *      Author: paolo
 */

#ifndef TEST_UTILS_MOCK_MODULES_MOCKFREESPACECHANNEL_H_
#define TEST_UTILS_MOCK_MODULES_MOCKFREESPACECHANNEL_H_

#include <omnetpp.h>
#include "channels/FSChannel.h"

using namespace omnetpp;
using quisp::channels::FSChannel;

class MockFreeSpaceChannel : FSChannel {
public:
    MockFreeSpaceChannel();
    virtual ~MockFreeSpaceChannel();
    void setNext_check_time(SimTime next_check);
    SimTime getNext_check_time() override;
private:
    SimTime next_check_time;

};

#endif /* TEST_UTILS_MOCK_MODULES_MOCKFREESPACECHANNEL_H_ */
