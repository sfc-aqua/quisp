/** \file Application.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief Application
 */
#include "Application.h"
#include <random>
#include <vector>
#include "utils/ComponentProvider.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

Application::Application() : provider(utils::ComponentProvider{this}) {}

/**
 * \brief Initialize module.
 *
 * If the node type is not EndNode, this module is automatically deleted in this function.
 */
void Application::initialize() {
  initializeLogger(provider);

  // Since we only need this module in EndNode, delete it otherwise.
  // We delete it in the handleMessage because it's the right way not to raise error
  if (!gate("toRouter")->isConnected()) {
    DeleteThisModule *msg = new DeleteThisModule("DeleteThisModule");
    scheduleAt(simTime(), msg);
    return;
  }

  my_address = provider.getQNode()->par("address");
  is_initiator = provider.getQNode()->par("isInitiator");

  if (!is_initiator) {
    return;
  }

  createEndNodeWeightMap();
  generateTrafficMsg = new GenerateTraffic("GenerateTraffic");
  scheduleAt(simTime() + 100, generateTrafficMsg);
  generateTraffic();
}

/**
 * \brief Generate connection setup response packet
 * @param dest_addr Destination address of this request
 */
ConnectionSetupRequest *Application::createConnectionSetupRequest(int dest_addr, int num_of_required_resources) {
  ConnectionSetupRequest *pk = new ConnectionSetupRequest("ConnSetupRequest");
  pk->setActual_srcAddr(my_address);
  pk->setActual_destAddr(dest_addr);
  pk->setDestAddr(my_address);
  pk->setSrcAddr(my_address);
  pk->setNum_measure(num_of_required_resources);
  pk->setKind(7);
  return pk;
}

/**
 * \brief Message handler
 *
 * @param msg OMNeT++ cMessage
 */
void Application::handleMessage(cMessage *msg) {
  if (dynamic_cast<DeleteThisModule *>(msg)) {
    delete msg;
    deleteModule();
    return;
  }

  if (auto *req = dynamic_cast<ConnectionSetupRequest *>(msg)) {
    logPacket("handleMessage", msg);
    send(msg, "toRouter");
    return;
  }

  if (dynamic_cast<ConnectionSetupResponse *>(msg)) {
    logPacket("handleMessage", msg);
    send(msg, "toRouter");
    return;
  }

  if (dynamic_cast<InternalRuleSetForwarding *>(msg)) {
    logPacket("handleMessage", msg);
    send(msg, "toRouter");
    return;
  }

  if (dynamic_cast<GenerateTraffic *>(msg)) {
    logPacket("handleMessage", msg);
    generateTraffic();
    scheduleAt(simTime() + 100, msg);
  }

  delete msg;
  error("Application not recognizing this packet");
}

/**
 * \brief Store communicatable EndNode addresses and their mass parameters
 */
void Application::createEndNodeWeightMap() {
  cTopology *topo = new cTopology("topo");

  topo->extractByParameter("nodeType", provider.getQNode()->par("nodeType").str().c_str());

  for (int i = 0; i < topo->getNumNodes(); i++) {
    cModule *endnodeModule = topo->getNode(i)->getModule();

    int addr = endnodeModule->par("address").intValue();
    int weight = endnodeModule->par("mass").intValue();

    if (addr == my_address) {
      // set self weight to 0 to avoid creating connection request with self
      end_node_weight_map[addr] = 0;
    } else {
      end_node_weight_map[addr] = weight;
    }
  }

  delete topo;
}

void Application::generateTraffic() {
  std::vector<int> weights;
  std::vector<int> addresses;

  cConfiguration *config = getEnvir()->getConfig();
  auto *sim_time_limit_option = cConfigOption::get("sim-time-limit");
  double max_sim_time = config->getAsDouble(sim_time_limit_option);

  auto generate_up_to_time = simTime() + 100;
  // if max_sim_time is not defined generate traffic for the next 100s for now
  if (max_sim_time != 0) {
    generate_up_to_time = max_sim_time;
    cancelAndDelete(generateTrafficMsg);
  }

  for (auto &it : end_node_weight_map) {
    weights.push_back(it.second);
    addresses.push_back(it.first);
  }

  std::discrete_distribution<int> dist(std::begin(weights), std::end(weights));
  std::mt19937 gen;
  gen.seed(time(0));  // if you want different results from different runs

  simtime_t send_time = simTime() + par("sendIaTime").doubleValue();

  while (send_time < generate_up_to_time) {
    int dest_addr = addresses[dist(gen)];
    int num_request_bell_pair = par("numberOfBellpair").intValue();
    ConnectionSetupRequest *pk = createConnectionSetupRequest(dest_addr, num_request_bell_pair);
    EV_INFO << "Node " << my_address << " will initiate connection to " << dest_addr << " at " << send_time << " with " << num_request_bell_pair << " Bell pairs\n";
    scheduleAt(send_time, pk);
    send_time = send_time + par("sendIaTime").doubleValue();
  }
}

}  // namespace modules
}  // namespace quisp
