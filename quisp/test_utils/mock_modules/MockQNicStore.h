#pragma once

#include <gmock/gmock.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/RuleEngine/QNicStore/IQNicStore.h"

namespace quisp_test::mock_modules::qnic_store {

using quisp::modules::qnic_store::IQNicStore;

class MockQNicStore : public IQNicStore {
 public:
  MOCK_METHOD(int, countNumFreeQubits, (QNIC_type type, int qnic_index), (override));
  MOCK_METHOD(int, takeFreeQubitIndex, (QNIC_type type, int qnic_index), (override));
  MOCK_METHOD(void, setQubitBusy, (QNIC_type type, int qnic_index, int qubit_index, bool is_busy), (override));
};
}  // namespace quisp_test::mock_modules::qnic_store
