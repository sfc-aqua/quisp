#include "Backend.h"
#include <cxxabi.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include "../interfaces/IRandomNumberGenerator.h"
#include "test.h"

namespace {
using namespace quisp::backends::error_tracking;
using namespace quisp_test::backends;
using namespace omnetpp;

class EtBackendTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng));
  }
  TestRNG* rng;
  std::unique_ptr<Backend> backend;
};

TEST_F(EtBackendTest, getQubit) {
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

}  // namespace
