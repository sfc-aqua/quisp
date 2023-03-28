#pragma once
#include <omnetpp.h>
#include <mutex>
#include <optional>
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
  void updateChannelWeightsInTopology(cTopology *&topo, std::optional<cModule *> rd_module);
  void updateChannelWeightsOfNode(cTopology::Node *node, std::optional<cModule *> rd_module);
  void setWeightOfChannel(cTopology::LinkOut *link, double weight, bool should_set_quantum_channel);
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
