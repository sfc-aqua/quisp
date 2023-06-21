#include <gtest/gtest.h>

#include <messages/classical_messages.h>
#include <test_utils/TestUtils.h>

#include "Router.h"
#include "gmock/gmock-spec-builders.h"
#include "modules/SharedResource/SharedResource.h"

using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using namespace quisp::modules::ospf;
using OriginalRouter = quisp::modules::Router;

namespace {

class MockLinkStateDatabase : public LinkStateDatabase {
 public:
  using LinkStateDatabase::link_state_database;
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode) : parent_qnode(_qnode) {}
  cModule* getNode() override { return parent_qnode; }
  int getNodeAddr() override { return parent_qnode->address; }
  SharedResource* getSharedResource() override { return &shared_resource; }

 private:
  TestQNode* parent_qnode;
  SharedResource shared_resource;
};

class Router : public OriginalRouter {
 public:
  using OriginalRouter::generateRoutingTable;
  using OriginalRouter::handleMessage;
  using OriginalRouter::initialize;
  using OriginalRouter::link_state_database;
  using OriginalRouter::my_address;
  using OriginalRouter::neighbor_table;
  using OriginalRouter::ospfInitializeRouter;
  using OriginalRouter::ospfSendHelloPacketToNeighbor;
  using OriginalRouter::par;
  using OriginalRouter::routing_table;
  using OriginalRouter::unrecognizable_destination_messages;
  explicit Router(TestQNode* parent_qnode) : OriginalRouter() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_router"));
    hmPort = new TestGate(this, "hmPort$o");
    rePort = new TestGate(this, "rePort$o");
    cmPort = new TestGate(this, "cmPort$o");
    queueGate = new TestGate(this, "toQueue");
    routing_table.insert({8, queueGate->getId()});
    setParBool(this, "run_ospf", true);
  }

  TestGate* hmPort;
  TestGate* rePort;
  TestGate* cmPort;
  TestGate* queueGate;

  std::map<const char*, cGate*> ports{};
  cGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "hmPort$o") == 0) return hmPort;
    if (strcmp(gatename, "cmPort$o") == 0) return cmPort;
    if (strcmp(gatename, "rePort$o") == 0) return rePort;
    if (strcmp(gatename, "toQueue") == 0) return queueGate;
    error("port: %s not found", gatename);
    return nullptr;
  }
  size_t getNumNeighbors() const override { return 1; }
  void generateRoutingTable() override{};
};

class OspfTestGate : public gate::TestGate {
 public:
  OspfTestGate(cModule* mod, const char* name) : TestGate(mod, name) { installChannel(&channel); };

 private:
  channel::TestDatarateChannel channel;
};

class OspfTestQNode : public qnode::TestQNode {
 public:
  OspfTestQNode(int addr, int mass, bool is_initiator) : TestQNode(addr, mass, is_initiator), port(this, "port"){};
  cGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "port$o") == 0) return &port;
    throw cRuntimeError("port: %s not found", gatename);
    return nullptr;
  }

 private:
  OspfTestGate port;
};

class RouterTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    qnode = new OspfTestQNode(10, 0, true);
    router = new Router(qnode);
    sim->registerComponent(router);
    sim->setContext(router);
    router->callInitialize();  // Router sends a message at initialization
    // pop the sent message so the tests won't be affected by the message
    router->queueGate->messages.pop_back();
  }
  void TearDown() {}

  /**
   * This function mimics the behavior of Omnet++ internals
   * that sets up the message arrival to Router module.
   * Call this function before router->handleMessages
   * when you want to retrieve the info of the arrival gate.
   */
  void mockMessageArrival(cMessage* msg) {
    int queue_size = 1;
    int arrival_gate_index = 0;
    router->addGateVector("fromQueue", cGate::Type::INPUT, queue_size);
    msg->setArrival(router->getId(), router->findGate("fromQueue", arrival_gate_index));
  }

  TestSimulation* sim;
  Router* router;
  TestQNode* qnode;
};

TEST_F(RouterTest, ospfReceiveHelloPacketHandleImpossibleCase) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  router->neighbor_table[src] = {};

  ASSERT_THROW(router->handleMessage(msg_from_other_node), cRuntimeError);
}

TEST_F(RouterTest, ospfReceiveHelloPacketAndEstablishInitState) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);

  mockMessageArrival(msg_from_other_node);

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].state, OspfState::INIT);
  int arrival_gate_index = 0;
  ASSERT_EQ(router->neighbor_table[src].gate_index, arrival_gate_index);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  auto sent_msg = router->queueGate->messages.front();
  ASSERT_TRUE(dynamic_cast<OspfHelloPacket*>(sent_msg));
}

