#ifndef QUISP_UTILS_COMPONENTPROVIDER_H_
#define QUISP_UTILS_COMPONENTPROVIDER_H_

#include "DefaultComponentProviderStrategy.h"
#include "IComponentProviderStrategy.h"
#include "utils.h"

namespace quisp {
namespace utils {

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

}  // namespace utils
} /* namespace quisp */
#endif /* QUISP_UTILS_COMPONENTPROVIDER_H_ */
