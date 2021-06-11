#include "ConnectionManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include "test_utils/TestUtils.h"

namespace {
using namespace omnetpp;
using namespace quisp_test;
class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() {}
  ~Strategy() {}
};

class ConnectionManagerTestTarget : public quisp::modules::ConnectionManager {
 public:
  using quisp::modules::ConnectionManager::par;
  ConnectionManagerTestTarget() : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>());
  }
};

TEST(ConnectionManagerTest, Init) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}

// TEST(ConnectionManagerTest, Init_table){
//   ConnectionManagerTestTarget c;
//   // c.initialize();
// }

}  // namespace
