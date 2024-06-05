#include <gtest/gtest.h>

#include <test_utils/ChannelType.h>
#include <test_utils/TestUtils.h>

#include "FSChannel.h"

#include <fstream>

#include "modules/SharedResource/SharedResource.h"

using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using namespace omnetpp;
using namespace quisp_test::utils;
using OriginalFSChannel = channels::FSChannel;
using quisp_test::channel_type::TestChannelType;

namespace {

class MockNode : public quisp_test::TestQNode {
 public:
  MockNode(int addr, int mass, bool is_initiator, bool i_am_qnode) : TestQNode(addr, mass, is_initiator), is_qnode(i_am_qnode) {}
  MockNode(int addr, int mass, bool is_initiator) : TestQNode(addr, mass, is_initiator), is_qnode(true) {}
  bool is_qnode;
};

class FSChannel : public OriginalFSChannel {
 public:
  FSChannel() : OriginalFSChannel::FSChannel() {
    setParDouble(this, "distance", 0);
    setParDouble(this, "delay", 0);
    setParDouble(this, "datarate", 0);
    setParDouble(this, "ber", 0);
    setParDouble(this, "per", 0);
    setParDouble(this, "orbital_period", 86400);
    setParDouble(this, "speed_of_light_in_FS", 299792458);
    setParBool(this, "disabled", false);
    setParBool(this, "CSV_varies_delay", true);

    setComponentType(new TestChannelType("test channel"));
  }
  cChannel::Result public_processMessage(cMessage* msg) { return processMessage(msg, SendOptions(), simTime()); };
  void addResultRecorders() override{};
};

class TestSimpleModule : public cSimpleModule {
 public:
  virtual void scheduleAfter(simtime_t delay, cMessage* msg) override {
    take(msg);
    cSimpleModule::scheduleAfter(delay, msg);
  }
  virtual void addResultRecorders() override{};

  virtual void handleMessage(cMessage* msg) override{};
  MockNode* parent;
  cModule* getParentModule() const override { return parent; };

  explicit TestSimpleModule(MockNode* parent_qnode) : cSimpleModule() {
    this->setComponentType(new TestModuleType("test_simple_module"));
    parent = parent_qnode;
    auto* sim = getTestSimulation();
    sim->registerComponent(this);
    port$o = new TestGate(this, "port$o");
    port$i = new TestGate(this, "port$i");
    this->addGate("port", cGate::INOUT);
  }

  TestGate* port$i;
  TestGate* port$o;

  std::map<const char*, cGate*> ports{};
  TestGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "port$i") == 0) return port$i;
    if (strcmp(gatename, "port$o") == 0) return port$o;
    error("port: %s not found", gatename);
    return nullptr;
  }
};

class FSChannelTest : public ::testing::Test {
 protected:
  void SetUp() {
    generateTestCSV("channels/test_dist_csv.csv");

    sim = prepareSimulation();

    sat_node = new MockNode(1, 0, false);
    ground_node = new MockNode(2, 0, false);

    sat_simplemodule = new TestSimpleModule(sat_node);

    sat_gate = sat_node->addGate("sat_gate", cGate::INOUT);
    ground_gate = ground_node->addGate("ground_gate", cGate::INOUT);

    downlink_chl = new FSChannel();

    sim->registerComponent(downlink_chl);

    utils::setParStr(downlink_chl, "distance_CSV", "channels/test_dist_csv.csv");

    sat_node->gate("sat_gate$o")->connectTo(ground_node->gate("ground_gate$i"), downlink_chl, true);

    sat_simplemodule->callInitialize();

    downlink_chl->finalizeParameters();  // THIS METHOD MAY ONLY BE CALLED WHEN THE CHANNEL IS CONNECTED
    downlink_chl->callInitialize();
  }
  void TearDown() { std::remove("channels/test_dist_csv.csv"); }

  /**
   * This function mimics the behavior of Omnet++ internals
   * that sets up the message arrival to PointingSystem module.
   * Call this function before PointingSystem->handleMessages
   * when you want to retrieve the info of the arrival gate.
   */

  void generateTestCSV(const char* name) {
    std::ofstream csv_to_generate;
    csv_to_generate.open(name);
    csv_to_generate << "200,100000\n";
    csv_to_generate << "300,300000\n";
    csv_to_generate << "400,200000\n";
    csv_to_generate.close();
  }

  TestSimulation* sim;
  TestSimpleModule* sat_simplemodule;
  MockNode* sat_node;
  MockNode* ground_node;
  FSChannel* downlink_chl;
  cGate* sat_gate;
  cGate* ground_gate;
};

TEST_F(FSChannelTest, messageWhenNonVisible) {
  cMessage* msg = new cMessage();
  cChannel::Result res = downlink_chl->public_processMessage(msg);
  sim->run();
  ASSERT_EQ(res.discard, true);
}

TEST_F(FSChannelTest, messageWhenVisible) {
  auto timeout = new cMessage;
  sat_simplemodule->scheduleAfter(200, timeout);
  sim->executeNextEvent();
  auto msg = new cMessage;
  cChannel::Result res = downlink_chl->public_processMessage(msg);
  sim->run();
  ASSERT_EQ(res.discard, false);
  simtime_t delay = downlink_chl->par("distance").doubleValue() / downlink_chl->par("speed_of_light_in_FS").doubleValue();
  ASSERT_EQ(res.delay.raw(), delay.raw());
}

TEST_F(FSChannelTest, messageAfterVisible) {
  auto timeout = new cMessage;
  sat_simplemodule->scheduleAfter(600, timeout);
  sim->executeNextEvent();
  auto msg = new cMessage;
  cChannel::Result res = downlink_chl->public_processMessage(msg);
  sim->run();
  ASSERT_EQ(res.discard, true);
}

TEST_F(FSChannelTest, messageFollowingDayVisible) {
  auto timeout = new cMessage;
  sat_simplemodule->scheduleAfter(86700, timeout);
  sim->executeNextEvent();
  auto msg = new cMessage;
  cChannel::Result res = downlink_chl->public_processMessage(msg);
  sim->run();
  ASSERT_EQ(res.discard, false);
  simtime_t delay = downlink_chl->par("distance").doubleValue() / downlink_chl->par("speed_of_light_in_FS").doubleValue();
  ASSERT_EQ(res.delay.raw(), delay.raw());  // Comparing the raw int64_t values doesn't lose precision, unlike .dbl().
}
TEST_F(FSChannelTest, messageFollowingDayNonVisible) {
  auto timeout = new cMessage;
  sat_simplemodule->scheduleAfter(86801, timeout);
  sim->executeNextEvent();
  auto msg = new cMessage;
  cChannel::Result res = downlink_chl->public_processMessage(msg);
  sim->run();
  ASSERT_EQ(res.discard, true);
}
}  // namespace
