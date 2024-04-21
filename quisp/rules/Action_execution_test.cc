#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp/simtime.h>

#include "Action.h"
#include "modules/QNIC.h"
#include "modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h"
#include "rules/RuleSetConverter/RuleSetConverter.h"
#include "runtime/Runtime.h"
#include "runtime/test.h"
#include "runtime/types.h"
#include "test_utils/TestUtils.h"

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
using quisp::rules::EntanglementSwapping;
using quisp::rules::Purification;
using quisp::rules::PurType;
using quisp::rules::Tomography;
using quisp::rules::rs_converter::RuleSetConverter;
Program terminator{"terminator", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}};
Program always_pass{"cond", {INSTR_RET_ReturnCode_{{ReturnCode::COND_PASSED}}}};
class ActionExecutionTest : public testing::Test {
 protected:
  void SetUp() {
    prepareSimulation();
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
  void setAction(const quisp::rules::Action* actionData, int send_tag = -1, int receive_tag = -1, bool debugging = false) {
    Program action = RuleSetConverter::constructAction(actionData);
    action.debugging = debugging;
    Rule rule{"", send_tag, receive_tag, always_pass, action};
    rs.rules.push_back(rule);
    rs.id = ruleset_id;
    // when runtime tries to promote qubit with 1 in rule0, it goes to rule -1 for testing purpose.
    rs.next_rule_table.insert({{QNodeAddr{1}, 0}, -1});
    runtime->assignRuleSet(rs);
  }
  void setGetQubitRule(int addr) {
    Program get_qubit{"", {INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{QubitId(0), QNodeAddr(addr), 1}}}};
    Rule rule{"", -1, -1, always_pass, get_qubit};
    rs.rules.push_back(rule);
  }
  void finalizeRuleset() { runtime->assignRuleSet(rs); }
  unsigned long long ruleset_id = 123;
  Runtime* runtime;
  MockRuntimeCallback* callback;
  RuleSet rs{
      "test",
      {},
      terminator,
  };
  IQubitRecord* qubit1;
  IQubitRecord* qubit2;
  IQubitRecord* qubit3;
  IQubitRecord* qubit4;
  IQubitRecord* qubit5;
  int partner_addr = 1;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 3;
};

TEST_F(ActionExecutionTest, Tomography) {
  Tomography action{500, 0, partner_addr};
  setAction(&action);
  finalizeRuleset();
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit1)).Times(1);
  EXPECT_CALL(*callback, measureQubitRandomly(qubit1)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'X', .outcome_is_plus = true}));
  EXPECT_CALL(*callback, sendLinkTomographyResult(ruleset_id, _, 0, QNodeAddr(partner_addr), 1, MeasurementOutcome{.basis = 'X', .outcome_is_plus = true}, 500, _)).Times(1);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);

  runtime->terminated = false;
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, measureQubitRandomly(qubit2)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'Z', .outcome_is_plus = false}));
  EXPECT_CALL(*callback, sendLinkTomographyResult(ruleset_id, _, 0, QNodeAddr(partner_addr), 2, MeasurementOutcome{.basis = 'Z', .outcome_is_plus = false}, 500, _)).Times(1);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);
}

