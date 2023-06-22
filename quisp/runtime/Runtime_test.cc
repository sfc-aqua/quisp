#include "Runtime.h"

#include <gtest/gtest.h>

#include "modules/QRSA/QRSA.h"
#include "modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h"
#include "runtime/InstructionVisitor.h"
#include "runtime/types.h"
#include "test.h"

using namespace testing;
using namespace quisp::runtime;
using namespace quisp_test;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_type;
using quisp::modules::qubit_record::QubitRecord;
namespace {

class RuntimeTest : public testing::Test {
 protected:
  void SetUp() {
    runtime = new Runtime();
    callback = new MockRuntimeCallback();
    runtime->callback = callback;
    runtime->rule_id = 0;
    runtime->cleanup();
    qubit = new QubitRecord{QNIC_E, 2, 3};
    qubit2 = new QubitRecord{QNIC_E, 2, 4};
    qubit3 = new QubitRecord{QNIC_E, 2, 5};
    qubit4 = new QubitRecord{QNIC_E, 2, 6};
    qubit5 = new QubitRecord{QNIC_E, 2, 7};
  }

  void TearDown() {
    delete runtime;
    delete callback;
  }

 public:
  Runtime* runtime;
  MockRuntimeCallback* callback;
  IQubitRecord* qubit;
  IQubitRecord* qubit2;
  IQubitRecord* qubit3;
  IQubitRecord* qubit4;
  IQubitRecord* qubit5;
  QubitId q0{0};
  QubitId q1{1};
  QubitId q2{2};
  QNodeAddr partner_addr{1};
  QNodeAddr partner_addr2{2};
};

TEST_F(RuntimeTest, initialize) { ASSERT_NE(runtime, nullptr); }

TEST_F(RuntimeTest, getMultipleQubits) {
  runtime->debugging = false;
  Program program{"get multiple qubits",
                  {
                      // clang-format off
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, partner_addr, 1}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q2, partner_addr, 2}},
                      // clang-format on
                  }};
  runtime->assignQubitToRule(partner_addr, runtime->rule_id, qubit);
  runtime->assignQubitToRule(partner_addr, runtime->rule_id + 1, qubit2);
  runtime->assignQubitToRule(partner_addr, runtime->rule_id, qubit3);
  runtime->assignQubitToRule(partner_addr, runtime->rule_id + 1, qubit4);
  runtime->assignQubitToRule(partner_addr, runtime->rule_id + 1, qubit5);

  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));
  runtime->execProgram(program);

  EXPECT_EQ(runtime->getQubitByQubitId(q0), qubit);
  EXPECT_EQ(runtime->getQubitByQubitId(q1), qubit3);
  EXPECT_EQ(runtime->getQubitByQubitId(q2), nullptr);
  EXPECT_FALSE(runtime->qubit_found);
}

TEST_F(RuntimeTest, CannotGetLockedQubits) {
  Program program{"",
                  {
                      // clang-format off
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}},
                      // clang-format on
                  }};
  runtime->assignQubitToRule(partner_addr, runtime->rule_id, qubit);
  EXPECT_CALL(*callback, isQubitLocked(qubit)).WillRepeatedly(Return(true));
  runtime->execProgram(program);

  EXPECT_EQ(runtime->getQubitByQubitId(q0), nullptr);
  EXPECT_FALSE(runtime->qubit_found);
}

TEST_F(RuntimeTest, ExecRuleSetWithCondPassed) {
  MemoryKey result_key{"result"};
  RuleSet rs{"",
             {Rule{
                 "",
                 -1,
                 -1,
                 Program{"cond passed",
                         {// initialize the memory with 0
                          INSTR_STORE_MemoryKey_int_{{result_key, 0}},
                          // return COND_PASSED
                          INSTR_RET_ReturnCode_{{ReturnCode::COND_PASSED}}}},
                 Program{"action", {INSTR_STORE_MemoryKey_int_{{result_key, 1}}}},
             }},
             // Terminate the RuleSet
             Program{"", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}}};

  runtime->assignRuleSet(rs);
  runtime->exec();
  EXPECT_EQ(runtime->loadVal(result_key).intValue(), 1);
}

TEST_F(RuntimeTest, ExecRuleSetWithCondFailed) {
  MemoryKey result_key{"result"};
  RuleSet rs{"",
             {Rule{
                 "",
                 -1,
                 -1,
                 Program{"cond failed",
                         {// initialize the memory with 0
                          INSTR_STORE_MemoryKey_int_{{result_key, 0}},
                          // return COND_PASSED
                          INSTR_RET_ReturnCode_{{ReturnCode::COND_FAILED}}}},
                 Program{"action", {INSTR_STORE_MemoryKey_int_{{result_key, 1}}}},
             }},
             // Terminate the RuleSet
             Program{"", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}}};
  runtime->assignRuleSet(rs);
  runtime->exec();
  EXPECT_EQ(runtime->loadVal(result_key).intValue(), 0);
}

