#include "StationaryQubit.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <cmath>
#include <unsupported/Eigen/MatrixFunctions>

using namespace quisp::modules;
using namespace quisp_test;
using namespace Eigen;
namespace {

class StatQubitTarget : public StationaryQubit {
 public:
  using StationaryQubit::getErrorMatrix;
  using StationaryQubit::getQuantumState;
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  StatQubitTarget() : StationaryQubit() { setComponentType(new TestModuleType("test qubit")); }
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

    setParDouble(this, "Hgate_error_rate", 1. / 2000);
    setParDouble(this, "Hgate_X_error_ratio", 0);
    setParDouble(this, "Hgate_Z_error_ratio", 0);
    setParDouble(this, "Hgate_Y_error_ratio", 0);

    setParDouble(this, "Xgate_error_rate", 1. / 2000);
    setParDouble(this, "Xgate_X_error_ratio", 0);
    setParDouble(this, "Xgate_Z_error_ratio", 0);
    setParDouble(this, "Xgate_Y_error_ratio", 0);

    setParDouble(this, "Zgate_error_rate", 1. / 2000);
    setParDouble(this, "Zgate_X_error_ratio", 0);
    setParDouble(this, "Zgate_Z_error_ratio", 0);
    setParDouble(this, "Zgate_Y_error_ratio", 0);

    setParDouble(this, "CNOTgate_error_rate", 1. / 2000);
    setParDouble(this, "CNOTgate_IX_error_ratio", 1);
    setParDouble(this, "CNOTgate_XI_error_ratio", 1);
    setParDouble(this, "CNOTgate_XX_error_ratio", 1);
    setParDouble(this, "CNOTgate_IZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZI_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_IY_error_ratio", 1);
    setParDouble(this, "CNOTgate_YI_error_ratio", 1);
    setParDouble(this, "CNOTgate_YY_error_ratio", 1);

    setParDouble(this, "X_measurement_error_rate", 1. / 2000);
    setParDouble(this, "Y_measurement_error_rate", 1. / 2000);
    setParDouble(this, "Z_measurement_error_rate", 1. / 2000);

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

TEST(StatQubitTest, initialize_memory_transition_matrix) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "memory_X_error_rate", .011);
  setParDouble(qubit, "memory_Y_error_rate", .012);
  setParDouble(qubit, "memory_Z_error_rate", .013);
  setParDouble(qubit, "memory_energy_excitation_rate", .014);
  setParDouble(qubit, "memory_energy_relaxation_rate", .015);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  sim->registerComponent(qubit);
  qubit->callInitialize();

  auto mat = qubit->Memory_Transition_matrix;

  // each element means: "Clean Xerror Zerror Yerror Excited Relaxed Mixed"
  Eigen::RowVectorXd row0(7);
  double sigma = .011 + .013 + .012 + .014 + .015;
  row0 << 1 - sigma, .011, .013, .012, .014, .015, .0;
  ASSERT_EQ(mat.row(0), row0);

  Eigen::RowVectorXd row1(7);
  row1 << .011, 1 - sigma, .012, .013, .014, .015, .0;
  ASSERT_EQ(mat.row(1), row1);

  Eigen::RowVectorXd row2(7);
  row2 << .013, .012, 1 - sigma, .011, .014, .015, .0;
  ASSERT_EQ(mat.row(2), row2);

  Eigen::RowVectorXd row3(7);
  row3 << .012, .013, .011, 1 - sigma, .014, .015, .0;
  ASSERT_EQ(mat.row(3), row3);

  Eigen::RowVectorXd row4(7);
  row4 << 0, 0, 0, 0, 1 - .015, .015, .0;
  ASSERT_EQ(mat.row(4), row4);

  Eigen::RowVectorXd row5(7);
  row5 << 0, 0, 0, 0, .014, 1 - .014, .0;
  ASSERT_EQ(mat.row(5), row5);

  Eigen::RowVectorXd row6(7);
  row6 << 0, 0, 0, 0, .014, .015, 1 - (.014 + .015);
  ASSERT_EQ(mat.row(6), row6);
}

