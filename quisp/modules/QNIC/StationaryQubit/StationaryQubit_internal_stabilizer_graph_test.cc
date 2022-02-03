#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>
#include "StationaryQubit.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "omnetpp/cexception.h"
#include "omnetpp/simtime.h"

using namespace quisp::modules;
using namespace quisp_test;
namespace {

class StatQubitFixture : public StationaryQubit {
 public:
  using StationaryQubit::addEdge;
  using StationaryQubit::applyClifford;
  using StationaryQubit::applyPureCZ;
  using StationaryQubit::applyRightClifford;
  using StationaryQubit::deleteEdge;
  using StationaryQubit::graphMeasureZ;
  using StationaryQubit::isNeighbor;
  using StationaryQubit::localComplement;
  using StationaryQubit::par;
  using StationaryQubit::removeAllEdges;
  using StationaryQubit::removeVertexOperation;
  using StationaryQubit::toggleEdge;

  StatQubitFixture() : StationaryQubit() { setComponentType(new TestModuleType("test qubit")); }
  void reset() {
    this->neighbors.clear();
    this->vertex_operator = quisp::types::CliffordOperator::H;
  }

  void fillParams() {
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_X_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    // No error= 0.4, X error = 0.6, Z error = 0.8, Y error = 1.0
    setParDouble(this, "Hgate_error_rate", 0.6);
    setParDouble(this, "Hgate_X_error_ratio", 1);
    setParDouble(this, "Hgate_Z_error_ratio", 1);
    setParDouble(this, "Hgate_Y_error_ratio", 1);

    setParDouble(this, "Xgate_error_rate", 0.6);
    setParDouble(this, "Xgate_X_error_ratio", 1);
    setParDouble(this, "Xgate_Z_error_ratio", 1);
    setParDouble(this, "Xgate_Y_error_ratio", 1);

    setParDouble(this, "Zgate_error_rate", 0.6);
    setParDouble(this, "Zgate_X_error_ratio", 1);
    setParDouble(this, "Zgate_Z_error_ratio", 1);
    setParDouble(this, "Zgate_Y_error_ratio", 1);

    // clean = 0.1,
    // IX = 0.2, XI = 0.3, XX = 0.4,
    // IZ = 0.5, ZI = 0.6, ZZ = 0.7,
    // IY = 0.8, IY = 0.9, YY = 1.0
    setParDouble(this, "CNOTgate_error_rate", 0.9);
    setParDouble(this, "CNOTgate_IX_error_ratio", 1);
    setParDouble(this, "CNOTgate_XI_error_ratio", 1);
    setParDouble(this, "CNOTgate_XX_error_ratio", 1);
    setParDouble(this, "CNOTgate_IZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZI_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_IY_error_ratio", 1);
    setParDouble(this, "CNOTgate_YI_error_ratio", 1);
    setParDouble(this, "CNOTgate_YY_error_ratio", 1);

    setParDouble(this, "X_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "Y_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "Z_measurement_error_rate", 1.0 / 2000);

    setParInt(this, "stationaryQubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

    setParDouble(this, "photon_emitted_at", 0.0);
    setParDouble(this, "last_updated_at", 0.0);
    setParBool(this, "GOD_Xerror", false);
    setParBool(this, "GOD_Zerror", false);
    setParBool(this, "GOD_CMerror", false);
    setParBool(this, "GOD_EXerror", false);
    setParBool(this, "GOD_REerror", false);
    setParBool(this, "isBusy", false);
    setParInt(this, "GOD_entangled_stationaryQubit_address", 0);
    setParInt(this, "GOD_entangled_node_address", 0);
    setParInt(this, "GOD_entangled_qnic_address", 0);
    setParInt(this, "GOD_entangled_qnic_type", 0);
    setParDouble(this, "fidelity", -1.0);
  }

  std::unordered_set<StationaryQubit *> getNeighborSet() { return this->neighbors; }

  void setVertexOperator(quisp::types::CliffordOperator op) { this->vertex_operator = op; }

  quisp::types::CliffordOperator getVertexOperator() { return this->vertex_operator; }
};

TEST(StatQubitInternalGraphTest, AddEdge) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};
  qubit->fillParams();
  another_qubit->fillParams();

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);

  // try adding self
  EXPECT_THROW(qubit->addEdge(qubit), cRuntimeError);

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

TEST(StatQubitInternalGraphTest, isNeighbor) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};
  auto *isolated_qubit = new StatQubitFixture{};

  qubit->fillParams();
  another_qubit->fillParams();
  isolated_qubit->fillParams();

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);
  sim->registerComponent(isolated_qubit);

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

TEST(StatQubitInternalGraphTest, DeleteEdge) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};
  auto *shared_neighbor = new StatQubitFixture{};

  qubit->fillParams();
  another_qubit->fillParams();
  shared_neighbor->fillParams();
  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);
  sim->registerComponent(shared_neighbor);

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

TEST(StatQubitInternalGraphTest, ToggleEdge) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};
  auto *shared_neighbor = new StatQubitFixture{};

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);
  sim->registerComponent(shared_neighbor);

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

