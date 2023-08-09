#include "omnetpp/ccomponent.h"
#include "omnetpp/cenvir.h"
#include "omnetpp/simtime.h"
#include "omnetpp/simtime_t.h"

namespace quisp::utils {
using omnetpp::cRNG;
using omnetpp::intuniform;
using omnetpp::SimTime;
using omnetpp::simtime_t;

class HelperFunctions {
 public:
  unsigned long createUniqueId(cRNG *rng, int node_address, simtime_t sim_time);
};
}  // namespace quisp::utils