TEST_F(RuntimeTest, PromoteQubit) {
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));
  RuleSet rs{"",
             {
                 Rule{
                     "requires qubit with partner_addr",
                     -1,
                     -1,
                     Program{"",
                             {

                                 INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}},
                                 // return COND_PASSED
                                 INSTR_RET_ReturnCode_{{ReturnCode::COND_FAILED}}}},
                     Program{"action", {}},
                 },
                 Rule{"requires qubit with partner_addr", -1, -1,
                      Program{"",
                              {
                                  // clang-format off
                              INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}},
                              INSTR_BRANCH_IF_QUBIT_FOUND_Label_{{Label{"qubit found"}}},
                              INSTR_RET_ReturnCode_{{ReturnCode::ERROR}},
                              INSTR_RET_ReturnCode_{{ReturnCode::COND_FAILED}, Label{"qubit found"}}
                                  // clang-format on
                              }},
                      Program{"action", {}}},
             },
             // Terminate the RuleSet
             Program{"", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}}};

  runtime->assignRuleSet(rs);
  runtime->rule_id = 0;
  EXPECT_EQ(runtime->qubits.size(), 0);
  runtime->assignQubitToRule(partner_addr, runtime->rule_id, qubit);

  auto* first_rule_qubit = runtime->getQubitByPartnerAddr(partner_addr, 0);
  EXPECT_EQ(first_rule_qubit, qubit);
  auto it = runtime->qubits.begin();
  runtime->promoteQubit(qubit);
  runtime->rule_id = 1;
  auto* second_rule_qubit = runtime->getQubitByPartnerAddr(partner_addr, 0);
  EXPECT_EQ(second_rule_qubit, qubit);
}

TEST_F(RuntimeTest, AssignQubit) {
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));
  RuleSet rs{
      "",
      {
          Rule{
              "requires qubit with partner_addr",
              -1,
              -1,
              Program{"",
                      {

                          INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}},
                          // return COND_PASSED
                          INSTR_RET_ReturnCode_{{ReturnCode::COND_FAILED}}}},
              Program{"action", {}},
          },
          Rule{"requires qubit with partner_addr", -1, -1,
               Program{"",
                       {
                           // clang-format off
                              INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr2, 0}},
                           // clang-format on
                       }},
               Program{"action", {}}},
      },
  };

  runtime->assignRuleSet(rs);
  runtime->rule_id = 0;
  EXPECT_EQ(runtime->qubits.size(), 0);
  runtime->assignQubitToRuleSet(partner_addr, qubit);
  runtime->assignQubitToRuleSet(partner_addr2, qubit2);
  runtime->assignQubitToRuleSet(partner_addr2, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);

  EXPECT_EQ(runtime->getQubitByPartnerAddr(partner_addr, 0), qubit);
  EXPECT_EQ(runtime->getQubitByPartnerAddr(partner_addr, 1), qubit4);

  runtime->rule_id = 1;
  EXPECT_EQ(runtime->getQubitByPartnerAddr(partner_addr2, 0), qubit2);
  EXPECT_EQ(runtime->getQubitByPartnerAddr(partner_addr2, 1), qubit3);
}

TEST_F(RuntimeTest, freeQubitFromRuleSet) {
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));
  RuleSet rs{
      "",
      {
          Rule{
              "requires qubit with partner_addr",
              -1,
              -1,
              Program{"",
                      {

                          INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}},
                          // return COND_PASSED
                          INSTR_RET_ReturnCode_{{ReturnCode::COND_FAILED}}}},
              Program{"action", {}},
          },
          Rule{"requires qubit with partner_addr", -1, -1,
               Program{"",
                       {
                           // clang-format off
                              INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr2, 0}},
                           // clang-format on
                       }},
               Program{"action", {}}},
      },
  };

  runtime->assignRuleSet(rs);
  runtime->rule_id = 0;
  EXPECT_EQ(runtime->qubits.size(), 0);
  runtime->assignQubitToRuleSet(partner_addr, qubit);
  runtime->assignQubitToRuleSet(partner_addr2, qubit2);

  runtime->assignQubitToRuleSet(partner_addr2, qubit3);
  runtime->assignQubitToRuleSet(partner_addr, qubit4);

  runtime->freeQubitFromRuleSet(partner_addr, qubit4);
  EXPECT_EQ(runtime->getQubitByPartnerAddr(partner_addr, 0), qubit);

  runtime->rule_id = 1;
  runtime->freeQubitFromRuleSet(partner_addr2, qubit2);
  EXPECT_EQ(runtime->getQubitByPartnerAddr(partner_addr2, 0), qubit3);
}

}  // namespace
