#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <Eigen/Eigen>
#include <memory>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>
#include "backends/GraphStateStabilizer/types.h"
#include "test.h"

namespace {
using namespace quisp_test::backends::graph_state_stabilizer;
class GssMultiQubitTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = new GraphStateStabilizerBackend(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<GraphStateStabilizerConfiguration>());
    std::vector<Qubit*> quantum_register(20);
    for (auto qubit : quantum_register) {
      qubit = new Qubit(new QubitId(&qubit - &quantum_register[0]), backend);
    }
  }
  std::vector<Qubit*> quantum_register;
  GraphStateStabilizerBackend* backend;
  TestRNG* rng;
};

TESTF(GssMultiQubitTest, multiGateEntanglementSwapping) {
  quantum_register[0]->gateH();
  quantum_register[0]->gateH();
}

}  // namespace