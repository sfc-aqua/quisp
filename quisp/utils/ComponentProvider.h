#ifndef QUISP_UTILS_COMPONENTPROVIDER_H_
#define QUISP_UTILS_COMPONENTPROVIDER_H_

#include "DefaultComponentProviderStrategy.h"
#include "IComponentProviderStrategy.h"
#include "omnetpp/cmodule.h"
#include "utils.h"

namespace quisp {
namespace utils {

/**
 * \brief ComponentProvider class provides a way to access other quisp other modules.
 *
 * This class itself doesn't know how to get other modules, All actual behaviors are
 * delegated to strategy class.
 * \see IComponentProviderStrategy
 * \see DefaultComponentProviderStrategy
 */
class ComponentProvider {
 public:
  ComponentProvider(omnetpp::cModule *_module);

  cModule *getQNode();
  cModule *getNeighborNode(cModule *qnic);
  bool isQNodeType(const cModuleType *const type);
  bool isHoMNodeType(const cModuleType *const type);
  bool isSPDCNodeType(const cModuleType *const type);
  StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type);
  IRoutingDaemon *getRoutingDaemon();
  IHardwareMonitor *getHardwareMonitor();

  // when a this class instantiated, a strategy class instantiation may fail because
  // the strategy class may depend on other modules instantiated by OMNeT++'s NED file.
  // So this method is for delaying to instantiate the strategy class.
  // And also we can inject a strategy for unit testing.
  void setStrategy(std::unique_ptr<IComponentProviderStrategy> _strategy);

  // an owner module of this class.
  // strategy class will access to other modules by the module.
  omnetpp::cModule *module;

 private:
  // An actual strategy.
  // This will be instantiated when it is needed through ensureStrategy method.
  // It will be deleted automatically when ComponentProvider's deconstructor called.
  std::unique_ptr<IComponentProviderStrategy> strategy = nullptr;

  // before calling strategy class, this internal method ensure that
  // the strategy class instance exists.
  // if there's no strategy, this method uses DefaultComponentProviderStrategy.
  void ensureStrategy();
};

}  // namespace utils
}  // namespace quisp

#endif /* QUISP_UTILS_COMPONENTPROVIDER_H_ */
