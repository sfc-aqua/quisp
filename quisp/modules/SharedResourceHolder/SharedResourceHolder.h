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
  cTopology *getTopologyForRoutingDaemon();

 protected:

 private:
  void updateChannelWeightsInTopology(cTopology *topo);
  void updateChannelWeightsOfNode(cTopology::Node *node);
  cModule *getStatQubit(cModule *parent_module);
  double calculateSecPerBellPair(cModule *node_module, const cTopology::LinkOut *const outgoing_link);

  std::once_flag app_init_flag{};
  std::unordered_map<int, int> end_node_weight_map;

  std::once_flag rd_init_flag{};
  cTopology *routingdaemon_topology = nullptr;
};

Define_Module(SharedResourceHolder);
}  // namespace quisp::modules::SharedResourceHolder