TEST_F(ActionExecutionTest, Swapping) {
  int left_partner_addr = 2;
  int right_partner_addr = 6;
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EntanglementSwapping action{std::vector{left_partner_addr, right_partner_addr}, 123};
  setAction(&action, 123);
  setGetQubitRule(2);
  setGetQubitRule(6);
  finalizeRuleset();

  EXPECT_CALL(*callback, gateCNOT(qubit1, qubit2)).Times(1);
  EXPECT_CALL(*callback, measureQubitX(qubit1)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'X', .outcome_is_plus = true}));
  EXPECT_CALL(*callback, measureQubitZ(qubit2)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'Z', .outcome_is_plus = true}));
  EXPECT_CALL(*callback, freeAndResetQubit(qubit1)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{left_partner_addr}, QNodeAddr{right_partner_addr}, 123, 1, 0b00)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{right_partner_addr}, QNodeAddr{left_partner_addr}, 123, 1, 0b00)).Times(1);

  runtime->assignQubitToRuleSet(QNodeAddr{left_partner_addr}, qubit1);
  runtime->assignQubitToRuleSet(QNodeAddr{right_partner_addr}, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);

  runtime->terminated = false;
  EXPECT_CALL(*callback, gateCNOT(qubit1, qubit2)).Times(1);
  EXPECT_CALL(*callback, measureQubitX(qubit1)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'X', .outcome_is_plus = false}));
  EXPECT_CALL(*callback, measureQubitZ(qubit2)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'Z', .outcome_is_plus = false}));
  EXPECT_CALL(*callback, freeAndResetQubit(qubit1)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{left_partner_addr}, QNodeAddr{right_partner_addr}, 123, 2, 0b11)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{right_partner_addr}, QNodeAddr{left_partner_addr}, 123, 2, 0b00)).Times(1);

  runtime->assignQubitToRuleSet(QNodeAddr{left_partner_addr}, qubit1);
  runtime->assignQubitToRuleSet(QNodeAddr{right_partner_addr}, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);

  runtime->terminated = false;
  EXPECT_CALL(*callback, gateCNOT(qubit1, qubit2)).Times(1);
  EXPECT_CALL(*callback, measureQubitX(qubit1)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'X', .outcome_is_plus = true}));
  EXPECT_CALL(*callback, measureQubitZ(qubit2)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'Z', .outcome_is_plus = false}));
  EXPECT_CALL(*callback, freeAndResetQubit(qubit1)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{left_partner_addr}, QNodeAddr{right_partner_addr}, 123, 3, 0b10)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{right_partner_addr}, QNodeAddr{left_partner_addr}, 123, 3, 0b00)).Times(1);

  runtime->assignQubitToRuleSet(QNodeAddr{left_partner_addr}, qubit1);
  runtime->assignQubitToRuleSet(QNodeAddr{right_partner_addr}, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);

  runtime->terminated = false;
  EXPECT_CALL(*callback, gateCNOT(qubit1, qubit2)).Times(1);
  EXPECT_CALL(*callback, measureQubitX(qubit1)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'X', .outcome_is_plus = false}));
  EXPECT_CALL(*callback, measureQubitZ(qubit2)).Times(1).WillOnce(Return(MeasurementOutcome{.basis = 'Z', .outcome_is_plus = true}));
  EXPECT_CALL(*callback, freeAndResetQubit(qubit1)).Times(1);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{left_partner_addr}, QNodeAddr{right_partner_addr}, 123, 4, 0b01)).Times(1);
  EXPECT_CALL(*callback, sendSwappingResult(ruleset_id, QNodeAddr{right_partner_addr}, QNodeAddr{left_partner_addr}, 123, 4, 0b00)).Times(1);

  runtime->assignQubitToRuleSet(QNodeAddr{left_partner_addr}, qubit1);
  runtime->assignQubitToRuleSet(QNodeAddr{right_partner_addr}, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);
}

TEST_F(ActionExecutionTest, PurifyX) {
  PurType pur_type = PurType::Single_Selection_X_Purification;
  Purification action{pur_type, partner_addr, 231};
  setAction(&action, 231);
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  EXPECT_CALL(*callback, freeAndResetQubit(qubit2)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit1, qubit2)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*callback, sendPurificationResult(ruleset_id, QNodeAddr{partner_addr}, 231, 1, _, pur_type)).Times(1);
  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  runtime->exec();
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);

  runtime->terminated = false;

  EXPECT_CALL(*callback, isQubitLocked(qubit1)).WillRepeatedly(Return(true));
  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  ASSERT_EQ(getResourceSizeByRuleId(*runtime, 0), 2);
  EXPECT_CALL(*callback, freeAndResetQubit(qubit4)).Times(1);
  EXPECT_CALL(*callback, purifyX(qubit3, qubit4)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*callback, sendPurificationResult(ruleset_id, QNodeAddr{partner_addr}, 231, 2, _, pur_type)).Times(1);
  runtime->exec();
  EXPECT_EQ(getResourceSizeByRuleId(*runtime, 0), 0);
}
}  // namespace
