#pragma once
#include <omnetpp.h>

using namespace omnetpp;

namespace quisp::modules::TopologyInitializer {

class TopologyInitializer : public omnetpp::cSimpleModule {
 public:
  TopologyInitializer();
  ~TopologyInitializer();

  void initialize() override;
  void finish() override;
  void initTopologyForApplication(cTopology *topo);
  cTopology *getTopologyForRoutingDaemon();

 protected:

 private:
  void updateChannelWeightsInTopology(cTopology *topo);
  void updateChannelWeightsOfNode(cTopology::Node *node);
  cModule *getStatQubit(cModule *parent_module);
  double calculateSecPerBellPair(cModule *node_module, const cTopology::LinkOut *const outgoing_link);
};

Define_Module(TopologyInitializer);
}  // namespace quisp::modules::TopologyInitializer
