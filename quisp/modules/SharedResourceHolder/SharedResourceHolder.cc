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
  std::call_once(app_init_flag, [&](){
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

cTopology *SharedResourceHolder::getTopologyForRoutingDaemon() {
  std::call_once(rd_init_flag, [&](){
    routingdaemon_topology = new cTopology("topo");
    // Any node that has a parameter included_in_topology will be included in routing
    routingdaemon_topology->extractByParameter("included_in_topology", "\"yes\"");
    updateChannelWeightsInTopology(routingdaemon_topology);

  });
  return routingdaemon_topology;
}

// Initialize channel weights for all existing links.
void SharedResourceHolder::updateChannelWeightsInTopology(cTopology *topo) {
  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all nodes
    auto node = topo->getNode(i);
    updateChannelWeightsOfNode(node);
  }
}

void SharedResourceHolder::updateChannelWeightsOfNode(cTopology::Node *node) {
  for (int i = 0; i < node->getNumOutLinks(); i++) {  // Traverse through all links from a specific node.

    // For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
    auto outgoing_link = node->getLinkOut(i);

    double channel_weight = calculateSecPerBellPair(node->getModule(), outgoing_link);

    if (strstr(outgoing_link->getLocalGate()->getFullName(), "quantum")) {
      // Otherwise, keep the quantum channels and set the weight
      outgoing_link->setWeight(channel_weight);  // Set channel weight
    } else {
      // Ignore classical link in quantum routing table
      outgoing_link->disable();
    }
  }
}

cModule *SharedResourceHolder::getStatQubit(cModule *parent_module) {
  if(parent_module == nullptr) return nullptr;
  return parent_module->getSubmodule("statQubit", 0);
}

// The cost metric is taken from https://arxiv.org/abs/1206.5655
double SharedResourceHolder::calculateSecPerBellPair(cModule *node_module, const cTopology::LinkOut *const outgoing_link) {
  double speed_of_light_in_fiber = outgoing_link->getLocalGate()->getChannel()->par("speed_of_light_in_fiber");
  double channel_length = outgoing_link->getLocalGate()->getChannel()->par("distance");

  auto *some_stationary_qubit_in_qnic = getStatQubit(node_module->getSubmodule("qnic", 0));
  auto *some_stationary_qubit_in_qnic_r = getStatQubit(node_module->getSubmodule("qnic_r", 0));

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

void SharedResourceHolder::finish() {}

}  // namespace quisp::modules::SharedResourceHolder
