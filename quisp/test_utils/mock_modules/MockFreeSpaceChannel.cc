/*
 * MockFreeSpaceChannel.cpp
 *
 *  Created on: Jan 18, 2024
 *      Author: paolo
 */

#include "MockFreeSpaceChannel.h"

void MockFreeSpaceChannel::setNext_check_time(SimTime next_check) {
    next_check_time = next_check;
}

SimTime MockFreeSpaceChannel::getNext_check_time() {
    return next_check_time;
}

