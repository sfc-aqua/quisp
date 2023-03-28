#include "SharedResourceHolder.h"
#include <memory>
#include <random>
#include <vector>
#include "omnetpp/ctopology.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::SharedResourceHolder {

SharedResourceHolder::SharedResourceHolder() {}

SharedResourceHolder::~SharedResourceHolder() {}

void SharedResourceHolder::initialize() {}

std::unordered_map<int, int> SharedResourceHolder::getEndNodeWeightMapForApplication(const char *node_type) {
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

cTopology *SharedResourceHolder::getTopologyForRouter() {
  std::call_once(router_init_flag, [&]() { updateChannelWeightsInTopology(router_topology, std::nullopt); });
  return router_topology;
}

cTopology *SharedResourceHolder::getTopologyForRoutingDaemon(cModule *rd_module) {
  std::call_once(rd_init_flag, [&]() { updateChannelWeightsInTopology(routingdaemon_topology, rd_module); });
  return routingdaemon_topology;
}

// Initialize channel weights for all existing links.
void SharedResourceHolder::updateChannelWeightsInTopology(cTopology *&topo, std::optional<cModule *> rd_module) {
  topo = new cTopology("topo");
  topo->extractByParameter("included_in_topology", "\"yes\"");
  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all nodes
    auto node = topo->getNode(i);
    updateChannelWeightsOfNode(node, rd_module);
  }
}

void SharedResourceHolder::updateChannelWeightsOfNode(cTopology::Node *node, std::optional<cModule *> rd_module) {
  for (int i = 0; i < node->getNumOutLinks(); i++) {  // Traverse through all links from a specific node.
    // For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
    auto outgoing_link = node->getLinkOut(i);

    if (rd_module.has_value()) {
      double channel_weight = calculateSecPerBellPair(rd_module.value(), outgoing_link);
      setWeightOfChannel(outgoing_link, channel_weight, true);
    } else {
      double channel_cost = outgoing_link->getLocalGate()->getChannel()->par("cost");
      setWeightOfChannel(outgoing_link, channel_cost, false);
    }
  }
}

// The cost metric is taken from https://arxiv.org/abs/1206.5655
double SharedResourceHolder::calculateSecPerBellPair(cModule *rd_module, const cTopology::LinkOut *const outgoing_link) {
  double speed_of_light_in_fiber = outgoing_link->getLocalGate()->getChannel()->par("speed_of_light_in_fiber");
  double channel_length = outgoing_link->getLocalGate()->getChannel()->par("distance");

  auto *some_stationary_qubit_in_qnic = rd_module->findModuleByPath("^.^.qnic[0].statQubit[0]");
  auto *some_stationary_qubit_in_qnic_r = rd_module->findModuleByPath("^.^.qnic_r[0].statQubit[0]");

  double emission_prob = 1.0;
  // TODO: fix this to read the emission success probability correctly. This is a quick fix!!
  if (some_stationary_qubit_in_qnic != nullptr) {
    emission_prob = some_stationary_qubit_in_qnic->par("emission_success_probability").doubleValue();
  } else if (some_stationary_qubit_in_qnic_r != nullptr) {
    emission_prob = some_stationary_qubit_in_qnic_r->par("emission_success_probability").doubleValue();
  } else {
    error("cannot read emission_success_probability from file");
  }

  return (channel_length / speed_of_light_in_fiber) * emission_prob;
}

void SharedResourceHolder::setWeightOfChannel(cTopology::LinkOut *link, double weight, bool should_set_quantum_channel) {
  bool is_quantum_channel = (strstr(link->getLocalGate()->getFullName(), "quantum") != nullptr);
  if (should_set_quantum_channel == is_quantum_channel) {
    link->setWeight(weight);
  } else {
    link->disable();
  }
}

void SharedResourceHolder::finish() {}

}  // namespace quisp::modules::SharedResourceHolder
