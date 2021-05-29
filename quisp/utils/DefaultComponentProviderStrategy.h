#ifndef QUISP_UTILS_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_
#define QUISP_UTILS_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_

#include "IComponentProviderStrategy.h"
#include "utils.h"

namespace quisp {
namespace utils {

class DefaultComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  DefaultComponentProviderStrategy(cModule *_self);
  cModule *getQNode() override;
  cModule *getNeighborNode(cModule *qnic) override;
  bool isQNodeType(const cModuleType *const type) override;
  bool isHoMNodeType(const cModuleType *const type) override;
  bool isSPDCNodeType(const cModuleType *const type) override;
  StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override;
  IRoutingDaemon *getRoutingDaemon() override;
  IHardwareMonitor *getHardwareMonitor() override;

 private:
  const cModuleType *const QNodeType = cModuleType::get("modules.QNode");
  const cModuleType *const SPDCType = cModuleType::get("modules.SPDC");
  const cModuleType *const HoMType = cModuleType::get("modules.HoM");
  cModule *self;
  cModule *getQRSA();
};

}  // namespace utils
}  // namespace quisp

#endif /* QUISP_UTILS_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_ */
