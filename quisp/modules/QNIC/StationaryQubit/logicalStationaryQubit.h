

#ifndef QUISP_MODULES_LOGICAL_STATIONARYQUBIT_H_
#define QUISP_MODULES_LOGICAL_STATIONARYQUBIT_H_

#include <vector>
#include "StationaryQubit.h"

using namespace Eigen;
using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

typedef std::complex<double> Complex;

struct logical_quantum_state {
  MatrixXcd state_in_density_matrix;
  VectorXcd state_in_ket;
};

struct logical_measurement_operator {
  MatrixXcd plus;
  MatrixXcd minus;
  VectorXcd plus_ket;
  VectorXcd minus_ket;
  char basis;
};

class logicalStationaryQubit : public cSimpleModule {
 public:
  bool locked;
  unsigned long locked_ruleset_id;
  int locked_rule_id;
  int action_index;

  bool isBusy;
  bool allocated;

  std::vector<int> encoding_protocol;
  std::map<int, std::string> location_errortype;

  // Possible not nessesary for logical qubit
  simtime_t emitted_time = -1;
  simtime_t updated_time = -1;

  // Parameters to deal with if logical parter was measured.
  bool logical_partner_measured;  // To flag which method to calculate the outcome.
  MatrixXcd Density_matrix_Collapsed;  // Density matrix after another logical qubit is measured
  // v2
  logical_quantum_state logicalQuantumState;
  std::vector<StationaryQubit *> combine_entangled_list;
  std::map<int, std::string> physical_readout;
  // end v2

  // Logical information
  std::vector<StationaryQubit *> encoded_qubits_list;
  logicalStationaryQubit *logical_entangled_partner = nullptr;

  VectorXcd ideal_logical_Bell_pair;
  MatrixXcd ideal_logical_density_matrix;

 protected:
  void initialize();
  void setPhysicalFree(bool consumed);

  bool checkBusy();
  void Lock(unsigned long rs_id, int rule_id, int action_id); /*In use. E.g. waiting for purification result.*/
  void Unlock();
  bool isLocked();
  void Allocate();
  void Deallocate();
  bool isAllocated();

  void addToLogicalList(StationaryQubit *encode_qubit);
  void setLogicalCompletelyMixedDensityMatrix();
  void setLogicalExcitedDensityMatrix();
  void setLogicalRelaxedDensityMatrix();
  void setLogicalEntangledPartnerInfo(logicalStationaryQubit *partner);
  void Hadamard_gate();
  void Z_gate();
  void X_gate();
  void CNOT_gate(std::vector<StationaryQubit *> target_qubit, std::vector<StationaryQubit *> control_qubit);

  // Error management related
  void ErrorDetectionAndCorrection(std::vector<StationaryQubit *> ancilla_qubit, std::string detection_protocol);
  // void errorCorrection(std::map<int, std::string> location_errortype);
  // std::map<int, std::string> errorDetection(std::vector<StationaryQubit *> ancilla_qubit, std::string detection_protocol);
  int bitArrayToInt32(bool arr[], int count);

  logical_quantum_state getLogicalQuantumState();
  logical_quantum_state getIdealLogicalQuantumState();
  // virtual measurement_outcome logical_measure_density_independent_v1();
  // virtual logical_measurement_operator logical_Random_Measurement_Basis_Selection();
  measurement_outcome logical_measure_density_independent_v2(StationaryQubit *physicalQubit, measurement_operator this_measurement);
  measurement_outcome logical_readout_v2(StationaryQubit *physicalQubit);
};

};  // namespace modules

}  // namespace quisp

#endif /* QUISP_MODULES_LOGICAL_STATIONARYQUBIT_H_ */
