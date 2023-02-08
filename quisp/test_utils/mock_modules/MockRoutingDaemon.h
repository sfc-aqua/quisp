#pragma once
#include <gmock/gmock.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>

namespace quisp_test {
namespace mock_modules {
namespace routing_daemon {

class MockRoutingDaemon : public quisp::modules::IRoutingDaemon {
 public:
  MOCK_METHOD(int, findQNicAddrByDestAddr, (int destAddr), (override));
  MOCK_METHOD(int, getNumEndNodes, (), (override));
};

}  // namespace routing_daemon
}  // namespace mock_modules
}  // namespace quisp_test
