#include "RoutingDaemon.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include "gmock/gmock-function-mocker.h"
#include "modules/QNIC.h"
#include "omnetpp/ccomponent.h"
#include "omnetpp/cmodule.h"
#include "test_utils/TestUtilFunctions.h"

namespace {

using namespace omnetpp;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::ospf;
using ospf::NeighborTable;
using routing_daemon::RoutingDaemon;
using SharedResource::SharedResource;

class MockLinkStateDatabase : public LinkStateDatabase {
 public:
  using LinkStateDatabase::link_state_database;
};

class MockQnic : public cModule {
 public:
  MockQnic(int address, int index, QNIC_type qnic_type) {
    setParInt(this, "self_qnic_address", address);
    setParInt(this, "self_qnic_index", index);
    setParInt(this, "self_qnic_type", qnic_type);
  }
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode, IHardwareMonitor* _hardware_monitor) : parent_qnode(_qnode), hardware_monitor(_hardware_monitor) { initQnicModules(); }
  Strategy(TestQNode* _qnode) : parent_qnode(_qnode) { initQnicModules(); }
  cModule* getNode() override { return parent_qnode; }
  cModule* getQNIC(int qnic_index, QNIC_type qnic_type) override {
    auto it = qnic_modules.find({qnic_type, qnic_index});
    if (it == qnic_modules.end()) return nullptr;
    return it->second;
  }
  int getNodeAddr() override { return parent_qnode->address; }
  SharedResource* getSharedResource() override { return &shared_resource; }
  IHardwareMonitor* getHardwareMonitor() override { return hardware_monitor; }

  void initQnicModules() {
    //   // init qnic E
    qnic_modules.insert({{QNIC_E, 0}, new MockQnic(0, 0, QNIC_E)});
    qnic_modules.insert({{QNIC_E, 1}, new MockQnic(1, 1, QNIC_E)});
    // init qnic R
    qnic_modules.insert({{QNIC_R, 0}, new MockQnic(2, 0, QNIC_R)});
    qnic_modules.insert({{QNIC_R, 1}, new MockQnic(3, 1, QNIC_R)});
    // init qnic RP
    qnic_modules.insert({{QNIC_RP, 0}, new MockQnic(4, 0, QNIC_RP)});
    qnic_modules.insert({{QNIC_RP, 1}, new MockQnic(5, 1, QNIC_RP)});
  }

  std::map<std::pair<QNIC_type, int>, cModule*> qnic_modules;

 private:
  TestQNode* parent_qnode;
  IHardwareMonitor* hardware_monitor = nullptr;
  SharedResource shared_resource;
};

class RoutingDaemonTestTarget : public RoutingDaemon {
 public:
  using RoutingDaemon::initialize;
  using RoutingDaemon::par;

  using RoutingDaemon::handleMessage;
  using RoutingDaemon::link_state_database;
  using RoutingDaemon::my_address;
  using RoutingDaemon::neighbor_table;
  using RoutingDaemon::qrtable;
  RoutingDaemonTestTarget(TestQNode* qnode) : RoutingDaemon() {
    setParBool(this, "run_ospf", true);
    setParInt(this, "number_of_qnics", 2);
    setParInt(this, "number_of_qnics_r", 2);
    setParInt(this, "number_of_qnics_rp", 2);
    my_address = qnode->address;
    RouterPort = new TestGate(this, "RouterPort$o");
    this->provider.setStrategy(std::make_unique<Strategy>(qnode));
  }

  cGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "RouterPort$o") == 0) return RouterPort;
    error("port: %s not found", gatename);
    return nullptr;
  }

  void setMockHardwareMonitor(MockHardwareMonitor* hardware_monitor) {
    auto node = dynamic_cast<TestQNode*>(this->provider.getNode());
    this->provider.setStrategy(std::make_unique<Strategy>(node, hardware_monitor));
  }

  TestGate* RouterPort;
};

class OspfTestQNode : public qnode::TestQNode {
 public:
  OspfTestQNode(int addr, int mass, bool is_initiator) : TestQNode(addr, mass, is_initiator) {
    const int num_port = 1;
    addGateVector("port", cGate::Type::INPUT, num_port);
  }
  OspfTestQNode(int addr, int mass, bool is_initiator, std::string s) : TestQNode(addr, mass, is_initiator) { port = std::make_unique<TestGate>(this, s.c_str()); }
  cGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "port$o") == 0) return port.get();
    throw cRuntimeError("port: %s not found", gatename);
    return nullptr;
  }

 private:
  std::unique_ptr<TestGate> port;
};

class RoutingDaemonTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    qnode = new OspfTestQNode(10, 0, true);
    routing_daemon = new RoutingDaemonTestTarget(qnode);
    sim->registerComponent(routing_daemon);
    sim->setContext(routing_daemon);
  }
  void TearDown() {}

  TestSimulation* sim;
  RoutingDaemonTestTarget* routing_daemon;
  TestQNode* qnode;
};

