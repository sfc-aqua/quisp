#pragma once

#include <gmock/gmock.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>
#include "modules/QNIC.h"
#include "modules/QRSA/RuleEngine/BellPairStore/BellPairStore.h"

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
  MOCK_METHOD(quisp::types::MeasureZResult, correlationMeasureZ, (), (override));
  MOCK_METHOD(quisp::types::MeasureXResult, correlationMeasureX, (), (override));
  MOCK_METHOD(quisp::types::MeasureYResult, correlationMeasureY, (), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, localMeasureX, (), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, localMeasureY, (), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, localMeasureZ, (), (override));
  MOCK_METHOD(bool, Xpurify, (IStationaryQubit *), (override));
  MOCK_METHOD(bool, Zpurify, (IStationaryQubit *), (override));
  MOCK_METHOD(void, addXerror, (), (override));
  MOCK_METHOD(void, addZerror, (), (override));
  MOCK_METHOD(void, Z_gate, (), (override));
  MOCK_METHOD(void, X_gate, (), (override));
  MOCK_METHOD(void, Hadamard_gate, (), (override));
  MOCK_METHOD(void, CNOT_gate, (IStationaryQubit *), (override));
  MOCK_METHOD(void, Lock, (unsigned long rs_id, int rule_id, int action_id), (override));
  MOCK_METHOD(void, Unlock, (), (override));
  MOCK_METHOD(bool, isLocked, (), (override));
  MOCK_METHOD(quisp::modules::measurement_outcome, measure_density_independent, (), (override));
  MOCK_METHOD(void, setCompletelyMixedDensityMatrix, (), (override));
  MOCK_METHOD(void, setEntangledPartnerInfo, (IStationaryQubit *), (override));

  MOCK_METHOD(quisp::types::EigenvalueResult, measureX, (), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, measureY, (), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, measureZ, (), (override));

  MOCK_METHOD(void, cnotGate, (IStationaryQubit * control_qubit), (override));
  MOCK_METHOD(void, hadamardGate, (), (override));
  MOCK_METHOD(void, zGate, (), (override));
  MOCK_METHOD(void, xGate, (), (override));
  MOCK_METHOD(void, sGate, (), (override));
  MOCK_METHOD(void, sdgGate, (), (override));
  MOCK_METHOD(void, excite, (), (override));
  MOCK_METHOD(void, relax, (), (override));

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
    setParDouble(this, "memory_x_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    setParDouble(this, "h_gate_error_rate", 1. / 2000);
    setParDouble(this, "h_gate_x_error_ratio", 0);
    setParDouble(this, "h_gate_z_error_ratio", 0);
    setParDouble(this, "h_gate_y_error_ratio", 0);

    setParDouble(this, "x_gate_error_rate", 1. / 2000);
    setParDouble(this, "x_gate_x_error_ratio", 0);
    setParDouble(this, "x_gate_z_error_ratio", 0);
    setParDouble(this, "x_gate_y_error_ratio", 0);

    setParDouble(this, "z_gate_error_rate", 1. / 2000);
    setParDouble(this, "z_gate_x_error_ratio", 0);
    setParDouble(this, "z_gate_z_error_ratio", 0);
    setParDouble(this, "z_gate_y_error_ratio", 0);

    setParDouble(this, "cnot_gate_error_rate", 1. / 2000);
    setParDouble(this, "cnot_gate_ix_error_ratio", 1);
    setParDouble(this, "cnot_gate_xi_error_ratio", 1);
    setParDouble(this, "cnot_gate_xx_error_ratio", 1);
    setParDouble(this, "cnot_gate_iz_error_ratio", 1);
    setParDouble(this, "cnot_gate_zi_error_ratio", 1);
    setParDouble(this, "cnot_gate_zz_error_ratio", 1);
    setParDouble(this, "cnot_gate_iy_error_ratio", 1);
    setParDouble(this, "cnot_gate_yi_error_ratio", 1);
    setParDouble(this, "cnot_gate_yy_error_ratio", 1);

    setParDouble(this, "x_measurement_error_rate", 1. / 2000);
    setParDouble(this, "y_measurement_error_rate", 1. / 2000);
    setParDouble(this, "z_measurement_error_rate", 1. / 2000);

    setParInt(this, "stationary_qubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

    setParDouble(this, "photon_emitted_at", 0.0);
    setParDouble(this, "last_updated_at", 0.0);
    setParBool(this, "god_x_error", false);
    setParBool(this, "god_z_error", false);
    setParBool(this, "god_completely_mixed_error", false);
    setParBool(this, "god_excitation_error", false);
    setParBool(this, "god_relaxation_error", false);
    setParBool(this, "is_busy", false);
    setParInt(this, "god_entangled_stationary_qubit_address", 0);
    setParInt(this, "god_entangled_node_address", 0);
    setParInt(this, "god_entangled_qnic_address", 0);
    setParInt(this, "god_entangled_qnic_type", 0);
    setParDouble(this, "fidelity", -1.0);
  }
};
}  // namespace stationary_qubit
}  // namespace mock_modules
}  // namespace quisp_test
