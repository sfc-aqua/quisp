#include <omnetpp.h>

#include "DefaultComponentProviderStrategy.h"

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

cModule *DefaultComponentProviderStrategy::getNode() {
  cModule *currentModule = self->getParentModule();
  auto *mod_type = currentModule->getModuleType();
  while (mod_type != QNodeType && mod_type != BSAType && mod_type != EPPSType) {
    currentModule = currentModule->getParentModule();
    mod_type = currentModule->getModuleType();
    if (currentModule == nullptr) {
      throw cRuntimeError("Node module not found. Have you changed the type name in ned file?");
    }
  }
  return currentModule;
}

int DefaultComponentProviderStrategy::getNodeAddr() { return getNode()->par("address"); }

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
  auto *casted_qubit = dynamic_cast<IStationaryQubit *>(qubit);
  if (casted_qubit == nullptr) {
    throw cRuntimeError("FAIL TO CAST QUBITS qubit index %d", qubit_index);
  }
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
  return qnic->par("num_buffer").intValue();
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
  cModule *currentModule = self->getParentModule();
  auto *mod = currentModule->findModuleByPath("backend");
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

SharedResource *DefaultComponentProviderStrategy::getSharedResource() {
  auto *mod = self->findModuleByPath("sharedResource");
  if (mod == nullptr) {
    throw cRuntimeError("SharedResource not found");
  }
  auto *shared_resource_holder = check_and_cast<SharedResource *>(mod);
  return shared_resource_holder;
}

cModule *DefaultComponentProviderStrategy::getQRSA() {
  auto *qnode = getQNode();
  auto *qrsa = qnode->getSubmodule("qrsa");
  if (qrsa == nullptr) {
    throw cRuntimeError("QRSA module not found.");
  }
  return qrsa;
}

bool DefaultComponentProviderStrategy::isBSANodeType(const cModuleType *const type) { return type == BSAType; }
bool DefaultComponentProviderStrategy::isQNodeType(const cModuleType *const type) { return type == QNodeType; }
bool DefaultComponentProviderStrategy::isEPPSNodeType(const cModuleType *const type) { return type == EPPSType; }
}  // namespace quisp::utils
