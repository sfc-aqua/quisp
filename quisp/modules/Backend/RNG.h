#pragma once

#include <backends/Backends.h>
#include <omnetpp.h>

namespace quisp::modules::backend {
class RNG :public backends::abstract::IRandomNumberGenerator {
 public:
  RNG(omnetpp::cModule* module) : module(module) {}
  double doubleRandom() override { return module->dblrand(); }

 private:
  omnetpp::cModule* module;
};
}  // namespace quisp::modules::backend
