#pragma once
#include <gmock/gmock.h>
#include "modules/QNIC.h"
#include "modules/QRSA/QRSA.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"

namespace quisp_test {
namespace mock_modules {
namespace realtime_controller {

using quisp::modules::QNIC_type;
using quisp::modules::qrsa::IQubitRecord;

class MockRealTimeController : public quisp::modules::IRealTimeController {
 public:
  MOCK_METHOD(void, initialize, (), (override));
  MOCK_METHOD(void, handleMessage, (cMessage * msg), (override));
  MOCK_METHOD(void, EmitPhoton, (int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse), (override));
  MOCK_METHOD(void, ReInitialize_StationaryQubit, (int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed), (override));
  MOCK_METHOD(void, applyXGate, (IQubitRecord* const qubit_record), (override));
  MOCK_METHOD(void, applyZGate, (IQubitRecord* const qubit_record), (override));
  MOCK_METHOD(void, assertNoEntanglement, (IQubitRecord* const qubit_record), (override));
};
}  // namespace realtime_controller
}  // namespace mock_modules
}  // namespace quisp_test
