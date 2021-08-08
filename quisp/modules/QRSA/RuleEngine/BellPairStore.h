#pragma once

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
namespace quisp {
namespace modules {

using QNodeAddr = int;
using QNicIndex = int;
// entangled partner qnode address -> qubit
using PartnerAddrQubitMap = std::multimap<QNodeAddr, IStationaryQubit*>;
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
  BellPairStore();
  ~BellPairStore();
  void eraseQubit(IStationaryQubit* const qubit);
  void insertEntangledQubit(QNodeAddr partner_addr, IStationaryQubit* const qubit);
  IStationaryQubit* findQubit(QNIC_type qnic_type, QNicIndex qnic_index, QNodeAddr addr);
  PartnerAddrQubitMapRange getBellPairsRange(QNIC_type qnic_type, QNicIndex qnic_index, QNodeAddr partner_addr);

 protected:
  std::map<ResourceKey, PartnerAddrQubitMap> _resources;
};
}  // namespace modules
}  // namespace quisp
