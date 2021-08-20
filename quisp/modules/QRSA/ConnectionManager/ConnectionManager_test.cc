#include "ConnectionManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include "modules/QNIC.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace omnetpp;
using namespace quisp_test;
using namespace testing;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(IRoutingDaemon *_routing_daemon, IHardwareMonitor *_hardware_monitor) : routing_daemon(_routing_daemon), hardware_monitor(_hardware_monitor) {}
  Strategy() {}
  ~Strategy() {}
  IRoutingDaemon *getRoutingDaemon() override { return routing_daemon; }
  IHardwareMonitor *getHardwareMonitor() override { return hardware_monitor; }
  IRoutingDaemon *routing_daemon = nullptr;
  IHardwareMonitor *hardware_monitor = nullptr;
};

class ConnectionManagerTestTarget : public quisp::modules::ConnectionManager {
 public:
  using quisp::modules::ConnectionManager::par;
  using quisp::modules::ConnectionManager::respondToRequest;
  ConnectionManagerTestTarget(IRoutingDaemon *routing_daemon, IHardwareMonitor *hardware_monitor) : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    setParBool(this, "simultaneous_es_enabled", false);
    setParBool(this, "entanglement_swapping_with_purification", true);
    setParInt(this, "num_remote_purification", 1);

    this->provider.setStrategy(std::make_unique<Strategy>(routing_daemon, hardware_monitor));
    setComponentType(new module_type::TestModuleType("test cm"));
  }
  ConnectionManagerTestTarget() : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>());
    setComponentType(new module_type::TestModuleType("test cm"));
  }
};

TEST(ConnectionManagerTest, Init) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}

TEST(ConnectionManagerTest, RespondToRequest) {
  auto *sim = prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  ConnectionManagerTestTarget connection_manager(routing_daemon, hardware_monitor);
  connection_manager.par("address") = 5;
  connection_manager.callInitialize();
  auto *req = new ConnectionSetupRequest;
  // [QNode2](qnic_addr:1) -- (2)[QNode3](3) -- (4)[QNode4](5) -- (6)[QNode5(test target)]
  req->setActual_destAddr(5);
  req->setActual_srcAddr(4);
  req->setDestAddr(5);
  req->setSrcAddr(2);
  req->setStack_of_QNICsArraySize(4);
  req->setStack_of_QNICs(0, QNIC_id_pair{.fst = NULL_CONNECTION_SETUP_INFO.qnic, .snd = {.type = QNIC_E, .index = 0, .address = 1}});
  req->setStack_of_QNICs(1, QNIC_id_pair{.fst = {.type = QNIC_E, .index = 0, .address = 2}, .snd = {.type = QNIC_E, .index = 1, .address = 3}});
  req->setStack_of_QNICs(1, QNIC_id_pair{.fst = {.type = QNIC_E, .index = 0, .address = 4}, .snd = {.type = QNIC_E, .index = 1, .address = 5}});

  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(5)).Times(1).WillOnce(Return(-1));
  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(4)).Times(1).WillOnce(Return(5));
  auto src_info = new ConnectionSetupInfo{};
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::unique_ptr<ConnectionSetupInfo>(src_info))));
  connection_manager.respondToRequest(req);
}

TEST(ConnectionManagerTest, GetQNICInterface) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace
