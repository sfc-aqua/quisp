#pragma once
#include <omnetpp.h>
#include <mutex>
#include <unordered_map>

using namespace omnetpp;

namespace quisp::modules::SharedResourceHolder {

class SharedResourceHolder : public omnetpp::cSimpleModule {
 public:
  SharedResourceHolder();
  ~SharedResourceHolder();

  void initialize() override;
  void finish() override;
  std::unordered_map<int, int> getEndNodeWeightMapForApplication(const char *node_type);
  cTopology *getTopologyForRoutingDaemon(cModule *rd_module);
  cTopology *getTopologyForRouter();

 protected:
 private:
  cTopology *constructTopology(cTopology *topo);
  void updateChannelWeightsInTopology(cTopology *topo, cModule *rd_module);
  void updateChannelWeightsOfNode(cTopology::Node *node, cModule *rd_module);
  // void setWeightIfClassicalChannel(cTopology::LinkOut *link, double weight);
  // void setWeightIfQuantumChannel(cTopology::LinkOut *link, double weight);
  void setWeightOfChannel(cTopology::LinkOut *link, double weight, bool is_quantum);
  double calculateSecPerBellPair(cModule *rd_module, const cTopology::LinkOut *const outgoing_link);

  std::once_flag app_init_flag{};
  std::unordered_map<int, int> end_node_weight_map;

  std::once_flag router_init_flag{};
  cTopology *router_topology = nullptr;

  std::once_flag rd_init_flag{};
  cTopology *routingdaemon_topology = nullptr;
};

Define_Module(SharedResourceHolder);
}  // namespace quisp::modules::SharedResourceHolder
