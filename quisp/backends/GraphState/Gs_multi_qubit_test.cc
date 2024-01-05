#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <Eigen/Eigen>
#include <memory>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>
#include "backends/GraphState/types.h"
#include "backends/interfaces/IQubit.h"
#include "test.h"

namespace {
using namespace quisp_test::backends::graph_state;
class GsMultiQubitTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<StationaryQubitConfiguration>());
    for (int i = 0; i < 16; i++) {
      quantum_register.push_back(dynamic_cast<Qubit*>(backend->createQubit(i)));
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
  // state : |0(control)0(target)> --> |0(control)0(target)>
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  auto meas0 = quantum_register.at(0)->measureZ();
  auto meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
  rng->double_value = 0.5;
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  // state : |1(control)0(target)> --> |1(control)1(target)>
  quantum_register.at(0)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();
  quantum_register.at(0)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // state : |0(control)1(target)> --> |0(control)1(target)>
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // state : |1(control)1(target)> --> |1(control)0(target)>
  quantum_register.at(0)->gateX();
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
  quantum_register.at(0)->gateX();
  quantum_register.at(1)->gateX();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, setFree) {
  // state |0>+|1>(control) |0>(target) --> |00> + |11> --> |0> |0>+|1>
  rng->double_value = 0;
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(0)->setFree();
  EXPECT_EQ(quantum_register.at(0)->measureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(quantum_register.at(1)->measureZ(), EigenvalueResult::PLUS_ONE);
  resetRegister();
  rng->double_value = 0.5;
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(0)->setFree();
  EXPECT_EQ(quantum_register.at(0)->measureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(quantum_register.at(1)->measureZ(), EigenvalueResult::MINUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsBellPairZmeasurement) {
  // check phi+
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  auto meas0 = quantum_register.at(0)->measureZ();
  auto meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // check phi-
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // check psi+
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  // check psi-
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureZ();
  meas1 = quantum_register.at(1)->measureZ();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsBellPairXmeasurement) {
  // check phi+
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  auto meas0 = quantum_register.at(0)->measureX();
  auto meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureX();
  meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();
  // check phi-
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureX();
  meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureX();
  meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  // check psi+
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureX();
  meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureX();
  meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // check psi-
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureX();
  meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureX();
  meas1 = quantum_register.at(1)->measureX();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsBellPairYmeasurement) {
  // check phi+
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0;
  auto meas0 = quantum_register.at(0)->measureY();
  auto meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureY();
  meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
  // check phi-
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureY();
  meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureY();
  meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // check psi+
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureY();
  meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureY();
  meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  // check psi-
  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0;
  meas0 = quantum_register.at(0)->measureY();
  meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(0)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateZ();
  quantum_register.at(1)->gateX();
  rng->double_value = 0.5;
  meas0 = quantum_register.at(0)->measureY();
  meas1 = quantum_register.at(1)->measureY();
  EXPECT_EQ(meas0, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsGHZstateZmeasurement) {
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 16; i++) {
    quantum_register.at(0)->gateCNOT(quantum_register.at(i));
  }
  rng->double_value = 0;
  for (int i = 0; i < 16; i++) {
    auto meas = quantum_register.at(i)->measureZ();
    EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  }
  resetRegister();
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 16; i++) {
    quantum_register.at(0)->gateCNOT(quantum_register.at(i));
  }
  rng->double_value = 0.5;
  for (int i = 0; i < 16; i++) {
    auto meas = quantum_register.at(i)->measureZ();
    EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  }
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsGHZstateXmeasurement) {
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 16; i++) {
    quantum_register.at(0)->gateCNOT(quantum_register.at(i));
  }
  rng->double_value = 0;
  for (int i = 0; i < 16; i++) {
    auto meas = quantum_register.at(i)->measureX();
    EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  }
  resetRegister();
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 16; i++) {
    quantum_register.at(0)->gateCNOT(quantum_register.at(i));
  }
  rng->double_value = 0.5;
  for (int i = 0; i < 16; i++) {
    auto meas = quantum_register.at(i)->measureX();
    // あとで計算する
    EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  }
  resetRegister();
}
TEST_F(GsMultiQubitTest, checkCorrelatedMeasurementResultsGHZstateYmeasurement) {
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 16; i++) {
    quantum_register.at(0)->gateCNOT(quantum_register.at(i));
  }
  rng->double_value = 0;
  for (int i = 0; i < 16; i++) {
    auto meas = quantum_register.at(i)->measureY();
    EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  }
  resetRegister();
  quantum_register.at(0)->gateH();
  for (int i = 1; i < 16; i++) {
    quantum_register.at(0)->gateCNOT(quantum_register.at(i));
  }
  rng->double_value = 0.5;
  for (int i = 0; i < 16; i++) {
    auto meas = quantum_register.at(i)->measureY();
    EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  }
  resetRegister();
}
TEST_F(GsMultiQubitTest, randomQuantumCircuit1) {
  rng->double_value = 0;
  quantum_register.at(0)->gateZ();
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateZ();
  quantum_register.at(2)->gateX();
  quantum_register.at(3)->gateX();
  auto meas1 = quantum_register.at(0)->measureZ();
  auto meas2 = quantum_register.at(1)->measureZ();
  auto meas3 = quantum_register.at(2)->measureZ();
  auto meas4 = quantum_register.at(3)->measureZ();
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas2, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas3, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas4, EigenvalueResult::MINUS_ONE);
  resetRegister();

  rng->double_value = 0.5;
  quantum_register.at(0)->gateZ();
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateZ();
  quantum_register.at(2)->gateX();
  quantum_register.at(3)->gateX();
  meas1 = quantum_register.at(0)->measureZ();
  meas2 = quantum_register.at(1)->measureZ();
  meas3 = quantum_register.at(2)->measureZ();
  meas4 = quantum_register.at(3)->measureZ();
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas2, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas3, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas4, EigenvalueResult::MINUS_ONE);
  resetRegister();
}
TEST_F(GsMultiQubitTest, randomQuantumCircuit2) {
  rng->double_value = 0;
  quantum_register.at(1)->gateS();
  quantum_register.at(2)->gateX();
  quantum_register.at(4)->gateX();
  quantum_register.at(3)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateH();
  quantum_register.at(3)->gateZ();
  quantum_register.at(0)->gateCNOT(quantum_register.at(3));
  quantum_register.at(1)->gateS();
  quantum_register.at(0)->gateCNOT(quantum_register.at(3));
  quantum_register.at(0)->gateS();
  auto meas1 = quantum_register.at(0)->measureZ();
  auto meas2 = quantum_register.at(1)->measureZ();
  auto meas3 = quantum_register.at(2)->measureZ();
  auto meas4 = quantum_register.at(3)->measureZ();
  auto meas5 = quantum_register.at(4)->measureZ();
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas2, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas3, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas4, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas5, EigenvalueResult::MINUS_ONE);
  resetRegister();

  rng->double_value = 0.5;
  quantum_register.at(1)->gateS();
  quantum_register.at(2)->gateX();
  quantum_register.at(4)->gateX();
  quantum_register.at(3)->gateCNOT(quantum_register.at(1));
  quantum_register.at(1)->gateH();
  quantum_register.at(3)->gateZ();
  quantum_register.at(0)->gateCNOT(quantum_register.at(3));
  quantum_register.at(1)->gateS();
  quantum_register.at(0)->gateCNOT(quantum_register.at(3));
  quantum_register.at(0)->gateS();
  meas1 = quantum_register.at(0)->measureZ();
  meas2 = quantum_register.at(1)->measureZ();
  meas3 = quantum_register.at(2)->measureZ();
  meas4 = quantum_register.at(3)->measureZ();
  meas5 = quantum_register.at(4)->measureZ();
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas2, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas3, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas4, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas5, EigenvalueResult::MINUS_ONE);
  resetRegister();
}

