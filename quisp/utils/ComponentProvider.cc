#include "ComponentProvider.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"

namespace quisp {
namespace utils {

ComponentProvider::ComponentProvider(cModule *_module) : module(_module) {}

cModule *ComponentProvider::getQNode() {
  ensureStrategy();
  return strategy->getQNode();
}

StationaryQubit *ComponentProvider::getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) {
  ensureStrategy();
  return strategy->getStationaryQubit(qnic_index, qubit_index, qnic_type);
}

IHardwareMonitor *ComponentProvider::getHardwareMonitor() {
  ensureStrategy();
  return strategy->getHardwareMonitor();
}

IRoutingDaemon *ComponentProvider::getRoutingDaemon() {
  ensureStrategy();
  return strategy->getRoutingDaemon();
}

void ComponentProvider::setStrategy(std::unique_ptr<IComponentProviderStrategy> _strategy) { strategy = std::move(_strategy); }

void ComponentProvider::ensureStrategy() {
  if (strategy != nullptr) return;
  strategy = std::make_unique<DefaultComponentProviderStrategy>(module);
}
}  // namespace utils
} /* namespace quisp */
