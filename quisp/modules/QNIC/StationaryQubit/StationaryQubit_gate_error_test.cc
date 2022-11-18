#include <gtest/gtest.h>
#include <modules/common_types.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>
#include "StationaryQubit.h"
#include "omnetpp/simtime.h"

using namespace quisp::modules;
using namespace quisp::modules::common;
using namespace quisp_test;
namespace {
class Strategy : public TestComponentProviderStrategy {
 public:
  Strategy() : backend(new MockQuantumBackend()) {}
  ~Strategy() {}
  IQuantumBackend *getQuantumBackend() override { return backend; }
  MockQuantumBackend *backend;
};

class StatQubitTarget : public StationaryQubit {
 public:
  using StationaryQubit::applySingleQubitGateError;
  using StationaryQubit::applyTwoQubitGateError;
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  using StationaryQubit::setSingleQubitGateErrorModel;
  using StationaryQubit::setTwoQubitGateErrorCeilings;
  StatQubitTarget() : StationaryQubit() {
    setComponentType(new TestModuleType("test qubit"));
    provider.setStrategy(std::make_unique<Strategy>());
  }
  void reset() {
    setFree(true);
    updated_time = SimTime(0);
    no_density_matrix_nullptr_entangled_partner_ok = true;
  }
  void fillParams() {
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_x_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    // No error= 0.4, X error = 0.6, Z error = 0.8, Y error = 1.0
    setParDouble(this, "h_gate_error_rate", 0.6);
    setParDouble(this, "h_gate_x_error_ratio", 1);
    setParDouble(this, "h_gate_z_error_ratio", 1);
    setParDouble(this, "h_gate_y_error_ratio", 1);

    setParDouble(this, "x_gate_error_rate", 0.6);
    setParDouble(this, "x_gate_x_error_ratio", 1);
    setParDouble(this, "x_gate_z_error_ratio", 1);
    setParDouble(this, "x_gate_y_error_ratio", 1);

    setParDouble(this, "z_gate_error_rate", 0.6);
    setParDouble(this, "z_gate_x_error_ratio", 1);
    setParDouble(this, "z_gate_z_error_ratio", 1);
    setParDouble(this, "z_gate_y_error_ratio", 1);

    // clean = 0.1,
    // IX = 0.2, XI = 0.3, XX = 0.4,
    // IZ = 0.5, ZI = 0.6, ZZ = 0.7,
    // IY = 0.8, IY = 0.9, YY = 1.0
    setParDouble(this, "cnot_gate_error_rate", 0.9);
    setParDouble(this, "cnot_gate_ix_error_ratio", 1);
    setParDouble(this, "cnot_gate_xi_error_ratio", 1);
    setParDouble(this, "cnot_gate_xx_error_ratio", 1);
    setParDouble(this, "cnot_gate_iz_error_ratio", 1);
    setParDouble(this, "cnot_gate_zi_error_ratio", 1);
    setParDouble(this, "cnot_gate_zz_error_ratio", 1);
    setParDouble(this, "cnot_gate_iy_error_ratio", 1);
    setParDouble(this, "cnot_gate_yi_error_ratio", 1);
    setParDouble(this, "cnot_gate_yy_error_ratio", 1);

    setParDouble(this, "x_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "y_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "z_measurement_error_rate", 1.0 / 2000);

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
    setParInt(this, "god_entangled_stationaryQubit_address", 0);
    setParInt(this, "god_entangled_node_address", 0);
    setParInt(this, "god_entangled_qnic_address", 0);
    setParInt(this, "god_entangled_qnic_type", 0);
    setParDouble(this, "fidelity", -1.0);
  }
};

TEST(StatQubitGateErrorTest, SetSingleQubitGateErrorCeilings) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "x_gate_error_rate", 0.1);
  setParDouble(qubit, "x_gate_x_error_ratio", 1);
  setParDouble(qubit, "x_gate_z_error_ratio", 2);
  setParDouble(qubit, "x_gate_y_error_ratio", 3);
  sim->registerComponent(qubit);
  qubit->setSingleQubitGateErrorModel(qubit->Xgate_error, std::string("x_gate"));
  auto &error_model = qubit->Xgate_error;
  EXPECT_FALSE(std::isnan(error_model.X_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Z_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.X_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Y_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Y_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Z_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Y_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.X_error_rate, 0.1 * 1 / 6);
  EXPECT_DOUBLE_EQ(error_model.Z_error_rate, 0.2 * 1 / 6);
  EXPECT_DOUBLE_EQ(error_model.Y_error_rate, 0.3 * 1 / 6);
}

TEST(StatQubitGateErrorTest, SetSingleQubitGateErrorCeilings_div_by_zero) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "x_gate_error_rate", 0.1);
  setParDouble(qubit, "x_gate_x_error_ratio", 0);
  setParDouble(qubit, "x_gate_z_error_ratio", 0);
  setParDouble(qubit, "x_gate_y_error_ratio", 0);
  sim->registerComponent(qubit);
  qubit->setSingleQubitGateErrorModel(qubit->Xgate_error, std::string("x_gate"));
  auto &error_model = qubit->Xgate_error;
  EXPECT_FALSE(std::isnan(error_model.X_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Z_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.X_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Y_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Y_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Z_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Y_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.X_error_rate, 0.1 * 1 / 3);
  EXPECT_DOUBLE_EQ(error_model.Z_error_rate, 0.1 * 1 / 3);
  EXPECT_DOUBLE_EQ(error_model.Y_error_rate, 0.1 * 1 / 3);
}

