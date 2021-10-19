#pragma once
#include <gmock/gmock.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>

namespace quisp_test {
namespace mock_modules {
namespace routing_daemon {

class MockRoutingDaemon : public quisp::modules::IRoutingDaemon {
 public:
  MOCK_METHOD(int, return_QNIC_address_to_destAddr, (int destAddr), (override));
  MOCK_METHOD(int, returnNumEndNodes, (), (override));
};

}  // namespace routing_daemon
}  // namespace mock_modules
}  // namespace quisp_test
