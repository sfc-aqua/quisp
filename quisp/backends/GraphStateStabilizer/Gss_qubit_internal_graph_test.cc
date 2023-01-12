#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>
#include "Qubit.h"
#include "backends/GraphStateStabilizer/Backend.h"
#include "omnetpp/cexception.h"
#include "omnetpp/simtime.h"
#include "test.h"
namespace {
using namespace quisp_test::backends::graph_state_stabilizer;
using namespace quisp::backends::graph_state_stabilizer;
using namespace quisp::backends::graph_state_stabilizer::types;

class GssQubitInternalGraphTest : public ::testing::Test {
 protected:
  void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = new GraphStateStabilizerBackend(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<GraphStateStabilizerConfiguration>());
    qubit = new Qubit(new QubitId(1), backend);
    another_qubit = new Qubit(new QubitId(2), backend);
    shared_neighbor = new Qubit(new QubitId(3), backend);
    center_qubit = new Qubit(new QubitId(4), backend);
    qubit_to_avoid = new Qubit(new QubitId(5), backend);
    isolated_qubit = new Qubit(new QubitId(6), backend);
  }
  void TearDown() {
    delete backend;
    delete rng;
  }
  Qubit* qubit;
  Qubit* another_qubit;
  Qubit* shared_neighbor;
  Qubit* center_qubit;
  Qubit* qubit_to_avoid;
  Qubit* isolated_qubit;
  GraphStateStabilizerBackend* backend;
  TestRNG* rng;
};

TEST_F(GssQubitInternalGraphTest, AddEdge) {
  // try adding self
  EXPECT_THROW({ qubit->addEdge(qubit); }, std::runtime_error);

  EXPECT_TRUE(qubit->getNeighborSet().empty());
  EXPECT_TRUE(another_qubit->getNeighborSet().empty());
  qubit->addEdge(another_qubit);
  EXPECT_EQ(qubit->getNeighborSet().size(), 1);
  EXPECT_EQ(another_qubit->getNeighborSet().size(), 1);
  EXPECT_NE(qubit->getNeighborSet().find(another_qubit), qubit->getNeighborSet().end());
  EXPECT_NE(another_qubit->getNeighborSet().find(qubit), another_qubit->getNeighborSet().end());

  // try adding it twice: Idempotent check
  qubit->addEdge(another_qubit);
  EXPECT_EQ(qubit->getNeighborSet().size(), 1);
  EXPECT_EQ(another_qubit->getNeighborSet().size(), 1);
  EXPECT_NE(qubit->getNeighborSet().find(another_qubit), qubit->getNeighborSet().end());
  EXPECT_NE(another_qubit->getNeighborSet().find(qubit), another_qubit->getNeighborSet().end());
}

TEST_F(GssQubitInternalGraphTest, isNeighbor) {
  qubit->addEdge(another_qubit);

  EXPECT_FALSE(qubit->isNeighbor(qubit));
  EXPECT_TRUE(qubit->isNeighbor(another_qubit));
  EXPECT_FALSE(qubit->isNeighbor(isolated_qubit));
  EXPECT_TRUE(another_qubit->isNeighbor(qubit));
  EXPECT_FALSE(another_qubit->isNeighbor(another_qubit));
  EXPECT_FALSE(another_qubit->isNeighbor(isolated_qubit));
  EXPECT_FALSE(isolated_qubit->isNeighbor(qubit));
  EXPECT_FALSE(isolated_qubit->isNeighbor(another_qubit));
  EXPECT_FALSE(isolated_qubit->isNeighbor(isolated_qubit));
}

TEST_F(GssQubitInternalGraphTest, DeleteEdge) {
  qubit->addEdge(another_qubit);
  qubit->deleteEdge(another_qubit);
  EXPECT_TRUE(qubit->getNeighborSet().empty());
  EXPECT_TRUE(another_qubit->getNeighborSet().empty());

  // triangle graph and delete only one edge
  qubit->addEdge(another_qubit);
  shared_neighbor->addEdge(qubit);
  shared_neighbor->addEdge(another_qubit);
  qubit->deleteEdge(another_qubit);
  EXPECT_FALSE(qubit->isNeighbor(another_qubit));
  EXPECT_TRUE(qubit->isNeighbor(shared_neighbor));
  EXPECT_FALSE(another_qubit->isNeighbor(qubit));
  EXPECT_TRUE(another_qubit->isNeighbor(shared_neighbor));

  // try adding it twice: Idempotent check
  qubit->deleteEdge(another_qubit);
  EXPECT_FALSE(qubit->isNeighbor(another_qubit));
  EXPECT_TRUE(qubit->isNeighbor(shared_neighbor));
  EXPECT_FALSE(another_qubit->isNeighbor(qubit));
  EXPECT_TRUE(another_qubit->isNeighbor(shared_neighbor));
}

