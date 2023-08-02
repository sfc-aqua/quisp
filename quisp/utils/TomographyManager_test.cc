#include "utils/TomographyManager.h"
#include <gtest/gtest.h>
#include "test_utils/TestUtilFunctions.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace quisp_test::utils;
using namespace quisp::utils;

class TomographyManager : public quisp::utils::TomographyManager {
 public:
  using quisp::utils::TomographyManager::addLocalResult;
};

class TomographyManagerTest : public testing::Test {
 protected:
  void SetUp() {
    prepareSimulation();
    tomography_manager = new TomographyManager();
  }
  void TearDown() { delete tomography_manager; }
  TomographyManager *tomography_manager;
};

TEST_F(TomographyManagerTest, addLocalResult) {}
}  // namespace
