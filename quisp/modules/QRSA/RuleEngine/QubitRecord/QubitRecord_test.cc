#include "QubitRecord.h"
#include "gtest/gtest.h"
#include "omnetpp/cexception.h"
#include "omnetpp/cmodule.h"
#include "test_utils/TestUtils.h"
#include "utils/ComponentProvider.h"

namespace {
using namespace quisp_test;
using quisp::utils::ComponentProvider;

class QubitRecord : public quisp::modules::qubit_record::QubitRecord {
 public:
  using quisp::modules::qubit_record::QubitRecord::applied_rule_ids;
  using quisp::modules::qubit_record::QubitRecord::is_allocated;
  using quisp::modules::qubit_record::QubitRecord::is_busy;
  using quisp::modules::qubit_record::QubitRecord::qnic_index;
  using quisp::modules::qubit_record::QubitRecord::qnic_type;
  using quisp::modules::qubit_record::QubitRecord::qubit_index;
  QubitRecord(QNIC_type qnic_type, int qnic_index, int qubit_index) : quisp::modules::qubit_record::QubitRecord(qnic_type, qnic_index, qubit_index) {}
};

class QubitRecordTest : public ::testing::Test {
 protected:
  void SetUp() override { record = QubitRecord(qnic_type, qnic_index, qubit_index); }
  int qnic_index = 3;
  QNIC_type qnic_type = QNIC_R;
  int qubit_index = 5;
  QubitRecord record = QubitRecord(QNIC_E, 0, 0);
};

TEST_F(QubitRecordTest, Init) {
  EXPECT_EQ(qubit_index, record.qubit_index);
  EXPECT_EQ(qnic_index, record.qnic_index);
  EXPECT_EQ(qnic_type, record.qnic_type);
}

TEST_F(QubitRecordTest, Getters) {
  EXPECT_EQ(qubit_index, record.getQubitIndex());
  EXPECT_EQ(qnic_index, record.getQNicIndex());
  EXPECT_EQ(qnic_type, record.getQNicType());
}

TEST_F(QubitRecordTest, SetBusy) {
  EXPECT_FALSE(record.is_busy);
  EXPECT_FALSE(record.isBusy());
  record.setBusy(true);
  EXPECT_TRUE(record.is_busy);
  EXPECT_TRUE(record.isBusy());
  EXPECT_THROW(record.setBusy(true), omnetpp::cRuntimeError);
}

TEST_F(QubitRecordTest, SetAllocated) {
  EXPECT_FALSE(record.is_allocated);
  EXPECT_FALSE(record.isAllocated());
  record.setAllocated(true);
  EXPECT_TRUE(record.is_allocated);
  EXPECT_TRUE(record.isAllocated());
  EXPECT_THROW(record.setAllocated(true), omnetpp::cRuntimeError);
}

TEST_F(QubitRecordTest, AppliedRules) {
  EXPECT_EQ(0, record.applied_rule_ids.size());
  EXPECT_FALSE(record.isRuleApplied(1));
  record.markRuleApplied(11);
  EXPECT_EQ(1, record.applied_rule_ids.size());
  EXPECT_FALSE(record.isRuleApplied(1));
  EXPECT_TRUE(record.isRuleApplied(11));
  record.markRuleApplied(12);
  record.markRuleApplied(13);
  record.markRuleApplied(14);
  record.markRuleApplied(15);
  EXPECT_EQ(5, record.applied_rule_ids.size());
  record.clearAppliedRules();
  EXPECT_EQ(0, record.applied_rule_ids.size());
}
}  // namespace
