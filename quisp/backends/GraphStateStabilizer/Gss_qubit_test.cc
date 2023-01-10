#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <Eigen/Eigen>
#include <memory>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/GraphStateStabilizer/types.h"
#include "test.h"

namespace {
using namespace quisp_test::backends::graph_state_stabilizer;
using Eigen::Matrix2cd;
using Eigen::Matrix4cd;
using Eigen::Vector4cd;

class GssQubitTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = new GraphStateStabilizerBackend(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<GraphStateStabilizerConfiguration>());
    qubit = new Qubit(new QubitId(1), backend);
    fillParams(qubit);
  }

  void fillParams(Qubit* qubit) {
    // ceiled values should be:
    // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
    double x_error_rate = .1;
    double y_error_rate = .1;
    double z_error_rate = .1;
    double energy_excitation_rate = .1;
    double energy_relaxation_rate = .1;
    double completely_mixed_rate = 0;
    qubit->setMemoryErrorRates(x_error_rate, y_error_rate, z_error_rate, energy_excitation_rate, energy_relaxation_rate, completely_mixed_rate);
  }

  Qubit* qubit;
  GraphStateStabilizerBackend* backend;
  TestRNG* rng;
};

TEST_F(GssQubitTest, setFreeUpdatesTime) {
  qubit->setFree();
  EXPECT_EQ(qubit->updated_time, backend->getSimTime());
  auto last_updated_at = qubit->updated_time;
  backend->setSimTime(10);
  EXPECT_EQ(qubit->updated_time, last_updated_at);
  qubit->setFree();
  EXPECT_EQ(qubit->updated_time, backend->getSimTime());
}

TEST_F(GssQubitTest, initializeMemoryTransitionMatrix) {
  qubit->setMemoryErrorRates(.011, .012, .013, .014, .015, .0);

  auto mat = qubit->memory_transition_matrix;

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
}  // namespace
