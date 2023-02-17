#include <cxxabi.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <stdexcept>
#include "Backend.h"
#include "Qubit.h"
#include "backends/interfaces/IConfiguration.h"
#include "test.h"

namespace {
using namespace quisp::backends::graph_state;
using namespace quisp_test::backends::graph_state;
using namespace omnetpp;

class TestGsQubit : public GraphStateQubit {
 public:
  using GraphStateQubit::gate_err_cnot;
  using GraphStateQubit::gate_err_h;
  using GraphStateQubit::gate_err_x;
  using GraphStateQubit::gate_err_z;
  using GraphStateQubit::measurement_err;
  using GraphStateQubit::memory_err;
};

class GsBackend : public GraphStateBackend {
 public:
  using GraphStateBackend::qubits;
  GsBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> config) : GraphStateBackend(std::move(rng), std::move(config)) {}
};

class GsBackendTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<GsBackend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<StationaryQubitConfiguration>());
  }
  TestRNG* rng;
  std::unique_ptr<GsBackend> backend;
  int randomSamplingWithLabelsAndWeights(std::vector<int> labels, std::vector<double> weights);
};

TEST_F(GsBackendTest, createQubit) {
  auto* id = new QubitId(123);
  EXPECT_EQ(backend->qubits.size(), 0);
  auto qubit = backend->createQubit(id);
  EXPECT_EQ(backend->qubits.size(), 1);
  ASSERT_THROW(backend->createQubit(id), std::runtime_error);
  EXPECT_EQ(backend->qubits.size(), 1);
}

TEST_F(GsBackendTest, getQubit) {
  auto* id = new QubitId(123);
  EXPECT_EQ(backend->qubits.size(), 0);
  auto qubit = backend->createQubit(id);
  EXPECT_EQ(backend->qubits.size(), 1);
  EXPECT_EQ(qubit, backend->getQubit(id));
  EXPECT_EQ(backend->qubits.size(), 1);

  auto* same_id = new QubitId(123);
  auto* same_qubit = backend->getQubit(same_id);
  EXPECT_EQ(backend->qubits.size(), 1);
  EXPECT_EQ(same_qubit, qubit);
}

TEST_F(GsBackendTest, getQubitTwice) {
  auto* id = new QubitId(3);
  backend->createQubit(id);
  auto* qubit1 = backend->getQubit(id);
  auto* qubit2 = backend->getQubit(id);
  EXPECT_NE(qubit1, nullptr);
  EXPECT_NE(qubit2, nullptr);
  EXPECT_EQ(qubit1, qubit2);
}

TEST_F(GsBackendTest, createQubitWithInvalidConfiguration) {
  auto conf = new IConfiguration;
  auto* id = new QubitId(4);
  ASSERT_THROW({ backend->createQubit(id, std::unique_ptr<IConfiguration>(conf)); }, std::runtime_error);
}

