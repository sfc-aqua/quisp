#pragma once
#include "backends/Backends.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "types/QNodeAddr.h"

namespace quisp::modules::qubit_id {

class QubitId : public quisp::backends::IQubitId {
 public:
  QubitId(types::QNodeAddr node_addr, int qnic_index, int qnic_type, int qubit_addr)
      : node_addr(node_addr), qnic_index(qnic_index), qnic_type(qnic_type), qubit_addr((qubit_addr)) {}
  std::size_t hash() const override {
    size_t seed = std::hash<types::QNodeAddr>()(node_addr);
    hashCombine(seed, qnic_index);
    hashCombine(seed, qnic_type);
    hashCombine(seed, qubit_addr);
    return seed;
  }

  bool compare(const IQubitId& id_ref) const override {
    const QubitId& id = dynamic_cast<const QubitId&>(id_ref);
    return node_addr == id.node_addr && qnic_index == id.qnic_index && qnic_type == id.qnic_type && qubit_addr == id.qubit_addr;
  }

  types::QNodeAddr node_addr;
  int qnic_index;
  int qnic_type;
  int qubit_addr;

 protected:
  // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
  void hashCombine(std::size_t& seed, int const& v) const { seed ^= std::hash<int>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2); }
};

}  // namespace quisp::modules::qubit_id
