#ifndef QUISP_MODULES_UTILS_COMPONENTPROVIDER_H_
#define QUISP_MODULES_UTILS_COMPONENTPROVIDER_H_
#include "omnetpp.h"

#include "DefaultComponentProviderStrategy.h"
#include "IComponentProviderStrategy.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"

namespace quisp {
namespace modules {

class ComponentProvider {
 public:
  ComponentProvider(omnetpp::cModule *_module);
  ~ComponentProvider();

  omnetpp::cModule *getQNode();
  StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type);

  void setStrategy(IComponentProviderStrategy *_strategy);

  omnetpp::cModule *module;

 private:
  IComponentProviderStrategy *strategy = nullptr;
  void ensureStrategy();
};

} /* namespace modules */
} /* namespace quisp */
#endif /* QUISP_MODULES_UTILS_COMPONENTPROVIDER_H_ */