TEST(StatQubitInternalGraphTest, removeAllEdges) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};
  auto *shared_neighbor = new StatQubitFixture{};

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);
  sim->registerComponent(shared_neighbor);

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

TEST(StatQubitInternalGraphTest, applyClifford) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);

  // test on isolated qubit
  for (int k = 0; k < 24; k++) {
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 24; j++) {
        qubit->reset();
        another_qubit->reset();
        qubit->setVertexOperator((quisp::types::CliffordOperator)i);
        another_qubit->setVertexOperator((quisp::types::CliffordOperator)k);

        qubit->applyClifford((quisp::types::CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (quisp::types::CliffordOperator)k);
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
        qubit->setVertexOperator((quisp::types::CliffordOperator)i);
        another_qubit->setVertexOperator((quisp::types::CliffordOperator)k);

        qubit->applyClifford((quisp::types::CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (quisp::types::CliffordOperator)k);
      }
    }
  }
}

TEST(StatQubitInternalGraphTest, applyRightClifford) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);

  // test on isolated qubit
  for (int k = 0; k < 24; k++) {
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 24; j++) {
        qubit->reset();
        another_qubit->reset();
        qubit->setVertexOperator((quisp::types::CliffordOperator)i);
        another_qubit->setVertexOperator((quisp::types::CliffordOperator)k);

        qubit->applyRightClifford((quisp::types::CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (quisp::types::CliffordOperator)k);
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
        qubit->setVertexOperator((quisp::types::CliffordOperator)i);
        another_qubit->setVertexOperator((quisp::types::CliffordOperator)k);

        qubit->applyRightClifford((quisp::types::CliffordOperator)j);
        EXPECT_EQ(another_qubit->getVertexOperator(), (quisp::types::CliffordOperator)k);
      }
    }
  }
}

TEST(StatQubitInternalGraphTest, localComplement) {
  auto *sim = prepareSimulation();
  auto *center_qubit = new StatQubitFixture{};
  std::vector<StatQubitFixture *> first_layer_qubits;
  std::vector<StatQubitFixture *> second_layer_qubits;

  sim->registerComponent(center_qubit);
  for (int i = 0; i < 10; i++) {
    first_layer_qubits.push_back(new StatQubitFixture{});
    second_layer_qubits.push_back(new StatQubitFixture{});
    sim->registerComponent(first_layer_qubits[i]);
    sim->registerComponent(second_layer_qubits[i]);
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
  EXPECT_EQ(center_qubit->getVertexOperator(), quisp::types::CliffordOperator::S_RY_INV);
  // 1st layer should be right applied by S
  for (auto v : first_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), quisp::types::CliffordOperator::S_INV_RX_INV);
  }
  // 2nd layer should be the same
  for (auto v : second_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), quisp::types::CliffordOperator::H);
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
  EXPECT_EQ(center_qubit->getVertexOperator(), quisp::types::CliffordOperator::RY_INV);
  // 1st layer should be right applied by S
  for (auto v : first_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), quisp::types::CliffordOperator::RY);
  }
  // 2nd layer should be the same
  for (auto v : second_layer_qubits) {
    EXPECT_EQ(v->getVertexOperator(), quisp::types::CliffordOperator::H);
  }
}

TEST(StatQubitInternalGraphTest, removeVertexOperation) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};
  auto *qubit_to_avoid = new StatQubitFixture{};

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);
  sim->registerComponent(qubit_to_avoid);

  // apply RZ to qubit and qubit_to_avoid should not be affected by it
  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(quisp::types::CliffordOperator::Id);
  qubit->setVertexOperator(quisp::types::CliffordOperator::S);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), quisp::types::CliffordOperator::Id);

  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(quisp::types::CliffordOperator::Id);
  qubit->setVertexOperator(quisp::types::CliffordOperator::S_INV);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), quisp::types::CliffordOperator::Id);

  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(quisp::types::CliffordOperator::Id);
  qubit->setVertexOperator(quisp::types::CliffordOperator::Z);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), quisp::types::CliffordOperator::Id);

  // expect qubit to be Id after
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int k = 0; k < 24; k++) {
        qubit->reset();
        another_qubit->reset();
        qubit_to_avoid->reset();
        qubit->addEdge(another_qubit);
        qubit->addEdge(qubit_to_avoid);
        qubit->setVertexOperator((quisp::types::CliffordOperator)i);
        another_qubit->setVertexOperator((quisp::types::CliffordOperator)j);
        qubit_to_avoid->setVertexOperator((quisp::types::CliffordOperator)k);
        qubit->removeVertexOperation(qubit_to_avoid);
        EXPECT_EQ(qubit->getVertexOperator(), quisp::types::CliffordOperator::Id);
      }
    }
  }
}

