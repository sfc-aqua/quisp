#pragma once

#include <gmock/gmock.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>
#include "backends/Backends.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/RuleEngine/BellPairStore/BellPairStore.h"

namespace quisp_test::mock_modules::stationary_qubit {

using quisp::backends::IQubit;
using quisp::backends::IQubitId;
using quisp::modules::IStationaryQubit;
using quisp_test::utils::setParBool;
using quisp_test::utils::setParDouble;
using quisp_test::utils::setParInt;

class MockQubit : public IStationaryQubit {
 public:
  using IStationaryQubit::initialize;
  using IStationaryQubit::par;
  IStationaryQubit *entangled_partner;

  MOCK_METHOD(void, emitPhoton, (int pulse), (override));
  MOCK_METHOD(void, setFree, (bool consumed), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, measureX, (), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, measureY, (), (override));
  MOCK_METHOD(quisp::types::EigenvalueResult, measureZ, (), (override));
  MOCK_METHOD(void, gateZ, (), (override));
  MOCK_METHOD(void, gateX, (), (override));
  MOCK_METHOD(void, gateHadamard, (), (override));
  MOCK_METHOD(void, gateCNOT, (IStationaryQubit *), (override));
  MOCK_METHOD(void, Lock, (unsigned long rs_id, int rule_id, int action_id), (override));
  MOCK_METHOD(void, Unlock, (), (override));
  MOCK_METHOD(bool, isLocked, (), (override));
  MOCK_METHOD(quisp::types::MeasurementOutcome, measureRandomPauliBasis, (), (override));
  MOCK_METHOD(IQubit *const, getBackendQubitRef, (), (const, override));

  MockQubit() : IStationaryQubit() { setComponentType(new module_type::TestModuleType("test qubit")); }
  MockQubit(quisp::modules::QNIC_type _type, quisp::modules::QNicIndex _qnic_index) : MockQubit() {
    qnic_type = _type;
    qnic_index = _qnic_index;
  }
  void reset() { setFree(true); }
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
    setParDouble(this, "emission_jittering_standard_deviation", 0.5);

    setParBool(this, "is_busy", false);
    setParDouble(this, "fidelity", -1.0);
  }
};
}  // namespace quisp_test::mock_modules::stationary_qubit
