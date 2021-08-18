#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include "ConnectionManager.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace omnetpp;
using namespace quisp_test;
class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() {}
  ~Strategy() {}
};

class ConnectionManager : public quisp::modules::ConnectionManager {
 public:
  using quisp::modules::ConnectionManager::par;
  ConnectionManager() : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>());
  }
};

TEST(ConnectionManagerRuleGenTest, PurificationRule) {
  ConnectionManager c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}

TEST(ConnectionManagerRuleGenTest, SwappingRule) {
  ConnectionManager c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace
