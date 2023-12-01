#include "Qubit.h"
#include <stdexcept>
#include <string>
#include "Backend.h"
#include "backends/interfaces/IQubit.h"
#include "backends/interfaces/IQubitId.h"
#include "types.h"

namespace quisp::backends::graph_state {
using types::CliffordOperator;
GraphStateQubit::GraphStateQubit(const IQubitId *id, GraphStateBackend *const backend, bool is_short_live)
    : memory_transition_matrix(MatrixXd::Zero(6, 6)), id(id), backend(backend), is_short_live(is_short_live) {
  // initialize variables for graph state representation tracking
  vertex_operator = CliffordOperator::H;
}

GraphStateQubit::~GraphStateQubit() {}

const IQubitId *const GraphStateQubit::getId() const { return id; }

void GraphStateQubit::relaseBackToPool() {
  if (!is_short_live) {
    throw std::runtime_error("cannot release non short-live qubit");
  }
  backend->returnToPool(this);
}

void GraphStateQubit::configure(std::unique_ptr<StationaryQubitConfiguration> c) {
  setMemoryErrorRates(c->memory_x_err_rate, c->memory_y_err_rate, c->memory_z_err_rate, c->memory_excitation_rate, c->memory_relaxation_rate);
  measurement_err.setParams(c->measurement_x_err_rate, c->measurement_y_err_rate, c->measurement_z_err_rate);
  gate_err_h.setParams(c->h_gate_x_err_ratio, c->h_gate_y_err_ratio, c->h_gate_z_err_ratio, c->h_gate_err_rate);
  gate_err_x.setParams(c->x_gate_x_err_ratio, c->x_gate_y_err_ratio, c->x_gate_z_err_ratio, c->x_gate_err_rate);
  gate_err_z.setParams(c->z_gate_x_err_ratio, c->z_gate_y_err_ratio, c->z_gate_z_err_ratio, c->z_gate_err_rate);
  gate_err_cnot.setParams(c->cnot_gate_err_rate, c->cnot_gate_ix_err_ratio, c->cnot_gate_xi_err_ratio, c->cnot_gate_xx_err_ratio, c->cnot_gate_iz_err_ratio,
                          c->cnot_gate_zi_err_ratio, c->cnot_gate_zz_err_ratio, c->cnot_gate_iy_err_ratio, c->cnot_gate_yi_err_ratio, c->cnot_gate_yy_err_ratio);
}
void GraphStateQubit::setMemoryErrorRates(double x_error_rate, double y_error_rate, double z_error_rate, double excitation_rate, double relaxation_rate) {
  memory_err.x_error_rate = x_error_rate;
  memory_err.y_error_rate = y_error_rate;
  memory_err.z_error_rate = z_error_rate;
  memory_err.excitation_error_rate = excitation_rate;
  memory_err.relaxation_error_rate = relaxation_rate;
  double error_rate = x_error_rate + y_error_rate + z_error_rate + excitation_rate + relaxation_rate;  // This is per μs.
  memory_err.error_rate = error_rate;
  // clang-format off
  memory_transition_matrix <<
    1 - error_rate,  x_error_rate,   z_error_rate,   y_error_rate,   excitation_rate,     relaxation_rate,
    x_error_rate,    1 - error_rate, y_error_rate,   z_error_rate,   excitation_rate,     relaxation_rate,
    z_error_rate,    y_error_rate,   1 - error_rate, x_error_rate,   excitation_rate,     relaxation_rate,
    y_error_rate,    z_error_rate,   x_error_rate,   1 - error_rate, excitation_rate,     relaxation_rate,
    0,               0,              0,              0,              1 - relaxation_rate, relaxation_rate,
    0,               0,              0,              0,              excitation_rate,     1 - excitation_rate;
  // clang-format on
}

void GraphStateQubit::applySingleQubitGateError(SingleGateErrorModel const &err) {
  if (err.pauli_error_rate == 0) {
    return;
  }

  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<ErrorLabel, double> weights = {
      {ErrorLabel::NO_ERR, 1 - err.pauli_error_rate}, {ErrorLabel::X, err.x_error_rate}, {ErrorLabel::Z, err.z_error_rate}, {ErrorLabel::Y, err.y_error_rate}};

  double rand = backend->dblrand();
  ErrorLabel r = samplingWithWeights(weights, rand);

  switch (r) {
    case ErrorLabel::NO_ERR:
      break;
    case ErrorLabel::X:
      this->applyClifford(CliffordOperator::X);
      break;
    case ErrorLabel::Z:
      this->applyClifford(CliffordOperator::Z);
      break;
    case ErrorLabel::Y:
      this->applyClifford(CliffordOperator::Y);
      break;
  }
}

void GraphStateQubit::applyTwoQubitGateError(TwoQubitGateErrorModel const &err, GraphStateQubit *another_qubit) {
  if (err.pauli_error_rate == 0) {
    return;
  }

  enum class ErrorLabel : int { NO_ERR, IX, XI, XX, IY, YI, YY, IZ, ZI, ZZ };
  std::map<ErrorLabel, double> weights{
      {ErrorLabel::NO_ERR, 1 - err.pauli_error_rate},
      {ErrorLabel::IX, err.ix_error_rate},
      {ErrorLabel::XI, err.xi_error_rate},
      {ErrorLabel::XX, err.xx_error_rate},
      {ErrorLabel::IY, err.iy_error_rate},
      {ErrorLabel::YI, err.yi_error_rate},
      {ErrorLabel::YY, err.yy_error_rate},
      {ErrorLabel::IZ, err.iz_error_rate},
      {ErrorLabel::ZI, err.zi_error_rate},
      {ErrorLabel::ZZ, err.zz_error_rate},
  };
  double rand = backend->dblrand();
  ErrorLabel r = samplingWithWeights(weights, rand);

  switch (r) {
    case ErrorLabel::NO_ERR:
      break;
    case ErrorLabel::IX:
      this->applyClifford(CliffordOperator::X);
      break;
    case ErrorLabel::XI:
      another_qubit->applyClifford(CliffordOperator::X);
      break;
    case ErrorLabel::XX:
      this->applyClifford(CliffordOperator::X);
      another_qubit->applyClifford(CliffordOperator::X);
      break;
    case ErrorLabel::IZ:
      this->applyClifford(CliffordOperator::Z);
      break;
    case ErrorLabel::ZI:
      another_qubit->applyClifford(CliffordOperator::Z);
      break;
    case ErrorLabel::ZZ:
      this->applyClifford(CliffordOperator::Z);
      another_qubit->applyClifford(CliffordOperator::Z);
      break;
    case ErrorLabel::IY:
      this->applyClifford(CliffordOperator::Y);
      break;
    case ErrorLabel::YI:
      another_qubit->applyClifford(CliffordOperator::Y);
      break;
    case ErrorLabel::YY:
      this->applyClifford(CliffordOperator::Y);
      another_qubit->applyClifford(CliffordOperator::Y);
      break;
  }
}

void GraphStateQubit::applyMemoryError() {
  // If no memory error occurs, skip this memory error simulation.
  if (memory_err.error_rate == 0) return;

  SimTime current_time = backend->getSimTime();

  // Check when the error got updated last time.
  // Errors will be performed depending on the difference between that time and the current time.
  double time_evolution = current_time.dbl() - updated_time.dbl();
  double time_evolution_microsec = time_evolution * 1000000 /** 100*/;
  if (time_evolution_microsec > 0) {
    bool skip_exponentiation = false;
    for (int i = 0; i < memory_transition_matrix.cols(); i++) {
      if (memory_transition_matrix(0, i) == 1) {
        // Do not to the exponentiation! Eigen will mess up the exponentiation anyway...
        skip_exponentiation = true;
        break;
      }
    }

    MatrixXd transition_mat(6, 6);
    if (!skip_exponentiation) {
      // calculate time evoluted error matrix: Q^(time_evolution_microsec) in Eq 5.3
      MatrixPower<MatrixXd> q_pow(memory_transition_matrix);
      transition_mat = q_pow(time_evolution_microsec);
    } else {
      transition_mat = memory_transition_matrix;
    }

    // validate transition_mat
    for (int r = 0; r < transition_mat.rows(); r++) {
      double col_sum = 0;
      for (int i = 0; i < transition_mat.cols(); i++) {
        col_sum += transition_mat(r, i);
      }
      if (col_sum > 1.01 || col_sum < 0.99) {
        throw std::runtime_error("Row of the transition matrix does not sum up to 1.");
      }
    }

    if (std::isnan(transition_mat(0, 0))) {
      throw std::runtime_error("Transition matrix is NaN. This is Eigen's fault.");
    }

    MatrixXd pi_vector(1, 6);
    pi_vector << 1, 0, 0, 0, 0, 0;
    // pi(t) in Eq 5.3
    // Clean, X, Z, Y, Excited, Relaxed
    // take error rate vector from DynamicTransitionMatrix Eq 5.3
    pi_vector = pi_vector * transition_mat;

    enum class ErrorLabel { NO_ERR, X, Z, Y, Excitation, Relaxation };
    std::map<ErrorLabel, double> weights = {{ErrorLabel::NO_ERR, pi_vector(0, 0)}, {ErrorLabel::X, pi_vector(0, 1)},          {ErrorLabel::Z, pi_vector(0, 2)},
                                            {ErrorLabel::Y, pi_vector(0, 3)},      {ErrorLabel::Excitation, pi_vector(0, 4)}, {ErrorLabel::Relaxation, pi_vector(0, 5)}};

    double rand = backend->dblrand();
    ErrorLabel r = samplingWithWeights(weights, rand);

    switch (r) {
      case ErrorLabel::NO_ERR:
        break;
      case ErrorLabel::X:
        this->applyClifford(CliffordOperator::X);
        break;
      case ErrorLabel::Z:
        this->applyClifford(CliffordOperator::Z);
        break;
      case ErrorLabel::Y:
        this->applyClifford(CliffordOperator::X);
        this->applyClifford(CliffordOperator::Z);
        break;
      case ErrorLabel::Excitation:
        this->excite();
        break;
      case ErrorLabel::Relaxation:
        this->relax();
        break;
      default:
          // Memory completely mixed error
          // This should never happen
          ;
    }
  }
  updated_time = current_time;
}

void GraphStateQubit::excite() {
  // check if it is correct
  auto result = this->graphMeasureZ();
  if (result == EigenvalueResult::PLUS_ONE) {
    this->applyClifford(CliffordOperator::X);
  }
}

void GraphStateQubit::relax() {
  // check if it is correct
  auto result = this->graphMeasureZ();
  if (result == EigenvalueResult::MINUS_ONE) {
    this->applyClifford(CliffordOperator::X);
  }
}

void GraphStateQubit::applyClifford(CliffordOperator op) { this->vertex_operator = clifford_application_lookup[(int)op][(int)(this->vertex_operator)]; }

void GraphStateQubit::applyRightClifford(CliffordOperator op) { this->vertex_operator = clifford_application_lookup[(int)(this->vertex_operator)][(int)op]; }

bool GraphStateQubit::isNeighbor(GraphStateQubit *another_qubit) { return this->neighbors.find(another_qubit) != this->neighbors.end(); }

void GraphStateQubit::addEdge(GraphStateQubit *another_qubit) {
  if (another_qubit == this) throw std::runtime_error("adding edge to self is not allowed");
  this->neighbors.insert(another_qubit);
  another_qubit->neighbors.insert(this);
}

void GraphStateQubit::deleteEdge(GraphStateQubit *another_qubit) {
  this->neighbors.erase(another_qubit);
  another_qubit->neighbors.erase(this);
}

void GraphStateQubit::toggleEdge(GraphStateQubit *another_qubit) {
  if (this->isNeighbor(another_qubit)) {
    this->deleteEdge(another_qubit);
  } else {
    this->addEdge(another_qubit);
  }
}

void GraphStateQubit::removeAllEdges() {
  for (auto *v : neighbors) {
    v->neighbors.erase(this);
  }
  this->neighbors.clear();
}

void GraphStateQubit::localComplement() {
  // this should work and not interfere with iterating orders
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

void GraphStateQubit::removeVertexOperation(GraphStateQubit *qubit_to_avoid) {
  if (this->neighbors.empty() || this->vertex_operator == CliffordOperator::Id) {
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

void GraphStateQubit::applyPureCZ(GraphStateQubit *another_qubit) {
  // clang-format off
  if ((this->isNeighbor(another_qubit) && this->neighbors.size() > 1) ||
      (!this->isNeighbor(another_qubit) && this->neighbors.size() > 0))
      this->removeVertexOperation(another_qubit);
  if ((another_qubit->isNeighbor(this) && another_qubit->neighbors.size() > 1) ||
      (!another_qubit->isNeighbor(this) && another_qubit->neighbors.size() > 0))
      another_qubit->removeVertexOperation(this);
  if ((this->isNeighbor(another_qubit) && this->neighbors.size() > 1) ||
      (!this->isNeighbor(another_qubit) && this->neighbors.size() > 0))
      this->removeVertexOperation(another_qubit);
  // clang-format on

  bool has_edge = this->isNeighbor(another_qubit);
  int current_vop = (int)(this->vertex_operator);
  int aq_vop = (int)(another_qubit->vertex_operator);
  this->vertex_operator = controlled_z_lookup_node_1[has_edge][current_vop][aq_vop];
  another_qubit->vertex_operator = controlled_z_lookup_node_2[has_edge][current_vop][aq_vop];
  if (has_edge != controlled_z_lookup_edge[has_edge][current_vop][aq_vop]) {
    this->toggleEdge(another_qubit);
  }
}

EigenvalueResult GraphStateQubit::graphMeasureZ() {
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
    if (result == EigenvalueResult::MINUS_ONE) {
      for (auto *v : neighbors) {
        v->applyRightClifford(CliffordOperator::Z);
      }
    }
    this->removeAllEdges();
  }
  this->vertex_operator = (result == EigenvalueResult::PLUS_ONE) ? CliffordOperator::H : CliffordOperator::RY;
  return result;
}

EigenvalueResult GraphStateQubit::graphMeasureZ(const EigenvalueResult eigenvalue) {
  auto vop = this->vertex_operator;
  if (this->neighbors.empty()) {
    bool resultMustBePlus = (vop == CliffordOperator::H || vop == CliffordOperator::RY_INV || vop == CliffordOperator::S_INV_RY_INV || vop == CliffordOperator::S_RY_INV);
    bool resultMustBeMinus = (vop == CliffordOperator::RY || vop == CliffordOperator::S_INV_RY || vop == CliffordOperator::S_RY || vop == CliffordOperator::Z_RY);
    if ((eigenvalue == EigenvalueResult::PLUS_ONE && resultMustBeMinus) || (eigenvalue == EigenvalueResult::MINUS_ONE && resultMustBePlus))
      std::runtime_error("graphMeasureZ:: cannot force isolated qubit with specified result");
  } else {
    this->removeVertexOperation(this);  // nothing to be avoided
    if (eigenvalue == EigenvalueResult::MINUS_ONE) {
      for (auto *v : neighbors) {
        v->applyRightClifford(CliffordOperator::Z);
      }
    }
    this->removeAllEdges();
  }
  return eigenvalue;
}

// public member functions

void GraphStateQubit::setFree() {
  // force qubit to be in |0> state
  this->graphMeasureZ();
  this->vertex_operator = CliffordOperator::H;
  updated_time = backend->getSimTime();
}

void GraphStateQubit::gateCNOT(IQubit *const target_qubit) {
  auto gs_target_qubit = dynamic_cast<GraphStateQubit *>(target_qubit);
  this->applyMemoryError();
  gs_target_qubit->applyMemoryError();
  gs_target_qubit->noiselessH();
  this->applyPureCZ(gs_target_qubit);
  gs_target_qubit->noiselessH();
  this->applyTwoQubitGateError(gate_err_cnot, gs_target_qubit);
}

void GraphStateQubit::gateH() {
  this->applyMemoryError();
  this->applyClifford(CliffordOperator::H);
  this->applySingleQubitGateError(gate_err_h);
}
void GraphStateQubit::gateZ() {
  this->applyMemoryError();
  this->applyClifford(CliffordOperator::Z);
  this->applySingleQubitGateError(gate_err_z);
}
void GraphStateQubit::gateX() {
  this->applyMemoryError();
  this->applyClifford(CliffordOperator::X);
  this->applySingleQubitGateError(gate_err_x);
}
void GraphStateQubit::gateY() {
  this->applyMemoryError();
  this->applyClifford(CliffordOperator::Y);
  // TODO: add single qubit error gate for Y?
  this->applySingleQubitGateError(gate_err_x);
}
void GraphStateQubit::gateS() {
  this->applyMemoryError();
  this->applyClifford(CliffordOperator::S);
  // apply s error, not implemented yet
  // or do we need to expose this gate to stat qubit?
}
void GraphStateQubit::gateSdg() {
  this->applyMemoryError();
  this->applyClifford(CliffordOperator::S_INV);
  // apply sdg error, not implemented yet
  // or do we need to expose this gate to stat qubit?
}

EigenvalueResult GraphStateQubit::measureX() {
  applyMemoryError();
  this->applyClifford(CliffordOperator::H);
  auto result = this->graphMeasureZ();
  // measurement error
  if (backend->dblrand() < this->measurement_err.x_error_rate) {
    result = result == EigenvalueResult::PLUS_ONE ? EigenvalueResult::MINUS_ONE : EigenvalueResult::PLUS_ONE;
  }
  return result;
}

EigenvalueResult GraphStateQubit::measureY() {
  applyMemoryError();
  this->applyClifford(CliffordOperator::S_INV);
  this->applyClifford(CliffordOperator::H);
  auto result = this->graphMeasureZ();
  // measurement error
  if (backend->dblrand() < this->measurement_err.y_error_rate) {
    result = result == EigenvalueResult::PLUS_ONE ? EigenvalueResult::MINUS_ONE : EigenvalueResult::PLUS_ONE;
  }
  return result;
}

EigenvalueResult GraphStateQubit::measureZ() {
  applyMemoryError();
  auto result = this->graphMeasureZ();
  // measurement error
  if (backend->dblrand() < this->measurement_err.z_error_rate) {
    result = result == EigenvalueResult::PLUS_ONE ? EigenvalueResult::MINUS_ONE : EigenvalueResult::PLUS_ONE;
  }
  return result;
}

void GraphStateQubit::noiselessX() { applyClifford(CliffordOperator::X); }
void GraphStateQubit::noiselessZ() { applyClifford(CliffordOperator::Z); }
void GraphStateQubit::noiselessH() { applyClifford(CliffordOperator::H); }
void GraphStateQubit::noiselessCNOT(IQubit *const target_qubit) {
  auto gs_target_qubit = static_cast<GraphStateQubit *>(target_qubit);
  gs_target_qubit->noiselessH();
  applyPureCZ(gs_target_qubit);
  gs_target_qubit->noiselessH();
}
EigenvalueResult GraphStateQubit::noiselessMeasureZ() { return graphMeasureZ(); }
EigenvalueResult GraphStateQubit::noiselessMeasureX() {
  applyClifford(CliffordOperator::H);
  return graphMeasureZ();
}
EigenvalueResult GraphStateQubit::noiselessMeasureZ(EigenvalueResult eigenvalue) { return graphMeasureZ(eigenvalue); }
EigenvalueResult GraphStateQubit::noiselessMeasureX(EigenvalueResult eigenvalue) {
  applyClifford(CliffordOperator::H);
  return graphMeasureZ(eigenvalue);
}

// map clifford operator to string
std::string GraphStateQubit::cliffordToString(CliffordOperator op) {
  switch (op) {
    case CliffordOperator::Id:
      return "Id";
    case CliffordOperator::X:
      return "X";
    case CliffordOperator::Y:
      return "Y";
    case CliffordOperator::Z:
      return "Z";
    case CliffordOperator::RX_INV:
      return "RX_INV";
    case CliffordOperator::Z_RX_INV:
      return "Z_RX_INV";
    case CliffordOperator::Z_RX:
      return "Z_RX";
    case CliffordOperator::RY_INV:
      return "RY_INV";
    case CliffordOperator::RY:
      return "RY";
    case CliffordOperator::H:
      return "H";
    case CliffordOperator::Z_RY:
      return "Z_RY";
    case CliffordOperator::S_INV:
      return "S_INV";
    case CliffordOperator::S:
      return "S";
    case CliffordOperator::X_S_INV:
      return "X_S_INV";
    case CliffordOperator::X_S:
      return "X_S";
    case CliffordOperator::S_INV_RX_INV:
      return "S_INV_RX_INV";
    case CliffordOperator::S_INV_RX:
      return "S_INV_RX";
    case CliffordOperator::S_RX_INV:
      return "S_RX_INV";
    case CliffordOperator::S_RX:
      return "S_RX";
    case CliffordOperator::S_INV_RY_INV:
      return "S_INV_RY_INV";
    case CliffordOperator::S_INV_RY:
      return "S_INV_RY";
    case CliffordOperator::S_RY_INV:
      return "S_RY_INV";
    case CliffordOperator::S_RY:
      return "S_RY";
    default:
      return "UNKNOWN";
  }
}

// initialize static variables
CliffordOperator GraphStateQubit::clifford_application_lookup[24][24] =
#include "clifford_application_lookup.tbl"
    ;

bool GraphStateQubit::controlled_z_lookup_edge[2][24][24] =
#include "cz_lookup_edge.tbl"
    ;

CliffordOperator GraphStateQubit::controlled_z_lookup_node_1[2][24][24] =
#include "cz_lookup_node_1.tbl"
    ;

CliffordOperator GraphStateQubit::controlled_z_lookup_node_2[2][24][24] =
#include "cz_lookup_node_2.tbl"
    ;

std::string GraphStateQubit::decomposition_table[24] = {
    "", "VV", "UUVV", "UU", "VVV", "V", "VUU", "UUV", "UVUUU", "UUUVU", "UVVVU", "UVU", "U", "UUU", "VVU", "UVV", "UVVV", "UV", "UVUU", "UUUV", "VVVU", "VU", "VUUU", "UUVU",
};
}  // namespace quisp::backends::graph_state
