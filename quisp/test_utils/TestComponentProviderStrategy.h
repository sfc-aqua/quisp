#pragma once

#include <modules/Logger/ILogger.h>
#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <modules/QRSA/RealTimeController/IRealTimeController.h>
#include <modules/SharedResource/SharedResource.h>
#include <utils/IComponentProviderStrategy.h>

#include "Logger.h"
#include "Simulation.h"

namespace quisp_test {
namespace strategy {

using quisp::modules::IHardwareMonitor;
using quisp::modules::IRealTimeController;
using quisp::modules::IRoutingDaemon;
using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_type;
using quisp::modules::common::IQuantumBackend;
using quisp::modules::Logger::ILogger;
using quisp::modules::SharedResource::SharedResource;
using quisp::utils::IComponentProviderStrategy;
using quisp_test::Logger::TestLogger;
using quisp_test::simulation::TestSimulation;

struct QNicSpec {
  QNIC_type type;
  int qnic_index;
  int num_qubits;
};

class TestComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  TestComponentProviderStrategy() : qnic_specs({}) {}
  TestComponentProviderStrategy(std::vector<QNicSpec> specs) : qnic_specs(specs) {}
  virtual ~TestComponentProviderStrategy() {}
  virtual cModule *getQNode() override { return nullptr; };
  virtual cModule *getNode() override { return nullptr; };
  virtual cModule *getNeighborNode(cModule *qnic) override { return nullptr; };
  virtual int getNodeAddr() override { return -1; };
  virtual bool isQNodeType(const cModuleType *const type) override { return false; };
  virtual bool isBSANodeType(const cModuleType *const type) override { return false; };
  virtual bool isEPPSNodeType(const cModuleType *const type) override { return false; };
  virtual IStationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override { return nullptr; };
  virtual cModule *getQNIC(int qnic_index, QNIC_type qnic_type) override { return nullptr; };
  virtual IRoutingDaemon *getRoutingDaemon() override { return nullptr; };
  virtual IHardwareMonitor *getHardwareMonitor() override { return nullptr; };
  virtual IRealTimeController *getRealTimeController() override { return nullptr; };
  virtual IQuantumBackend *getQuantumBackend() override { return nullptr; };
  virtual ILogger *getLogger() override { return new TestLogger(); };
  virtual SharedResource *getSharedResource() override { return nullptr; };
  std::vector<QNicSpec> qnic_specs;
  virtual int getNumQubits(int qnic_index, QNIC_type qnic_type) override {
    for (auto spec : qnic_specs) {
      if (spec.qnic_index == qnic_index && spec.type == qnic_type) {
        return spec.num_qubits;
      }
    }
    return 0;
  };
};

}  // namespace strategy
}  // namespace quisp_test
