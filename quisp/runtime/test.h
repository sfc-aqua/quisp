#pragma once

#include <gmock/gmock.h>
#include <runtime/Runtime.h>
#include "runtime/types.h"

namespace quisp_test {
using quisp::runtime::IQubitRecord;
using quisp::runtime::MeasurementOutcome;
using quisp::runtime::QNodeAddr;

class MockRuntimeCallback : public quisp::runtime::Runtime::ICallBack {
 public:
  MOCK_METHOD(MeasurementOutcome, measureQubitRandomly, (IQubitRecord*), (override));
  MOCK_METHOD(MeasurementOutcome, measureQubitX, (IQubitRecord*), (override));
  MOCK_METHOD(MeasurementOutcome, measureQubitZ, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateX, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateZ, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateCNOT, (IQubitRecord*, IQubitRecord*), (override));
  MOCK_METHOD(bool, purifyX, (IQubitRecord*, IQubitRecord*), (override));
  MOCK_METHOD(bool, purifyZ, (IQubitRecord*, IQubitRecord*), (override));
  MOCK_METHOD(void, sendLinkTomographyResult,
              (const unsigned long ruleset_id, const quisp::runtime::Rule& rule, const int action_index, QNodeAddr partner_addr, int count, MeasurementOutcome outcome,
               bool is_finished),
              (override));
  MOCK_METHOD(void, sendPurificationResult, (const unsigned long ruleset_id, const quisp::runtime::Rule& rule, const int action_index, QNodeAddr partner_addr, bool result),
              (override));
  MOCK_METHOD(void, sendSwappingResults,
              (const unsigned long ruleset_id, const quisp::runtime::Rule& rule, const QNodeAddr left_partner_addr, int left_op, const QNodeAddr right_partner_addr, int right_op),
              (override));
  MOCK_METHOD(void, freeAndResetQubit, (IQubitRecord*), (override));
  MOCK_METHOD(bool, isQubitLocked, (IQubitRecord* const), (override));
  MOCK_METHOD(void, lockQubit, (IQubitRecord* const, unsigned long rs_id, int rule_id, int action_index), (override));
  MOCK_METHOD(void, hackSwappingPartners, (IQubitRecord* const, IQubitRecord* const), (override));
};
}  // namespace quisp_test
