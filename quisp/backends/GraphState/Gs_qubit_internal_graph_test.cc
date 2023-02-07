#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>
#include "Qubit.h"
#include "backends/GraphState/Backend.h"
#include "omnetpp/cexception.h"
#include "omnetpp/simtime.h"
#include "test.h"
namespace {
using namespace quisp_test::backends::graph_state;
using namespace quisp::backends::graph_state;
using namespace quisp::backends::graph_state::types;

class GsQubitInternalGraphTest : public ::testing::Test {
 protected:
  void SetUp() {
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<StationaryQubitConfiguration>());
    qubit = dynamic_cast<Qubit *>(backend->createQubit(1));
    another_qubit = dynamic_cast<Qubit *>(backend->createQubit(2));
    shared_neighbor = dynamic_cast<Qubit *>(backend->createQubit(3));
    center_qubit = dynamic_cast<Qubit *>(backend->createQubit(4));
    qubit_to_avoid = dynamic_cast<Qubit *>(backend->createQubit(5));
    isolated_qubit = dynamic_cast<Qubit *>(backend->createQubit(6));
    qubit->fillParams();
    another_qubit->fillParams();
    shared_neighbor->fillParams();
    center_qubit->fillParams();
    qubit_to_avoid->fillParams();
    isolated_qubit->fillParams();
  }
  Qubit *qubit;
  Qubit *another_qubit;
  Qubit *shared_neighbor;
  Qubit *center_qubit;
  Qubit *qubit_to_avoid;
  Qubit *isolated_qubit;
  std::unique_ptr<Backend> backend;
  TestRNG *rng;
};

