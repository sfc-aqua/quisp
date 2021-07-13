#include "ResourceStore.h"
#include <gtest/gtest.h>

namespace {

class ResourceStore : public quisp::modules::ResourceStore {
 public:
  using quisp::modules::ResourceStore::_resources;
};

TEST(ResourceStoreTest, init) {
  ResourceStore rs;
  EXPECT_EQ(rs._resources.size(), 0);
}
}  // namespace
