#include "BellPairStore.h"
#include <utility>
#include "modules/QNIC.h"
#include "modules/QRSA/QRSA.h"

namespace quisp {
namespace modules {
BellPairStore::BellPairStore() {}
BellPairStore::~BellPairStore() {}

void BellPairStore::insertEntangledQubit(QNodeAddr partner_addr, qrsa::IQubitRecord *const qubit) {
  auto qnic_type = qubit->getQNicType();
  auto qnic_index = qubit->getQNicIndex();
  ResourceKey key{qnic_type, qnic_index};
  if (_resources.find(key) == _resources.cend()) {
    _resources.emplace(key, std::multimap<int, qrsa::IQubitRecord *>{std::make_pair(partner_addr, qubit)});
  } else {
    _resources[key].emplace(partner_addr, qubit);
  }
}

void BellPairStore::eraseQubit(qrsa::IQubitRecord *const qubit) {
  auto qnic_type = (QNIC_type)qubit->getQNicType();
  auto qnic_index = qubit->getQNicIndex();
  if (_resources.find(std::make_pair(qnic_type, qnic_index)) == _resources.cend()) {
    return;
  }
  // take the ref of entangled partner qubits map
  auto &resource = _resources[std::make_pair(qnic_type, qnic_index)];
  auto it = resource.begin();
  while (it != resource.cend()) {
    if (it->second == qubit) {
      it = resource.erase(it);
    } else
      it++;
  }
}

qrsa::IQubitRecord *BellPairStore::findQubit(QNIC_type qnic_type, QNicIndex qnic_index, QNodeAddr addr) {
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

PartnerAddrQubitMapRange BellPairStore::getBellPairsRange(QNIC_type qnic_type, int qnic_index, int partner_addr) {
  auto key = std::make_pair(qnic_type, qnic_index);
  if (_resources.find(key) == _resources.cend()) {
    _resources.emplace(key, std::multimap<int, qrsa::IQubitRecord *>{});
  }
  return _resources[key].equal_range(partner_addr);
}

}  // namespace modules
}  // namespace quisp
