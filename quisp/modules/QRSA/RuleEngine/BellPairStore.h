#pragma once

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
namespace quisp {
namespace modules {

using QNodeAddr = int;
using QNicIndex = int;
// entangled partner qnode address -> qubit
using PartnerAddrQubitMap = std::multimap<QNodeAddr, StationaryQubit*>;
using ResourceKey = std::pair<QNIC_type, QNicIndex>;
using PartnerAddrQubitMapRange = std::pair<PartnerAddrQubitMap::iterator, PartnerAddrQubitMap::iterator>;

class BellPairStore {
 public:
  BellPairStore();
  ~BellPairStore();
  void eraseQubit(StationaryQubit* const qubit);
  void insertEntangledQubit(QNodeAddr partner_addr, StationaryQubit* const qubit);
  StationaryQubit* findQubit(QNIC_type qnic_type, QNicIndex qnic_index, QNodeAddr addr);
  PartnerAddrQubitMapRange getBellPairsRange(QNIC_type qnic_type, QNicIndex qnic_index, QNodeAddr partner_addr);

 protected:
  std::map<ResourceKey, PartnerAddrQubitMap> _resources;
};
}  // namespace modules
}  // namespace quisp
