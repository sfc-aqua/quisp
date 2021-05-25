#include "ComponentProvider.h"

namespace quisp {
namespace utils {

ComponentProvider::ComponentProvider(cModule *_module) : module(_module) {}

ComponentProvider::~ComponentProvider() {
  if (strategy == nullptr) return;
  delete strategy;
}

cModule *ComponentProvider::getQNode() {
  ensureStrategy();
  return strategy->getQNode();
}

StationaryQubit *ComponentProvider::getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) {
  ensureStrategy();
  return strategy->getStationaryQubit(qnic_index, qubit_index, qnic_type);
}

void ComponentProvider::setStrategy(IComponentProviderStrategy *_strategy) { strategy = _strategy; }

void ComponentProvider::ensureStrategy() {
  if (strategy != nullptr) return;
  strategy = new DefaultComponentProviderStrategy{module};
}
}  // namespace utils
} /* namespace quisp */
