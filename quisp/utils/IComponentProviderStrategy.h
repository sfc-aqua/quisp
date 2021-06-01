#ifndef QUISP_UTILS_ICOMPONENTPROVIDER_STRATEGY_H_
#define QUISP_UTILS_ICOMPONENTPROVIDER_STRATEGY_H_

#include <memory>
#include "utils.h"

namespace quisp {
namespace utils {

class IComponentProviderStrategy {
 public:
  IComponentProviderStrategy() {}
  virtual ~IComponentProviderStrategy() {}
  virtual cModule *getQNode() = 0;
  virtual StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual IRoutingDaemon *getRoutingDaemon() = 0;
  virtual IHardwareMonitor *getHardwareMonitor() = 0;
};

}  // namespace utils
}  // namespace quisp

#endif /* QUISP_UTILS_ICOMPONENTPROVIDER_STRATEGY_H_ */
