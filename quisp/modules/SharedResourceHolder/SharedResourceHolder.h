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
  const std::unordered_map<int, int> getEndNodeWeightMapForApplication(const char *const node_type);
  const cTopology *const getTopologyForRoutingDaemon(const cModule *const rd_module);
  const cTopology *const getTopologyForRouter();

 protected:
 private:
  void updateChannelWeightsInTopology(cTopology *&topo, std::optional<const cModule *const> rd_module);
  void updateChannelWeightsOfNode(cTopology::Node *node, std::optional<const cModule *const> rd_module);
  double calculateSecPerBellPair(const cModule *const rd_module, const cTopology::LinkOut *const outgoing_link);
  void setWeightOfLink(cTopology::LinkOut *link, double weight, bool should_set_quantum_channel);

  std::once_flag app_init_flag{};
  std::unordered_map<int, int> end_node_weight_map;

  std::once_flag router_init_flag{};
  cTopology *router_topology = nullptr;

  std::once_flag rd_init_flag{};
  cTopology *routingdaemon_topology = nullptr;
};

Define_Module(SharedResourceHolder);
}  // namespace quisp::modules::SharedResourceHolder
