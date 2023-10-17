#pragma once

#include <omnetpp.h>
#include <memory>

using namespace omnetpp;

namespace quisp::modules {

class IHardwareMonitor : public cSimpleModule {
 public:
  virtual ~IHardwareMonitor(){};
  virtual double getLinkCost(int neighbor_address) = 0;
};
}  // namespace quisp::modules