TEST_F(GssQubitInternalGraphTest, ToggleEdge) {
  // no edge -> edge
  shared_neighbor->addEdge(qubit);
  shared_neighbor->addEdge(another_qubit);
  qubit->toggleEdge(another_qubit);
  EXPECT_TRUE(qubit->isNeighbor(another_qubit));
  EXPECT_TRUE(qubit->isNeighbor(shared_neighbor));
  EXPECT_TRUE(another_qubit->isNeighbor(qubit));
  EXPECT_TRUE(another_qubit->isNeighbor(shared_neighbor));

  // edge -> no edge
  qubit->reset();
  another_qubit->reset();
  shared_neighbor->reset();
  qubit->addEdge(another_qubit);
  shared_neighbor->addEdge(qubit);
  shared_neighbor->addEdge(another_qubit);
  qubit->toggleEdge(another_qubit);
  EXPECT_FALSE(qubit->isNeighbor(another_qubit));
  EXPECT_TRUE(qubit->isNeighbor(shared_neighbor));
  EXPECT_FALSE(another_qubit->isNeighbor(qubit));
  EXPECT_TRUE(another_qubit->isNeighbor(shared_neighbor));
}

TEST_F(GssQubitInternalGraphTest, removeAllEdges) {
  qubit->addEdge(another_qubit);
  qubit->addEdge(shared_neighbor);
  another_qubit->addEdge(shared_neighbor);
  qubit->removeAllEdges();
  EXPECT_TRUE(qubit->getNeighborSet().empty());
  EXPECT_FALSE(another_qubit->isNeighbor(qubit));
  EXPECT_FALSE(shared_neighbor->isNeighbor(qubit));
  EXPECT_TRUE(another_qubit->isNeighbor(shared_neighbor));
  // repeat to check idempotent behaviour
  qubit->removeAllEdges();
  EXPECT_TRUE(qubit->getNeighborSet().empty());
  EXPECT_FALSE(another_qubit->isNeighbor(qubit));
  EXPECT_FALSE(shared_neighbor->isNeighbor(qubit));
  EXPECT_TRUE(another_qubit->isNeighbor(shared_neighbor));
}

TEST_F(GssQubitInternalGraphTest, applyClifford) {
  // test on isolated qubit
  for (int k = 0; k < 24; k++) {
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 24; j++) {
        qubit->reset();
        another_qubit->reset();
        qubit->setVertexOperator((CliffordOperator)i);
        another_qubit->setVertexOperator((CliffordOperator)k);

        qubit->applyClifford((CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (CliffordOperator)k);
      }
    }
  }

  // test on qubit with neighbors
  for (int k = 0; k < 24; k++) {
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 24; j++) {
        qubit->reset();
        another_qubit->reset();
        qubit->addEdge(another_qubit);
        qubit->setVertexOperator((CliffordOperator)i);
        another_qubit->setVertexOperator((CliffordOperator)k);

        qubit->applyClifford((CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (CliffordOperator)k);
      }
    }
  }
}

TEST_F(GssQubitInternalGraphTest, applyRightClifford) {
  // test on isolated qubit
  for (int k = 0; k < 24; k++) {
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 24; j++) {
        qubit->reset();
        another_qubit->reset();
        qubit->setVertexOperator((CliffordOperator)i);
        another_qubit->setVertexOperator((CliffordOperator)k);

        qubit->applyRightClifford((CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (CliffordOperator)k);
      }
    }
  }

  // test on qubit with neighbors
  for (int k = 0; k < 24; k++) {
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 24; j++) {
        qubit->reset();
        another_qubit->reset();
        qubit->addEdge(another_qubit);
        qubit->setVertexOperator((CliffordOperator)i);
        another_qubit->setVertexOperator((CliffordOperator)k);

        qubit->applyRightClifford((CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (CliffordOperator)k);
      }
    }
  }
}