TEST_F(GsQubitInternalGraphTest, AddEdge) {
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

TEST_F(GsQubitInternalGraphTest, isNeighbor) {
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

TEST_F(GsQubitInternalGraphTest, DeleteEdge) {
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

TEST_F(GsQubitInternalGraphTest, ToggleEdge) {
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

TEST_F(GsQubitInternalGraphTest, removeAllEdges) {
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

TEST_F(GsQubitInternalGraphTest, applyClifford) {
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

TEST_F(GsQubitInternalGraphTest, applyRightClifford) {
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

TEST_F(GsQubitInternalGraphTest, localComplement) {
  std::vector<Qubit *> first_layer_qubits;
  std::vector<Qubit *> second_layer_qubits;

  for (int i = 0; i < 10; i++) {
    first_layer_qubits.push_back(dynamic_cast<Qubit *>(backend->createQubit(i + 10)));
    second_layer_qubits.push_back(dynamic_cast<Qubit *>(backend->createQubit(i + 20)));
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

TEST_F(GsQubitInternalGraphTest, removeVertexOperationResultShouldBeinIdentity) {
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

TEST_F(GsQubitInternalGraphTest, removeVertexOperationForGroupZ) {
  std::vector<CliffordOperator> clifford_z_group = {CliffordOperator::Id, CliffordOperator::S, CliffordOperator::S_INV, CliffordOperator::Z};

  // apply RZ to qubit. qubit_to_avoid should not be affected by it
  for (int vop = 0; vop < 24; vop++) {
    for (int i = 0; i < 4; i++) {
      qubit->reset();
      another_qubit->reset();
      qubit_to_avoid->reset();
      qubit->addEdge(qubit_to_avoid);
      qubit->addEdge(another_qubit);
      qubit_to_avoid->setVertexOperator((CliffordOperator)vop);
      qubit->setVertexOperator(clifford_z_group[i]);
      qubit->removeVertexOperation(qubit_to_avoid);
      EXPECT_EQ(qubit_to_avoid->getVertexOperator(), (CliffordOperator)vop);
    }
  }
}

TEST_F(GsQubitInternalGraphTest, removeVertexOperationForGroupX) {
  std::vector<CliffordOperator> clifford_x_group = {CliffordOperator::Id, CliffordOperator::X, CliffordOperator::RX_INV, CliffordOperator::RX};
  // apply RX to qubit. qubit_to_avoid should be left in Z
  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(CliffordOperator::Id);
  qubit->setVertexOperator(CliffordOperator::Id);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), CliffordOperator::Id);

  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(CliffordOperator::Id);
  qubit->setVertexOperator(CliffordOperator::RX);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), CliffordOperator::S);

  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(CliffordOperator::Id);
  qubit->setVertexOperator(CliffordOperator::RX_INV);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), CliffordOperator::S_INV);

  qubit->reset();
  another_qubit->reset();
  qubit_to_avoid->reset();
  qubit->addEdge(qubit_to_avoid);
  qubit->addEdge(another_qubit);
  qubit_to_avoid->setVertexOperator(CliffordOperator::Id);
  qubit->setVertexOperator(CliffordOperator::X);
  qubit->removeVertexOperation(qubit_to_avoid);
  EXPECT_EQ(qubit_to_avoid->getVertexOperator(), CliffordOperator::Z);
}

TEST_F(GsQubitInternalGraphTest, removeVertexOperation_QubitToAvoidShouldStaysInGroupZ) {
  std::vector<CliffordOperator> clifford_z_group = {CliffordOperator::Id, CliffordOperator::S, CliffordOperator::S_INV, CliffordOperator::Z};
  // if qubit_to_avoid starts in Z; it should still be in Z
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int k = 0; k < 4; k++) {
        qubit->reset();
        another_qubit->reset();
        qubit_to_avoid->reset();
        qubit->addEdge(another_qubit);
        qubit->addEdge(qubit_to_avoid);
        qubit->setVertexOperator((CliffordOperator)i);
        another_qubit->setVertexOperator((CliffordOperator)j);
        qubit_to_avoid->setVertexOperator(clifford_z_group[k]);
        qubit->removeVertexOperation(qubit_to_avoid);
        EXPECT_THAT(clifford_z_group, testing::Contains(qubit_to_avoid->vertex_operator));
      }
    }
  }
}

TEST_F(GsQubitInternalGraphTest, Phiplus_Measure_in_ZZ) {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      qubit->reset();
      qubit->fillParams();
      another_qubit->reset();
      another_qubit->fillParams();

      qubit->addEdge(another_qubit);
      qubit->vertex_operator = CliffordOperator::Id;
      rng->double_value = (double)i / 100;
      auto result_left = qubit->measureZ();
      rng->double_value = (double)j / 100;
      auto result_right = another_qubit->measureZ();
      EXPECT_EQ(result_left, result_right);
    }
  }

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      qubit->reset();
      qubit->fillParams();
      another_qubit->reset();
      another_qubit->fillParams();

      qubit->addEdge(another_qubit);
      another_qubit->vertex_operator = CliffordOperator::Id;
      rng->double_value = (double)i / 100;
      auto result_left = qubit->measureZ();
      rng->double_value = (double)j / 100;
      auto result_right = another_qubit->measureZ();
      EXPECT_EQ(result_left, result_right);
    }
  }
}

TEST_F(GsQubitInternalGraphTest, Phiplus_Measure_in_XX) {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      qubit->reset();
      qubit->fillParams();
      another_qubit->reset();
      another_qubit->fillParams();

      qubit->addEdge(another_qubit);
      qubit->vertex_operator = CliffordOperator::Id;
      another_qubit->vertex_operator = CliffordOperator::H;
      rng->double_value = (double)i / 100;
      auto result_left = qubit->measureX();
      rng->double_value = (double)j / 100;
      auto result_right = another_qubit->measureX();
      EXPECT_EQ(result_left, result_right);
    }
  }
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      qubit->reset();
      qubit->fillParams();
      another_qubit->reset();
      another_qubit->fillParams();

      qubit->addEdge(another_qubit);
      another_qubit->vertex_operator = CliffordOperator::Id;
      qubit->vertex_operator = CliffordOperator::H;
      rng->double_value = (double)i / 100;

      auto c1 = qubit->vertex_operator;
      auto c2 = another_qubit->vertex_operator;

      auto result_left = qubit->measureX();
      rng->double_value = (double)j / 100;
      auto result_right = another_qubit->measureX();
      EXPECT_EQ(result_left, result_right);
    }
  }
}

