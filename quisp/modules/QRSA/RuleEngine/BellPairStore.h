#pragma once

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
namespace quisp {
namespace modules {

using QNodeAddr = int;
using QNicIndex = int;
// entangled partner qnode address -> qubit
using EntangledPartnerAddrQubitMap = std::multimap<QNodeAddr, StationaryQubit*>;
using ResourceKey = std::pair<QNIC_type, QNicIndex>;
using EntangledQubitsRangeIterator = std::pair<EntangledPartnerAddrQubitMap::iterator, EntangledPartnerAddrQubitMap::iterator>;

class BellPairStore {
 public:
  BellPairStore();
  ~BellPairStore();
  void eraseQubit(StationaryQubit* const qubit);
  void insertEntangledQubit(int partner_addr, StationaryQubit* const qubit);
  StationaryQubit* findQubit(QNIC_type qnic_type, int qnic_index, int addr);
  EntangledQubitsRangeIterator getQubitsRange(QNIC_type qnic_type, int qnic_index, int partner_addr);

 protected:
  std::map<ResourceKey, EntangledPartnerAddrQubitMap> _resources;
};
}  // namespace modules
}  // namespace quisp
