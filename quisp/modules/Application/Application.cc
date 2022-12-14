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
  is_initiator = provider.getQNode()->par("is_initiator");

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
    logger->logPacket("handleMessage", msg);
    send(msg, "toRouter");
    return;
  }

  if (dynamic_cast<ConnectionSetupResponse *>(msg)) {
    logger->logPacket("handleMessage", msg);
    send(msg, "toRouter");
    return;
  }

  if (dynamic_cast<InternalRuleSetForwarding *>(msg)) {
    logger->logPacket("handleMessage", msg);
    send(msg, "toRouter");
    return;
  }

  if (dynamic_cast<GenerateTraffic *>(msg)) {
    logger->logPacket("handleMessage", msg);
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
  std::unordered_map<int, int> temp_end_node_weight_map;

  topo->extractByParameter("node_type", provider.getQNode()->par("node_type").str().c_str());

  for (int i = 0; i < topo->getNumNodes(); i++) {
    cModule *endnodeModule = topo->getNode(i)->getModule();
    int address = endnodeModule->par("address").intValue();
    int weight = endnodeModule->par("mass").intValue();

    temp_end_node_weight_map[address] = weight;
  }
  delete topo;

  if (!par("has_specific_recipients").boolValue()) {
    // set self weight to 0; so we don't create self traffic
    temp_end_node_weight_map[my_address] = 0;
    std::swap(end_node_weight_map, temp_end_node_weight_map);
    return;
  }

  auto recipient_addresses = ((cValueArray *)(par("possible_recipients").objectValue()))->asIntVector();

  for (int address : recipient_addresses) {
    if (temp_end_node_weight_map.find(address) == temp_end_node_weight_map.end()) {
      error("possible recipints list contains non-existing address");
    }
    end_node_weight_map[address] = temp_end_node_weight_map[address];
  }

  // error checking
  if (recipient_addresses.size() == 0) {
    error("setting has_specific_recipients to true but given an empty array of recipients is not allowed");
  }
  if (end_node_weight_map[my_address] != 0) {
    error("setting self as possible recipient is not allowed");
  }
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

  simtime_t send_time = simTime() + par("request_generation_interval").doubleValue();

  while (send_time < generate_up_to_time) {
    int dest_addr = addresses[dist(gen)];
    int num_request_bell_pair = par("number_of_bellpair").intValue();
    ConnectionSetupRequest *pk = createConnectionSetupRequest(dest_addr, num_request_bell_pair);
    EV_INFO << "Node " << my_address << " will initiate connection to " << dest_addr << " at " << send_time << " with " << num_request_bell_pair << " Bell pairs\n";
    scheduleAt(send_time, pk);
    send_time = send_time + par("request_generation_interval").doubleValue();
  }
}

}  // namespace modules
}  // namespace quisp
