#pragma once
#include <omnetpp.h>
#include "omnetpp/ceventheap.h"

namespace quisp_test::simulation {

using omnetpp::cEnvir;
using omnetpp::cEvent;
using omnetpp::cSimulation;

class TestSimulation : public cSimulation {
 public:
  TestSimulation(const char* name, cEnvir* env);
  void finishNetworkSetup();
  void run();
  void setConfigValue(const char* key, const char* value);
  bool executeNextEvent();
};

}  // namespace quisp_test::simulation