TEST_F(RouterTest, ospfReceiveHelloPacketAndEstablishTwoWayState) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  NeighborTable neighbor_table;
  neighbor_table[router->my_address] = OspfNeighborInfo(router->my_address);
  msg_from_other_node->setNeighbor_table(neighbor_table);

  mockMessageArrival(msg_from_other_node);

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].state, OspfState::TWO_WAY);
  const int arrival_gate_index = 0;
  ASSERT_EQ(router->neighbor_table[src].gate_index, arrival_gate_index);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  auto sent_msg = router->queueGate->messages.front();
  ASSERT_TRUE(dynamic_cast<OspfHelloPacket*>(sent_msg));
}

TEST_F(RouterTest, ospfReceiveHelloPacketAndTransitionFromInitToTwoWayState) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  NeighborTable neighbor_table;
  neighbor_table[router->my_address] = OspfNeighborInfo(router->my_address);
  msg_from_other_node->setNeighbor_table(neighbor_table);

  mockMessageArrival(msg_from_other_node);

  const int arrival_gate_index = 0;
  router->neighbor_table[src] = OspfNeighborInfo(arrival_gate_index, OspfState::INIT);

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].state, OspfState::EXSTART);
  ASSERT_EQ(router->neighbor_table[src].gate_index, arrival_gate_index);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  auto sent_msg = router->queueGate->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->getIs_master());
}

TEST_F(RouterTest, ospfReceiveHelloPacketButCannotTransitionToTwoWayState) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  NeighborTable neighbor_table;
  neighbor_table[router->my_address] = OspfNeighborInfo(router->my_address);
  msg_from_other_node->setNeighbor_table(neighbor_table);

  mockMessageArrival(msg_from_other_node);

  router->neighbor_table[src] = OspfNeighborInfo(0, OspfState::DOWN);

  ASSERT_ANY_THROW(router->handleMessage(msg_from_other_node));
}

TEST_F(RouterTest, ospfMasterRespondsToExstartPacketOfSoonToBeSlave) {
  const NodeAddr src = 1;
  auto slave_wants_to_be_master_pk = new OspfDbdPacket;
  slave_wants_to_be_master_pk->setSrcAddr(src);
  slave_wants_to_be_master_pk->setIs_master(true);
  slave_wants_to_be_master_pk->setState(OspfState::EXSTART);

  router->handleMessage(slave_wants_to_be_master_pk);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  auto sent_msg = router->queueGate->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->getIs_master());
  ASSERT_EQ(dbd_pk->getLsdb().size(), 0);
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXSTART);
}

TEST_F(RouterTest, ospfMasterRespondsToExstartPacketOfSlave) {
  const NodeAddr src = 1;
  auto slave_wants_to_be_master_pk = new OspfDbdPacket;
  slave_wants_to_be_master_pk->setSrcAddr(src);
  slave_wants_to_be_master_pk->setIs_master(false);
  slave_wants_to_be_master_pk->setState(OspfState::EXSTART);

  router->handleMessage(slave_wants_to_be_master_pk);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  auto sent_msg = router->queueGate->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->getIs_master());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXSTART);
}

TEST_F(RouterTest, ospfSlaveRespondsToExstartPacketOfMaster) {
  const NodeAddr src = router->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIs_master(true);
  msg_from_other_node->setState(OspfState::EXSTART);
  router->neighbor_table[src].state = OspfState::EXSTART;

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].state, OspfState::EXCHANGE);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  auto sent_msg = router->queueGate->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_FALSE(dbd_pk->getIs_master());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXCHANGE);
}

TEST_F(RouterTest, ospfSlaveDoesNotSendExchangePacketTwice) {
  const NodeAddr src = router->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIs_master(true);
  msg_from_other_node->setState(OspfState::EXSTART);
  msg_from_other_node->setLsdb({SummaryLinkStateAdvertisement()});
  router->neighbor_table[src].state = OspfState::EXCHANGE;

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].state, OspfState::EXCHANGE);
  ASSERT_EQ(router->queueGate->messages.size(), 0);
}

TEST_F(RouterTest, ospfMasterRespondsToExchangePacketOfSlave) {
  const NodeAddr src = router->my_address - 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIs_master(false);
  msg_from_other_node->setState(OspfState::EXCHANGE);
  msg_from_other_node->setLsdb({SummaryLinkStateAdvertisement()});
  router->neighbor_table[src].state = OspfState::EXSTART;

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].state, OspfState::LOADING);
  ASSERT_EQ(router->queueGate->messages.size(), 2);
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(router->queueGate->messages.front());
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->getIs_master());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXCHANGE);
  auto lsr_pk = dynamic_cast<OspfLsrPacket*>(router->queueGate->messages.back());
  ASSERT_TRUE(lsr_pk);
}

TEST_F(RouterTest, ospfSlaveRespondsToExchangePacketOfMaster) {
  const NodeAddr src = router->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIs_master(true);
  msg_from_other_node->setState(OspfState::EXCHANGE);
  msg_from_other_node->setLsdb({SummaryLinkStateAdvertisement()});

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  auto sent_msg = router->queueGate->messages.front();
  ASSERT_TRUE(dynamic_cast<OspfLsrPacket*>(sent_msg));
}

