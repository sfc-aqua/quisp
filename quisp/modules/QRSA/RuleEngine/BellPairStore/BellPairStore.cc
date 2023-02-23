#include "BellPairStore.h"
#include <sstream>
#include <utility>
#include "modules/QNIC.h"
#include "modules/QRSA/QRSA.h"

namespace quisp::modules {
BellPairStore::BellPairStore(Logger::ILogger *logger) : logger(logger) {}
BellPairStore::~BellPairStore() {}

void BellPairStore::insertEntangledQubit(QNodeAddr partner_addr, qrsa::IQubitRecord *const qubit) {
  auto qnic_type = qubit->getQNicType();
  auto qnic_index = qubit->getQNicIndex();
  ResourceKey key{qnic_type, qnic_index};
  logger->logBellPairInfo("Generated", partner_addr, qubit->getQNicType(), qubit->getQNicIndex(), qubit->getQubitIndex());
  if (_resources.find(key) == _resources.cend()) {
    _resources.emplace(key, std::multimap<QNodeAddr, qrsa::IQubitRecord *>{std::make_pair(partner_addr, qubit)});
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
      logger->logBellPairInfo("Erased", it->first, qubit->getQNicType(), qubit->getQNicIndex(), qubit->getQubitIndex());
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

PartnerAddrQubitMapRange BellPairStore::getBellPairsRange(QNIC_type qnic_type, int qnic_index, QNodeAddr partner_addr) {
  auto key = std::make_pair(qnic_type, qnic_index);
  if (_resources.find(key) == _resources.cend()) {
    _resources.emplace(key, std::multimap<QNodeAddr, qrsa::IQubitRecord *>{});
  }
  return _resources[key].equal_range(partner_addr);
}

std::string BellPairStore::toString() const {
  std::stringstream ss;
  for (auto &[key, partner_qubit_map] : _resources) {
    for (auto &[partner, qubit] : partner_qubit_map) {
      ss << "(type:" << key.first << ", qnic:" << key.second << ", qubit:" << qubit->getQubitIndex() << ")=>(partner:" << partner << "), ";
    }
  }
  return ss.str();
}

std::ostream &operator<<(std::ostream &os, const quisp::modules::BellPairStore &store) {
  os << store.toString();
  return os;
}
}  // namespace quisp::modules