TEST_F(RoutingDaemonTest, initializeTest) {
  routing_daemon->initialize(0);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  ASSERT_TRUE(dynamic_cast<OspfHelloPacket*>(sent_msg));
}

TEST_F(RoutingDaemonTest, noInitializationAfterStage0) {
  routing_daemon->initialize(1);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 0);
}

TEST_F(RoutingDaemonTest, ospfReceiveHelloPacketHandleImpossibleCase) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  routing_daemon->neighbor_table[src] = {};

  ASSERT_THROW(routing_daemon->handleMessage(msg_from_other_node), cRuntimeError);
}

TEST_F(RoutingDaemonTest, ospfReceiveHelloPacketAndEstablishInitState) {
  auto mock_hardware_monitor = std::make_unique<MockHardwareMonitor>();
  routing_daemon->setMockHardwareMonitor(mock_hardware_monitor.get());

  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);

  EXPECT_CALL(*mock_hardware_monitor, getLinkCost).WillOnce(Return(1));

  routing_daemon->handleMessage(msg_from_other_node);

  ASSERT_EQ(routing_daemon->neighbor_table[src].state, OspfState::INIT);
  int arrival_gate_index = 0;
  ASSERT_EQ(routing_daemon->neighbor_table[src].hop_address, arrival_gate_index);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  ASSERT_TRUE(dynamic_cast<OspfHelloPacket*>(sent_msg));
}

TEST_F(RoutingDaemonTest, ospfReceiveHelloPacketAndEstablishTwoWayState) {
  auto mock_hardware_monitor = std::make_unique<MockHardwareMonitor>();
  routing_daemon->setMockHardwareMonitor(mock_hardware_monitor.get());

  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  NeighborTable neighbor_table;
  neighbor_table[routing_daemon->my_address] = OspfNeighborInfo(routing_daemon->my_address);
  msg_from_other_node->setNeighborTable(neighbor_table);

  // auto expected_qnic = std::make_unique<InterfaceInfo>();
  // expected_qnic->qnic.address = 0;
  // expected_qnic->link_cost = 1;
  // EXPECT_CALL(*mock_hardware_monitor, findInterfaceByNeighborAddr(_)).WillOnce(Return(ByMove(std::move(expected_qnic))));

  routing_daemon->handleMessage(msg_from_other_node);

  ASSERT_EQ(routing_daemon->neighbor_table[src].state, OspfState::TWO_WAY);
  const int arrival_gate_index = 0;
  ASSERT_EQ(routing_daemon->neighbor_table[src].hop_address, arrival_gate_index);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  ASSERT_TRUE(dynamic_cast<OspfHelloPacket*>(sent_msg));
}

TEST_F(RoutingDaemonTest, ospfReceiveHelloPacketAndTransitionFromInitToTwoWayState) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  NeighborTable neighbor_table;
  neighbor_table[routing_daemon->my_address] = OspfNeighborInfo(routing_daemon->my_address);
  msg_from_other_node->setNeighborTable(neighbor_table);

  const int arrival_gate_index = 0;
  routing_daemon->neighbor_table[src] = OspfNeighborInfo(arrival_gate_index, OspfState::INIT);

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->neighbor_table[src].state, OspfState::EXSTART);
  ASSERT_EQ(routing_daemon->neighbor_table[src].hop_address, arrival_gate_index);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->isMaster());
}

TEST_F(RoutingDaemonTest, ospfReceiveHelloPacketButCannotTransitionToTwoWayState) {
  const NodeAddr src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  NeighborTable neighbor_table;
  neighbor_table[routing_daemon->my_address] = OspfNeighborInfo(routing_daemon->my_address);
  msg_from_other_node->setNeighborTable(neighbor_table);

  routing_daemon->neighbor_table[src] = OspfNeighborInfo(0, OspfState::DOWN);

  ASSERT_ANY_THROW(routing_daemon->handleMessage(msg_from_other_node));
}

TEST_F(RoutingDaemonTest, ospfMasterRespondsToExstartPacketOfSoonToBeSlave) {
  const NodeAddr src = 1;
  auto slave_wants_to_be_master_pk = new OspfDbdPacket;
  slave_wants_to_be_master_pk->setSrcAddr(src);
  slave_wants_to_be_master_pk->setIsMaster(true);
  slave_wants_to_be_master_pk->setState(OspfState::EXSTART);

  routing_daemon->handleMessage(slave_wants_to_be_master_pk);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->isMaster());
  ASSERT_EQ(dbd_pk->getLsdb().size(), 0);
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXSTART);
}

TEST_F(RoutingDaemonTest, ospfMasterRespondsToExstartPacketOfSlave) {
  const NodeAddr src = 1;
  auto slave_wants_to_be_master_pk = new OspfDbdPacket;
  slave_wants_to_be_master_pk->setSrcAddr(src);
  slave_wants_to_be_master_pk->setIsMaster(false);
  slave_wants_to_be_master_pk->setState(OspfState::EXSTART);

  routing_daemon->handleMessage(slave_wants_to_be_master_pk);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->isMaster());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXSTART);
}

