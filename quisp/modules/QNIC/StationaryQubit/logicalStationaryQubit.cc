#include "logicalStationaryQubit.h"
#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <bitset>
#include <fstream>
#include <iterator>
#include <map>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>

namespace quisp {
namespace modules {
Define_Module(logicalStationaryQubit);

void logicalStationaryQubit::initialize() {
  // Logical measurement basis
  encode_size = 0;
  setPhysicalFree(false);

}

void logicalStationaryQubit::setPhysicalFree(bool consumed) {
  // set initial parameter

  // Parameters for task locking.
  locked = false;
  locked_ruleset_id = -1;
  locked_rule_id = -1;
  action_index = -1;

  isBusy = false;
  allocated = false;
  emitted_time = -1;
  updated_time = -1;

  // Parameters to deal with if logical parter was measured.
  logical_partner_measured = false;  // To flag which method to calculate the outcome.
  // GOD_dm_Zerror_list = nullptr; // List of Z error that already occur to another logical qubit that used to this logical qubit.
  // GOD_dm_Xerror_list = nullptr; // Same as above but with X error
  MatrixXcd Density_matrix_Collapsed;
  // v2
  logicalQuantumState = getIdealLogicalQuantumState();
  std::vector<StationaryQubit *> combine_entangled_list;
  std::map<int, std::string> physical_readout;
  // end v2

  // Logical information
  std::vector<StationaryQubit *> encoded_qubits_list;
  logical_entangled_partner = nullptr;

  if (hasGUI()) {
    if (consumed) {
      bubble("Consumed!");
      getDisplayString().setTagArg("i", 1, "yellow");
    } else {
      bubble("Failed to entangle!");
      getDisplayString().setTagArg("i", 1, "blue");
    }
  }
}

void logicalStationaryQubit::addToLogicalList(std::vector<StationaryQubit *> qubits_for_encode) {
  // Add encode qubit to list of physical qubits used for encode logical qubit

  // Switch input to [2]
  auto temp1 = qubits_for_encode[0];
  auto temp2 = qubits_for_encode[2];

  qubits_for_encode[0] = temp2;
  qubits_for_encode[2] = temp1;

  this->encoded_qubits_list = qubits_for_encode;
}

bool logicalStationaryQubit::checkBusy() {
  Enter_Method("checkBusy()");
  return isBusy;
}

void logicalStationaryQubit::Lock(unsigned long rs_id, int rule_id, int action_id) {
  if (rs_id == -1 || rule_id == -1 || action_id == -1) {
    error("ruleset_id || rule_id || action_id == -1");
  }

  locked = true;
  locked_ruleset_id = rs_id;  // Used to identify what this qubit is locked for.
  locked_rule_id = rule_id;
  action_index = action_id;

  if (hasGUI()) {
    bubble("Locked!");
    getDisplayString().setTagArg("i", 1, "purple");
  }
}

void logicalStationaryQubit::Unlock() {
  locked = false;
  locked_ruleset_id = -1;  // Used to identify what this qubit is locked for.
  locked_rule_id = -1;
  action_index = -1;

  if (hasGUI()) {
    bubble("Unlocked!");
    getDisplayString().setTagArg("i", 1, "pink");
  }
}

bool logicalStationaryQubit::isLocked() { return locked; }

void logicalStationaryQubit::Allocate() {
  allocated = true;
  if (hasGUI()) {
    bubble("Allocated!");
    getDisplayString().setTagArg("i", 1, "purple");
  }
}

void logicalStationaryQubit::Deallocate() { allocated = false; }

bool logicalStationaryQubit::isAllocated() { return allocated; }

// S1 Need more research to define those functions below
void logicalStationaryQubit::setLogicalCompletelyMixedDensityMatrix() {}
void logicalStationaryQubit::setLogicalExcitedDensityMatrix() {}
void logicalStationaryQubit::setLogicalRelaxedDensityMatrix() {}
// end S1

void logicalStationaryQubit::setLogicalEntangledPartnerInfo(logicalStationaryQubit *partner) {

  this->logical_entangled_partner = partner;
  partner->logical_entangled_partner = this;

  if (combine_entangled_list.size() != this->encode_size) {
    // v2
    std::vector<StationaryQubit *> comb_list;
    comb_list.reserve(this->encoded_qubits_list.size() + this->logical_entangled_partner->encoded_qubits_list.size());
    comb_list.insert(comb_list.end(), this->encoded_qubits_list.begin(), this->encoded_qubits_list.end());
    comb_list.insert(comb_list.end(), this->logical_entangled_partner->encoded_qubits_list.begin(), this->logical_entangled_partner->encoded_qubits_list.end());
    this->combine_entangled_list = comb_list;
    // end v2

    partner->combine_entangled_list = comb_list;
  }
  
}

// For logical qubit gate,
/*
    This should be generalize to any code.
    2020/01/12 - Steane Code is an only option.
*/
void logicalStationaryQubit::Hadamard_gate() {
  // Steane Code
  for (int i = 0; i < encoded_qubits_list.size(); i++) {
    this->encoded_qubits_list[i]->Hadamard_gate();
  }
}
void logicalStationaryQubit::Z_gate() {
  // Steane Code
  for (int i = 0; i < encoded_qubits_list.size(); i++) {
    this->encoded_qubits_list[i]->Z_gate();
  }
}
void logicalStationaryQubit::X_gate() {
  // Steane Code
  for (int i = 0; i < encoded_qubits_list.size(); i++) {
    this->encoded_qubits_list[i]->X_gate();
  }
}
/*
void logicalStationaryQubit::CNOT_gate(logicalStationaryQubit *control_qubit) {
    // Steane Code
    for (int i; i < encoded_qubits_list.size(); i++ ){
        this->encoded_qubits_list[i]->CNOT_gate(control_qubit->encoded_qubits_list[i]); // Target -> Control
    }
}
*/

void logicalStationaryQubit::CNOT_gate(std::vector<StationaryQubit *> target_qubit, std::vector<StationaryQubit *> control_qubit) {
  // Steane Code
  for (int i = 0; i < control_qubit.size(); i++) {
    target_qubit[i]->CNOT_gate(control_qubit[i]);  // Target -> Control
  }
}

void logicalStationaryQubit::Encode(int code) {

  // Hard code for Steane code
  encoded_qubits_list[0]->Hadamard_gate();
  encoded_qubits_list[1]->Hadamard_gate();
  encoded_qubits_list[3]->Hadamard_gate();

  encoded_qubits_list[2]->CNOT_gate(encoded_qubits_list[4]);
  encoded_qubits_list[2]->CNOT_gate(encoded_qubits_list[5]);

  encoded_qubits_list[0]->CNOT_gate(encoded_qubits_list[2]);
  encoded_qubits_list[0]->CNOT_gate(encoded_qubits_list[4]);
  encoded_qubits_list[0]->CNOT_gate(encoded_qubits_list[6]);

  encoded_qubits_list[1]->CNOT_gate(encoded_qubits_list[2]);
  encoded_qubits_list[1]->CNOT_gate(encoded_qubits_list[5]);
  encoded_qubits_list[1]->CNOT_gate(encoded_qubits_list[6]);

  encoded_qubits_list[3]->CNOT_gate(encoded_qubits_list[4]);
  encoded_qubits_list[3]->CNOT_gate(encoded_qubits_list[5]);
  encoded_qubits_list[3]->CNOT_gate(encoded_qubits_list[6]);

  this->encode_size = 14;
}

void logicalStationaryQubit::ErrorDetectionAndCorrection(std::vector<StationaryQubit *> ancilla_qubit, int detection_protocol) {
  // Return location and type of error

  // Hard code for simple Steane scheme using 6 physical qubits
  // Error detection Z
  // Generator 1
  ancilla_qubit[0]->Hadamard_gate();
  encoded_qubits_list[3]->CNOT_gate(ancilla_qubit[0]);  // Target-> Control
  encoded_qubits_list[4]->CNOT_gate(ancilla_qubit[0]);
  encoded_qubits_list[5]->CNOT_gate(ancilla_qubit[0]);
  encoded_qubits_list[6]->CNOT_gate(ancilla_qubit[0]);
  ancilla_qubit[0]->Hadamard_gate();

  // Generator 2
  ancilla_qubit[1]->Hadamard_gate();
  encoded_qubits_list[0]->CNOT_gate(ancilla_qubit[1]);  // Target-> Control
  encoded_qubits_list[2]->CNOT_gate(ancilla_qubit[1]);
  encoded_qubits_list[4]->CNOT_gate(ancilla_qubit[1]);
  encoded_qubits_list[6]->CNOT_gate(ancilla_qubit[1]);
  ancilla_qubit[1]->Hadamard_gate();

  // Generator 3
  ancilla_qubit[2]->Hadamard_gate();
  encoded_qubits_list[1]->CNOT_gate(ancilla_qubit[2]);  // Target-> Control
  encoded_qubits_list[2]->CNOT_gate(ancilla_qubit[2]);
  encoded_qubits_list[5]->CNOT_gate(ancilla_qubit[2]);
  encoded_qubits_list[6]->CNOT_gate(ancilla_qubit[2]);
  ancilla_qubit[2]->Hadamard_gate();

  // Error detection X Change from CNOT => CZ via Hadamard gate
  // Generator 4
  ancilla_qubit[3]->Hadamard_gate();
  encoded_qubits_list[3]->Hadamard_gate();
  encoded_qubits_list[3]->CNOT_gate(ancilla_qubit[3]);  // Target-> Control
  encoded_qubits_list[3]->Hadamard_gate();
  encoded_qubits_list[4]->Hadamard_gate();
  encoded_qubits_list[4]->CNOT_gate(ancilla_qubit[3]);
  encoded_qubits_list[4]->Hadamard_gate();
  encoded_qubits_list[5]->Hadamard_gate();
  encoded_qubits_list[5]->CNOT_gate(ancilla_qubit[3]);
  encoded_qubits_list[5]->Hadamard_gate();
  encoded_qubits_list[6]->Hadamard_gate();
  encoded_qubits_list[6]->CNOT_gate(ancilla_qubit[3]);
  encoded_qubits_list[6]->Hadamard_gate();
  ancilla_qubit[3]->Hadamard_gate();

  // Generator 5
  ancilla_qubit[4]->Hadamard_gate();
  encoded_qubits_list[0]->Hadamard_gate();
  encoded_qubits_list[0]->CNOT_gate(ancilla_qubit[4]);  // Target-> Control
  encoded_qubits_list[0]->Hadamard_gate();
  encoded_qubits_list[2]->Hadamard_gate();
  encoded_qubits_list[2]->CNOT_gate(ancilla_qubit[4]);
  encoded_qubits_list[2]->Hadamard_gate();
  encoded_qubits_list[4]->Hadamard_gate();
  encoded_qubits_list[4]->CNOT_gate(ancilla_qubit[4]);
  encoded_qubits_list[4]->Hadamard_gate();
  encoded_qubits_list[6]->Hadamard_gate();
  encoded_qubits_list[6]->CNOT_gate(ancilla_qubit[4]);
  encoded_qubits_list[6]->Hadamard_gate();
  ancilla_qubit[4]->Hadamard_gate();

  // Generator 6
  ancilla_qubit[5]->Hadamard_gate();
  encoded_qubits_list[1]->Hadamard_gate();
  encoded_qubits_list[1]->CNOT_gate(ancilla_qubit[5]);  // Target-> Control
  encoded_qubits_list[1]->Hadamard_gate();
  encoded_qubits_list[2]->Hadamard_gate();
  encoded_qubits_list[2]->CNOT_gate(ancilla_qubit[5]);
  encoded_qubits_list[2]->Hadamard_gate();
  encoded_qubits_list[5]->Hadamard_gate();
  encoded_qubits_list[5]->CNOT_gate(ancilla_qubit[5]);
  encoded_qubits_list[5]->Hadamard_gate();
  encoded_qubits_list[6]->Hadamard_gate();
  encoded_qubits_list[6]->CNOT_gate(ancilla_qubit[5]);
  encoded_qubits_list[6]->Hadamard_gate();
  ancilla_qubit[5]->Hadamard_gate();

  // Should calculate syndrome from GOD_?error of each physcial qubits and return corresponding syndrome to error
  // std::map<int, std::string> location_errortype
  // e.g. location_errortype.insert(pair<int, std::string>(2, "X");

  location_errortype.insert(std::pair<int, std::string>(0, "I"));  // <-- Just in case...
  // Check commutator (? kind of) with generator
  std::vector<std::vector<int>> Generators{
      {false, false, false, true, true, true, true},  // G1
      {false, true, true, false, false, true, true},  // G2
      {true, false, true, false, true, false, true}  // G3
  };

  // Check X error with commuator of generator Z (Luckily that X and Z generator is the same in bool form)
  bool flag;
  bool location_bool[3] = {false};
  for (int i = 0; i < Generators.size(); i++) {
    flag = false;
    for (int j = 0; j < encoded_qubits_list.size(); j++) {
      if (bool(encoded_qubits_list[j]->par("God_Xerror")) != bool(Generators[i][j])) {
        flag = !flag;
      }
    }
    location_bool[i] = flag;
  }
  // convert commutor flag to location in decimal
  int location = bitArrayToInt32(location_bool, 3);  // <- 32?
  // Store result to location_errortype
  location_errortype.insert(std::pair<int, std::string>(location, "X"));

  // Check Z error with commuator of generator X
  for (int i = 0; i < Generators.size(); i++) {
    flag = false;
    for (int j = 0; j < encoded_qubits_list.size(); j++) {
      if (bool(encoded_qubits_list[j]->par("God_Zerror")) != bool(Generators[i][j])) {
        flag = !flag;
      }
    }
    location_bool[i] = flag;
  }
  // convert commutor flag to location in decimal
  location = bitArrayToInt32(location_bool, 3);

  // Store result to location_errortype
  location_errortype.insert(std::pair<int, std::string>(location, "Z"));

  std::map<int, std::string>::iterator itr;
  for (itr = location_errortype.begin(); itr != location_errortype.end(); ++itr) {
    if (itr->second == "X") {
      encoded_qubits_list[itr->first]->X_gate();
    }
    if (itr->second == "Z") {
      encoded_qubits_list[itr->first]->Z_gate();
    }
  }
}

int logicalStationaryQubit::bitArrayToInt32(bool arr[], int count) {
  // https://stackoverflow.com/questions/32410186/convert-bool-array-to-int32-unsigned-int-and-double
  int ret = 0;
  int tmp;
  for (int i = 0; i < count; i++) {
    tmp = arr[i];
    ret |= tmp << (count - i - 1);
  }
  return ret;
}

logical_quantum_state logicalStationaryQubit::getLogicalQuantumState() {
  if (this->encoded_qubits_list.size() != 7) {  // <-- Specifically for Steane code
    error("The number of physical qubits used to encoded is not 7");
  }
  if (this->logical_entangled_partner == nullptr) {
    error("There is no entangled logical qubit partner");
  }
  if (this->logical_entangled_partner->encoded_qubits_list.size() != 7) {
    error("The number of physical qubits used to encoded partner logical qubit is not 7");
  }

  // Get Combined Error matrix of each physical qubits from this logical qubit.
  MatrixXcd combined_errors_self = this->encoded_qubits_list[0]->getErrorMatrix(this->encoded_qubits_list[0]);
  for (int i = 1; i <= this->encoded_qubits_list.size(); i++) {
    combined_errors_self = kroneckerProduct(combined_errors_self, this->encoded_qubits_list[i]->getErrorMatrix(this->encoded_qubits_list[i])).eval();
  }
  // Get Combined Error matrix of each physical qubits from partner logical qubit.
  MatrixXcd combined_errors_partner = this->logical_entangled_partner->encoded_qubits_list[0]->getErrorMatrix(this->logical_entangled_partner->encoded_qubits_list[0]);
  for (int i = 1; i <= this->encoded_qubits_list.size(); i++) {
    combined_errors_partner =
        kroneckerProduct(combined_errors_partner, this->logical_entangled_partner->encoded_qubits_list[i]->getErrorMatrix(this->logical_entangled_partner->encoded_qubits_list[i]))
            .eval();
  }

  MatrixXcd combined_errors = kroneckerProduct(combined_errors_self, combined_errors_partner);

  VectorXcd ideal_logical_Bell_pair = this->logicalQuantumState.state_in_ket;
  VectorXcd actual_logical_Bell_state = combined_errors * ideal_logical_Bell_pair;
  // EV<<"Current physical state is = "<<actual_Bell_state;
  MatrixXcd logical_density_matrix = actual_logical_Bell_state * actual_logical_Bell_state.adjoint();
  // EV<<"dm = "<<density_matrix<<"\n";

  logical_quantum_state q;
  q.state_in_density_matrix = logical_density_matrix;
  q.state_in_ket = actual_logical_Bell_state;
  return q;
}

logical_quantum_state logicalStationaryQubit::getIdealLogicalQuantumState() {
  std::vector<std::complex<double>> data;
  // VectorXcd data;
  std::ifstream fin("LogicalBellSteane713.txt");
  double real;
  double img;
  while (fin >> real >> img) {
    const std::complex<double> temp(real, img);
    data.push_back(temp);
  }
  // VectorXcd ideal_logical_Bell_pair = data;
  // VectorXcd ideal_logical_Bell_pair(data.data());
  Eigen::Map<VectorXcd> ideal_logical_Bell_pair(data.data(), data.size());
  MatrixXcd ideal_logical_density_matrix = ideal_logical_Bell_pair * ideal_logical_Bell_pair.adjoint();

  logical_quantum_state q;
  q.state_in_density_matrix = ideal_logical_density_matrix;
  q.state_in_ket = ideal_logical_Bell_pair;
  return q;
}

measurement_outcome logicalStationaryQubit::logical_measure_density_independent_v2(StationaryQubit *physicalQubit, measurement_operator this_measurement) {
  /*
      After consideration, what original QuISP expected is just 2 physical qubits.
      So the meaurement operation is specifically design for that case, which involve two part.
      If no physical qubit has measured, then it will get (noisy) full-quantum state,
      then use that to calculate the outcome of the first qubit. After that, the resulting density martrix
      will calculated and stored in "Density_Matrix_Collapsed" parameter. Which link to another condition,
      if there is a qubit already measured then it will use "Density_Matrix_Collapsed" to calculate the outcome
      upon calling this function, but! with update of its. Because this qubit also subject to noise during some waiting time too,
      so the function will check "GOD_dm_?Error" which act like a save point after measured the first qubit.

      So in order to serve th propose of this save point in more general cases,
      my idea is to re-design this function to just reset "GOD_?Error" after whichever qubit was measured.
      Instead of save error that already considerd in previous measurement, and carry the check point to another qubits,
      I suggest to reset "GOD_?Error" of all physical qubit to false as a flag that we already deal with qubit's current error.
      If the qubit suject to new error before the measurement then fine! The function just have to applie that error to the carried
      density matrix instead.

      Let's dive into pesudo-code.

      logicalQuantumState = Ideal 14-physical qubits that encode 2 logical Bell pair. (Shared variable)
      encoded_qubits_list = List of 7 physical qubits used to encode logical qubit.
      combine_entangled_list = List of 14 physical qubits used to encode logical Bell pair. (Shared variable)
      physical_readout = Readout ordered-list of physcial qubits, initialize to be nullptr

      function logical_measure_density_independent_v2(physicalQubit, this_measurement): // this_measurement is measurement basis.
          index_qubit = get index of qubit in combine_entangled_list associate with physicalQubit
          index_qubit_in_system = get index of qubit from encoded_qubits_list
          measurement_plus_ket = tensor product of identity and this_measurement.plus_ket associate with index_qubit
          measurement_plus = outer product of measurement_plus_ket
          Apply memory error to all physicalQubits
          Apply measurement error to physicalQubit
          Error_matrix = tensor product of all error (GOD_?Error from getErrorMatrix) that occur on all remaining physical qubit from list
          current_state = Error_matrix * logicalQuantumState.state_in_ket
          Prob_plus = inner product of measurement_plus and current_state
          outcome = Get measurement outcome based on Prob_plus
          physical_readout[index_qubit_in_system] = outcome in form of string '+' or '-'.
          logicalQuantumState = measurement_plus_ket * current_state * measurement_plus_ket.adjoint() and renormalize it.
          reset GOD_?Error of all remaining physical qubits to false.
          remove physicalQubit from combine_entangled_list

  */

  // Get index of qubit in combine_entangled_list associate with physicalQubit
  int index_qubit;
  for (int i = 0; i < combine_entangled_list.size(); i++) {
    if (combine_entangled_list[i] == physicalQubit) {
      index_qubit = i;
    }
  }

  // get index of qubit from encoded_qubits_list
  int index_qubit_in_system;
  for (int i = 0; i < encoded_qubits_list.size(); i++) {
    if (encoded_qubits_list[i] == physicalQubit) {
      index_qubit_in_system = i;
    }
  }

  // Randomly choose basis (call Random_Measurement_Basis_Selection())
  // measurement_operator this_measurement = physicalQubit->Random_Measurement_Basis_Selection();

  // tensor product of identity and this_measurement.plus_ket associate with index_qubit
  MatrixXcd measurement_plus = physicalQubit->Pauli.I;
  if (index_qubit == 0) {
    measurement_plus = this_measurement.plus;
  }
  Matrix2cd m_operator;
  for (int i = 1; i < combine_entangled_list.size(); i++) {
    if (i == index_qubit) {
      m_operator = this_measurement.plus;
    } else {
      m_operator = physicalQubit->Pauli.I;
    }
    measurement_plus = kroneckerProduct(measurement_plus, m_operator).eval();
  }

  // Outer product of measurement_plus_ket
  // MatrixXcd measurement_plus = measurement_plus_ket * measurement_plus_ket.adjoint();

  // Apply memory error to all physicalQubits

  for (int i = 0; i < combine_entangled_list.size(); i++) {
    this->combine_entangled_list.at(i)->apply_memory_error(this->combine_entangled_list.at(i));
  }

  // physicalQubit->apply_memory_error(physicalQubit);

  // Apply measurement error to physicalQubit
  physicalQubit->apply_single_qubit_gate_error(physicalQubit->Measurement_error, physicalQubit);

  // Tensor product of all error (GOD_?Error from getErrorMatrix) that occur on all remaining physical qubit from list
  MatrixXcd Error_matrix = this->combine_entangled_list.at(0)->getErrorMatrix(this->combine_entangled_list.at(0));
  for (int i = 1; i < combine_entangled_list.size(); i++) {
    Error_matrix = kroneckerProduct(Error_matrix, this->combine_entangled_list.at(i)->getErrorMatrix(this->combine_entangled_list.at(i))).eval();
  }

  // Error_matrix * logicalQuantumState.state_in_ket
  MatrixXcd current_state;
  current_state = Error_matrix * this->logicalQuantumState.state_in_density_matrix * Error_matrix.adjoint();

  // Prob_plus = inner product of measurement_plus and current_state
  // Complex Prob_plus = (current_state.adjoint() * measurement_plus * current_state).value();
  Complex Prob_plus = (current_state * measurement_plus).trace();

  // Get measurement outcome based on Prob_plus
  double dbl = dblrand();
  Vector2cd ms;

  char Output;
  bool Output_is_plus;

  if (dbl < Prob_plus.real()) {  // Measurement output was plus
    Output = '+';
    ms = measurement_plus;
    Output_is_plus = true;
  } else {  // Otherwise, it was negative.
    Output = '-';

    MatrixXcd measurement_minus = physicalQubit->Pauli.I;
    if (index_qubit == 0) {
      measurement_minus = this_measurement.minus;
    }
    Matrix2cd m_operator;
    for (int i = 1; i < combine_entangled_list.size(); i++) {
      if (i == index_qubit) {
        m_operator = this_measurement.minus;
      } else {
        m_operator = physicalQubit->Pauli.I;
      }
      measurement_minus = kroneckerProduct(measurement_minus, m_operator).eval();
    }

    ms = measurement_minus;
    Output_is_plus = false;
  }

  // physical_readout[index_qubit_in_system] = outcome in form of string '+''' or '-'.
  this->physical_readout[index_qubit_in_system] = Output;

  // Calculate the new density matrix; logicalQuantumState = measurement_plus_ket * current_state * measurement_plus_ket.adjoint() and renormalize it.

  MatrixXcd partners_dm, normalized_partners_dm;
  // partners_dm = ms.adjoint() * (current_state * current_state.adjoint()) * ms;
  partners_dm = ms * (current_state)*ms.adjoint();
  normalized_partners_dm = partners_dm / partners_dm.trace();
  logicalQuantumState.state_in_density_matrix = normalized_partners_dm;

  // reset GOD_?Error of all remaining physical qubits to false.

  for (int i = 0; i < combine_entangled_list.size(); i++) {
    this->combine_entangled_list[i]->par("GOD_Xerror") = false;
    this->combine_entangled_list[i]->par("GOD_Zerror") = false;
  }

  // remove physicalQubit from combine_entangled_list

  this->combine_entangled_list.erase(combine_entangled_list.begin() + index_qubit);
  this->logical_entangled_partner->combine_entangled_list = this->combine_entangled_list;

  measurement_outcome o;
  o.basis = this_measurement.basis;
  o.outcome_is_plus = Output_is_plus;
  return o;
}

measurement_outcome logicalStationaryQubit::logical_readout_v2(StationaryQubit *physicalQubit) {
  // Randomly choose basis (call Random_Measurement_Basis_Selection())
  measurement_operator this_measurement = physicalQubit->Random_Measurement_Basis_Selection();

  /*
  Lock this process, if measure?

  */

  for (int i = 0; i < encoded_qubits_list.size(); i++) {
    this->logical_measure_density_independent_v2(this->encoded_qubits_list[i], this_measurement);
  }

  std::string combind_outcome_string = "";
  std::map<int, std::string>::iterator it;
  for (it = this->physical_readout.begin(); it != this->physical_readout.end(); it++) {
    combind_outcome_string += combind_outcome_string + it->second;
  }

  int num_encoded = 8;
  std::string logical_zero[8] = {"+++++++", "-+-+-+-", "+--++--", "--++--+", "+++----", "-+--+-+", "+----++", "--+-++-"};
  std::string logical_one[8] = {"-------", "+-+-+-+", "-++--++", "++--++-", "---++++", "+-++-+-", "-++++--", "++-+--+"};

  char Output_is_plus;

  for (int i = 0; i < num_encoded; i++) {
    if (combind_outcome_string == logical_zero[i]) {
      Output_is_plus = true;
    } else if (combind_outcome_string == logical_one[i]) {
      Output_is_plus = false;
    } else {
      error("Invalid cordword");
    }
  }

  measurement_outcome o;
  o.basis = this_measurement.basis;
  o.outcome_is_plus = Output_is_plus;
  return o;
}

}  // namespace modules
}  // namespace quisp
