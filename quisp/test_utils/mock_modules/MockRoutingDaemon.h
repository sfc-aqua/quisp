#pragma once
#include <gmock/gmock.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>

namespace quisp_test::mock_modules::routing_daemon {

class MockRoutingDaemon : public quisp::modules::IRoutingDaemon {
 public:
  MOCK_METHOD(int, findQNicAddrByDestAddr, (quisp::types::QNodeAddr destAddr), (override));
  MOCK_METHOD(int, getNumEndNodes, (), (override));
};

}  // namespace quisp_test::mock_modules::routing_daemon