TEST_F(GsBackendTest, getQubitWithConfiguration) {
  auto conf = new StationaryQubitConfiguration;
  conf->cnot_gate_err_rate = 0.75;
  conf->cnot_gate_ix_err_ratio = 0.75 / 9.;
  conf->cnot_gate_xi_err_ratio = 0.75 / 9.;
  conf->cnot_gate_xx_err_ratio = 0.75 / 9.;
  conf->cnot_gate_iy_err_ratio = 0.75 / 9.;
  conf->cnot_gate_yi_err_ratio = 0.75 / 9.;
  conf->cnot_gate_yy_err_ratio = 0.75 / 9.;
  conf->cnot_gate_iz_err_ratio = 0.75 / 9.;
  conf->cnot_gate_zi_err_ratio = 0.75 / 9.;
  conf->cnot_gate_zz_err_ratio = 0.75 / 9.;
  conf->h_gate_err_rate = 1.0;
  conf->h_gate_x_err_ratio = 1. / 3.;
  conf->h_gate_y_err_ratio = 1. / 3.;
  conf->h_gate_z_err_ratio = 1. / 3.;
  conf->x_gate_err_rate = 0.5;
  conf->x_gate_x_err_ratio = 0.5 / 3.;
  conf->x_gate_y_err_ratio = 0.5 / 3.;
  conf->x_gate_z_err_ratio = 0.5 / 3.;
  conf->z_gate_err_rate = 0.25;
  conf->z_gate_x_err_ratio = 0.25 / 3.;
  conf->z_gate_y_err_ratio = 0.25 / 3.;
  conf->z_gate_z_err_ratio = 0.25 / 3.;
  conf->measurement_x_err_rate = 0.23;
  conf->measurement_y_err_rate = 0.24;
  conf->measurement_z_err_rate = 0.25;
  conf->memory_x_err_rate = 0.26;
  conf->memory_y_err_rate = 0.27;
  conf->memory_z_err_rate = 0.28;
  conf->memory_relaxation_rate = 0.29;
  conf->memory_excitation_rate = 0.30;

  auto conf2 = std::make_unique<StationaryQubitConfiguration>(*conf);

  auto* id = new QubitId(123);
  EXPECT_EQ(backend->qubits.size(), 0);
  auto* qubit = backend->createQubit(id, std::move(conf2));
  EXPECT_EQ(backend->qubits.size(), 1);
  EXPECT_EQ(qubit, backend->getQubit(id));
  EXPECT_EQ(backend->qubits.size(), 1);
  auto Gs_qubit = reinterpret_cast<TestGsQubit*>(qubit);

  EXPECT_EQ(Gs_qubit->gate_err_h.x_error_rate, conf->h_gate_x_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_h.y_error_rate, conf->h_gate_y_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_h.z_error_rate, conf->h_gate_z_err_ratio);

  EXPECT_EQ(Gs_qubit->gate_err_x.x_error_rate, conf->x_gate_x_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_x.y_error_rate, conf->x_gate_y_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_x.z_error_rate, conf->x_gate_z_err_ratio);

  EXPECT_EQ(Gs_qubit->gate_err_z.x_error_rate, conf->z_gate_x_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_z.y_error_rate, conf->z_gate_y_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_z.z_error_rate, conf->z_gate_z_err_ratio);

  EXPECT_EQ(Gs_qubit->measurement_err.x_error_rate, conf->measurement_x_err_rate);
  EXPECT_EQ(Gs_qubit->measurement_err.y_error_rate, conf->measurement_y_err_rate);
  EXPECT_EQ(Gs_qubit->measurement_err.z_error_rate, conf->measurement_z_err_rate);

  EXPECT_EQ(Gs_qubit->memory_err.x_error_rate, conf->memory_x_err_rate);
  EXPECT_EQ(Gs_qubit->memory_err.y_error_rate, conf->memory_y_err_rate);
  EXPECT_EQ(Gs_qubit->memory_err.z_error_rate, conf->memory_z_err_rate);
  EXPECT_EQ(Gs_qubit->memory_err.excitation_error_rate, conf->memory_excitation_rate);
  EXPECT_EQ(Gs_qubit->memory_err.relaxation_error_rate, conf->memory_relaxation_rate);

  EXPECT_EQ(Gs_qubit->gate_err_cnot.ix_error_rate, conf->cnot_gate_ix_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.xi_error_rate, conf->cnot_gate_xi_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.xx_error_rate, conf->cnot_gate_xx_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.iy_error_rate, conf->cnot_gate_iy_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.yi_error_rate, conf->cnot_gate_yi_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.yy_error_rate, conf->cnot_gate_yy_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.iz_error_rate, conf->cnot_gate_iz_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.zi_error_rate, conf->cnot_gate_zi_err_ratio);
  EXPECT_EQ(Gs_qubit->gate_err_cnot.zz_error_rate, conf->cnot_gate_zz_err_ratio);
}

TEST_F(GsBackendTest, ThrowRuntimeErrorOnRandomSamplingWithLabelsAndWeights1) {
  enum Labels { No_err, X_err, Z_err, Y_err };
  std::vector<int> labels = {No_err, X_err, Z_err, Y_err};
  std::vector<double> weights = {0.3, 0.5, 0.8, 0.9};

  EXPECT_THROW(this->randomSamplingWithLabelsAndWeights(labels, weights), std::runtime_error);
}
TEST_F(GsBackendTest, ThrowRuntimeErrorOnRandomSamplingWithLabelsAndWeights2) {
  enum Labels { No_err, X_err, Z_err, Y_err };
  std::vector<int> labels = {No_err, X_err, Z_err};
  std::vector<double> weights = {0.3, 0.5, 0.8, 0.9};

  EXPECT_THROW(this->randomSamplingWithLabelsAndWeights(labels, weights), std::runtime_error);
}

TEST_F(GsBackendTest, ThrowRuntimeErrorOnRandomSamplingWithLabelsAndWeights3) {
  enum Labels { No_err, X_err, Z_err, Y_err };
  std::vector<int> labels = {No_err, X_err, Z_err};
  std::vector<double> weights = {0.3, 0.5};

  EXPECT_THROW(this->randomSamplingWithLabelsAndWeights(labels, weights), std::runtime_error);
}

}  // namespace
