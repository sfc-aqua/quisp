/*
 * Stub.h
 *
 *  Created on: Jan 18, 2024
 *      Author: paolo
 * I use this class in tests: whenever a Channel needs to be included in a Module's test, I
 * plug one end to the module under test and the other to this stub.
 */

#ifndef TEST_UTILS_STUB_H_
#define TEST_UTILS_STUB_H_

#include <omnetpp.h>

using namespace omnetpp;

class Stub: public cModule {
    private:
    TestGate* stub_gate;
};

#endif /* TEST_UTILS_STUB_H_ */
