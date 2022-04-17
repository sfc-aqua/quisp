#include "Backend.h"

namespace quisp::backends::graph_state_stabilizer {
GraphStateStabilizerBackend::GraphStateStabilizerBackend(std::unique_ptr<IRandomNumberGenerator> rng) : rng(std::move(rng)) {}
GraphStateStabilizerBackend::~GraphStateStabilizerBackend() {}

IQubit* GraphStateStabilizerBackend::getQubit(const IQubitId* id) {}
double GraphStateStabilizerBackend::dblrand() { return rng->doubleRandom(); }

}  // namespace quisp::backends::graph_state_stabilizer
