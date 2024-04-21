#include "ComponentProvider.h"

namespace quisp::utils {

ComponentProvider::ComponentProvider(cModule *_module) : module(_module) {}

cModule *ComponentProvider::getQNode() {
  ensureStrategy();
  return strategy->getQNode();
}

cModule *ComponentProvider::getNode() {
  ensureStrategy();
  return strategy->getNode();
}

int ComponentProvider::getNodeAddr() {
  ensureStrategy();
  return strategy->getNodeAddr();
}

cModule *ComponentProvider::getNeighborNode(cModule *qnic) {
  ensureStrategy();
  return strategy->getNeighborNode(qnic);
}

bool ComponentProvider::isBSANodeType(const cModuleType *const type) {
  ensureStrategy();
  return strategy->isBSANodeType(type);
}

bool ComponentProvider::isEPPSNodeType(const cModuleType *const type) {
  ensureStrategy();
  return strategy->isEPPSNodeType(type);
}

bool ComponentProvider::isQNodeType(const cModuleType *const type) {
  ensureStrategy();
  return strategy->isQNodeType(type);
}

IStationaryQubit *ComponentProvider::getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) {
  ensureStrategy();
  return strategy->getStationaryQubit(qnic_index, qubit_index, qnic_type);
}

IStationaryQubit *ComponentProvider::getStationaryQubit(modules::qrsa::IQubitRecord *const qubit_record) {
  ensureStrategy();
  if (qubit_record->qubit_ptr == nullptr) {
    qubit_record->qubit_ptr = strategy->getStationaryQubit(qubit_record->getQNicIndex(), qubit_record->getQubitIndex(), qubit_record->getQNicType());
  }
  return qubit_record->qubit_ptr;
}

cModule *ComponentProvider::getQNIC(int qnic_index, QNIC_type qnic_type) {
  ensureStrategy();
  return strategy->getQNIC(qnic_index, qnic_type);
}

int ComponentProvider::getNumQubits(int qnic_index, QNIC_type qnic_type) {
  ensureStrategy();
  return strategy->getNumQubits(qnic_index, qnic_type);
}

IHardwareMonitor *ComponentProvider::getHardwareMonitor() {
  ensureStrategy();
  return strategy->getHardwareMonitor();
}

IRoutingDaemon *ComponentProvider::getRoutingDaemon() {
  ensureStrategy();
  return strategy->getRoutingDaemon();
}
IRealTimeController *ComponentProvider::getRealTimeController() {
  ensureStrategy();
  return strategy->getRealTimeController();
}

IQuantumBackend *ComponentProvider::getQuantumBackend() {
  ensureStrategy();
  return strategy->getQuantumBackend();
}

ILogger *ComponentProvider::getLogger() {
  ensureStrategy();
  return strategy->getLogger();
}

const std::unordered_map<int, int> ComponentProvider::getEndNodeWeightMapForApplication(std::string node_type) {
  auto shared_resource = getSharedResource();
  return shared_resource->getEndNodeWeightMapForApplication(node_type.c_str());
}

cTopology *ComponentProvider::getTopologyForRoutingDaemon(const cModule *const rd_module) {
  auto shared_resource = getSharedResource();
  return shared_resource->getTopologyForRoutingDaemon(rd_module);
}

cTopology *ComponentProvider::getTopologyForRouter() {
  auto shared_resource = getSharedResource();
  return shared_resource->getTopologyForRouter();
}

void ComponentProvider::setStrategy(std::unique_ptr<IComponentProviderStrategy> _strategy) { strategy = std::move(_strategy); }

SharedResource *ComponentProvider::getSharedResource() {
  ensureStrategy();
  return strategy->getSharedResource();
}

void ComponentProvider::ensureStrategy() {
  if (strategy != nullptr) return;
  strategy = std::make_unique<DefaultComponentProviderStrategy>(module);
}
}  // namespace quisp::utils