TEST_F(GssQubitInternalGraphTest, localComplement) {
  std::vector<Qubit*> first_layer_qubits;
  std::vector<Qubit*> second_layer_qubits;

  for (int i = 0; i < 10; i++) {
    first_layer_qubits.push_back(new Qubit{new QubitId(i), backend});
    second_layer_qubits.push_back(new Qubit{new QubitId(i + 10), backend});
  }

  center_qubit->reset();
  for (int i = 0; i < 10; i++) {
    first_layer_qubits[i]->reset();
    second_layer_qubits[i]->reset();
  }

  // initialize two layer star graph
  for (int i = 0; i < 10; i++) {
    center_qubit->addEdge(first_layer_qubits[i]);
    first_layer_qubits[i]->addEdge(second_layer_qubits[i]);
  }

  center_qubit->localComplement();
  // center should still connected with all its previous neighbors
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(center_qubit->isNeighbor(first_layer_qubits[i]));
    EXPECT_FALSE(center_qubit->isNeighbor(second_layer_qubits[i]));
  }
  // 1st layer and 2nd layer mustn't change;
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(first_layer_qubits[i]->isNeighbor(second_layer_qubits[i]));
  }
  // 1st layer should be all connected
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      EXPECT_TRUE(first_layer_qubits[i]->isNeighbor(first_layer_qubits[j]));
    }
  }
  // 2nd layer shouldn't be connected to each other
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      EXPECT_FALSE(second_layer_qubits[i]->isNeighbor(second_layer_qubits[j]));
    }
  }
  // center should be right applied by RX_INV
  EXPECT_EQ(center_qubit->getVertexOperator(), CliffordOperator::S_RY_INV);
  // 1st layer should be right applied by S
  for (auto v : first_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), CliffordOperator::S_INV_RX_INV);
  }
  // 2nd layer should be the same
  for (auto v : second_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), CliffordOperator::H);
  }

  // apply again
  center_qubit->localComplement();
  // center should still connected with all its previous neighbors
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(center_qubit->isNeighbor(first_layer_qubits[i]));
    EXPECT_FALSE(center_qubit->isNeighbor(second_layer_qubits[i]));
  }
  // 1st layer and 2nd layer mustn't change;
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(first_layer_qubits[i]->isNeighbor(second_layer_qubits[i]));
  }
  // 1st layer shouldn't be connected
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      EXPECT_FALSE(first_layer_qubits[i]->isNeighbor(first_layer_qubits[j]));
    }
  }
  // 2nd layer shouldn't be connected to each other
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      EXPECT_FALSE(second_layer_qubits[i]->isNeighbor(second_layer_qubits[j]));
    }
  }
  // center should be right applied by RX_INV
  EXPECT_EQ(center_qubit->getVertexOperator(), CliffordOperator::RY_INV);
  // 1st layer should be right applied by S
  for (auto v : first_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), CliffordOperator::RY);
  }
  // 2nd layer should be the same
  for (auto v : second_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), CliffordOperator::H);
  }
}

TEST_F(GssQubitInternalGraphTest, removeVertexOperation) {
  // apply RZ to qubit and qubit_to_avoid should not be affected by it
  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(CliffordOperator::Id);
  qubit->setVertexOperator(CliffordOperator::S);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), CliffordOperator::Id);

  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(CliffordOperator::Id);
  qubit->setVertexOperator(CliffordOperator::S_INV);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), CliffordOperator::Id);

  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(CliffordOperator::Id);
  qubit->setVertexOperator(CliffordOperator::Z);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), CliffordOperator::Id);

  // expect qubit to be Id after
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int k = 0; k < 24; k++) {
        qubit->reset();
        another_qubit->reset();
        qubit_to_avoid->reset();
        qubit->addEdge(another_qubit);
        qubit->addEdge(qubit_to_avoid);
        qubit->setVertexOperator((CliffordOperator)i);
        another_qubit->setVertexOperator((CliffordOperator)j);
        qubit_to_avoid->setVertexOperator((CliffordOperator)k);
        qubit->removeVertexOperation(qubit_to_avoid);
        EXPECT_EQ(qubit->getVertexOperator(), CliffordOperator::Id);
      }
    }
  }
}

