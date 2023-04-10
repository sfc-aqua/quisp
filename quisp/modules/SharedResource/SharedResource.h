#pragma once
#include <omnetpp.h>
#include <mutex>
#include <optional>
#include <unordered_map>

using namespace omnetpp;

/**
 * @brief SharedResource is a global module that initializes shared static resources
 * and provides them to other modules.
 *
 * @details
 * SharedResource provides the following:
 * 1. EndNodeWeightMap for Application module
 * 2. cTopology that has channel weights initialized for RoutingDaemon and Router modules
 *
 * SharedResource initializes these resources the first time when other modules
 * attempt to access the resources.
 * Once the initialization is done, the resources are
 * never modified again for the lifetime of the SharedResource instance.
 *
 * Modules can access the shared resources by calling methods from ComponentProvider
 *
 */

namespace quisp::modules::SharedResource {

class SharedResource : public omnetpp::cSimpleModule {
 public:
  SharedResource();
  ~SharedResource();

  void initialize() override;
  void finish() override;
  const std::unordered_map<int, int> getEndNodeWeightMapForApplication(const char *const node_type);
  cTopology *getTopologyForRoutingDaemon(const cModule *const rd_module);
  cTopology *getTopologyForRouter();

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

Define_Module(SharedResource);
}  // namespace quisp::modules::SharedResource
