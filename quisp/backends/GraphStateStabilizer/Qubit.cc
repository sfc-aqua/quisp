#include "Qubit.h"
#include "types.h"

namespace quisp::backends::graph_state_stabilizer {
using types::CliffordOperator;
GraphStateStabilizerQubit::GraphStateStabilizerQubit(const IQubitId *id, GraphStateStabilizerBackend *const backend) : id(id), backend(backend) {
  // initialize variables for graph state representation tracking
  vertex_operator = CliffordOperator::H;
}
GraphStateStabilizerQubit::~GraphStateStabilizerQubit() {}
void GraphStateStabilizerQubit::setFree() {}
void GraphStateStabilizerQubit::applyClifford(types::CliffordOperator op) { this->vertex_operator = clifford_application_lookup[(int)op][(int)(this->vertex_operator)]; }

void GraphStateStabilizerQubit::applyRightClifford(types::CliffordOperator op) { this->vertex_operator = clifford_application_lookup[(int)(this->vertex_operator)][(int)op]; }

bool GraphStateStabilizerQubit::isNeighbor(GraphStateStabilizerQubit *another_qubit) { return this->neighbors.find(another_qubit) != this->neighbors.end(); }

void GraphStateStabilizerQubit::addEdge(GraphStateStabilizerQubit *another_qubit) {
  if (another_qubit == this) throw std::runtime_error("adding edge to self is not allowed");
  this->neighbors.insert(another_qubit);
  another_qubit->neighbors.insert(this);
}

void GraphStateStabilizerQubit::deleteEdge(GraphStateStabilizerQubit *another_qubit) {
  this->neighbors.erase(another_qubit);
  another_qubit->neighbors.erase(this);
}

void GraphStateStabilizerQubit::toggleEdge(GraphStateStabilizerQubit *another_qubit) {
  if (this->isNeighbor(another_qubit)) {
    this->deleteEdge(another_qubit);
  } else {
    this->addEdge(another_qubit);
  }
}

void GraphStateStabilizerQubit::removeAllEdges() {
  for (auto *v : this->neighbors) {
    v->neighbors.erase(this);
  }
  this->neighbors.clear();
}

void GraphStateStabilizerQubit::localComplement() {
  auto it_end = this->neighbors.end();
  for (auto it_u = this->neighbors.begin(); it_u != it_end; it_u++) {
    auto it_v = std::next(it_u);
    for (; it_v != it_end; it_v++) {
      (*it_u)->toggleEdge(*it_v);
    }
  }
  for (auto *v : this->neighbors) {
    v->applyRightClifford(CliffordOperator::S);
  }
  this->applyRightClifford(CliffordOperator::RX_INV);
}

void GraphStateStabilizerQubit::removeVertexOperation(GraphStateStabilizerQubit *qubit_to_avoid) {
  if (this->neighbors.empty() || this->vertex_operator == types::CliffordOperator::Id) {
    return;
  }
  auto *swapping_partner_temp = qubit_to_avoid;
  for (auto *v : this->neighbors) {
    if (v != qubit_to_avoid) {
      swapping_partner_temp = v;
      break;
    }
  }
  auto swapping_partner = swapping_partner_temp;
  std::string decomposition_string = decomposition_table[(int)this->vertex_operator];
  for (int i = decomposition_string.size() - 1; i >= 0; i--) {
    if (decomposition_string[i] == 'V') {
      this->localComplement();
    } else {
      // 'U'
      swapping_partner->localComplement();
    }
  }
}

void GraphStateStabilizerQubit::applyPureCZ(GraphStateStabilizerQubit *another_qubit) {
  auto *aq = another_qubit;
  this->removeVertexOperation(aq);
  aq->removeVertexOperation(this);
  this->removeVertexOperation(aq);

  bool has_edge = this->isNeighbor(aq);
  int current_vop = (int)(this->vertex_operator);
  int aq_vop = (int)(aq->vertex_operator);
  this->vertex_operator = controlled_Z_lookup_node_1[has_edge][current_vop][aq_vop];
  aq->vertex_operator = controlled_Z_lookup_node_2[has_edge][current_vop][aq_vop];
  if (has_edge != controlled_Z_lookup_edge[has_edge][current_vop][aq_vop]) {
    this->toggleEdge(aq);
  }
}

EigenvalueResult GraphStateStabilizerQubit::graphMeasureZ() {
  auto vop = this->vertex_operator;
  auto result = EigenvalueResult::PLUS_ONE;
  if (this->neighbors.empty()) {
    switch (vop) {
      case CliffordOperator::H:
      case CliffordOperator::RY_INV:
      case CliffordOperator::S_INV_RY_INV:
      case CliffordOperator::S_RY_INV:
        break;
      case CliffordOperator::RY:
      case CliffordOperator::S_INV_RY:
      case CliffordOperator::S_RY:
      case CliffordOperator::Z_RY:
        result = EigenvalueResult::MINUS_ONE;
        break;
      default:
        result = (backend->dblrand() < 0.5) ? EigenvalueResult::PLUS_ONE : EigenvalueResult::MINUS_ONE;
    }
  } else {
    this->removeVertexOperation(this);  // nothing to be avoided
    result = (backend->dblrand() < 0.5) ? EigenvalueResult::PLUS_ONE : EigenvalueResult::MINUS_ONE;
    this->removeAllEdges();
  }
  this->vertex_operator = (result == EigenvalueResult::PLUS_ONE) ? CliffordOperator::H : CliffordOperator::RY;
  return result;
}

// public member functions

void GraphStateStabilizerQubit::gateCNOT(IQubit *const control_qubit) {
  // apply memory error
  this->applyClifford(CliffordOperator::H);  // use apply Clifford for pure operation
  this->applyPureCZ((GraphStateStabilizerQubit *)control_qubit);
  this->applyClifford(CliffordOperator::H);
  // apply CNOT error
}

void GraphStateStabilizerQubit::gateH() {
  // apply memory error
  this->applyClifford(CliffordOperator::H);
  // apply single qubit gate error
}
void GraphStateStabilizerQubit::gateZ() {
  // apply memory error
  this->applyClifford(CliffordOperator::Z);
  // apply single qubit gate error
}
void GraphStateStabilizerQubit::gateX() {
  // apply memory error
  this->applyClifford(CliffordOperator::X);
  // apply single qubit gate error
}
void GraphStateStabilizerQubit::gateS() {
  // apply memory error
  this->applyClifford(CliffordOperator::S);
  // apply single qubit gate error
}
void GraphStateStabilizerQubit::gateSdg() {
  // apply memory error
  this->applyClifford(CliffordOperator::S_INV);
  // apply single qubit gate error
}
void GraphStateStabilizerQubit::excite() {
  auto result = this->measureZ();
  if (result == EigenvalueResult::PLUS_ONE) {
    this->applyClifford(CliffordOperator::X);
  }
}
void GraphStateStabilizerQubit::relax() {
  auto result = this->measureZ();
  if (result == EigenvalueResult::MINUS_ONE) {
    this->applyClifford(CliffordOperator::X);
  }
}

EigenvalueResult GraphStateStabilizerQubit::measureX() {
  this->gateH();
  return this->measureZ();
}

EigenvalueResult GraphStateStabilizerQubit::measureY() {
  this->gateSdg();
  this->gateH();
  return this->measureZ();
}

EigenvalueResult GraphStateStabilizerQubit::measureZ() {
  // apply memory error
  auto result = this->graphMeasureZ();
  // apply measurement error
  return result;
}

// initialize static variables
CliffordOperator GraphStateStabilizerQubit::clifford_application_lookup[24][24] =
#include "clifford_application_lookup.tbl"
    ;

bool GraphStateStabilizerQubit::controlled_Z_lookup_edge[2][24][24] =
#include "cz_lookup_edge.tbl"
    ;

CliffordOperator GraphStateStabilizerQubit::controlled_Z_lookup_node_1[2][24][24] =
#include "cz_lookup_node_1.tbl"
    ;

CliffordOperator GraphStateStabilizerQubit::controlled_Z_lookup_node_2[2][24][24] =
#include "cz_lookup_node_2.tbl"
    ;

std::string GraphStateStabilizerQubit::decomposition_table[24] = {
    "", "VV", "UUVV", "UU", "VVV", "V", "VUU", "UUV", "UVUUU", "UUUVU", "UVVVU", "UVU", "U", "UUU", "VVU", "UVV", "UVVV", "UV", "UVUU", "UUUV", "VVVU", "VU", "VUUU", "UUVU",
};
}  // namespace quisp::backends::graph_state_stabilizer
