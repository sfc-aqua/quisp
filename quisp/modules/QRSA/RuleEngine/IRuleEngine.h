#pragma once

#include <omnetpp.h>

#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <rules/RuleSet.h>

using namespace omnetpp;

namespace quisp::modules {

class IRuleEngine : public cSimpleModule {
 public:
  ~IRuleEngine() {}
  virtual void freeResource(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual void freeConsumedResource(int qnic_index, IStationaryQubit *qubit, QNIC_type qnic_type) = 0;
  virtual void ResourceAllocation(int qnic_type, int qnic_index) = 0;
};

}  // namespace quisp::modules