TEST(StatQubitGateErrorTest, SetTwoQubitGateErrorCeilings) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "cnot_gate_error_rate", 0.1);
  setParDouble(qubit, "cnot_gate_ix_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_xi_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_xx_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_iz_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_zi_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_zz_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_iy_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_yi_error_ratio", 1);
  setParDouble(qubit, "cnot_gate_yy_error_ratio", 1);
  sim->registerComponent(qubit);
  qubit->setTwoQubitGateErrorCeilings(qubit->CNOTgate_error, std::string("cnot_gate"));
  auto const &error_model = qubit->CNOTgate_error;
  EXPECT_FALSE(std::isnan(error_model.IX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YY_error_ceil));

  EXPECT_FALSE(std::isinf(error_model.XI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.XX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YY_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.XI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.XX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IY_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YY_error_rate, 0.1 * 1 / 9);
}

TEST(StatQubitGateErrorTest, SetTwoQubitGateErrorCeilings_div_by_zero) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "cnot_gate_error_rate", 0.1);
  setParDouble(qubit, "cnot_gate_ix_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_xi_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_xx_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_iz_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_zi_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_zz_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_iy_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_yi_error_ratio", 0);
  setParDouble(qubit, "cnot_gate_yy_error_ratio", 0);
  sim->registerComponent(qubit);
  qubit->setTwoQubitGateErrorCeilings(qubit->CNOTgate_error, std::string("cnot_gate"));
  auto const &error_model = qubit->CNOTgate_error;
  EXPECT_FALSE(std::isnan(error_model.IX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YY_error_ceil));

  EXPECT_FALSE(std::isinf(error_model.XI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.XX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YY_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.XI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.XX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IY_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YY_error_rate, 0.1 * 1 / 9);
}

TEST(StatQubitGateErrorTest, do_nothing_single_qubit_gate) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "x_gate_error_rate", 0.0);
  sim->registerComponent(qubit);

  qubit->callInitialize();
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  EXPECT_TRUE(qubit->par("god_x_error"));
  EXPECT_TRUE(qubit->par("god_z_error"));
  EXPECT_FALSE(qubit->par("god_relaxation_error"));
  EXPECT_FALSE(qubit->par("god_excitation_error"));

  qubit->applySingleQubitGateError(qubit->Xgate_error);

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->par("god_x_error"));
  EXPECT_TRUE(qubit->par("god_z_error"));
  EXPECT_FALSE(qubit->par("god_relaxation_error"));
  EXPECT_FALSE(qubit->par("god_excitation_error"));
}

TEST(StatQubitGateErrorTest, do_nothing_two_qubit_gate) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  auto *qubit2 = new StatQubitTarget{};
  sim->registerComponent(qubit);
  sim->registerComponent(qubit2);

  qubit->fillParams();
  qubit2->fillParams();
  setParDouble(qubit, "cnot_gate_error_rate", 0.0);
  qubit->callInitialize();
  qubit2->callInitialize();
  qubit->reset();
  qubit2->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  qubit2->par("god_x_error") = true;
  qubit2->par("god_z_error") = true;
  EXPECT_TRUE(qubit->par("god_x_error"));
  EXPECT_TRUE(qubit->par("god_z_error"));
  EXPECT_FALSE(qubit->par("god_relaxation_error"));
  EXPECT_FALSE(qubit->par("god_excitation_error"));
  EXPECT_TRUE(qubit2->par("god_x_error"));
  EXPECT_TRUE(qubit2->par("god_z_error"));
  EXPECT_FALSE(qubit2->par("god_relaxation_error"));
  EXPECT_FALSE(qubit2->par("god_excitation_error"));

  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->par("god_x_error"));
  EXPECT_TRUE(qubit->par("god_z_error"));
  EXPECT_FALSE(qubit->par("god_relaxation_error"));
  EXPECT_FALSE(qubit->par("god_excitation_error"));
  EXPECT_TRUE(qubit2->par("god_x_error"));
  EXPECT_TRUE(qubit2->par("god_z_error"));
  EXPECT_FALSE(qubit2->par("god_relaxation_error"));
  EXPECT_FALSE(qubit2->par("god_excitation_error"));
}

TEST(StatQubitGateErrorTest, apply_single_qubit_gate_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  sim->registerComponent(qubit);

  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));
  // No error
  qubit->reset();
  rng->doubleValue = 0.35;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // X error
  qubit->reset();
  rng->doubleValue = 0.45;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Z error
  qubit->reset();
  rng->doubleValue = 0.65;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Y error
  qubit->reset();
  rng->doubleValue = 0.85;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());
}

TEST(StatQubitGateErrorTest, apply_two_qubit_gate_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit1 = new StatQubitTarget{};
  auto *qubit2 = new StatQubitTarget{};
  qubit1->fillParams();
  qubit2->fillParams();
  sim->registerComponent(qubit1);
  sim->registerComponent(qubit2);
  qubit1->callInitialize();
  qubit2->callInitialize();

  sim->setSimTime(SimTime(1, SIMTIME_US));

  // No error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.05;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_FALSE(qubit1->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // IX error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.15;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_TRUE(qubit1->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // XI error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.25;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_FALSE(qubit1->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // XX error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.35;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_TRUE(qubit1->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // IZ error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.45;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_FALSE(qubit1->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // ZI error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.55;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_FALSE(qubit1->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // ZZ error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.65;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_FALSE(qubit1->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // IY error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.75;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_TRUE(qubit1->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // YI error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.85;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_FALSE(qubit1->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());

  // YY error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.95;
  qubit1->applyTwoQubitGateError(qubit1->CNOTgate_error, qubit2);
  EXPECT_TRUE(qubit1->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit1->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit1->par("god_completely_mixed_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit2->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit2->par("god_completely_mixed_error").boolValue());
}
}  // namespace