TEST_F(GsQubitInternalGraphTest, Phiplus_Measure_in_YY) {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      qubit->reset();
      qubit->fillParams();
      another_qubit->reset();
      another_qubit->fillParams();

      qubit->addEdge(another_qubit);
      qubit->vertex_operator = CliffordOperator::Id;
      rng->double_value = (double)i / 100;
      auto result_left = qubit->measureY();
      rng->double_value = (double)j / 100;
      auto result_right = another_qubit->measureY();
      EXPECT_NE(result_left, result_right);
    }
  }
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      qubit->reset();
      qubit->fillParams();
      another_qubit->reset();
      another_qubit->fillParams();

      qubit->addEdge(another_qubit);
      another_qubit->vertex_operator = CliffordOperator::Id;
      rng->double_value = (double)i / 100;
      auto result_left = qubit->measureY();
      rng->double_value = (double)j / 100;
      auto result_right = another_qubit->measureY();
      EXPECT_NE(result_left, result_right);
    }
  }
}

TEST_F(GsQubitInternalGraphTest, purifyX_Phiplus_Phiplus_Measure_in_ZZ) {
  auto *alice_keep = static_cast<Qubit *>(backend->createQubit(11));
  auto *alice_trash = static_cast<Qubit *>(backend->createQubit(12));
  auto *bob_keep = static_cast<Qubit *>(backend->createQubit(13));
  auto *bob_trash = static_cast<Qubit *>(backend->createQubit(14));

  // measure in order
  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= 2; j++) {
      for (int m = 1; m < 100; m++) {
        for (int n = 1; n < 100; n++) {
          alice_keep->reset();
          alice_trash->reset();
          bob_keep->reset();
          bob_trash->reset();
          alice_keep->fillParams();
          alice_trash->fillParams();
          bob_keep->fillParams();
          bob_trash->fillParams();

          alice_keep->addEdge(bob_keep);
          alice_keep->vertex_operator = CliffordOperator::Id;
          alice_trash->addEdge(bob_trash);
          alice_trash->vertex_operator = CliffordOperator::Id;

          alice_keep->gateCNOT(alice_trash);
          bob_keep->gateCNOT(bob_trash);

          rng->double_value = (double)i / 3;
          auto alice_result = alice_trash->measureZ();
          rng->double_value = (double)j / 3;
          auto bob_result = bob_trash->measureZ();

          EXPECT_EQ(alice_result, bob_result);

          // expect a bell pair
          EXPECT_EQ(alice_keep->neighbors.size(), 1);
          EXPECT_EQ(bob_keep->neighbors.size(), 1);
          EXPECT_TRUE(alice_keep->isNeighbor(bob_keep));
          EXPECT_TRUE(bob_keep->isNeighbor(alice_keep));

          rng->double_value = double(m) / 100;
          alice_result = alice_keep->measureZ();
          rng->double_value = double(n) / 100;
          bob_result = alice_keep->measureZ();
          EXPECT_EQ(alice_result, bob_result);
        }
      }
    }
  }

  // measure out of order
  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= 2; j++) {
      for (int m = 0; m < 100; m++) {
        for (int n = 0; n < 100; n++) {
          alice_keep->reset();
          alice_trash->reset();
          bob_keep->reset();
          bob_trash->reset();
          alice_keep->fillParams();
          alice_trash->fillParams();
          bob_keep->fillParams();
          bob_trash->fillParams();

          alice_keep->addEdge(bob_keep);
          alice_keep->vertex_operator = CliffordOperator::Id;
          alice_trash->addEdge(bob_trash);
          alice_trash->vertex_operator = CliffordOperator::Id;

          auto alk = alice_keep->vertex_operator;
          auto alt = alice_trash->vertex_operator;
          auto bk = bob_keep->vertex_operator;
          auto bt = bob_trash->vertex_operator;

          alice_keep->gateCNOT(alice_trash);

          alk = alice_keep->vertex_operator;
          alt = alice_trash->vertex_operator;
          bk = bob_keep->vertex_operator;
          bt = bob_trash->vertex_operator;

          rng->double_value = (double)i / 3;
          auto alice_result = alice_trash->measureZ();

          alk = alice_keep->vertex_operator;
          alt = alice_trash->vertex_operator;
          bk = bob_keep->vertex_operator;
          bt = bob_trash->vertex_operator;

          bob_keep->gateCNOT(bob_trash);

          EXPECT_EQ(bob_trash->neighbors.size(), 0);
          EXPECT_EQ(alice_keep->neighbors.size(), 1);
          EXPECT_EQ(bob_keep->neighbors.size(), 1);
          EXPECT_TRUE(alice_keep->isNeighbor(bob_keep));
          EXPECT_TRUE(bob_keep->isNeighbor(alice_keep));

          rng->double_value = (double)j / 3;
          auto bob_result = bob_trash->measureZ();

          EXPECT_EQ(alice_result, bob_result);

          // expect a bell pair
          EXPECT_EQ(alice_keep->neighbors.size(), 1);
          EXPECT_EQ(bob_keep->neighbors.size(), 1);
          EXPECT_TRUE(alice_keep->isNeighbor(bob_keep));
          EXPECT_TRUE(bob_keep->isNeighbor(alice_keep));

          rng->double_value = double(m) / 100;
          alice_result = alice_keep->measureZ();
          rng->double_value = double(n) / 100;
          bob_result = alice_keep->measureZ();
          EXPECT_EQ(alice_result, bob_result);
        }
      }
    }
  }
}

