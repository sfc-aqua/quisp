#include <gtest/gtest.h>

#include <test_utils/TestUtils.h>
#include <test_utils/ChannelType.h>

#include "FSChannel.h"

#include <fstream>

#include "modules/SharedResource/SharedResource.h"

using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using namespace omnetpp;
using OriginalFSChannel = quisp::channels::FSChannel;
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
      quisp_test::utils::setParDouble(this,"delay",0);
      quisp_test::utils::setParDouble(this,"datarate",0);
      quisp_test::utils::setParDouble(this,"ber",0);
      quisp_test::utils::setParDouble(this,"per",0);
      quisp_test::utils::setParBool(this,"disabled",false);

      setComponentType(new TestChannelType("test channel"));
    }
    void addResultRecorders() override {};
};

// class Strategy : public quisp_test::TestComponentProviderStrategy {
//  public:
//   Strategy(MockNode* _qnode) : parent_qnode(_qnode) {}
//   cModule* getNode() override { return parent_qnode; }
//   int getNodeAddr() override { return parent_qnode->address; }
//   SharedResource* getSharedResource() override { return &shared_resource; }
//  private:
//   MockNode* parent_qnode;
//   SharedResource shared_resource;
// };
// class FSChannel : public OriginalFSChannel {
//  public:
//   using OriginalFSChannel::handleMessage;
//   using OriginalFSChannel::initialize;
//   void addResultRecorders() override{};
//   MockNode* parent;
//   cModule* getParentModule() const override { return parent; };
//   explicit FSChannel(MockNode* parent_qnode) : OriginalFSChannel() {
//     this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
//     this->setComponentType(new TestModuleType("test_pointing_system"));
//     parent = parent_qnode;
//     auto* sim = getTestSimulation();
//     sim->registerComponent(this);
//     recPort = new TestGate(this, "rec");
//     ansPort = new TestGate(this, "ans");
//     this->addGate("rec", cGate::INPUT);
//     this->addGate("ans", cGate::OUTPUT);
//   }
//   TestGate* ansPort;
//   TestGate* recPort;
//   std::map<const char*, cGate*> ports{};
//   TestGate* gate(const char* gatename, int index = -1) override {
//     if (strcmp(gatename, "rec") == 0) return recPort;
//     if (strcmp(gatename, "ans") == 0) return ansPort;
//     error("port: %s not found", gatename);
//     return nullptr;
//   }
//   bool parentModuleIsQNode() { return dynamic_cast<MockNode*>(provider.getNode())->is_qnode; }
//   void setIsQnode(bool is_qnode) { dynamic_cast<MockNode*>(provider.getNode())->is_qnode = is_qnode; }
// };

class TestSimpleModule : public cSimpleModule {
 public:
  virtual void send(omnetpp::cMessage* msg, const char* gatename, int gateindex = -1) override {
    take(msg);
    cSimpleModule::send(msg, gatename, gateindex);
  };

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
    ground_node = new MockNode(2,0, false);

    sat_simplemodule = new TestSimpleModule(sat_node);
    ground_simplemodule = new TestSimpleModule(ground_node);

    sat_gate = sat_node->addGate("sat_gate", cGate::INOUT);
    ground_gate = ground_node->addGate("ground_gate", cGate::INOUT);


    downlink_chl = new FSChannel();
    uplink_chl = new FSChannel();

    sim->registerComponent(downlink_chl);
    sim->registerComponent(uplink_chl);


    utils::setParStr(downlink_chl,"distance_CSV","channels/test_dist_csv.csv");
    utils::setParStr(uplink_chl,"distance_CSV","channels/test_dist_csv.csv");

    sat_simplemodule->gate("port$o")->quiet_connectTo(sat_node->gate("sat_gate$o"));
    sat_node->gate("sat_gate$o")->connectTo(ground_node->gate("ground_gate$i"), downlink_chl, true);
    ground_node->gate("ground_gate$i")->connectTo(ground_simplemodule->gate("port$i"));

    ground_simplemodule->gate("port$o")->quiet_connectTo(ground_node->gate("ground_gate$o"));
    ground_node->gate("ground_gate$o")->connectTo(sat_node->gate("sat_gate$i"), uplink_chl, true);
    sat_node->gate("sat_gate$i")->connectTo(sat_simplemodule->gate("port$i"));

    downlink_chl->finalizeParameters();  // THIS METHOD MAY ONLY BE CALLED WHEN THE CHANNEL IS CONNECTED
    downlink_chl->callInitialize();

    uplink_chl->finalizeParameters();
    uplink_chl->callInitialize();
  }
  void TearDown() {
    std::remove("channels/test_dist_csv.csv");
  }

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
  TestSimpleModule* ground_simplemodule;
  MockNode* sat_node;
  MockNode* ground_node;
  FSChannel* downlink_chl;
  FSChannel* uplink_chl;
  cGate* sat_gate;
  cGate* ground_gate;

};

TEST_F(FSChannelTest, messageWhenNonVisible) {
  auto msg = new cMessage;
  sat_simplemodule->send(msg,"sat_gate");
  sim->executeNextEvent();
  ASSERT_EQ(ground_simplemodule->gate("port")->messages.size(), 0);
}


}  // namespace
