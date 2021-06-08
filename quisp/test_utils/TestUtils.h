#ifndef QUISP_UTILS_TEST_UTILS_H_
#define QUISP_UTILS_TEST_UTILS_H_

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <modules/QRSA/HardwareMonitor/IHardwareMonitor.h>
#include <modules/QRSA/RealTimeController/IRealTimeController.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>
#include <utils/IComponentProviderStrategy.h>
#include <utils/utils.h>
#include <memory>

namespace quisp_test {
using quisp::modules::IHardwareMonitor;
using quisp::modules::IRealTimeController;
using quisp::modules::IRoutingDaemon;
using quisp::modules::QNIC_type;
using quisp::modules::StationaryQubit;
using quisp::utils::IComponentProviderStrategy;

void setParInt(cModule *module, const char *name, const int val);
void setParBool(cModule *module, const char *name, const bool val);
void setParStr(cModule *module, const char *name, const char *val);

class TestComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  TestComponentProviderStrategy() {}
  virtual ~TestComponentProviderStrategy() {}
  virtual cModule *getQNode() override { return nullptr; };
  virtual cModule *getNeighborNode(cModule *qnic) override { return nullptr; };
  virtual bool isQNodeType(const cModuleType *const type) override { return false; };
  virtual bool isHoMNodeType(const cModuleType *const type) override { return false; };
  virtual bool isSPDCNodeType(const cModuleType *const type) override { return false; };
  virtual StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override { return nullptr; };
  virtual cModule *getQNIC(int qnic_index, QNIC_type qnic_type) override { return nullptr; };
  virtual IRoutingDaemon *getRoutingDaemon() override { return nullptr; };
  virtual IHardwareMonitor *getHardwareMonitor() override { return nullptr; };
  virtual IRealTimeController *getRealTimeController() override { return nullptr; };
};

}  // namespace quisp_test

#endif /* QUISP_UTILS_TEST_UTILS_H_ */
