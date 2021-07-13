#include "ResourceStore.h"
#include <utility>
#include "modules/QNIC.h"

namespace quisp {
namespace modules {
ResourceStore::ResourceStore() {}
ResourceStore::~ResourceStore() {}

void ResourceStore::insert(QNIC_type qnic_type, int qnic_index, int addr, StationaryQubit *const qubit) {
  auto key = std::make_pair(qnic_type, qnic_index);
  if (_resources.find(key) == _resources.cend()) {
    _resources.emplace(key, std::multimap<int, StationaryQubit *>{std::make_pair(addr, qubit)});
  } else {
    _resources[key].emplace(addr, qubit);
  }
}

void ResourceStore::erase(QNIC_type qnic_type, int qnic_index, StationaryQubit *const qubit) {
  if (_resources.find(std::make_pair(qnic_type, qnic_index)) == _resources.cend()) {
    return;
  }
  // take the ref of entangled partner qubits map
  auto &resource = _resources[std::make_pair(qnic_type, qnic_index)];
  for (auto it = resource.begin(); it != resource.cend(); ++it) {
    if (it->second == qubit) {
      it = resource.erase(it);
    }
  }
}

StationaryQubit *ResourceStore::find(QNIC_type qnic_type, int qnic_index, int addr) {
  auto key = std::make_pair(qnic_type, qnic_index);
  if (_resources.find(key) == _resources.cend()) {
    return nullptr;
  }
  auto it = _resources[key].find(addr);
  if (it == _resources[key].cend()) {
    return nullptr;
  }
  return it->second;
}

std::multimap<int, quisp::modules::StationaryQubit *> ResourceStore::range(QNIC_type qnic_type, int qnic_index) { return _resources[std::make_pair(qnic_type, qnic_index)]; }

}  // namespace modules
}  // namespace quisp