TEST(StatQubitInternalGraphTest, graphMeasureZIsolatedQubit) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitFixture{};

  sim->registerComponent(qubit);

  std::vector<quisp::types::CliffordOperator> zero_state_cliffords = {quisp::types::CliffordOperator::Id, quisp::types::CliffordOperator::Z, quisp::types::CliffordOperator::S,
                                                                      quisp::types::CliffordOperator::S_INV};
  std::vector<quisp::types::CliffordOperator> one_state_cliffords = {quisp::types::CliffordOperator::X, quisp::types::CliffordOperator::Y, quisp::types::CliffordOperator::X_S,
                                                                     quisp::types::CliffordOperator::X_S_INV};
  std::vector<quisp::types::CliffordOperator> superposition_state_cliffords = {
      quisp::types::CliffordOperator::RX,       quisp::types::CliffordOperator::RX_INV,   quisp::types::CliffordOperator::Z_RX,     quisp::types::CliffordOperator::Z_RX_INV,
      quisp::types::CliffordOperator::S_RX,     quisp::types::CliffordOperator::S_RX_INV, quisp::types::CliffordOperator::S_INV_RX, quisp::types::CliffordOperator::S_INV_RX_INV,
      quisp::types::CliffordOperator::RY,       quisp::types::CliffordOperator::RY_INV,   quisp::types::CliffordOperator::Z_RY,     quisp::types::CliffordOperator::H,
      quisp::types::CliffordOperator::S_RY_INV, quisp::types::CliffordOperator::S_RY,     quisp::types::CliffordOperator::S_INV_RY, quisp::types::CliffordOperator::S_INV_RY_INV};

  // repeated measurement shouldn't change the result
  // test 1000 times with rng
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    qubit->applyClifford(quisp::types::CliffordOperator::H);
    auto first_measure = qubit->graphMeasureZ();
    auto second_measure = qubit->graphMeasureZ();
    EXPECT_EQ(first_measure, second_measure);
  }

  // isolated qubit in |0> / |1> state
  rng->doubleValue = 0.25;
  for (auto cop : zero_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), quisp::types::CliffordOperator::H);
  }
  for (auto cop : one_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), quisp::types::CliffordOperator::RY);
  }

  // isolated qubit in |0> / |1> state
  rng->doubleValue = 0.75;
  for (auto cop : zero_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), quisp::types::CliffordOperator::H);
  }
  for (auto cop : one_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), quisp::types::CliffordOperator::RY);
  }

  // isolated qubit in other states output 0
  rng->doubleValue = 0.25;
  for (auto cop : superposition_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), quisp::types::CliffordOperator::H);
  }
  // isolated qubit in other states output 1
  rng->doubleValue = 0.75;
  for (auto cop : superposition_state_cliffords) {
    qubit->reset();
    qubit->applyClifford(cop);
    EXPECT_EQ(qubit->graphMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
    EXPECT_EQ(qubit->getVertexOperator(), quisp::types::CliffordOperator::RY);
  }
}

TEST(StatQubitInternalGraphTest, graphMeasureZGHZState) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitFixture{};
  auto *another_qubit = new StatQubitFixture{};
  std::vector<StatQubitFixture *> qarrs;
  for (int i = 0; i < 10; i++) {
    qarrs.push_back(new StatQubitFixture{});
  }

  sim->registerComponent(qubit);
  sim->registerComponent(another_qubit);
  for (auto q : qarrs) {
    sim->registerComponent(q);
  }

  // Bell pair
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    another_qubit->reset();
    qubit->addEdge(another_qubit);
    qubit->setVertexOperator(quisp::types::CliffordOperator::Id);

    auto result_left = qubit->graphMeasureZ();
    EXPECT_TRUE(qubit->getNeighborSet().empty());
    EXPECT_TRUE(another_qubit->getNeighborSet().empty());
    auto result_right = another_qubit->graphMeasureZ();
    EXPECT_EQ(result_left, result_right);
  }

  // GHZ state measure in Z; star graph; measure from center
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    qubit->setVertexOperator(quisp::types::CliffordOperator::Id);
    for (auto v : qarrs) {
      v->reset();
      v->addEdge(qubit);
      v->setVertexOperator(quisp::types::CliffordOperator::H);
    }
    std::vector<quisp::types::EigenvalueResult> measurement_result;

    measurement_result.push_back(qubit->graphMeasureZ());

    // check that all nodes now isolated
    EXPECT_TRUE(qubit->getNeighborSet().empty());
    for (auto v : qarrs) {
      EXPECT_TRUE(v->getNeighborSet().empty());
    }

    for (auto v : qarrs) {
      measurement_result.push_back(v->measureZ());
    }
    for (auto r : measurement_result) {
      EXPECT_EQ(r, measurement_result[0]);
    }
  }

  // GHZ state measure in Z; star graph; measure center last
  for (int i = 0; i < 1000; i++) {
    qubit->reset();
    qubit->setVertexOperator(quisp::types::CliffordOperator::Id);
    for (auto v : qarrs) {
      v->reset();
      v->addEdge(qubit);
      v->setVertexOperator(quisp::types::CliffordOperator::H);
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
      measurement_result.push_back(v->measureZ());
    }
    measurement_result.push_back(qubit->graphMeasureZ());
    for (auto r : measurement_result) {
      EXPECT_EQ(r, measurement_result[0]);
    }
  }
}
}  // end namespace