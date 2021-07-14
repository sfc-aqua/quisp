#include "BellPairStore.h"
#include <gtest/gtest.h>

namespace {

class ResourceStore : public quisp::modules::BellPairStore {
 public:
  using quisp::modules::BellPairStore::_resources;
};

TEST(ResourceStoreTest, init) {
  ResourceStore rs;
  EXPECT_EQ(rs._resources.size(), 0);
}
}  // namespace
