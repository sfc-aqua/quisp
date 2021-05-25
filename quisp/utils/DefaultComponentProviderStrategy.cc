#include "utils/DefaultComponentProviderStrategy.h"

namespace quisp {
namespace utils {

DefaultComponentProviderStrategy::DefaultComponentProviderStrategy(cModule *_self) : self(_self) {}

cModule *DefaultComponentProviderStrategy::getQNode() {
  cModule *currentModule = self->getParentModule();
  while (currentModule->getModuleType() != QNodeType) {
    currentModule = currentModule->getParentModule();
    if (currentModule == nullptr) {
      throw cRuntimeError("QNode module not found. Have you changed the type name in ned file?");
    }
  }
  return currentModule;
}

StationaryQubit *DefaultComponentProviderStrategy::getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) {
  if (qnic_type > QNIC_N) {
    throw cRuntimeError("got invalid qnic type: %d", qnic_type);
  }
  auto qnode = getQNode();
  auto qubit = qnode->getSubmodule(QNIC_names[qnic_type], qnic_index)->getSubmodule("statQubit", qubit_index);
  return check_and_cast<StationaryQubit *>(qubit);
}

}  // namespace utils
}  // namespace quisp
