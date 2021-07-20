#include "BellPairStore.h"
#include <gtest/gtest.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <utility>
#include "test_utils/TestUtils.h"

namespace {
using namespace quisp::modules;
using namespace quisp_test;
class MockQubit : public StationaryQubit {
 public:
  explicit MockQubit(QNIC_type t, QNicIndex i, QNodeAddr addr) : StationaryQubit() {
    qnic_type = t;
    qnic_index = i;
    node_address = addr;
  }
};

class BellPairStore : public quisp::modules::BellPairStore {
 public:
  using quisp::modules::BellPairStore::_resources;
};

TEST(BellPairStoreTest, init) {
  BellPairStore store;
  EXPECT_EQ(store._resources.size(), 0);
}

TEST(BellPairStoreTest, insert) {
  prepareSimulation();
  auto *qubit1 = new MockQubit(QNIC_E, 3, 6);
  BellPairStore store;
  store.insertEntangledQubit(7, qubit1);
  auto key = std::make_pair(QNIC_E, 3);
  // check the PartnerAddrQubitMap is created for the key
  ASSERT_EQ(store._resources.size(), 1);
  ASSERT_NE(store._resources.find(key), store._resources.end());
  auto it = store._resources[key].find(7);
  ASSERT_FALSE(it == store._resources[key].end());
  EXPECT_EQ(it->second, dynamic_cast<StationaryQubit *>(qubit1));
}

TEST(BellPairStoreTest, erase) {
  prepareSimulation();
  auto *qubit1 = new MockQubit(QNIC_E, 3, 6);
  BellPairStore store;
  store.insertEntangledQubit(7, qubit1);
  auto key = std::make_pair(QNIC_E, 3);
  store.eraseQubit(qubit1);
  auto it = store._resources[key].find(7);
  ASSERT_TRUE(it == store._resources[key].end());

  auto *qubit2 = new MockQubit(QNIC_E, 3, 6);
  auto *qubit3 = new MockQubit(QNIC_E, 3, 6);
  store.insertEntangledQubit(7, qubit1);
  store.insertEntangledQubit(7, qubit2);
  store.insertEntangledQubit(7, qubit1);
  store.insertEntangledQubit(7, qubit3);
  store.eraseQubit(qubit1);
  it = store._resources[key].find(7);
  EXPECT_EQ(store._resources[key].size(), 2);
}

TEST(BellPairStoreTest, find) {
  prepareSimulation();
  auto *qubit1 = new MockQubit(QNIC_E, 3, 6);
  auto *qubit2 = new MockQubit(QNIC_E, 3, 6);
  auto *qubit3 = new MockQubit(QNIC_E, 3, 6);
  BellPairStore store;
  store.insertEntangledQubit(7, qubit1);
  store.insertEntangledQubit(8, qubit2);
  store.insertEntangledQubit(9, qubit3);
  auto key = std::make_pair(QNIC_E, 3);
  auto *result = store.findQubit(QNIC_E, 3, 7);
  EXPECT_EQ(result, qubit1);

  result = store.findQubit(QNIC_E, 3, 700);
  EXPECT_TRUE(result == nullptr);

  result = store.findQubit(QNIC_E, 300, 700);
  EXPECT_TRUE(result == nullptr);
}

TEST(BellPairStoreTest, getRange) {
  prepareSimulation();
  auto *qubit1 = new MockQubit(QNIC_E, 3, 6);
  auto *qubit2 = new MockQubit(QNIC_E, 3, 6);
  auto *qubit3 = new MockQubit(QNIC_E, 3, 6);
  BellPairStore store;
  store.insertEntangledQubit(7, qubit1);
  store.insertEntangledQubit(6, qubit2);
  store.insertEntangledQubit(7, qubit3);
  auto range = store.getBellPairsRange(QNIC_E, 3, 7);
  auto it = range.first;
  EXPECT_EQ(it->second, qubit1);
  it++;
  EXPECT_EQ(it->second, qubit3);
  it++;
  EXPECT_EQ(it, range.second);

  auto empty_range = store.getBellPairsRange(QNIC_E, 3, 700);
  EXPECT_EQ(empty_range.first, empty_range.second);
}
TEST(BellPairStoreTest, getRangeWithLoop) {
  prepareSimulation();
  BellPairStore store;

  // empty resources
  auto range = store.getBellPairsRange(QNIC_E, 3, 700);
  int count = 0;
  for (auto it = range.first; it != range.second; it++) {
    count++;
  }
  EXPECT_EQ(count, 0);

  // 1 qubit
  auto *qubit1 = new MockQubit(QNIC_E, 3, 6);
  store.insertEntangledQubit(7, qubit1);
  range = store.getBellPairsRange(QNIC_E, 3, 7);
  count = 0;
  for (auto it = range.first; it != range.second; it++) {
    count++;
  }
  EXPECT_EQ(count, 1);

  // 4 qubits and same partner addr.
  auto *qubit2 = new MockQubit(QNIC_E, 3, 6);
  auto *qubit3 = new MockQubit(QNIC_E, 3, 6);
  auto *qubit4 = new MockQubit(QNIC_E, 3, 6);
  store.insertEntangledQubit(7, qubit2);
  store.insertEntangledQubit(7, qubit3);
  store.insertEntangledQubit(7, qubit4);
  range = store.getBellPairsRange(QNIC_E, 3, 7);
  count = 0;
  for (auto it = range.first; it != range.second; it++) {
    count++;
  }
  EXPECT_EQ(count, 4);
}
}  // namespace
