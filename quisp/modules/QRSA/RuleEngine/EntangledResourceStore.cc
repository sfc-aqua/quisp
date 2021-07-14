#include "EntangledResourceStore.h"
#include <utility>
#include "modules/QNIC.h"

namespace quisp {
namespace modules {
EntangledResourceStore::EntangledResourceStore() {}
EntangledResourceStore::~EntangledResourceStore() {}

void EntangledResourceStore::insertEntangledQubit(int partner_addr, StationaryQubit *const qubit) {
  auto qnic_type = (QNIC_type)qubit->qnic_type;
  auto qnic_index = qubit->qnic_index;
  auto key = std::make_pair(qnic_type, qnic_index);
  if (_resources.find(key) == _resources.cend()) {
    _resources.emplace(key, std::multimap<int, StationaryQubit *>{std::make_pair(partner_addr, qubit)});
  } else {
    _resources[key].emplace(partner_addr, qubit);
  }
}

void EntangledResourceStore::eraseQubit(StationaryQubit *const qubit) {
  auto qnic_type = (QNIC_type)qubit->qnic_type;
  auto qnic_index = qubit->qnic_index;
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

StationaryQubit *EntangledResourceStore::findQubit(QNIC_type qnic_type, int qnic_index, int addr) {
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

EntangledPartnerAddrQubitMap EntangledResourceStore::range(QNIC_type qnic_type, int qnic_index) { return _resources[std::make_pair(qnic_type, qnic_index)]; }

}  // namespace modules
}  // namespace quisp
