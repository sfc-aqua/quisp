#include "DefaultComponentProviderStrategy.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "omnetpp/cexception.h"
#include "omnetpp/cmodule.h"
#include "utils/utils.h"

namespace quisp::utils {

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
cModule *DefaultComponentProviderStrategy::getNeighborNode(cModule *qnic) {
  if (qnic == nullptr) throw cRuntimeError("failed to get neighbor node. given qnic is nullptr");
  auto *neighbor_node = qnic->gate("qnic_quantum_port$o")->getNextGate()->getNextGate()->getOwnerModule();
  if (neighbor_node == nullptr) throw cRuntimeError("failed to get neighbor node. neighbor node is nullptr");
  return neighbor_node;
}

IStationaryQubit *DefaultComponentProviderStrategy::getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) {
  auto *qnic = getQNIC(qnic_index, qnic_type);
  if (qnic == nullptr) {
    throw cRuntimeError("QNIC not found. index: %d, type: %d", qnic_index, qnic_type);
  }
  auto *qubit = qnic->getSubmodule("statQubit", qubit_index);
  return check_and_cast<IStationaryQubit *>(qubit);
}

cModule *DefaultComponentProviderStrategy::getQNIC(int qnic_index, QNIC_type qnic_type) {
  if (qnic_type > QNIC_N) {
    throw cRuntimeError("got invalid qnic type: %d", qnic_type);
  }
  auto qnode = getQNode();
  return qnode->getSubmodule(QNIC_names[qnic_type], qnic_index);
}
int DefaultComponentProviderStrategy::getNumQubits(int qnic_index, QNIC_type qnic_type) {
  auto *qnic = getQNIC(qnic_index, qnic_type);
  if (qnic == nullptr) {
    throw cRuntimeError("DefaultComponentProviderStrategy::getNumQubits: QNIC not found. index: %d, type: %d", qnic_index, qnic_type);
  }
  return qnic->par("numBuffer").intValue();
}

IRoutingDaemon *DefaultComponentProviderStrategy::getRoutingDaemon() {
  auto *qrsa = getQRSA();
  return check_and_cast<IRoutingDaemon *>(qrsa->getSubmodule("rd"));
}
IHardwareMonitor *DefaultComponentProviderStrategy::getHardwareMonitor() {
  auto *qrsa = getQRSA();
  return check_and_cast<IHardwareMonitor *>(qrsa->getSubmodule("hm"));
}
modules::IRealTimeController *DefaultComponentProviderStrategy::getRealTimeController() {
  auto *qrsa = getQRSA();
  return check_and_cast<IRealTimeController *>(qrsa->getSubmodule("rt"));
}
IQuantumBackend *DefaultComponentProviderStrategy::getQuantumBackend() {
  auto *qnode = getQNode();
  auto *mod = qnode->findModuleByPath("backend");
  if (mod == nullptr) {
    throw cRuntimeError("Quantum backend not found");
  }
  auto *backend_container = check_and_cast<BackendContainer *>(mod);
  return backend_container->getQuantumBackend();
}

ILogger *DefaultComponentProviderStrategy::getLogger() {
  auto *qnode = getQNode();
  auto *mod = qnode->findModuleByPath("logger");
  if (mod == nullptr) {
    throw cRuntimeError("LoggerModule not found");
  }
  auto *logger_module = check_and_cast<LoggerModule *>(mod);
  return logger_module->getLogger();
}

cModule *DefaultComponentProviderStrategy::getQRSA() {
  auto *qnode = getQNode();
  auto *qrsa = qnode->getSubmodule("qrsa");
  if (qrsa == nullptr) {
    throw cRuntimeError("QRSA module not found.");
  }
  return qrsa;
}

bool DefaultComponentProviderStrategy::isHOMNodeType(const cModuleType *const type) { return type == HOMType; }
bool DefaultComponentProviderStrategy::isQNodeType(const cModuleType *const type) { return type == QNodeType; }
bool DefaultComponentProviderStrategy::isSPDCNodeType(const cModuleType *const type) { return type == SPDCType; }
}  // namespace quisp::utils
