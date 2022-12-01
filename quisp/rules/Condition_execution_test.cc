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
#include "omnetpp/simtime.h"
#include "rules/Clause.h"
#include "rules/Condition.h"
#include "rules/RuleSetConverter/RuleSetConverter.h"
#include "runtime/Value.h"

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
using quisp::rules::Clause;
using quisp::rules::Condition;
using quisp::rules::EnoughResourceConditionClause;
using quisp::rules::MeasureCountConditionClause;
using quisp::rules::rs_converter::RuleSetConverter;
Program empty{"empty", {}};
class ConditionExecutionTest : public testing::Test {
 protected:
  void SetUp() {
    runtime = new Runtime;
    callback = new MockRuntimeCallback;
    runtime->callback = callback;
    runtime->rule_id = 0;
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

TEST_F(ConditionExecutionTest, MeasurementCount) {
  int num_measure = 100;
  Condition cond{};
  auto clause = new MeasureCountConditionClause(num_measure, partner_addr, qnic_type, qnic_id);
  cond.addClause(std::unique_ptr<Clause>(clause));
  auto program = RuleSetConverter::constructCondition(&cond);

  MemoryKey key{"measure_count1"};
  ASSERT_EQ(runtime->return_code, ReturnCode::NONE);
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_PASSED);
  EXPECT_EQ(runtime->loadVal(key).intValue(), 1);

  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_PASSED);
  EXPECT_EQ(runtime->loadVal(key).intValue(), 2);

  runtime->storeVal(key, MemoryValue{99});
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_PASSED);
  EXPECT_EQ(runtime->loadVal(key).intValue(), 100);

  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_FAILED);
  EXPECT_EQ(runtime->loadVal(key).intValue(), 100);
}

TEST_F(ConditionExecutionTest, MeasurementCountTermination) {
  int num_measure = 100;
  Condition cond{};
  auto clause = new MeasureCountConditionClause(num_measure, partner_addr, qnic_type, qnic_id);
  cond.addClause(std::unique_ptr<Clause>(clause));
  runtime->execProgram(RuleSetConverter::constructCondition(&cond));
  auto program = RuleSetConverter::constructTerminateCondition(&cond);

  MemoryKey key{"measure_count1"};
  ASSERT_EQ(runtime->return_code, ReturnCode::COND_PASSED);
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
  EXPECT_EQ(runtime->loadVal(key).intValue(), 1);

  runtime->storeVal(key, MemoryValue{99});
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
  EXPECT_EQ(runtime->loadVal(key).intValue(), 99);

  runtime->storeVal(key, MemoryValue{100});
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::RS_TERMINATED);
  EXPECT_EQ(runtime->loadVal(key).intValue(), 100);
}

TEST_F(ConditionExecutionTest, EnoughResourceCondition) {
  int num_resource_required = 3;
  double required_fidelity = 0.89;
  Condition cond{};
  auto clause = new EnoughResourceConditionClause(num_resource_required, required_fidelity, partner_addr, qnic_type, qnic_id);
  cond.addClause(std::unique_ptr<Clause>(clause));
  auto program = RuleSetConverter::constructCondition(&cond);
  runtime->ruleset.partner_initial_rule_table.insert({QNodeAddr{partner_addr}, 0});
  EXPECT_CALL(*callback, isQubitLocked(_)).WillRepeatedly(Return(false));

  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_FAILED);

  runtime->assignQubitToRuleSet(partner_addr, qubit1);
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_FAILED);

  runtime->assignQubitToRuleSet(partner_addr, qubit2);
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_FAILED);

  runtime->assignQubitToRuleSet(partner_addr, qubit3);
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_PASSED);

  runtime->assignQubitToRuleSet(partner_addr, qubit4);
  runtime->execProgram(program);
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_PASSED);
}
}  // namespace