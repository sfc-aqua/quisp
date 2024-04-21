#pragma once

#include "IComponentProviderStrategy.h"

namespace quisp::utils {

class DefaultComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  DefaultComponentProviderStrategy(cModule *_self);
  cModule *getQNode() override;
  cModule *getNode() override;
  cModule *getNeighborNode(cModule *qnic) override;
  int getNodeAddr() override;
  bool isQNodeType(const cModuleType *const type) override;
  bool isBSANodeType(const cModuleType *const type) override;
  bool isEPPSNodeType(const cModuleType *const type) override;
  IStationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override;
  cModule *getQNIC(int qnic_index, QNIC_type qnic_type) override;
  int getNumQubits(int qnic_index, QNIC_type qnic_type) override;
  IRoutingDaemon *getRoutingDaemon() override;
  IHardwareMonitor *getHardwareMonitor() override;
  IRealTimeController *getRealTimeController() override;
  IQuantumBackend *getQuantumBackend() override;
  ILogger *getLogger() override;
  SharedResource *getSharedResource() override;

 private:
  const cModuleType *const QNodeType = cModuleType::get("modules.QNode");
  const cModuleType *const EPPSType = cModuleType::get("modules.EPPSNode");
  const cModuleType *const BSAType = cModuleType::get("modules.BSANode");
  cModule *self;
  cModule *getQRSA();
};

}  // namespace quisp::utils
