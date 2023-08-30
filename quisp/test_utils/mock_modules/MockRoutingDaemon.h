#pragma once
#include <gmock/gmock.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>

namespace quisp_test {
namespace mock_modules {
namespace routing_daemon {

class MockRoutingDaemon : public quisp::modules::IRoutingDaemon {
 public:
  MOCK_METHOD(int, findQNicAddrByDestAddr, (int destAddr), (override));
  MOCK_METHOD(std::vector<int>, getNeighborAddresses, (), (override));
  MOCK_METHOD(quisp::modules::QuantumInterfaceInfo, getQuantumInterfaceInfo, (int dest_addr), (override));
};

}  // namespace routing_daemon
}  // namespace mock_modules
}  // namespace quisp_test