TEST_F(GsMultiQubitTest, checkMSMLinkConnection) {
  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(2)->gateH();
  quantum_register.at(3)->gateCNOT(quantum_register.at(2));
  quantum_register.at(5)->gateH();
  quantum_register.at(5)->gateCNOT(quantum_register.at(4));
  quantum_register.at(1)->gateX();
  quantum_register.at(4)->gateX();
  quantum_register.at(1)->gateCNOT(quantum_register.at(2));
  quantum_register.at(4)->gateCNOT(quantum_register.at(3));
  quantum_register.at(1)->noiselessMeasureX(EigenvalueResult::PLUS_ONE);
  quantum_register.at(2)->noiselessMeasureZ(EigenvalueResult::PLUS_ONE);
  quantum_register.at(3)->noiselessMeasureZ(EigenvalueResult::PLUS_ONE);
  quantum_register.at(4)->noiselessMeasureX(EigenvalueResult::PLUS_ONE);

  rng->double_value = 0;
  auto meas1 = quantum_register.at(0)->measureZ();
  auto meas2 = quantum_register.at(0)->measureZ();
  EXPECT_EQ(meas1, EigenvalueResult::PLUS_ONE);
  EXPECT_EQ(meas2, EigenvalueResult::PLUS_ONE);
  resetRegister();

  quantum_register.at(0)->gateH();
  quantum_register.at(1)->gateCNOT(quantum_register.at(0));
  quantum_register.at(2)->gateH();
  quantum_register.at(3)->gateCNOT(quantum_register.at(2));
  quantum_register.at(5)->gateH();
  quantum_register.at(5)->gateCNOT(quantum_register.at(4));
  quantum_register.at(1)->gateX();
  quantum_register.at(4)->gateX();
  quantum_register.at(1)->gateCNOT(quantum_register.at(2));
  quantum_register.at(4)->gateCNOT(quantum_register.at(3));
  quantum_register.at(1)->noiselessMeasureX(EigenvalueResult::PLUS_ONE);
  quantum_register.at(2)->noiselessMeasureZ(EigenvalueResult::PLUS_ONE);
  quantum_register.at(3)->noiselessMeasureZ(EigenvalueResult::PLUS_ONE);
  quantum_register.at(4)->noiselessMeasureX(EigenvalueResult::PLUS_ONE);

  rng->double_value = 0.5;
  meas1 = quantum_register.at(0)->measureZ();
  meas2 = quantum_register.at(0)->measureZ();
  EXPECT_EQ(meas1, EigenvalueResult::MINUS_ONE);
  EXPECT_EQ(meas2, EigenvalueResult::MINUS_ONE);
  resetRegister();
}

}  // namespace
