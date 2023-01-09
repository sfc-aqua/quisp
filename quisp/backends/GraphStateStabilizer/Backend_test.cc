#include "Backend.h"
#include <cxxabi.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <stdexcept>
#include "Configuration.h"
#include "Qubit.h"
#include "backends/interfaces/IConfiguration.h"
#include "test.h"

namespace {
using namespace quisp::backends::graph_state_stabilizer;
using namespace quisp_test::backends;
using namespace omnetpp;

class TestGssQubit : public GraphStateStabilizerQubit {
 public:
  using GraphStateStabilizerQubit::gate_err_cnot;
  using GraphStateStabilizerQubit::gate_err_h;
  using GraphStateStabilizerQubit::gate_err_x;
  using GraphStateStabilizerQubit::gate_err_z;
  using GraphStateStabilizerQubit::measurement_err;
  using GraphStateStabilizerQubit::memory_err;
};

class GssBackend : public GraphStateStabilizerBackend {
 public:
  using GraphStateStabilizerBackend::qubits;
  GssBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateStabilizerConfiguration> config) : GraphStateStabilizerBackend(std::move(rng), std::move(config)) {}
};

class GssBackendTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<GssBackend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<GraphStateStabilizerConfiguration>());
  }
  TestRNG* rng;
  std::unique_ptr<GssBackend> backend;
};

TEST_F(GssBackendTest, getQubit) {
  auto* id = new QubitId(123);
  EXPECT_EQ(backend->qubits.size(), 0);
  auto qubit = backend->getQubit(id);
  EXPECT_EQ(backend->qubits.size(), 1);
  EXPECT_EQ(qubit, backend->getQubit(id));
  EXPECT_EQ(backend->qubits.size(), 1);

  auto* same_id = new QubitId(123);
  auto* same_qubit = backend->getQubit(same_id);
  EXPECT_EQ(backend->qubits.size(), 1);
  EXPECT_EQ(same_qubit, qubit);
}

TEST_F(GssBackendTest, getQubitTwice) {
  auto* id = new QubitId(3);
  auto* qubit1 = backend->getQubit(id);
  auto* qubit2 = backend->getQubit(id);
  EXPECT_NE(qubit1, nullptr);
  EXPECT_NE(qubit2, nullptr);
  EXPECT_EQ(qubit1, qubit2);
}

TEST_F(GssBackendTest, getQubitWithInvalidConfiguration) {
  auto conf = new IConfiguration;
  auto* id = new QubitId(4);
  ASSERT_THROW({ backend->getQubit(id, std::unique_ptr<IConfiguration>(conf)); }, std::runtime_error);
}

TEST_F(GssBackendTest, getQubitWithConfiguration) {
  auto conf = new GraphStateStabilizerConfiguration;
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
  conf->memory_completely_mixed_rate = 0.31;

  auto conf2 = std::make_unique<GraphStateStabilizerConfiguration>(*conf);

  auto* id = new QubitId(123);
  EXPECT_EQ(backend->qubits.size(), 0);
  auto* qubit = backend->getQubit(id, std::move(conf2));
  EXPECT_EQ(backend->qubits.size(), 1);
  EXPECT_EQ(qubit, backend->getQubit(id));
  EXPECT_EQ(backend->qubits.size(), 1);
  auto gss_qubit = reinterpret_cast<TestGssQubit*>(qubit);

  EXPECT_EQ(gss_qubit->gate_err_h.x_error_rate, conf->h_gate_x_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_h.y_error_rate, conf->h_gate_y_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_h.z_error_rate, conf->h_gate_z_err_ratio);

  EXPECT_EQ(gss_qubit->gate_err_x.x_error_rate, conf->x_gate_x_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_x.y_error_rate, conf->x_gate_y_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_x.z_error_rate, conf->x_gate_z_err_ratio);

  EXPECT_EQ(gss_qubit->gate_err_z.x_error_rate, conf->z_gate_x_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_z.y_error_rate, conf->z_gate_y_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_z.z_error_rate, conf->z_gate_z_err_ratio);

  EXPECT_EQ(gss_qubit->measurement_err.x_error_rate, conf->measurement_x_err_rate);
  EXPECT_EQ(gss_qubit->measurement_err.y_error_rate, conf->measurement_y_err_rate);
  EXPECT_EQ(gss_qubit->measurement_err.z_error_rate, conf->measurement_z_err_rate);

  EXPECT_EQ(gss_qubit->memory_err.x_error_rate, conf->memory_x_err_rate);
  EXPECT_EQ(gss_qubit->memory_err.y_error_rate, conf->memory_y_err_rate);
  EXPECT_EQ(gss_qubit->memory_err.z_error_rate, conf->memory_z_err_rate);
  EXPECT_EQ(gss_qubit->memory_err.excitation_error_rate, conf->memory_excitation_rate);
  EXPECT_EQ(gss_qubit->memory_err.relaxation_error_rate, conf->memory_relaxation_rate);
  EXPECT_EQ(gss_qubit->memory_err.completely_mixed_rate, conf->memory_completely_mixed_rate);

  EXPECT_EQ(gss_qubit->gate_err_cnot.ix_error_rate, conf->cnot_gate_ix_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.xi_error_rate, conf->cnot_gate_xi_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.xx_error_rate, conf->cnot_gate_xx_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.iy_error_rate, conf->cnot_gate_iy_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.yi_error_rate, conf->cnot_gate_yi_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.yy_error_rate, conf->cnot_gate_yy_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.iz_error_rate, conf->cnot_gate_iz_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.zi_error_rate, conf->cnot_gate_zi_err_ratio);
  EXPECT_EQ(gss_qubit->gate_err_cnot.zz_error_rate, conf->cnot_gate_zz_err_ratio);
}

}  // namespace
