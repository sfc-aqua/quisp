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
    for(auto qubit: qubits){
        qubit = new Qubit(new QubitId(&qubit - &qubits[0]), backend);
    }
  }
  std::vector<Qubit*> qubits(20);
  Qubit* qubit;
  GraphStateStabilizerBackend* backend;
  TestRNG* rng;
};

}// namespace