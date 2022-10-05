#pragma once

#include <gmock/gmock.h>
#include <runtime/Runtime.h>

namespace quisp_test {
using quisp::runtime::MeasurementOutcome;
using quisp::runtime::IQubitRecord;
using quisp::runtime::QNodeAddr;

class MockRuntimeCallback : public quisp::runtime::Runtime::ICallBack {
 public:
  MOCK_METHOD(MeasurementOutcome, measureQubitRandomly, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateX, (IQubitRecord*), (override));
  MOCK_METHOD(void, gateZ, (IQubitRecord*), (override));
  MOCK_METHOD(void, sendLinkTomographyResult, (QNodeAddr partner_addr, int count, MeasurementOutcome outcome, bool is_finished), (override));
  MOCK_METHOD(void, freeAndResetQubit, (IQubitRecord*), (override));
};
}  // namespace quisp_test::runtime
