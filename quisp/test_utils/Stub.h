/*
 * Stub.h
 *
 *  Created on: Jan 18, 2024
 *      Author: paolo
 * I use this class in tests: whenever a Channel needs to be included in a Module's test, I
 * plug one end to the module under test and the other to this stub.
 */

#pragma once

#include <omnetpp.h>
#include "TestUtilFunctions.h"
#include "ModuleType.h"

using quisp_test::module_type::TestModuleType;

class Stub : public omnetpp::cModule {
  public:
  explicit Stub();
  void addResultRecorders() override {};

};