TEST_F(GsQubitInternalGraphTest, purifyX_Phiplus_Phiplus_Measure_in_XX) {
  auto *alice_keep = static_cast<Qubit *>(backend->createQubit(11));
  auto *alice_trash = static_cast<Qubit *>(backend->createQubit(12));
  auto *bob_keep = static_cast<Qubit *>(backend->createQubit(13));
  auto *bob_trash = static_cast<Qubit *>(backend->createQubit(14));

  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= 2; j++) {
      for (int m = 0; m < 100; m++) {
        for (int n = 0; n < 100; n++) {
          alice_keep->reset();
          alice_trash->reset();
          bob_keep->reset();
          bob_trash->reset();
          alice_keep->fillParams();
          alice_trash->fillParams();
          bob_keep->fillParams();
          bob_trash->fillParams();

          alice_keep->addEdge(bob_keep);
          alice_keep->vertex_operator = CliffordOperator::Id;
          alice_trash->addEdge(bob_trash);
          alice_trash->vertex_operator = CliffordOperator::Id;

          alice_keep->gateCNOT(alice_trash);
          bob_keep->gateCNOT(bob_trash);

          rng->double_value = (double)i / 3;
          auto alice_result = alice_trash->measureZ();
          rng->double_value = (double)j / 3;
          auto bob_result = bob_trash->measureZ();

          EXPECT_EQ(alice_result, bob_result);

          // expect a bell pair
          EXPECT_EQ(alice_keep->neighbors.size(), 1);
          EXPECT_EQ(bob_keep->neighbors.size(), 1);
          EXPECT_TRUE(alice_keep->isNeighbor(bob_keep));
          EXPECT_TRUE(bob_keep->isNeighbor(alice_keep));

          auto c1 = alice_keep->vertex_operator;
          auto c2 = bob_keep->vertex_operator;
          if (c2 < c1) std::swap(c1, c2);
          EXPECT_EQ(c1, CliffordOperator::Id);
          EXPECT_EQ(c2, CliffordOperator::H);

          rng->double_value = double(m) / 100;
          alice_result = alice_keep->measureX();
          rng->double_value = double(n) / 100;
          bob_result = bob_keep->measureX();
          EXPECT_EQ(alice_result, bob_result);
        }
      }
    }
  }
}

