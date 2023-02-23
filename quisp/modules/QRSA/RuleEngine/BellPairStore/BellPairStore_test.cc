#include "BellPairStore.h"
#include <gtest/gtest.h>

#include <modules/Logger/DisabledLogger.h>
#include <modules/QRSA/RuleEngine/QubitRecord/IQubitRecord.h>
#include <modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h>
#include <utility>
#include "test_utils/TestUtils.h"

namespace {
using namespace quisp::modules;
using quisp::modules::qubit_record::IQubitRecord;
using quisp::modules::qubit_record::QubitRecord;
using namespace quisp::modules::Logger;
using namespace quisp_test;

class BellPairStore : public quisp::modules::BellPairStore {
 public:
  using quisp::modules::BellPairStore::_resources;
  using quisp::modules::BellPairStore::BellPairStore;
};

class BellPairStoreTest : public ::testing::Test {
 protected:
  void SetUp() override {
    qubit1 = new QubitRecord(QNIC_E, 3, 6);
    qubit2 = new QubitRecord(QNIC_E, 3, 6);
    qubit3 = new QubitRecord(QNIC_E, 3, 6);
    qubit4 = new QubitRecord(QNIC_E, 3, 6);
    logger = new DisabledLogger{};
    store = BellPairStore(logger);
  }

  void TearDown() override {
    delete qubit1;
    delete qubit2;
    delete qubit3;
    delete qubit4;
  }

  BellPairStore store;
  QubitRecord *qubit1;
  QubitRecord *qubit2;
  QubitRecord *qubit3;
  QubitRecord *qubit4;
  ILogger *logger;
};

TEST_F(BellPairStoreTest, init) { EXPECT_EQ(store._resources.size(), 0); }

TEST_F(BellPairStoreTest, insert) {
  store.insertEntangledQubit(QNodeAddr{7}, qubit1);
  auto key = std::make_pair(QNIC_E, 3);
  // check the PartnerAddrQubitMap is created for the key
  ASSERT_EQ(store._resources.size(), 1);
  ASSERT_NE(store._resources.find(key), store._resources.end()) << "bell pair not found";
  auto it = store._resources[key].find(QNodeAddr{7});
  ASSERT_FALSE(it == store._resources[key].end());
  EXPECT_EQ(it->second, dynamic_cast<IQubitRecord *>(qubit1));
}

TEST_F(BellPairStoreTest, erase) {
  store.insertEntangledQubit(QNodeAddr{7}, qubit1);
  auto key = std::make_pair(QNIC_E, 3);
  store.eraseQubit(qubit1);
  auto it = store._resources[key].find(QNodeAddr{7});
  ASSERT_TRUE(it == store._resources[key].end());

  store.insertEntangledQubit(QNodeAddr{7}, qubit1);
  store.insertEntangledQubit(QNodeAddr{7}, qubit2);
  store.insertEntangledQubit(QNodeAddr{7}, qubit1);
  store.insertEntangledQubit(QNodeAddr{7}, qubit3);
  store.eraseQubit(qubit1);
  it = store._resources[key].find(QNodeAddr{7});
  EXPECT_EQ(store._resources[key].size(), 2);
}

TEST_F(BellPairStoreTest, find) {
  store.insertEntangledQubit(QNodeAddr{7}, qubit1);
  store.insertEntangledQubit(QNodeAddr{8}, qubit2);
  store.insertEntangledQubit(QNodeAddr{9}, qubit3);
  auto *result = store.findQubit(QNIC_E, 3, QNodeAddr{7});
  EXPECT_EQ(result, qubit1);

  result = store.findQubit(QNIC_E, 3, QNodeAddr{700});
  EXPECT_TRUE(result == nullptr);

  result = store.findQubit(QNIC_E, 300, QNodeAddr{700});
  EXPECT_TRUE(result == nullptr);
}

TEST_F(BellPairStoreTest, getRange) {
  store.insertEntangledQubit(QNodeAddr{7}, qubit1);
  store.insertEntangledQubit(QNodeAddr{6}, qubit2);
  store.insertEntangledQubit(QNodeAddr{7}, qubit3);
  auto range = store.getBellPairsRange(QNIC_E, 3, QNodeAddr{7});
  auto it = range.first;
  EXPECT_EQ(it->second, qubit1);
  it++;
  EXPECT_EQ(it->second, qubit3);
  it++;
  EXPECT_EQ(it, range.second);

  auto empty_range = store.getBellPairsRange(QNIC_E, 3, QNodeAddr{700});
  EXPECT_EQ(empty_range.first, empty_range.second);
}

TEST_F(BellPairStoreTest, getRangeWithLoop) {
  // empty resources
  auto range = store.getBellPairsRange(QNIC_E, 3, QNodeAddr{700});
  int count = 0;
  for (auto it = range.first; it != range.second; it++) {
    count++;
  }
  EXPECT_EQ(count, 0);

  // 1 qubit
  store.insertEntangledQubit(QNodeAddr{7}, qubit1);
  range = store.getBellPairsRange(QNIC_E, 3, QNodeAddr{7});
  count = 0;
  for (auto it = range.first; it != range.second; it++) {
    count++;
  }
  EXPECT_EQ(count, 1);

  // 4 qubits and same partner addr.
  store.insertEntangledQubit(QNodeAddr{7}, qubit2);
  store.insertEntangledQubit(QNodeAddr{7}, qubit3);
  store.insertEntangledQubit(QNodeAddr{7}, qubit4);
  range = store.getBellPairsRange(QNIC_E, 3, QNodeAddr{7});
  count = 0;
  for (auto it = range.first; it != range.second; it++) {
    count++;
  }
  EXPECT_EQ(count, 4);
}
}  // namespace