TEST_F(RoutingDaemonTest, ospfSlaveRespondsToExstartPacketOfMaster) {
  const NodeAddr src = routing_daemon->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIsMaster(true);
  msg_from_other_node->setState(OspfState::EXSTART);
  routing_daemon->neighbor_table[src].state = OspfState::EXSTART;

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->neighbor_table[src].state, OspfState::EXCHANGE);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(sent_msg);
  ASSERT_TRUE(dbd_pk);
  ASSERT_FALSE(dbd_pk->isMaster());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXCHANGE);
}

TEST_F(RoutingDaemonTest, ospfSlaveDoesNotSendExchangePacketTwice) {
  const NodeAddr src = routing_daemon->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIsMaster(true);
  msg_from_other_node->setState(OspfState::EXSTART);
  msg_from_other_node->setLsdb({SummaryLinkStateAdvertisement()});
  routing_daemon->neighbor_table[src].state = OspfState::EXCHANGE;

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->neighbor_table[src].state, OspfState::EXCHANGE);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 0);
}

TEST_F(RoutingDaemonTest, ospfMasterRespondsToExchangePacketOfSlave) {
  const NodeAddr src = routing_daemon->my_address - 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIsMaster(false);
  msg_from_other_node->setState(OspfState::EXCHANGE);
  msg_from_other_node->setLsdb({SummaryLinkStateAdvertisement()});
  routing_daemon->neighbor_table[src].state = OspfState::EXSTART;

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->neighbor_table[src].state, OspfState::LOADING);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 2);
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(routing_daemon->RouterPort->messages.front());
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->isMaster());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXCHANGE);
  auto lsr_pk = dynamic_cast<OspfLsrPacket*>(routing_daemon->RouterPort->messages.back());
  ASSERT_TRUE(lsr_pk);
}

TEST_F(RoutingDaemonTest, ospfSlaveRespondsToExchangePacketOfMaster) {
  const NodeAddr src = routing_daemon->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIsMaster(true);
  msg_from_other_node->setState(OspfState::EXCHANGE);
  msg_from_other_node->setLsdb({SummaryLinkStateAdvertisement()});

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  auto sent_msg = routing_daemon->RouterPort->messages.front();
  ASSERT_TRUE(dynamic_cast<OspfLsrPacket*>(sent_msg));
}

TEST_F(RoutingDaemonTest, ospfReceiveDbdPacketWithNoLsdb) {
  const NodeAddr src = routing_daemon->my_address + 1;
  auto msg_from_other_node = new OspfDbdPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->setIsMaster(true);
  msg_from_other_node->setState(OspfState::EXCHANGE);
  auto other_node_lsa = LinkStateAdvertisement(src, src, {});
  msg_from_other_node->setLsdb({other_node_lsa});
  MockLinkStateDatabase mock_link_state_database;
  mock_link_state_database.link_state_database[src] = other_node_lsa;
  routing_daemon->link_state_database = mock_link_state_database;

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->neighbor_table[src].state, OspfState::FULL);
}

TEST_F(RoutingDaemonTest, ospfRespondToLsrPacket) {
  auto msg_from_other_node = new OspfLsrPacket;

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 1);
  ASSERT_TRUE(dynamic_cast<OspfLsuPacket*>(routing_daemon->RouterPort->messages.front()));
}

TEST_F(RoutingDaemonTest, ospfRespondToLsuPacket) {
  const NodeAddr other_node = 1;
  const NodeAddr my_address = routing_daemon->my_address;
  auto msg_from_other_node = new OspfLsuPacket;

  MockLinkStateDatabase mock_link_state_database;
  routing_daemon->neighbor_table[other_node] = OspfNeighborInfo(other_node, other_node, 0);
  mock_link_state_database.link_state_database[my_address] = LinkStateAdvertisement(my_address, my_address, routing_daemon->neighbor_table);

  NeighborTable other_node_neighbor_table;
  other_node_neighbor_table[my_address] = OspfNeighborInfo(my_address, my_address, 0);
  mock_link_state_database.link_state_database[other_node] = LinkStateAdvertisement(other_node, other_node, other_node_neighbor_table);

  routing_daemon->link_state_database = mock_link_state_database;

  routing_daemon->handleMessage(msg_from_other_node);
  ASSERT_EQ(routing_daemon->RouterPort->messages.size(), 2);
  ASSERT_TRUE(dynamic_cast<OspfLsAckPacket*>(routing_daemon->RouterPort->messages[0]));
  auto dbd_pk = dynamic_cast<OspfDbdPacket*>(routing_daemon->RouterPort->messages[1]);
  ASSERT_TRUE(dbd_pk);
  ASSERT_TRUE(dbd_pk->isMaster());
  ASSERT_EQ(dbd_pk->getState(), OspfState::EXCHANGE);
}
}  // namespace
