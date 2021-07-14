#include "EntangledResourceStore.h"
#include <gtest/gtest.h>

namespace {

class ResourceStore : public quisp::modules::EntangledResourceStore {
 public:
  using quisp::modules::EntangledResourceStore::_resources;
};

TEST(ResourceStoreTest, init) {
  ResourceStore rs;
  EXPECT_EQ(rs._resources.size(), 0);
}
}  // namespace
