#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h>
#include <runtime/Runtime.h>
#include <runtime/test.h>
#include <runtime/types.h>
#include <test_utils/TestUtils.h>
#include <memory>

#include "Action.h"
#include "modules/QNIC.h"
#include "rules/RuleSetConverter/RuleSetConverter.h"

namespace {
using namespace quisp_test;
using namespace quisp::runtime;
using namespace testing;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_N;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;
using quisp::modules::QNIC_type;
using quisp::modules::qubit_record::QubitRecord;
using quisp::rules::Purification;
using quisp::rules::PurType;
using quisp::rules::rs_converter::RuleSetConverter;
Program terminator{"terminator", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}};
Program always_pass{"cond", {INSTR_RET_ReturnCode_{{ReturnCode::COND_PASSED}}}};
class ActionExecutionTest : public testing::Test {
 protected:
  void SetUp() {
    runtime = new Runtime;
    callback = new MockRuntimeCallback;
    runtime->callback = callback;
    qubit1 = new QubitRecord{QNIC_E, qnic_id, 1};
    qubit2 = new QubitRecord{QNIC_E, qnic_id, 2};
    qubit3 = new QubitRecord{QNIC_E, qnic_id, 3};
    qubit4 = new QubitRecord{QNIC_E, qnic_id, 4};
    qubit5 = new QubitRecord{QNIC_E, qnic_id, 5};
  }
  void TearDown() {
    delete runtime;
    delete callback;
    delete qubit1;
    delete qubit2;
    delete qubit3;
    delete qubit4;
  }
  void setAction(const quisp::rules::Action* actionData, bool debugging = false) {
    Program action = RuleSetConverter::constructAction(actionData);
    action.debugging = debugging;
    Rule rule{"", 0, always_pass, action};
    RuleSet rs{
        "test",
        {rule},
        terminator,
    };
    rs.id = ruleset_id;
    runtime->assignRuleSet(rs);
  }
  unsigned long long ruleset_id = 123;
  Runtime* runtime;
  MockRuntimeCallback* callback;
  IQubitRecord* qubit1;
  IQubitRecord* qubit2;
  IQubitRecord* qubit3;
  IQubitRecord* qubit4;
  IQubitRecord* qubit5;
  int partner_addr = 1;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 3;
};

TEST_F(ActionExecutionTest, PurifyX) {
  PurType pur_type = PurType::SINGLE_X;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendSinglePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);

  runtime->terminated = false;

  EXPECT_CALL(*callback, isQubitLocked(qubit1)).WillRepeatedly(Return(true));
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  EXPECT_CALL(*callback, lockQubit(qubit3, ruleset_id, 0, 1)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendSinglePurificationResult(ruleset_id, _, 1 /* action_index */, QNodeAddr(partner_addr), false, pur_type)).Times(1);
  runtime->exec();
  EXPECT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
}

TEST_F(ActionExecutionTest, PurifyZ) {
  PurType pur_type = PurType::SINGLE_Z;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendSinglePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);

  runtime->terminated = false;

  EXPECT_CALL(*callback, isQubitLocked(qubit1)).WillRepeatedly(Return(true));
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  EXPECT_CALL(*callback, lockQubit(qubit3, ruleset_id, 0, 1)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, purifyZ(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendSinglePurificationResult(ruleset_id, _, 1 /* action_index */, QNodeAddr(partner_addr), false, pur_type)).Times(1);
  runtime->exec();
  EXPECT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
}

TEST_F(ActionExecutionTest, DoublePurifyBothTrue) {
  PurType pur_type = PurType::DOUBLE;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoublePurifyBothFalse) {
  PurType pur_type = PurType::DOUBLE;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoublePurifyXTrue) {
  PurType pur_type = PurType::DOUBLE;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoublePurifyZTrue) {
  PurType pur_type = PurType::DOUBLE;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoublePurifyInvBothTrue) {
  PurType pur_type = PurType::DOUBLE_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoublePurifyInvBothFalse) {
  PurType pur_type = PurType::DOUBLE_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoublePurifyInvXTrue) {
  PurType pur_type = PurType::DOUBLE_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoublePurifyInvZTrue) {
  PurType pur_type = PurType::DOUBLE_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyBothTrue) {
  PurType pur_type = PurType::DSSA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyBothFalse) {
  PurType pur_type = PurType::DSSA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyXTrue) {
  PurType pur_type = PurType::DSSA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyZTrue) {
  PurType pur_type = PurType::DSSA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyInvBothTrue) {
  PurType pur_type = PurType::DSSA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit3, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyInvBothFalse) {
  PurType pur_type = PurType::DSSA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit3, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyInvXTrue) {
  PurType pur_type = PurType::DSSA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit3, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionPurifyInvZTrue) {
  PurType pur_type = PurType::DSSA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit3, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendDoublePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 3);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

// TEST_F(ActionExecutionTest, DoubleSelectionDualActionSecondPurify) {
//   PurType pur_type = PurType::DSDA_SECOND;
//   Purification action{pur_type, partner_addr, qnic_type, qnic_id};
//   setAction(&action);
//   EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

//   EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
//   EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
//   EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
//   EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
//   EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
//   EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
//   EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
//   EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
//   EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
//   EXPECT_CALL(*callback, purifyZ(qubit2, qubit4)).Times(1).WillOnce(Return(false));
//   EXPECT_CALL(*callback, sendTriplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, true, true, pur_type)).Times(1);
//   runtime->assignQubitToRuleSet(partner_addr, qubit1);
//   runtime->assignQubitToRuleSet(partner_addr, qubit2);
//   runtime->assignQubitToRuleSet(partner_addr, qubit3);
//   runtime->assignQubitToRuleSet(partner_addr, qubit4);
//   ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 4);
//   runtime->exec();
//   ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
// }

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyAllTrue) {
  PurType pur_type = PurType::DSDA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, true, true, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyAllFalse) {
  PurType pur_type = PurType::DSDA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, false, false, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyAllXTrueZTrueZFalseXFalse) {
  PurType pur_type = PurType::DSDA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, true, true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyXFalseZFalseZTrueXTrue) {
  PurType pur_type = PurType::DSDA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, false, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyXFalseZTrueZTrueXFalse) {
  PurType pur_type = PurType::DSDA;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyInvAllTrue) {
  PurType pur_type = PurType::DSDA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, true, true, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyInvAllFalse) {
  PurType pur_type = PurType::DSDA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, false, false, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyInvXTrueZTrueZFalseXFalse) {
  PurType pur_type = PurType::DSDA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), false, true, true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyInvXFalseZFalseZTrueXTrue) {
  PurType pur_type = PurType::DSDA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, false, true, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

TEST_F(ActionExecutionTest, DoubleSelectionDualActionPurifyInvXFalseZTrueZTrueXFalse) {
  PurType pur_type = PurType::DSDA_INV;
  Purification action{pur_type, partner_addr, qnic_type, qnic_id};
  setAction(&action);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, lockQubit(qubit1, ruleset_id, 0, 0)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit2)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit3)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit4)).Times(1);
  EXPECT_CALL(*callback, hackBreakEntanglement(qubit5)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit3)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit5)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, purifyZ(qubit2, qubit5)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyZ(qubit1, qubit3)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendQuadruplePurificationResult(ruleset_id, _, 0 /* action_index */, QNodeAddr(partner_addr), true, false, true, false, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->assignQubitToRuleSet(partner_addr, qubit5);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 5);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
}

}  // namespace