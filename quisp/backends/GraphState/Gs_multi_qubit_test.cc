#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <Eigen/Eigen>
#include <memory>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>
#include "backends/GraphState/types.h"
#include "test.h"

namespace {
using namespace quisp_test::backends::graph_state;
class GsMultiQubitTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<GraphStateConfiguration>());
    for (int i = 0; i < 16; i++) {
      quantum_register.push_back(dynamic_cast<Qubit*>(backend->getQubit(i)));
      quantum_register.at(i)->fillParams();
    }
  }
  void resetRegister() {
    for (int i = 0; i < 16; i++) {
      quantum_register.at(i)->reset();
    }
  }
  std::vector<Qubit*> quantum_register;
  std::unique_ptr<Backend> backend;
  TestRNG* rng;
};
TEST_F(GsMultiQubitTest, gateCNOTZmeasurement) {
  // state : |0(target)0(control)> --> |0(target)0(control)>
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  auto meas0 = quantum_register.at(0)->localMeasureZ();
  auto meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
  rng->double_value = 0.5;
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  // state : |0(target)1(control)> --> |1(target)1(control)>
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // state : |1(target)0(control)> --> |1(target)0(control)>
  quantum_register.at(0)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
  quantum_register.at(0)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  // state : |1(target)1(control)> --> |0(target)1(control)>
  quantum_register.at(0)->gateX();
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();
  quantum_register.at(0)->gateX();
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, setFree) {
  // state |0>+|1>(control) |0>(target) --> |00> + |11> --> |0> |0>+|1>
  rng->double_value = 0;
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(0)->setFree();
  EXPECT_EQ(quantum_register.at(0)->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(quantum_register.at(1)->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  resetRegister();
  rng->double_value = 0.5;
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(0)->setFree();
  EXPECT_EQ(quantum_register.at(0)->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(quantum_register.at(1)->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsBellPairZmeasurement) {
  // check phi+
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  rng->double_value = 0;
  auto meas0 = quantum_register.at(0)->localMeasureZ();
  auto meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();
  // check phi-
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // check psi+
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  // check psi-
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->localMeasureZ();
  meas1 = quantum_register.at(1)->localMeasureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsGHZstateZmeasurement) {
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 15; i++) {
    quantum_register.at(i)->gateCNOT(quantum_register.at(0));
  }
  rng->double_value = 0;
  for (int i = 0; i < 15; i++) {
    auto meas = quantum_register.at(i)->localMeasureZ();
    EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  }
  resetRegister();
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 15; i++) {
    quantum_register.at(i)->gateCNOT(quantum_register.at(0));
  }
  rng->double_value = 0.5;
  for (int i = 0; i < 15; i++) {
    auto meas = quantum_register.at(i)->localMeasureZ();
    EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  }
  resetRegister();
}
}  // namespace