TEST(StatQubitTest, setFree) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  sim->registerComponent(qubit);
  qubit->fillParams();
  qubit->callInitialize();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  qubit->par("GOD_EXerror") = true;
  qubit->par("GOD_REerror") = true;
  qubit->par("GOD_CMerror") = true;

  qubit->setFree(true);
  EXPECT_EQ(qubit->updated_time, simTime());
  auto last_updated_at = qubit->updated_time;
  sim->setSimTime(10);
  EXPECT_EQ(qubit->updated_time, last_updated_at);
  qubit->setFree(true);
  EXPECT_EQ(qubit->updated_time, simTime());

  // check the qubit reset properly
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

TEST(StatQubitTest, setFreeUpdatesTime) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  sim->registerComponent(qubit);
  qubit->fillParams();
  qubit->callInitialize();

  qubit->setFree(true);
  EXPECT_EQ(qubit->updated_time, simTime());

  auto last_updated_at = qubit->updated_time;
  sim->setSimTime(10);
  EXPECT_EQ(qubit->updated_time, last_updated_at);

  qubit->setFree(true);
  EXPECT_EQ(qubit->updated_time, simTime());
}

TEST(StatQubitTest, addXError) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  sim->registerComponent(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror"));
  qubit->addXerror();
  EXPECT_TRUE(qubit->par("GOD_Xerror"));
  qubit->addXerror();
  EXPECT_FALSE(qubit->par("GOD_Xerror"));
}

TEST(StatQubitTest, addZError) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  sim->registerComponent(qubit);
  EXPECT_FALSE(qubit->par("GOD_Zerror"));
  qubit->addZerror();
  EXPECT_TRUE(qubit->par("GOD_Zerror"));
  qubit->addZerror();
  EXPECT_FALSE(qubit->par("GOD_Zerror"));
}

TEST(StatQubitTest, getErrorMatrixTest) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  sim->registerComponent(qubit);
  qubit->callInitialize();
  Matrix2cd err;

  err = qubit->getErrorMatrix(qubit);
  EXPECT_EQ(Matrix2cd::Identity(), err);

  Matrix2cd Z(2, 2);
  Z << 1, 0, 0, -1;
  qubit->addZerror();
  err = qubit->getErrorMatrix(qubit);
  EXPECT_EQ(Z, err);
  qubit->setFree(true);

  Matrix2cd X(2, 2);
  X << 0, 1, 1, 0;
  qubit->addXerror();
  err = qubit->getErrorMatrix(qubit);
  EXPECT_EQ(X, err);
  qubit->setFree(true);

  Matrix2cd Y(2, 2);
  Y << 0, Complex(0, -1), Complex(0, 1), 0;
  qubit->addXerror();
  qubit->addZerror();
  err = qubit->getErrorMatrix(qubit);
  EXPECT_EQ(Y, err);
  qubit->setFree(true);
}

TEST(StatQubitTest, getQuantumState) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  auto *partner_qubit = new StatQubitTarget{};
  sim->registerComponent(qubit);
  sim->registerComponent(partner_qubit);
  qubit->fillParams();
  qubit->callInitialize();
  partner_qubit->fillParams();
  partner_qubit->callInitialize();
  qubit->setEntangledPartnerInfo(partner_qubit);

  quantum_state state;

  state = qubit->getQuantumState();
  Vector4cd state_vector(4);
  state_vector << 1 / sqrt(2), 0, 0, 1 / sqrt(2);
  Matrix4cd dm(4, 4);
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);

  qubit->addXerror();
  state = qubit->getQuantumState();
  state_vector << 0, 1 / sqrt(2), 1 / sqrt(2), 0;
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);
  qubit->addXerror();

  partner_qubit->addXerror();
  state = qubit->getQuantumState();
  state_vector << 0, 1 / sqrt(2), 1 / sqrt(2), 0;
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);
  partner_qubit->addXerror();

  qubit->addZerror();
  state = qubit->getQuantumState();
  state_vector << 1 / sqrt(2), 0, 0, -1 / sqrt(2);
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);
  qubit->addZerror();
}
}  // namespace
