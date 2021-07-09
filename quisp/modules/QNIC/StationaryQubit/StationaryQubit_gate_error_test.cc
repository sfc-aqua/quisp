#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>
#include "StationaryQubit.h"
#include "omnetpp/simtime.h"

using namespace quisp::modules;
using namespace quisp_test;
namespace {

class StatQubitTarget : public StationaryQubit {
 public:
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  using StationaryQubit::SetSingleQubitGateErrorCeilings;
  using StationaryQubit::SetTwoQubitGateErrorCeilings;
  StatQubitTarget() : StationaryQubit() { setComponentType(new TestModuleType("test qubit")); }
  void reset() {
    setFree(true);
    updated_time = SimTime(0);
    no_density_matrix_nullptr_entangled_partner_ok = true;
  }
  void fillParams() {
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_X_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    // No error= 0.4, X error = 0.6, Z error = 0.8, Y error = 1.0
    setParDouble(this, "Hgate_error_rate", 0.6);
    setParDouble(this, "Hgate_X_error_ratio", 1);
    setParDouble(this, "Hgate_Z_error_ratio", 1);
    setParDouble(this, "Hgate_Y_error_ratio", 1);

    setParDouble(this, "Xgate_error_rate", 0.6);
    setParDouble(this, "Xgate_X_error_ratio", 1);
    setParDouble(this, "Xgate_Z_error_ratio", 1);
    setParDouble(this, "Xgate_Y_error_ratio", 1);

    setParDouble(this, "Zgate_error_rate", 0.6);
    setParDouble(this, "Zgate_X_error_ratio", 1);
    setParDouble(this, "Zgate_Z_error_ratio", 1);
    setParDouble(this, "Zgate_Y_error_ratio", 1);

    setParDouble(this, "Measurement_error_rate", 0.6);
    setParDouble(this, "Measurement_X_error_ratio", 1);
    setParDouble(this, "Measurement_Y_error_ratio", 1);
    setParDouble(this, "Measurement_Z_error_ratio", 1);

    // clean = 0.1,
    // IX = 0.2, XI = 0.3, XX = 0.4,
    // IZ = 0.5, ZI = 0.6, ZZ = 0.7,
    // IY = 0.8, IY = 0.9, YY = 1.0
    setParDouble(this, "CNOTgate_error_rate", 0.9);
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

TEST(StationaryQubitTest, SetSingleQubitGateErrorCeilings) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "Xgate_error_rate", 0.1);
  setParDouble(qubit, "Xgate_X_error_ratio", 1);
  setParDouble(qubit, "Xgate_Z_error_ratio", 2);
  setParDouble(qubit, "Xgate_Y_error_ratio", 3);
  sim->registerComponent(qubit);
  auto error_model = qubit->SetSingleQubitGateErrorCeilings(std::string("Xgate"));
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

TEST(StationaryQubitTest, SetSingleQubitGateErrorCeilings_div_by_zero) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "Xgate_error_rate", 0.1);
  setParDouble(qubit, "Xgate_X_error_ratio", 0);
  setParDouble(qubit, "Xgate_Z_error_ratio", 0);
  setParDouble(qubit, "Xgate_Y_error_ratio", 0);
  sim->registerComponent(qubit);
  auto error_model = qubit->SetSingleQubitGateErrorCeilings(std::string("Xgate"));
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

TEST(StationaryQubitTest, SetTwoQubitGateErrorCeilings) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "CNOTgate_error_rate", 0.1);
  setParDouble(qubit, "CNOTgate_IX_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_XI_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_XX_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_IZ_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_ZI_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_ZZ_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_IY_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_YI_error_ratio", 1);
  setParDouble(qubit, "CNOTgate_YY_error_ratio", 1);
  sim->registerComponent(qubit);
  auto error_model = qubit->SetTwoQubitGateErrorCeilings(std::string("CNOTgate"));
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

TEST(StationaryQubitTest, SetTwoQubitGateErrorCeilings_div_by_zero) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "CNOTgate_error_rate", 0.1);
  setParDouble(qubit, "CNOTgate_IX_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_XI_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_XX_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_IZ_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_ZI_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_ZZ_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_IY_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_YI_error_ratio", 0);
  setParDouble(qubit, "CNOTgate_YY_error_ratio", 0);
  sim->registerComponent(qubit);
  auto error_model = qubit->SetTwoQubitGateErrorCeilings(std::string("CNOTgate"));
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
TEST(StationaryQubitMemoryErrorTest, do_nothing) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->callInitialize();
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  EXPECT_TRUE(qubit->par("GOD_Xerror"));
  EXPECT_TRUE(qubit->par("GOD_Zerror"));
  EXPECT_FALSE(qubit->par("GOD_REerror"));
  EXPECT_FALSE(qubit->par("GOD_EXerror"));
  sim->registerComponent(qubit);

  // if current time and updated_time are same, do nothing
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  sim->setSimTime(SimTime(0, SIMTIME_US));
  qubit->apply_memory_error(qubit);

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->par("GOD_Xerror"));
  EXPECT_TRUE(qubit->par("GOD_Zerror"));
  EXPECT_FALSE(qubit->par("GOD_REerror"));
  EXPECT_FALSE(qubit->par("GOD_EXerror"));
}

TEST(StationaryQubitSingleGateErrorTest, apply_single_qubit_gate_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  qubit->callInitialize();
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));
  // No error
  qubit->reset();
  rng->doubleValue = 0.35;
  qubit->apply_single_qubit_gate_error(qubit->Xgate_error);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // X error
  qubit->reset();
  rng->doubleValue = 0.45;
  qubit->apply_single_qubit_gate_error(qubit->Xgate_error);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Z error
  qubit->reset();
  rng->doubleValue = 0.65;
  qubit->apply_single_qubit_gate_error(qubit->Xgate_error);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Y error
  qubit->reset();
  rng->doubleValue = 0.85;
  qubit->apply_single_qubit_gate_error(qubit->Xgate_error);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

TEST(StationaryQubitSingleGateErrorTest, apply_two_qubit_gate_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit1 = new StatQubitTarget{};
  auto *qubit2 = new StatQubitTarget{};
  qubit1->fillParams();
  qubit2->fillParams();

  qubit1->callInitialize();
  qubit2->callInitialize();
  sim->registerComponent(qubit1);
  sim->registerComponent(qubit2);
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // No error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.05;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_FALSE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // IX error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.15;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_TRUE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // XI error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.25;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_FALSE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // XX error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.35;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_TRUE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // IZ error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.45;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_FALSE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // ZI error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.55;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_FALSE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // ZZ error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.65;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_FALSE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // IY error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.75;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_TRUE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // YI error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.85;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_FALSE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());

  // YY error
  qubit1->reset();
  qubit2->reset();
  rng->doubleValue = 0.95;
  qubit1->apply_two_qubit_gate_error(qubit1->CNOTgate_error, qubit1, qubit2);
  EXPECT_TRUE(qubit1->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit1->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit1->par("GOD_CMerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit2->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit2->par("GOD_CMerror").boolValue());
}
}  // namespace
