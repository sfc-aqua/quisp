#pragma once

#include <memory>

#include "utils.h"

namespace quisp::utils {

class IComponentProviderStrategy {
 public:
  IComponentProviderStrategy() {}
  virtual ~IComponentProviderStrategy() {}
  virtual cModule *getQNode() = 0;
  virtual cModule *getNode() = 0;
  virtual cModule *getNeighborNode(cModule *qnic) = 0;
  virtual int getNodeAddr() = 0;
  virtual bool isQNodeType(const cModuleType *const module) = 0;
  virtual bool isBSANodeType(const cModuleType *const module) = 0;
  virtual bool isEPPSNodeType(const cModuleType *const module) = 0;
  virtual IStationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual cModule *getQNIC(int qnic_index, QNIC_type qnic_type) = 0;
  virtual int getNumQubits(int qnic_index, QNIC_type qnic_type) = 0;
  virtual IRoutingDaemon *getRoutingDaemon() = 0;
  virtual IHardwareMonitor *getHardwareMonitor() = 0;
  virtual IRealTimeController *getRealTimeController() = 0;
  virtual IQuantumBackend *getQuantumBackend() = 0;
  virtual ILogger *getLogger() = 0;
  virtual SharedResource *getSharedResource() = 0;
};

}  // namespace quisp::utils
