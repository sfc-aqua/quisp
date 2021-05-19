#ifndef QUISP_MODULES_ICOMPONENTPROVIDER_STRATEGY_H_
#define QUISP_MODULES_ICOMPONENTPROVIDER_STRATEGY_H_
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "omnetpp/cmodule.h"

using omnetpp::cModule;

namespace quisp {
namespace modules {

class IComponentProviderStrategy {
 public:
  IComponentProviderStrategy() {}
  virtual ~IComponentProviderStrategy() {}
  virtual cModule *getQNode() = 0;
  virtual StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
};

}  // namespace modules
}  // namespace quisp
#endif