TEST_F(GsQubitInternalGraphTest, purifyX_Phiplus_Phiplus_Measure_in_YY) {
  auto *alice_keep = static_cast<Qubit *>(backend->createQubit(11));
  auto *alice_trash = static_cast<Qubit *>(backend->createQubit(12));
  auto *bob_keep = static_cast<Qubit *>(backend->createQubit(13));
  auto *bob_trash = static_cast<Qubit *>(backend->createQubit(14));

  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j <= 2; j++) {
      for (int m = 0; m < 100; m++) {
        for (int n = 0; n < 100; n++) {
          alice_keep->reset();
          alice_trash->reset();
          bob_keep->reset();
          bob_trash->reset();
          alice_keep->fillParams();
          alice_trash->fillParams();
          bob_keep->fillParams();
          bob_trash->fillParams();

          alice_keep->addEdge(bob_keep);
          alice_keep->vertex_operator = CliffordOperator::Id;
          alice_trash->addEdge(bob_trash);
          alice_trash->vertex_operator = CliffordOperator::Id;

          alice_keep->gateCNOT(alice_trash);
          bob_keep->gateCNOT(bob_trash);

          rng->double_value = (double)i / 3;
          auto alice_result = alice_trash->measureZ();
          rng->double_value = (double)j / 3;
          auto bob_result = bob_trash->measureZ();

          EXPECT_EQ(alice_result, bob_result);

          // expect a bell pair
          EXPECT_EQ(alice_keep->neighbors.size(), 1);
          EXPECT_EQ(bob_keep->neighbors.size(), 1);
          EXPECT_TRUE(alice_keep->isNeighbor(bob_keep));
          EXPECT_TRUE(bob_keep->isNeighbor(alice_keep));

          auto c1 = alice_keep->vertex_operator;
          auto c2 = bob_keep->vertex_operator;
          if (c2 < c1) std::swap(c1, c2);
          EXPECT_EQ(c1, CliffordOperator::Id);
          EXPECT_EQ(c2, CliffordOperator::H);

          rng->double_value = double(m) / 100;
          alice_result = alice_keep->measureY();
          rng->double_value = double(n) / 100;
          bob_result = bob_keep->measureY();
          EXPECT_NE(alice_result, bob_result);
        }
      }
    }
  }
}

TEST_F(GsQubitInternalGraphTest, graphMeasureZIsolatedQubit) {
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

TEST_F(GsQubitInternalGraphTest, graphMeasureZGHZStatePlusEigenvalue) {
  std::vector<Qubit *> qarrs;
  for (int i = 0; i < 10; i++) {
    qarrs.push_back(dynamic_cast<Qubit *>(backend->createQubit(i + 50)));
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
      measurement_result.push_back(v->graphMeasureZ());
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
      measurement_result.push_back(v->graphMeasureZ());
    }
    measurement_result.push_back(qubit->graphMeasureZ());
    for (auto r : measurement_result) {
      EXPECT_EQ(r, measurement_result[0]);
    }
  }
}
TEST_F(GsQubitInternalGraphTest, graphMeasureZGHZStateMinusEigenvalue) {
  std::vector<Qubit *> qarrs;
  rng->double_value = 0.5;
  for (int i = 0; i < 10; i++) {
    qarrs.push_back(dynamic_cast<Qubit *>(backend->createQubit(i + 100)));
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
      measurement_result.push_back(v->graphMeasureZ());
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
      measurement_result.push_back(v->graphMeasureZ());
    }
    measurement_result.push_back(qubit->graphMeasureZ());
    for (auto r : measurement_result) {
      EXPECT_EQ(r, measurement_result[0]);
    }
  }
}
}  // end namespace
