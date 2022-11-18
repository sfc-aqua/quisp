#include "Runtime.h"
#include <gtest/gtest.h>
#include <modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h>
#include "modules/QRSA/QRSA.h"
#include "rules/Active/ActiveRuleSet.h"
#include "runtime/InstructionVisitor.h"
#include "runtime/types.h"
#include "test.h"

using namespace testing;
using namespace quisp::runtime;
using namespace quisp::rules;
using namespace quisp::rules::active;
using namespace quisp_test;
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
  qrsa::IQubitRecord* qubit;
  qrsa::IQubitRecord* qubit2;
  qrsa::IQubitRecord* qubit3;
  qrsa::IQubitRecord* qubit4;
  qrsa::IQubitRecord* qubit5;
};

TEST_F(RuntimeTest, initialize) { ASSERT_NE(runtime, nullptr); }

TEST_F(RuntimeTest, getMultipleQubits) {
  QubitId q0{0};
  QubitId q1{1};
  QubitId q2{2};
  QNodeAddr partner_addr{2};
  runtime->debugging = false;
  Program program{"get multiple qubits",
                  {
                      // clang-format off
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, partner_addr, 1}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q2, partner_addr, 2}},
INSTR_ERROR_String_{"no qubit"},
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
}

TEST_F(RuntimeTest, CannotGetLockedQubits) {

}

TEST_F(RuntimeTest, ExecRuleSetWithCondPassed) {

}

TEST_F(RuntimeTest, ExecRuleSetWithCondFailed) {

}

TEST_F(RuntimeTest, ExecRuleSetWithTerminating) {

}

TEST_F(RuntimeTest, PromoteQubit) {

}

TEST_F(RuntimeTest, AssignQubit) {

}

}  // namespace