TEST_F(GssQubitInternalGraphTest, graphMeasureZIsolatedQubit) {
  std::vector<CliffordOperator> zero_state_cliffords = {CliffordOperator::Id, CliffordOperator::Z, CliffordOperator::S, CliffordOperator::S_INV};
  std::vector<CliffordOperator> one_state_cliffords = {CliffordOperator::X, CliffordOperator::Y, CliffordOperator::X_S, CliffordOperator::X_S_INV};
  std::vector<CliffordOperator> superposition_state_cliffords = {
      CliffordOperator::RX,       CliffordOperator::RX_INV,       CliffordOperator::Z_RX,     CliffordOperator::Z_RX_INV,    CliffordOperator::S_RX, CliffordOperator::S_RX_INV,
      CliffordOperator::S_INV_RX, CliffordOperator::S_INV_RX_INV, CliffordOperator::RY,       CliffordOperator::RY_INV,      CliffordOperator::Z_RY, CliffordOperator::H,
      CliffordOperator::S_RY_INV, CliffordOperator::S_RY,         CliffordOperator::S_INV_RY, CliffordOperator::S_INV_RY_INV};

  // repeated measurement shouldn't change the result
  // test 1000 times with rng
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    qubit->applyClifford(CliffordOperator::H);
    auto first_measure = qubit->graphMeasureZ();
    auto second_measure = qubit->graphMeasureZ();
    EXPECT_EQ(first_measure, second_measure);
  }

  // isolated qubit in |0> / |1> state
  rng->double_value = 0.25;
  for (auto cop : zero_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), CliffordOperator::H);
  }
  for (auto cop : one_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), CliffordOperator::RY);
  }

  // isolated qubit in |0> / |1> state
  rng->double_value = 0.75;
  for (auto cop : zero_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), CliffordOperator::H);
  }
  for (auto cop : one_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), CliffordOperator::RY);
  }

  // isolated qubit in other states output 0
  rng->double_value = 0.25;
  for (auto cop : superposition_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), CliffordOperator::H);
  }
  // isolated qubit in other states output 1
  rng->double_value = 0.75;
  for (auto cop : superposition_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), CliffordOperator::RY);
  }
}

TEST_F(GssQubitInternalGraphTest, graphMeasureZGHZState) {
  std::vector<Qubit*> qarrs;
  for (int i = 0; i < 10; i++) {
    qarrs.push_back(new Qubit{new QubitId(i), backend});
  }

  // Bell pair
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    another_qubit->reset();
    qubit->addEdge(another_qubit);
    qubit->setVertexOperator(CliffordOperator::Id);

    auto result_left = qubit->graphMeasureZ();
    EXPECT_TRUE(qubit->getNeighborSet().empty());
    EXPECT_TRUE(another_qubit->getNeighborSet().empty());
    auto result_right = another_qubit->graphMeasureZ();
    EXPECT_EQ(result_left, result_right);
  }

  // GHZ state measure in Z; star graph; measure from center
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    qubit->setVertexOperator(CliffordOperator::Id);
    for (auto v : qarrs) {
      v->reset();
      v->addEdge(qubit);
      v->setVertexOperator(CliffordOperator::H);
    }
    std::vector<quisp::types::EigenvalueResult> measurement_result;

    measurement_result.push_back(qubit->graphMeasureZ());

    // check that all nodes now isolated
    EXPECT_TRUE(qubit->getNeighborSet().empty());
    for (auto v : qarrs) {
      EXPECT_TRUE(v->getNeighborSet().empty());
    }

    for (auto v : qarrs) {
      measurement_result.push_back(v->localMeasureZ());
    }
    for (auto r : measurement_result) {
      EXPECT_EQ(r, measurement_result[0]);
    }
  }

  // GHZ state measure in Z; star graph; measure center last
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    qubit->setVertexOperator(CliffordOperator::Id);
    for (auto v : qarrs) {
      v->reset();
      v->addEdge(qubit);
      v->setVertexOperator(CliffordOperator::H);
    }
    std::vector<quisp::types::EigenvalueResult> measurement_result;
    // measure one leaf node
    qarrs[0]->graphMeasureZ();
    // check that all nodes now isolated
    EXPECT_TRUE(qubit->getNeighborSet().empty());
    for (auto v : qarrs) {
      EXPECT_TRUE(v->getNeighborSet().empty());
    }
    // collect all measurement results
    for (auto v : qarrs) {
      measurement_result.push_back(v->localMeasureZ());
    }
    measurement_result.push_back(qubit->graphMeasureZ());
    for (auto r : measurement_result) {
      EXPECT_EQ(r, measurement_result[0]);
    }
  }
}
}  // end namespace
