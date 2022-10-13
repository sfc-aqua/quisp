#pragma once

#include <gmock/gmock.h>
#include <runtime/Runtime.h>

namespace quisp_test {
using quisp::runtime::IQubitRecord;
using quisp::runtime::MeasurementOutcome;
using quisp::runtime::QNodeAddr;

class MockRuntimeCallback : public quisp::runtime::Runtime::ICallBack {
 public:
  MOCK_METHOD(MeasurementOutcome, measureQubitRandomly, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateX, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateZ, (IQubitRecord*), (override));
  MOCK_METHOD(void, sendLinkTomographyResult,
              (const unsigned long ruleset_id, const quisp::runtime::Rule& rule, const int action_index, QNodeAddr partner_addr, int count, MeasurementOutcome outcome,
               bool is_finished),
              (override));
  MOCK_METHOD(void, sendPurificationResult, (const unsigned long ruleset_id, const quisp::runtime::Rule& rule, const int action_index, QNodeAddr partner_addr, bool result),
              (override));
  MOCK_METHOD(void, freeAndResetQubit, (IQubitRecord*), (override));
  MOCK_METHOD(bool, isQubitLocked, (IQubitRecord* const), (override));
};
}  // namespace quisp_test
