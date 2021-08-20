#pragma once

#include <gmock/gmock.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"

namespace quisp_test {
namespace mock_modules {
namespace hardware_monitor {

using quisp::modules::ConnectionSetupInfo;
using quisp::modules::IHardwareMonitor;
using quisp::modules::InterfaceInfo;
using quisp::modules::NeighborTable;
using quisp::modules::QNIC_type;
using quisp_test::utils::setParBool;
using quisp_test::utils::setParDouble;
using quisp_test::utils::setParInt;

class MockHardwareMonitor : public IHardwareMonitor {
 public:
  MOCK_METHOD(int, getQnicNumQubits, (int i, QNIC_type qnic_type), (override));
  MOCK_METHOD(NeighborTable, passNeighborTable, (), (override));
  MOCK_METHOD(std::unique_ptr<InterfaceInfo>, findInterfaceByNeighborAddr, (int neighbor_address), (override));
  MOCK_METHOD(std::unique_ptr<ConnectionSetupInfo>, findConnectionInfoByQnicAddr, (int qnic_address), (override));
};
}  // namespace hardware_monitor
}  // namespace mock_modules
}  // namespace quisp_test
