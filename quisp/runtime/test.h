/**
 * @file test.h
 * @brief test utilities for Runtime. You can include this file for unit testing.
 */
#pragma once

#include <gmock/gmock.h>
#include "Runtime.h"
#include "types.h"

namespace quisp_test {
using quisp::runtime::IQubitRecord;
using quisp::runtime::MeasurementOutcome;
using quisp::runtime::QNodeAddr;

class MockRuntimeCallback : public quisp::runtime::Runtime::ICallBack {
 public:
  MOCK_METHOD(MeasurementOutcome, measureQubitRandomly, (IQubitRecord*), (override));
  MOCK_METHOD(MeasurementOutcome, measureQubitX, (IQubitRecord*), (override));
  MOCK_METHOD(MeasurementOutcome, measureQubitZ, (IQubitRecord*), (override));
  MOCK_METHOD(MeasurementOutcome, measureQubitY, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateX, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateY, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateZ, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateCNOT, (IQubitRecord*, IQubitRecord*), (override));
  MOCK_METHOD(int, purifyX, (IQubitRecord*, IQubitRecord*), (override));
  MOCK_METHOD(int, purifyY, (IQubitRecord*, IQubitRecord*), (override));
  MOCK_METHOD(int, purifyZ, (IQubitRecord*, IQubitRecord*), (override));
  MOCK_METHOD(void, sendLinkTomographyResult,
              (const unsigned long ruleset_id, const quisp::runtime::Rule& rule, const int action_index, QNodeAddr partner_addr, int count, MeasurementOutcome outcome,
               int max_count, SimTime started_time),
              (override));
  MOCK_METHOD(void, sendPurificationResult,
              (const unsigned long ruleset_id, const QNodeAddr partner_addr, const int shared_rule_tag, const int sequence_number, const int measurement_result,
               quisp::runtime::PurType protocol),
              (override));
  MOCK_METHOD(void, sendSwappingResult,
              (const unsigned long ruleset_id, const QNodeAddr partner_addr, const QNodeAddr new_partner_addr, const int shared_rule_tag, const int sequence_number,
               const int frame_correction),
              (override));
  MOCK_METHOD(void, freeAndResetQubit, (IQubitRecord*), (override));
  MOCK_METHOD(bool, isQubitLocked, (IQubitRecord* const), (override));
  MOCK_METHOD(void, lockQubit, (IQubitRecord* const, unsigned long rs_id, int rule_id, int action_index), (override));
  MOCK_METHOD(int, getActionIndex, (IQubitRecord* const), (override));
};

/// @brief count the number of qubit resources assigned to the rule.
static int getResourceSizeByRuleId(quisp::runtime::Runtime& rt, quisp::runtime::RuleId id) {
  int count = 0;
  for (auto& it : rt.qubits) {
    auto& [_, rule_id] = it.first;
    if (rule_id == id) {
      count++;
    }
  }
  return count;
}
}  // namespace quisp_test
