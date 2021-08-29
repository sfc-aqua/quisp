#pragma once

#include <gmock/gmock.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>
#include "modules/QNIC.h"
#include "modules/QRSA/RuleEngine/BellPairStore.h"

namespace quisp_test {
namespace mock_modules {
namespace stationary_qubit {

using quisp::modules::IStationaryQubit;
using quisp_test::utils::setParBool;
using quisp_test::utils::setParDouble;
using quisp_test::utils::setParInt;

class MockQubit : public IStationaryQubit {
 public:
  using IStationaryQubit::initialize;
  using IStationaryQubit::par;
  MOCK_METHOD(void, emitPhoton, (int pulse), (override));
  MOCK_METHOD(void, setFree, (bool consumed), (override));
  MOCK_METHOD(quisp::types::MeasureZResult, measure_Z, (), (override));
  MOCK_METHOD(quisp::types::MeasureXResult, measure_X, (), (override));
  MOCK_METHOD(quisp::types::MeasureYResult, measure_Y, (), (override));
  MOCK_METHOD(bool, Xpurify, (IStationaryQubit *), (override));
  MOCK_METHOD(bool, Zpurify, (IStationaryQubit *), (override));
  MOCK_METHOD(bool, checkBusy, (), (override));
  MOCK_METHOD(void, addXerror, (), (override));
  MOCK_METHOD(void, addZerror, (), (override));
  MOCK_METHOD(void, Z_gate, (), (override));
  MOCK_METHOD(void, X_gate, (), (override));
  MOCK_METHOD(void, Hadamard_gate, (), (override));
  MOCK_METHOD(void, CNOT_gate, (IStationaryQubit *), (override));
  MOCK_METHOD(void, Lock, (unsigned long rs_id, unsigned long rule_id, int action_id), (override));
  MOCK_METHOD(void, Unlock, (), (override));
  MOCK_METHOD(bool, isLocked, (), (override));
  MOCK_METHOD(void, Allocate, (), (override));
  MOCK_METHOD(void, Deallocate, (), (override));
  MOCK_METHOD(bool, isAllocated, (), (override));
  MOCK_METHOD(quisp::modules::measurement_outcome, measure_density_independent, (), (override));
  MOCK_METHOD(void, setCompletelyMixedDensityMatrix, (), (override));
  MOCK_METHOD(void, setEntangledPartnerInfo, (IStationaryQubit *), (override));
  MockQubit() : IStationaryQubit() { setComponentType(new module_type::TestModuleType("test qubit")); }
  MockQubit(quisp::modules::QNIC_type _type, quisp::modules::QNicIndex _qnic_index) : MockQubit() {
    qnic_type = _type;
    qnic_index = _qnic_index;
  }
  void reset() {
    setFree(true);
    updated_time = SimTime(0);
    no_density_matrix_nullptr_entangled_partner_ok = true;
  }
  void fillParams() {
    // see networks/omnetpp.ini
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_X_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    setParDouble(this, "Hgate_error_rate", 1 / 2000);
    setParDouble(this, "Hgate_X_error_ratio", 0);
    setParDouble(this, "Hgate_Z_error_ratio", 0);
    setParDouble(this, "Hgate_Y_error_ratio", 0);

    setParDouble(this, "Xgate_error_rate", 1 / 2000);
    setParDouble(this, "Xgate_X_error_ratio", 0);
    setParDouble(this, "Xgate_Z_error_ratio", 0);
    setParDouble(this, "Xgate_Y_error_ratio", 0);

    setParDouble(this, "Zgate_error_rate", 1 / 2000);
    setParDouble(this, "Zgate_X_error_ratio", 0);
    setParDouble(this, "Zgate_Z_error_ratio", 0);
    setParDouble(this, "Zgate_Y_error_ratio", 0);

    setParDouble(this, "Measurement_error_rate", 1 / 2000);
    setParDouble(this, "Measurement_X_error_ratio", 1);
    setParDouble(this, "Measurement_Y_error_ratio", 1);
    setParDouble(this, "Measurement_Z_error_ratio", 1);

    setParDouble(this, "CNOTgate_error_rate", 1 / 2000);
    setParDouble(this, "CNOTgate_IX_error_ratio", 1);
    setParDouble(this, "CNOTgate_XI_error_ratio", 1);
    setParDouble(this, "CNOTgate_XX_error_ratio", 1);
    setParDouble(this, "CNOTgate_IZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZI_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_IY_error_ratio", 1);
    setParDouble(this, "CNOTgate_YI_error_ratio", 1);
    setParDouble(this, "CNOTgate_YY_error_ratio", 1);

    setParInt(this, "stationaryQubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

    setParDouble(this, "photon_emitted_at", 0.0);
    setParDouble(this, "last_updated_at", 0.0);
    setParBool(this, "GOD_Xerror", false);
    setParBool(this, "GOD_Zerror", false);
    setParBool(this, "GOD_CMerror", false);
    setParBool(this, "GOD_EXerror", false);
    setParBool(this, "GOD_REerror", false);
    setParBool(this, "isBusy", false);
    setParInt(this, "GOD_entangled_stationaryQubit_address", 0);
    setParInt(this, "GOD_entangled_node_address", 0);
    setParInt(this, "GOD_entangled_qnic_address", 0);
    setParInt(this, "GOD_entangled_qnic_type", 0);
    setParDouble(this, "fidelity", -1.0);
  }
};
}  // namespace stationary_qubit
}  // namespace mock_modules
}  // namespace quisp_test
