#include "backends/Backends.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"

namespace quisp::modules::qubit_id {

void hash_combine(std::size_t& seed, int const& v) { seed ^= std::hash<int>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2); }

class QubitId : public quisp::backends::IQubitId {
 public:
  QubitId(int node_addr, int qnic_index, int qnic_type, int qubit_addr) : node_addr(node_addr), qnic_index(qnic_index), qnic_type(qnic_type), qubit_addr((qubit_addr)) {}
  std::size_t hash() const override {
    size_t seed = std::hash<int>()(node_addr);
    hash_combine(seed, qnic_index);
    hash_combine(seed, qnic_type);
    hash_combine(seed, qubit_addr);
    return seed;
  }

  bool compare(const IQubitId& id_ref) const override {
    const QubitId& id = dynamic_cast<const QubitId&>(id_ref);
    return node_addr == id.node_addr && qnic_index == id.qnic_index && qnic_type == id.qnic_type && qubit_addr == id.qubit_addr;
  }

 protected:
  // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine

  int node_addr;
  int qnic_index;
  int qnic_type;
  int qubit_addr;
};

}  // namespace quisp::modules::qubit_id
