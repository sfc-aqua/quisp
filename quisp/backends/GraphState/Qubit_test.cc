#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <Eigen/Eigen>
#include <memory>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/GraphState/types.h"
#include "backends/interfaces/IQubit.h"
#include "test.h"

namespace {
using namespace quisp_test::backends::graph_state;
using Eigen::Matrix2cd;
using Eigen::Matrix4cd;
using Eigen::Vector4cd;

class TestGsQubit : public GraphStateQubit {
 public:
  using GraphStateQubit::gate_err_cnot;
  using GraphStateQubit::gate_err_h;
  using GraphStateQubit::gate_err_x;
  using GraphStateQubit::gate_err_z;
  using GraphStateQubit::measurement_err;
  using GraphStateQubit::memory_err;
};

class GsQubit : public GraphStateBackend {
 public:
  using GraphStateBackend::qubits;
  GsQubit(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> config) : GraphStateBackend(std::move(rng), std::move(config)) {}
};

class QubitTest : public ::testing::Test {
 protected:
  void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<StationaryQubitConfiguration>());
    qubit = dynamic_cast<Qubit*>(backend->createQubit(1));
    qubit->fillParams();
  }
  Qubit* qubit;
  std::unique_ptr<Backend> backend;
  TestRNG* rng;
};

TEST_F(QubitTest, applySingleQubitGateErrorTest) {
  auto conf = new StationaryQubitConfiguration;
  EigenvalueResult meas;

  conf->x_gate_err_rate = 0.9;
  conf->x_gate_x_err_ratio = 0.3;
  conf->x_gate_y_err_ratio = 0.3;
  conf->x_gate_z_err_ratio = 0.3;

  auto conf2 = std::make_unique<StationaryQubitConfiguration>(*conf);

  auto* id = new QubitId(123);
  auto* qubit = backend->GsQubit::createQubit(id, std::move(conf2));
  auto Gs_qubit = reinterpret_cast<TestGsQubit*>(qubit);

  rng->double_value = 0.;
  Gs_qubit->gateX();
  meas = Gs_qubit->measureZ();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  Gs_qubit->setFree();

  rng->double_value = 0.4;
  Gs_qubit->gateX();
  meas = Gs_qubit->measureZ();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureX();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureY();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  Gs_qubit->setFree();
  
  rng->double_value = 0.7;
  Gs_qubit->gateX();
  meas = Gs_qubit->measureZ();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureY();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  Gs_qubit->setFree();
  
  rng->double_value = 1.0;
  Gs_qubit->gateX();
  meas = Gs_qubit->measureZ();
  EXPECT_EQ(meas, EigenvalueResult::PLUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureX();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  Gs_qubit->setFree();
  Gs_qubit->gateX();
  meas = qubit->measureY();
  EXPECT_EQ(meas, EigenvalueResult::MINUS_ONE);
  Gs_qubit->setFree();
}

}  // namespace
