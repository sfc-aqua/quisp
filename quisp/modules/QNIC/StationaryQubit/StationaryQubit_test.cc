#include "StationaryQubit.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <modules/common_types.h>
#include <test_utils/TestUtils.h>
#include <cmath>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/interfaces/IConfiguration.h"
#include "backends/interfaces/IQuantumBackend.h"
#include "test_utils/UtilFunctions.h"
#include "test_utils/mock_backends/MockQuantumBackend.h"

using namespace testing;
using namespace quisp::modules;
using namespace quisp::modules::common;
using namespace quisp_test;
using namespace Eigen;

namespace {

class Strategy : public TestComponentProviderStrategy {
 public:
  Strategy(IQuantumBackend *backend) : backend(backend) {}
  ~Strategy() {}
  IQuantumBackend *getQuantumBackend() override { return backend; }
  IQuantumBackend *backend;
};

class StatQubitTarget : public StationaryQubit {
 public:
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  StatQubitTarget(IQuantumBackend *backend) : StationaryQubit() {
    setComponentType(new TestModuleType("test qubit"));
    provider.setStrategy(std::make_unique<Strategy>(backend));
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
    setParDouble(this, "emission_jittering_standard_deviation", 0.5);
    setParBool(this, "overwrite_backend_qubit_config", false);
  }
};

class StatQubitTest : public ::testing::Test {
 protected:
  void SetUp() {
    prepareSimulation();
    backend = new MockQuantumBackend();
    qubit = new StatQubitTarget(backend);
    qubit->fillParams();
  }
  void TearDown() { delete backend; }

  StatQubitTarget *qubit;
  MockQuantumBackend *backend;
};

// TEST(StatQubitTest, initialize_memory_transition_matrix) {
//   auto *sim = prepareSimulation();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   setParDouble(qubit, "memory_X_error_rate", .011);
//   setParDouble(qubit, "memory_Y_error_rate", .012);
//   setParDouble(qubit, "memory_Z_error_rate", .013);
//   setParDouble(qubit, "memory_energy_excitation_rate", .014);
//   setParDouble(qubit, "memory_energy_relaxation_rate", .015);
//   setParDouble(qubit, "memory_completely_mixed_rate", 0);
//   sim->registerComponent(qubit);
//   qubit->callInitialize();

//   auto mat = qubit->Memory_Transition_matrix;

//   // each element means: "Clean Xerror Zerror Yerror Excited Relaxed Mixed"
//   Eigen::RowVectorXd row0(7);
//   double sigma = .011 + .013 + .012 + .014 + .015;
//   row0 << 1 - sigma, .011, .013, .012, .014, .015, .0;
//   ASSERT_EQ(mat.row(0), row0);

//   Eigen::RowVectorXd row1(7);
//   row1 << .011, 1 - sigma, .012, .013, .014, .015, .0;
//   ASSERT_EQ(mat.row(1), row1);

//   Eigen::RowVectorXd row2(7);
//   row2 << .013, .012, 1 - sigma, .011, .014, .015, .0;
//   ASSERT_EQ(mat.row(2), row2);

//   Eigen::RowVectorXd row3(7);
//   row3 << .012, .013, .011, 1 - sigma, .014, .015, .0;
//   ASSERT_EQ(mat.row(3), row3);

//   Eigen::RowVectorXd row4(7);
//   row4 << 0, 0, 0, 0, 1 - .015, .015, .0;
//   ASSERT_EQ(mat.row(4), row4);

//   Eigen::RowVectorXd row5(7);
//   row5 << 0, 0, 0, 0, .014, 1 - .014, .0;
//   ASSERT_EQ(mat.row(5), row5);

//   Eigen::RowVectorXd row6(7);
//   row6 << 0, 0, 0, 0, .014, .015, 1 - (.014 + .015);
//   ASSERT_EQ(mat.row(6), row6);
// }

TEST_F(StatQubitTest, init) {
  auto *backend_qubit = new MockBackendQubit();
  auto *config = new IConfiguration();
  EXPECT_CALL(*backend, getDefaultConfiguration()).WillOnce(Return(ByMove(std::unique_ptr<IConfiguration>(config))));
  EXPECT_CALL(*backend, getQubit(NotNull(), NotNull())).WillOnce(Return(backend_qubit));
  EXPECT_CALL(*backend_qubit, setFree()).WillOnce(Return());
  qubit->callInitialize();
  delete backend_qubit;
}

// TEST(StatQubitTest, addXError) {
//   auto *sim = prepareSimulation();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   sim->registerComponent(qubit);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   qubit->addXerror();
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   qubit->addXerror();
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
// }

// TEST(StatQubitTest, addZError) {
//   auto *sim = prepareSimulation();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   sim->registerComponent(qubit);
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   qubit->addZerror();
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   qubit->addZerror();
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
// }

}  // namespace
