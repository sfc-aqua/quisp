#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <Eigen/Eigen>
#include <memory>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/GraphState/types.h"
#include "test.h"

namespace {
using namespace quisp_test::backends::graph_state;
using Eigen::Matrix2cd;
using Eigen::Matrix4cd;
using Eigen::Vector4cd;

class GsSingleQubitTest : public ::testing::Test {
 protected:
  void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<GraphStateConfiguration>());
    qubit = dynamic_cast<Qubit*>(backend->getQubit(1));
    qubit->fillParams();
  }
  Qubit* qubit;
  std::unique_ptr<Backend> backend;
  TestRNG* rng;
};

TEST_F(GsSingleQubitTest, setFreeUpdatesTime) {
  qubit->setFree();
  EXPECT_EQ(qubit->updated_time, backend->getSimTime());
  auto last_updated_at = qubit->updated_time;
  backend->setSimTime(10);
  EXPECT_EQ(qubit->updated_time, last_updated_at);
  qubit->setFree();
  EXPECT_EQ(qubit->updated_time, backend->getSimTime());
}

TEST_F(GsSingleQubitTest, setMemoryErrorTransitionMatrix) {
  qubit->setMemoryErrorRates(.011, .012, .013, .014, .015);

  auto mat = qubit->memory_transition_matrix;

  // each element means: "Clean Xerror Zerror Yerror Excited Relaxed Mixed"
  Eigen::RowVectorXd row0(6);
  double sigma = .011 + .013 + .012 + .014 + .015;
  row0 << 1 - sigma, .011, .013, .012, .014, .015;
  EXPECT_EQ(mat.row(0), row0);

  Eigen::RowVectorXd row1(6);
  row1 << .011, 1 - sigma, .012, .013, .014, .015;
  EXPECT_EQ(mat.row(1), row1);

  Eigen::RowVectorXd row2(6);
  row2 << .013, .012, 1 - sigma, .011, .014, .015;
  EXPECT_EQ(mat.row(2), row2);

  Eigen::RowVectorXd row3(6);
  row3 << .012, .013, .011, 1 - sigma, .014, .015;
  EXPECT_EQ(mat.row(3), row3);

  Eigen::RowVectorXd row4(6);
  row4 << 0, 0, 0, 0, 1 - .015, .015;
  EXPECT_EQ(mat.row(4), row4);

  Eigen::RowVectorXd row5(6);
  row5 << 0, 0, 0, 0, .014, 1 - .014;
  EXPECT_EQ(mat.row(5), row5);
  qubit->setMemoryErrorRates(0, 0, 0, 0, 0);
}

TEST_F(GsSingleQubitTest, dontSetCompletelyMixedDensityMatrix) { EXPECT_EQ(qubit->pi_vector_completely_mixed, false); }

TEST_F(GsSingleQubitTest, setCompletelyMixedDensityMatrix) {
  qubit->setCompletelyMixedDensityMatrix();
  EXPECT_EQ(qubit->pi_vector_completely_mixed, true);
}

TEST_F(GsSingleQubitTest, singleGatemeasureZ) {
  // do nothing
  auto meas = qubit->localMeasureZ();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();

  // hadamard gate
  qubit->gateH();
  rng->double_value = 0;
  meas = qubit->localMeasureZ();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateH();
  rng->double_value = 0.5;
  meas = qubit->localMeasureZ();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // x gate
  qubit->gateX();
  meas = qubit->localMeasureZ();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // z gate
  qubit->gateZ();
  meas = qubit->localMeasureZ();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();

  // s gate
  qubit->gateS();
  meas = qubit->localMeasureZ();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();

  // sdg gate
  qubit->gateSdg();
  meas = qubit->localMeasureZ();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
}

TEST_F(GsSingleQubitTest, singleGatemeasureX) {
  // do nothing
  rng->double_value = 0;
  auto meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  rng->double_value = 0.5;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // hadamard gate
  qubit->gateH();
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();

  // x gate
  qubit->gateX();
  rng->double_value = 0;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateX();
  rng->double_value = 0.5;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // z gate
  qubit->gateZ();
  rng->double_value = 0;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateZ();
  rng->double_value = 0.5;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // s gate
  qubit->gateS();
  rng->double_value = 0;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateS();
  rng->double_value = 0.5;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // sdg gate
  qubit->gateSdg();
  rng->double_value = 0;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateSdg();
  rng->double_value = 0.5;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();
}

TEST_F(GsSingleQubitTest, singleGatemeasureY) {
  // do nothing
  rng->double_value = 0;
  auto meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  rng->double_value = 0.5;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // hadamard gate
  qubit->gateH();
  rng->double_value = 0;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateH();
  rng->double_value = 0.5;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // x gate
  qubit->gateX();
  rng->double_value = 0;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateX();
  rng->double_value = 0.5;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // z gate
  qubit->gateZ();
  rng->double_value = 0;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateZ();
  rng->double_value = 0.5;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // s gate
  qubit->gateS();
  rng->double_value = 0;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateS();
  rng->double_value = 0.5;
  meas = qubit->localMeasureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();

  // sdg gate
  qubit->gateSdg();
  rng->double_value = 0;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  qubit->setFree();
  qubit->gateSdg();
  rng->double_value = 0.5;
  meas = qubit->localMeasureY();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  qubit->setFree();
}
}  // namespace
