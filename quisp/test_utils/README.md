# Test Utilities

## Usage
use `TestUtils.h` and write `using namespace quisp_test` in your test file.

first you need call `prepareSimulation` in your test.
this remove current simulation if it exists and create new simulation.

when you want to set value to your test component, use `setPar~` functions.
if you finish setting up the test network, call `TestSimulation::run` and then it runs the simulation on the test network. if you want to run a simulation step by step, you can call `TestSimulation::executeNextEvent`.

if you write a test for QRSA modules, you need QNode component because QRSA modules depends on QNode.

## Grab a packet
you can use `TestGate` to grab a packet from a test target module.
`TestGate` has `messages` member and if the gate received `cMessage`, `TestGate` copies the message and store it into `messages` field.
After runnig the simulation, you can get `messages` field of `TestGate`

## Example
```cpp
using namespace quisp_test;

namespace {

// Strategy used in AppTestTarget in order to provide component through ComponentProvider
class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode *_qnode) : parent_qnode(_qnode) {}
  cModule *getQNode() override { return parent_qnode; }

 private:
  TestQNode *parent_qnode;
};

class AppTestTarget : public quisp::modules::Application {
 public:
  using quisp::modules::Application::getParentModule;
  using quisp::modules::Application::initialize;
  using quisp::modules::Application::par;
  explicit AppTestTarget(TestQNode *parent_qnode)
    : Application(),
      toRouterGate(new TestGate(this, "toRouter")) {
    // set Strategy to provider. then this module can use other component provided by Strategy.
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    // simulation needs ComponentType info for this module
    setComponentType(new TestModuleType("test qnode"));
  }

  // utility methods to check a membmer values
  std::vector<int> getOtherEndNodeAdresses() { return this->other_end_node_addresses; }
  int getAddress() { return this->my_address; }

  // a gate used in this module. we don't have ned file in unit test so we need to inject it.
  TestGate *toRouterGate;

  // override `gate` method and
  cGate *gate(const char *gatename, int index = -1) override { return toRouterGate; };
};

TEST(AppTest, Init_OneConnection_Sender) {
  // setup simulation first
  auto *sim = prepareSimulation();

  // create qnode which has address 123
  auto *mock_qnode = new TestQNode{123};

  // create test target module which inherits quisp::module::Application (actual test target)
  auto *app = new AppTestTarget{mock_qnode};

  // set parameters for the module
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 1);
  setParInt(app, "LoneInitiatorAddress", mock_qnode->address);

  // register app to current simulation
  sim->registerComponent(app);

  auto *mock_qnode2 = new TestQNode{456};

  // call Application::initialize through cModule::callInitialize.
  // cModule::callInitialize prepares context or something before calling Application::initialize
  app->callInitialize();

  // check app's address initialized properly
  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  // check app's other addresses
  ASSERT_EQ(app->getOtherEndNodeAdresses().size(), 1);

  // run test simulation. it executes events like transfer packet.
  sim->run();

  // assert app sent one message to "toRouter" gate
  ASSERT_EQ(app->toRouterGate->messages.size(), 1);

  // TestGate contains received messages from app module.
  // so let's take a first message.
  auto *msg = app->toRouterGate->messages.at(0);
  ASSERT_NE(msg, nullptr);

  // msg's type is cMessage* so cast it into ConnectionSetupRequest*
  auto *pkt = dynamic_cast<ConnectionSetupRequest *>(msg);
  // then you can check details of the ConnectionSetupRequest sent from app
  ASSERT_EQ(pkt->getActual_srcAddr(), 123);
  ASSERT_EQ(pkt->getActual_destAddr(), mock_qnode2->address);
  ASSERT_EQ(pkt->getSrcAddr(), 123);
  ASSERT_EQ(pkt->getDestAddr(), 123);
  ASSERT_EQ(pkt->getNumber_of_required_Bellpairs(), 5);
}
}
```
