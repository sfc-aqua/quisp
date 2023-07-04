#include "SharedResource.h"
#include <memory>
#include <random>
#include <vector>
#include "omnetpp/ctopology.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::SharedResource {

SharedResource::SharedResource() {}

SharedResource::~SharedResource() {}

void SharedResource::initialize() {}

const std::unordered_map<int, int> SharedResource::getEndNodeWeightMapForApplication(const char *const node_type) {
  std::call_once(app_init_flag, [&]() {
    cTopology *topo = new cTopology("topo");

    topo->extractByParameter("node_type", node_type);

    for (int i = 0; i < topo->getNumNodes(); i++) {
      cModule *endnodeModule = topo->getNode(i)->getModule();
      int address = endnodeModule->par("address").intValue();
      int weight = endnodeModule->par("mass").intValue();

      end_node_weight_map[address] = weight;
    }
    delete topo;
  });
  return end_node_weight_map;
}

cTopology *SharedResource::getTopologyForRouter() {
  std::call_once(router_init_flag, [&]() { updateChannelWeightsInTopology(router_topology, std::nullopt); });
  return router_topology;
}

cTopology *SharedResource::getTopologyForRoutingDaemon(const cModule *const rd_module) {
  std::call_once(rd_init_flag, [&]() { updateChannelWeightsInTopology(routingdaemon_topology, rd_module); });
  return routingdaemon_topology;
}

/**
 * @brief Initialize channel weights for all existing links in the Topology
 *
 * @param topo router_topology or routingdaemon_topology
 * @param rd_module
 * rd_module is needed for the function to distinguish between Router and RoutingDaemon,
 * as they require different procedures to initialize cTopology.
 * In detail, RoutingDaemon must call calculateSecPerBellPair function to update
 * the channel weights, and calculateSecPerBellPair function requires the rd_module.
 */
void SharedResource::updateChannelWeightsInTopology(cTopology *&topo, std::optional<const cModule *const> rd_module) {
  topo = new cTopology("topo");
  topo->extractByParameter("included_in_topology", "\"yes\"");
  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all nodes
    auto node = topo->getNode(i);
    updateChannelWeightsOfNode(node, rd_module);
  }
}

void SharedResource::updateChannelWeightsOfNode(cTopology::Node *node, std::optional<const cModule *const> rd_module) {
  for (int i = 0; i < node->getNumOutLinks(); i++) {  // Traverse through all links from a specific node.
    // For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
    auto outgoing_link = node->getLinkOut(i);

    if (rd_module.has_value()) {
      double channel_weight = calculateSecPerBellPair(rd_module.value(), outgoing_link);
      setWeightOfLink(outgoing_link, channel_weight, true);
    } else {
      double channel_cost = outgoing_link->getLocalGate()->getChannel()->par("cost");
      setWeightOfLink(outgoing_link, channel_cost, false);
    }
  }
}

// The cost metric is taken from https://arxiv.org/abs/1206.5655
double SharedResource::calculateSecPerBellPair(const cModule *const rd_module, const cTopology::LinkOut *const outgoing_link) {
  double speed_of_light_in_fiber = outgoing_link->getLocalGate()->getChannel()->par("speed_of_light_in_fiber");
  double channel_length = outgoing_link->getLocalGate()->getChannel()->par("distance");

  auto *some_stationary_qubit_in_qnic = rd_module->findModuleByPath("^.^.qnic[0].statQubit[0]");
  auto *some_stationary_qubit_in_qnic_r = rd_module->findModuleByPath("^.^.qnic_r[0].statQubit[0]");
  auto *some_stationary_qubit_in_qnic_rp = rd_module->findModuleByPath("^.^.qnic_rp[0].statQubit[0]");

  double emission_prob = 1.0;
  // TODO: fix this to read the emission success probability correctly. This is a quick fix!!
  if (some_stationary_qubit_in_qnic != nullptr) {
    emission_prob = some_stationary_qubit_in_qnic->par("emission_success_probability").doubleValue();
  } else if (some_stationary_qubit_in_qnic_r != nullptr) {
    emission_prob = some_stationary_qubit_in_qnic_r->par("emission_success_probability").doubleValue();
  } else if (some_stationary_qubit_in_qnic_rp != nullptr) {
    emission_prob = some_stationary_qubit_in_qnic_rp->par("emission_success_probability").doubleValue();
  } else {
    error("cannot read emission_success_probability from file");
  }

  return (channel_length / speed_of_light_in_fiber) * emission_prob;
}

/**
 * @param link
 * @param weight
 * @param should_set_quantum_link
 * If should_set_quantum_link is true, the function will set quantum links to the value of weight (RoutingDaemon sets quantum links).
 * If should_set_quantum_link is false, the function will set any other links to the value of weight (Router sets classical links).
 */
void SharedResource::setWeightOfLink(cTopology::LinkOut *link, double weight, bool should_set_quantum_link) {
  bool is_quantum_link = (strstr(link->getLocalGate()->getFullName(), "quantum") != nullptr);
  if (should_set_quantum_link == is_quantum_link) {
    link->setWeight(weight);
  } else {
    link->disable();
  }
}

void SharedResource::finish() {}

}  // namespace quisp::modules::SharedResource
