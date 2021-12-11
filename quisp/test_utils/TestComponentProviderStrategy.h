#pragma once

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <modules/QRSA/RealTimeController/IRealTimeController.h>
#include <utils/IComponentProviderStrategy.h>
#include "Simulation.h"

namespace quisp_test {
namespace strategy {

using quisp::modules::IHardwareMonitor;
using quisp::modules::IRealTimeController;
using quisp::modules::IRoutingDaemon;
using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_type;
using quisp::utils::IComponentProviderStrategy;
using quisp_test::simulation::TestSimulation;

class TestComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  TestComponentProviderStrategy() {}
  virtual ~TestComponentProviderStrategy() {}
  virtual cModule *getQNode() override { return nullptr; };
  virtual cModule *getNeighborNode(cModule *qnic) override { return nullptr; };
  virtual bool isQNodeType(const cModuleType *const type) override { return false; };
  virtual bool isHoMNodeType(const cModuleType *const type) override { return false; };
  virtual bool isSPDCNodeType(const cModuleType *const type) override { return false; };
  virtual IStationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override { return nullptr; };
  virtual cModule *getQNIC(int qnic_index, QNIC_type qnic_type) override { return nullptr; };
  virtual int getNumQubits(int qnic_index, QNIC_type qnic_type) override { return 0; };
  virtual IRoutingDaemon *getRoutingDaemon() override { return nullptr; };
  virtual IHardwareMonitor *getHardwareMonitor() override { return nullptr; };
  virtual IRealTimeController *getRealTimeController() override { return nullptr; };
};

}  // namespace strategy
}  // namespace quisp_test
