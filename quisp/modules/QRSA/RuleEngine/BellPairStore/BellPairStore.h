#pragma once

#include <modules/Logger/ILogger.h>
#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <modules/QRSA/QRSA.h>

namespace quisp::modules {

using QNodeAddr = int;
using QNicIndex = int;
// entangled partner qnode address -> qubit
using PartnerAddrQubitMap = std::multimap<QNodeAddr, qrsa::IQubitRecord*>;
using ResourceKey = std::pair<QNIC_type, QNicIndex>;
using PartnerAddrQubitMapRange = std::pair<PartnerAddrQubitMap::iterator, PartnerAddrQubitMap::iterator>;

/**
 * this class contains the bell pair information for RuleEngine.
 * this tracks the entangled qubit and its partner addr.
 * RuleEngine recognizes a bell pair generated, store the information to this class.
 * if RuleSet needs bell pair resource, RuleEngine takes a bell pair from this class.
 */
class BellPairStore {
 public:
  BellPairStore(Logger::ILogger* logger = nullptr);
  ~BellPairStore();
  void eraseQubit(qrsa::IQubitRecord* const qubit);
  void insertEntangledQubit(QNodeAddr partner_addr, qrsa::IQubitRecord* qubit);
  qrsa::IQubitRecord* findQubit(QNIC_type qnic_type, QNicIndex qnic_index, QNodeAddr addr);
  PartnerAddrQubitMapRange getBellPairsRange(QNIC_type qnic_type, QNicIndex qnic_index, QNodeAddr partner_addr);
  std::string toString() const;
  Logger::ILogger* logger;

 protected:
  std::map<ResourceKey, PartnerAddrQubitMap> _resources;
};
std::ostream& operator<<(std::ostream& os, const quisp::modules::BellPairStore& store);
}  // namespace quisp::modules
