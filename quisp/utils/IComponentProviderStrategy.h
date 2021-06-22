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
  virtual cModule *getNeighborNode(cModule *qnic) = 0;
  virtual bool isQNodeType(const cModuleType *const module) = 0;
  virtual bool isHoMNodeType(const cModuleType *const module) = 0;
  virtual bool isSPDCNodeType(const cModuleType *const module) = 0;
  virtual StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual StationaryQubit *getStationaryQubitForLogicalEncoding(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;  // get physical qubit for logical qubit encoding
  virtual StationaryQubit *getAncillaQubitForDetection(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;  // get physical qubit for error detection
  virtual cModule *getQNIC(int qnic_index, QNIC_type qnic_type) = 0;
  virtual IRoutingDaemon *getRoutingDaemon() = 0;
  virtual IHardwareMonitor *getHardwareMonitor() = 0;
  virtual IRealTimeController *getRealTimeController() = 0;
};

}  // namespace utils
}  // namespace quisp

#endif /* QUISP_UTILS_ICOMPONENTPROVIDER_STRATEGY_H_ */
