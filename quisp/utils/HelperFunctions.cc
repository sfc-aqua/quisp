#include "HelperFunctions.h"

namespace quisp::utils {

unsigned long HelperFunctions::createUniqueId(cRNG *rng, int node_address, simtime_t sim_time) {
  std::string time = SimTime().str();
  std::string address = std::to_string(node_address);
  std::string random = std::to_string(intuniform(rng, 0, 10000000));
  std::string hash_seed = address + time + random;
  std::hash<std::string> hash_fn;
  size_t t = hash_fn(hash_seed);
  unsigned long unique_id = static_cast<long>(t);
  return unique_id;
}
}  // namespace quisp::utils
