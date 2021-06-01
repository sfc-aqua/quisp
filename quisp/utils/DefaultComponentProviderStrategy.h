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
  StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override;
  IRoutingDaemon *getRoutingDaemon() override;
  IHardwareMonitor *getHardwareMonitor() override;

 private:
  const cModuleType *const QNodeType = cModuleType::get("modules.QNode");
  cModule *self;

  cModule *getQRSA();
};

}  // namespace utils
}  // namespace quisp

#endif /* QUISP_UTILS_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_ */