TEST_F(RouterTest, ospfReceiveDbdPacketWithNoLsdb) {
  const NodeAddr src = router->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIs_master(true);
  msg_from_other_node->setState(OspfState::EXCHANGE);
  auto other_node_lsa = LinkStateAdvertisement(src, src, {});
  msg_from_other_node->setLsdb({other_node_lsa});
  MockLinkStateDatabase mock_link_state_database;
  mock_link_state_database.link_state_database[src] = other_node_lsa;
  router->link_state_database = mock_link_state_database;

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].state, OspfState::FULL);
}

TEST_F(RouterTest, ospfRespondToLsrPacket) {
  auto msg_from_other_node = new OspfLsrPacket;

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  ASSERT_TRUE(dynamic_cast<OspfLsuPacket*>(router->queueGate->messages.front()));
}

TEST_F(RouterTest, ospfRespondToLsuPacket) {
  const NodeAddr other_node = 1;
  const NodeAddr my_address = router->my_address;
  auto msg_from_other_node = new OspfLsuPacket;

  MockLinkStateDatabase mock_link_state_database;
  router->neighbor_table[other_node] = OspfNeighborInfo(other_node, other_node, 0);
  mock_link_state_database.link_state_database[my_address] = LinkStateAdvertisement(my_address, my_address, router->neighbor_table);

  NeighborTable other_node_neighbor_table;
  other_node_neighbor_table[my_address] = OspfNeighborInfo(my_address, my_address, 0);
  mock_link_state_database.link_state_database[other_node] = LinkStateAdvertisement(other_node, other_node, other_node_neighbor_table);

  router->link_state_database = mock_link_state_database;

  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->queueGate->messages.size(), 2);
  ASSERT_TRUE(dynamic_cast<OspfLsAckPacket*>(router->queueGate->messages[0]));
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(router->queueGate->messages[1]);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->getIs_master());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXCHANGE);
}

TEST_F(RouterTest, handlePacketForUnknownAddr) {
  auto unknown_addr_msg = new ConnectionSetupRequest;
  unknown_addr_msg->setDestAddr(7);
  router->handleMessage(unknown_addr_msg);
  ASSERT_EQ(router->unrecognizable_destination_messages.size(), 1);

  auto known_addr_msg = new ConnectionSetupRequest;
  known_addr_msg->setDestAddr(8);
  ASSERT_THROW({ router->handleMessage(known_addr_msg); }, cRuntimeError);
}

TEST_F(RouterTest, packetForUnknownAddrIsSentAfterRoutingTableUpdate) {
  const int dest = 7;
  auto unknown_addr_msg = new LinkTomographyRequest;
  unknown_addr_msg->setDestAddr(dest);
  router->handleMessage(unknown_addr_msg);
  ASSERT_EQ(router->unrecognizable_destination_messages.size(), 1);
  router->routing_table[dest] = 0;

  auto link_state_update = new OspfLsuPacket;
  router->handleMessage(link_state_update);
  ASSERT_EQ(router->queueGate->messages.size(), 2);
  ASSERT_TRUE(dynamic_cast<OspfLsAckPacket*>(router->queueGate->messages.front()));
  ASSERT_TRUE(dynamic_cast<LinkTomographyRequest*>(router->queueGate->messages.back()));
}

TEST_F(RouterTest, handlePacketForOtherNode) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(8);
  router->handleMessage(msg);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  {
    auto* msg = router->queueGate->messages.at(0);
    auto req = dynamic_cast<ConnectionSetupRequest*>(msg);
    EXPECT_EQ(req->getHopCount(), 1);
  }
}

TEST_F(RouterTest, handleConnSetupRequest) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleConnSetupResponse) {
  auto msg = new ConnectionSetupResponse;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleBSMTimingNotification) {
  auto msg = new BSMTimingNotification;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleEPPSTimingNotifier) {
  auto msg = new EPPStimingNotifier;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleRejectConnectionSetupReq) {
  auto msg = new RejectConnectionSetupRequest;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleInternalRuleSetForwarding) {
  auto msg = new InternalRuleSetForwarding;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleInternalRuleSetForwarding_Application) {
  auto msg = new InternalRuleSetForwarding_Application;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleSwappingResult) {
  auto msg = new SwappingResult;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyAck) {
  auto msg = new LinkTomographyAck;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->hmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyRequest) {
  auto msg = new LinkTomographyRequest;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->hmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyRuleSet) {
  auto msg = new LinkTomographyRuleSet;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handlePurificationResult) {
  auto msg = new PurificationResult;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleStopEmitting) {
  auto msg = new StopEmitting;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}
}  // namespace
