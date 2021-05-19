#include "ComponentProvider.h"
#include "classical_messages_m.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/Utils/DefaultComponentProviderStrategy.h"
#include "modules/Utils/IComponentProviderStrategy.h"
#include "omnetpp/cmodule.h"

using omnetpp::cModule;

namespace quisp {
namespace modules {

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
} /* namespace modules */
} /* namespace quisp */
