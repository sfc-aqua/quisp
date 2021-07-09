/** \file StationaryQubit.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief StationaryQubit
 */
#include "StationaryQubit.h"

#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <bitset>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>
#include <vector>

namespace quisp {
namespace modules {

Define_Module(StationaryQubit);

/**
 * \brief Initialize StationaryQubit
 *
 * Omnet called method to initialize objects.
 *
 */
void StationaryQubit::initialize() {
  double rand = dblrand();

  /*Photon emission time error rates*/

  /*
  emission_success_probability = par("emission_success_probability");
  emission_error.X_error_rate = par("emission_Z_error_rate");//par("name") will be read from .ini or .ned file
  emission_error.X_error_rate =  par("emission_X_error_rate");
  emission_error.Z_error_rate = par("emission_Y_error_rate");
  emission_error.pauli_error_rate = emission_error.Y_error_rate + emission_error.Z_error_rate + emission_error.X_error_rate;


  emission_error.No_error_ceil =1-emission_error.pauli_error_rate;// if 0 <= dblrand < fidelity = No error
  emission_error.X_error_ceil = emission_error.No_error_ceil + emission_error.X_error_rate; // if fidelity <= dblrand < fidelity+X error rate = X error
  emission_error.Z_error_ceil = emission_error.X_error_ceil + emission_error.Z_error_rate;
  emission_error.Y_error_ceil = 1;


  std::cout<<"emission_error.No_error_ceil = "<<emission_error.No_error_ceil<<"\n";
  std::cout<<"emission_error.X_error_ceil = "<<emission_error.X_error_ceil<<"\n";
  std::cout<<"emission_error.Y_error_ceil = "<<emission_error.Y_error_ceil<<"\n";
  std::cout<<"emission_error.Z_error_ceil = "<<emission_error.Z_error_ceil<<"\n";
  */
  emission_success_probability = par("emission_success_probability");
  // numemitted = 0;
  // setErrorCeilings();

  /*Memory error rates*/

  /*
double memory_Z_error_ratio = par("memory_Z_error_ratio");//par("name") will be read from .ini or .ned file
double memory_X_error_ratio = par("memory_X_error_ratio");
double memory_Y_error_ratio = par("memory_Y_error_ratio");
double memory_excitation_error_ratio = par("memory_energy_excitation_ratio");
double memory_relaxation_error_ratio = par("memory_energy_relaxation_ratio");
double memory_completely_mixed_ratio = par("memory_completely_mixed_ratio");

if(memory_Z_error_ratio == 0 && memory_X_error_ratio == 0 && memory_Y_error_ratio == 0 && memory_excitation_error_ratio == 0 && memory_relaxation_error_ratio == 0 &&
memory_completely_mixed_ratio ==0){ memory_Z_error_ratio = 1; memory_X_error_ratio = 1; memory_Y_error_ratio = 1; memory_excitation_error_ratio = 1; memory_relaxation_error_ratio =
1; memory_completely_mixed_ratio = 1;
}

//EV<<"memory_excitation_error_ratio = "<<memory_excitation_error_ratio<<", memory_relaxation_error_ratio"<<memory_relaxation_error_ratio<<"\n";
double memory_ratio_sum = memory_Z_error_ratio+memory_X_error_ratio+memory_Y_error_ratio + memory_excitation_error_ratio + memory_relaxation_error_ratio +
memory_completely_mixed_ratio; memory_err.error_rate = par("memory_error_rate");//This is per μs. memory_err.X_error_rate = memory_err.error_rate *
(memory_X_error_ratio/memory_ratio_sum); memory_err.Y_error_rate = memory_err.error_rate * (memory_Y_error_ratio/memory_ratio_sum); memory_err.Z_error_rate = memory_err.error_rate
* (memory_Z_error_ratio/memory_ratio_sum); memory_err.excitation_error_rate = memory_err.error_rate * (memory_excitation_error_ratio/memory_ratio_sum);
memory_err.relaxation_error_rate = memory_err.error_rate * (memory_relaxation_error_ratio/memory_ratio_sum);
memory_err.completely_mixed_rate = memory_err.error_rate * (memory_completely_mixed_ratio/memory_ratio_sum);
  */

  memory_err.X_error_rate = (double)par("memory_X_error_rate").doubleValue();
  memory_err.Y_error_rate = (double)par("memory_Y_error_rate").doubleValue();
  memory_err.Z_error_rate = (double)par("memory_Z_error_rate").doubleValue();
  memory_err.excitation_error_rate = (double)par("memory_energy_excitation_rate").doubleValue();
  memory_err.relaxation_error_rate = (double)par("memory_energy_relaxation_rate").doubleValue();
  memory_err.completely_mixed_rate = (double)par("memory_completely_mixed_rate").doubleValue();
  memory_err.error_rate = memory_err.X_error_rate + memory_err.Y_error_rate + memory_err.Z_error_rate + memory_err.excitation_error_rate + memory_err.relaxation_error_rate +
                          memory_err.completely_mixed_rate;  // This is per μs.
  /*EV<<"Err rate = "<<memory_err.pauli_error_rate<<"\n";
  EV<<"Ratio sum = "<<memory_ratio_sum<<"\n";
  EV<<"I error rate (mem) = "<<1-memory_err.pauli_error_rate<<"\n";
  EV<<"X error rate (mem) = "<<memory_err.X_error_rate<<"\n";
  EV<<"Y error rate (mem) = "<<memory_err.Y_error_rate<<"\n";
  EV<<"Z error rate (mem) = "<<memory_err.Z_error_rate<<"\n";
  EV<<"Excitation error rate (mem) = "<<memory_err.excitation_error_rate<<"\n";
  EV<<"Relaxation error rate (mem) = "<<memory_err.relaxation_error_rate<<"\n";*/
  Memory_Transition_matrix = MatrixXd::Zero(7, 7);
  // clang-format off
  Memory_Transition_matrix <<
    1 - memory_err.error_rate,  memory_err.X_error_rate,   memory_err.Z_error_rate,   memory_err.Y_error_rate,    memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    memory_err.X_error_rate,    1 - memory_err.error_rate, memory_err.Y_error_rate,   memory_err.Z_error_rate,    memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    memory_err.Z_error_rate,    memory_err.Y_error_rate,   1 - memory_err.error_rate, memory_err.X_error_rate,    memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    memory_err.Y_error_rate,    memory_err.Z_error_rate,   memory_err.X_error_rate,   1 - memory_err.error_rate,  memory_err.excitation_error_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    0,                          0,                         0,                         0,                          1 - memory_err.relaxation_error_rate - memory_err.completely_mixed_rate, memory_err.relaxation_error_rate, memory_err.completely_mixed_rate,
    0,                          0,                         0,                         0,                          memory_err.excitation_error_rate, 1 - memory_err.excitation_error_rate - memory_err.completely_mixed_rate, memory_err.completely_mixed_rate,
    0,                          0,                         0,                         0,                          memory_err.excitation_error_rate, memory_err.relaxation_error_rate, 1 - memory_err.excitation_error_rate - memory_err.relaxation_error_rate;
  // clang-format on
  std::cout << "Memory_Transition_matrix = \n " << Memory_Transition_matrix << " done \n";

  Hgate_error = SetSingleQubitGateErrorCeilings("Hgate");
  Xgate_error = SetSingleQubitGateErrorCeilings("Xgate");
  Zgate_error = SetSingleQubitGateErrorCeilings("Zgate");
  Measurement_error = SetSingleQubitGateErrorCeilings("Measurement");
  CNOTgate_error = SetTwoQubitGateErrorCeilings("CNOTgate");

  std::cout << Memory_Transition_matrix << "\n";
  // endSimulation();

  // Set error matrices. This is used in the process of simulating tomography.
  Pauli.X << 0, 1, 1, 0;
  Pauli.Y << 0, Complex(0, -1), Complex(0, 1), 0;
  Pauli.Z << 1, 0, 0, -1;
  Pauli.I << 1, 0, 0, 1;

  // Set measurement operators. This is used in the process of simulating tomography.
  meas_op.X_basis.plus << 0.5, 0.5, 0.5, 0.5;
  meas_op.X_basis.minus << 0.5, -0.5, -0.5, 0.5;
  meas_op.X_basis.plus_ket << 1 / sqrt(2), 1 / sqrt(2);
  meas_op.X_basis.minus_ket << 1 / sqrt(2), -1 / sqrt(2);
  meas_op.X_basis.basis = 'X';
  meas_op.Z_basis.plus << 1, 0, 0, 0;
  meas_op.Z_basis.minus << 0, 0, 0, 1;
  meas_op.Z_basis.plus_ket << 1, 0;
  meas_op.Z_basis.minus_ket << 0, 1;
  meas_op.Z_basis.basis = 'Z';
  meas_op.Y_basis.plus << 0.5, Complex(0, -0.5), Complex(0, 0.5), 0.5;
  meas_op.Y_basis.minus << 0.5, Complex(0, 0.5), Complex(0, -0.5), 0.5;
  meas_op.Y_basis.plus_ket << 1 / sqrt(2), Complex(0, 1 / sqrt(2));
  meas_op.Y_basis.minus_ket << 1 / sqrt(2), -Complex(0, 1 / sqrt(2));
  meas_op.Y_basis.basis = 'Y';
  meas_op.identity << 1, 0, 0, 1;

  // Get parameters from omnet
  stationaryQubit_address = par("stationaryQubit_address");
  node_address = par("node_address");
  qnic_address = par("qnic_address");
  qnic_type = par("qnic_type");
  qnic_index = par("qnic_index");
  std = par("std");
  setFree(false);
  setFidelity(-1.);

  DEBUG_memory_X_count = 0;
  DEBUG_memory_Y_count = 0;
  DEBUG_memory_Z_count = 0;

  /* e^(t/T1) energy relaxation, e^(t/T2) phase relaxation. Want to use only 1/10 of T1 and T2 in general.*/
}

void StationaryQubit::finish() {
  // std::cout<<"emitted "<<numemitted<<"¥n";
}

/**
 * \brief cSimpleModule handleMessage function
 *
 * \param msg is the message
 */
void StationaryQubit::handleMessage(cMessage *msg) {
  bubble("Got a photon!!");
  setBusy();
  // numemitted++;
  // setEmissionPauliError();
  double rand = dblrand();
  if (rand < (1 - emission_success_probability)) {
    PhotonicQubit *pk = check_and_cast<PhotonicQubit *>(msg);
    pk->setPhotonLost(true);
    send(pk, "tolens_quantum_port$o");
  } else {
    send(msg, "tolens_quantum_port$o");
  }
}

SingleGateErrorModel StationaryQubit::SetSingleQubitGateErrorCeilings(std::string gate_name) {
  SingleGateErrorModel gate;
  auto err_rate_name = gate_name + std::string("_error_rate");
  auto x_ratio_name = gate_name + std::string("_X_error_ratio");
  auto z_ratio_name = gate_name + std::string("_Z_error_ratio");
  auto y_ratio_name = gate_name + std::string("_Y_error_ratio");
  gate.pauli_error_rate = par(err_rate_name.c_str()).doubleValue();
  auto x_ratio = par(x_ratio_name.c_str()).doubleValue();
  auto z_ratio = par(z_ratio_name.c_str()).doubleValue();
  auto y_ratio = par(y_ratio_name.c_str()).doubleValue();

  double sum = x_ratio + z_ratio + y_ratio;
  if (sum == 0) {
    x_ratio = 1.;
    z_ratio = 1.;
    y_ratio = 1.;
    sum = 3.;
  }

  gate.X_error_rate = gate.pauli_error_rate * (x_ratio / sum);
  gate.Y_error_rate = gate.pauli_error_rate * (y_ratio / sum);
  gate.Z_error_rate = gate.pauli_error_rate * (z_ratio / sum);
  gate.No_error_ceil = 1 - gate.pauli_error_rate;
  gate.X_error_ceil = gate.No_error_ceil + gate.X_error_rate;
  gate.Z_error_ceil = gate.X_error_ceil + gate.Z_error_rate;
  gate.Y_error_ceil = gate.Z_error_ceil + gate.Y_error_rate;
  return gate;
}

TwoQubitGateErrorModel StationaryQubit::SetTwoQubitGateErrorCeilings(std::string gate_name) {
  TwoQubitGateErrorModel gate;

  // prepare parameter names
  std::string err_rate_name = std::string(gate_name) + std::string("_error_rate");
  auto ix_ratio_name = gate_name + std::string("_IX_error_ratio");
  auto xi_ratio_name = gate_name + std::string("_XI_error_ratio");
  auto xx_rationame = gate_name + std::string("_XX_error_ratio");

  auto iz_ratio_name = gate_name + std::string("_IZ_error_ratio");
  auto zi_ratio_name = gate_name + std::string("_ZI_error_ratio");
  auto zz_ratio_name = gate_name + std::string("_ZZ_error_ratio");

  auto iy_ratio_name = gate_name + std::string("_IY_error_ratio");
  auto yi_ratio_name = gate_name + std::string("_YI_error_ratio");
  auto yy_ratio_name = gate_name + std::string("_YY_error_ratio");

  // get error ratios from parameter
  gate.pauli_error_rate = par(err_rate_name.c_str()).doubleValue();
  double ix_ratio = par(ix_ratio_name.c_str()).doubleValue();
  double xi_ratio = par(xi_ratio_name.c_str()).doubleValue();
  double xx_ratio = par(xx_rationame.c_str()).doubleValue();

  double iz_ratio = par(iz_ratio_name.c_str()).doubleValue();
  double zi_ratio = par(zi_ratio_name.c_str()).doubleValue();
  double zz_ratio = par(zz_ratio_name.c_str()).doubleValue();

  double iy_ratio = par(iy_ratio_name.c_str()).doubleValue();
  double yi_ratio = par(yi_ratio_name.c_str()).doubleValue();
  double yy_ratio = par(yy_ratio_name.c_str()).doubleValue();

  double ratio_sum = ix_ratio + xi_ratio + xx_ratio + iz_ratio + zi_ratio + zz_ratio + iy_ratio + yi_ratio + yy_ratio;

  if (ratio_sum == 0) {
    ix_ratio = 1.;
    xi_ratio = 1.;
    xx_ratio = 1.;
    iz_ratio = 1.;
    zi_ratio = 1.;
    zz_ratio = 1.;
    iy_ratio = 1.;
    yi_ratio = 1.;
    yy_ratio = 1.;
    ratio_sum = 9.;
  }

  gate.IX_error_rate = gate.pauli_error_rate * (ix_ratio / ratio_sum);
  gate.XI_error_rate = gate.pauli_error_rate * (xi_ratio / ratio_sum);
  gate.XX_error_rate = gate.pauli_error_rate * (xx_ratio / ratio_sum);

  gate.IZ_error_rate = gate.pauli_error_rate * (iz_ratio / ratio_sum);
  gate.ZI_error_rate = gate.pauli_error_rate * (zi_ratio / ratio_sum);
  gate.ZZ_error_rate = gate.pauli_error_rate * (zz_ratio / ratio_sum);

  gate.IY_error_rate = gate.pauli_error_rate * (iy_ratio / ratio_sum);
  gate.YI_error_rate = gate.pauli_error_rate * (yi_ratio / ratio_sum);
  gate.YY_error_rate = gate.pauli_error_rate * (yy_ratio / ratio_sum);

  gate.No_error_ceil = 1 - gate.pauli_error_rate;
  gate.IX_error_ceil = gate.No_error_ceil + gate.IX_error_rate;
  gate.XI_error_ceil = gate.IX_error_ceil + gate.XI_error_rate;
  gate.XX_error_ceil = gate.XI_error_ceil + gate.XX_error_rate;

  gate.IZ_error_ceil = gate.XX_error_ceil + gate.IZ_error_rate;
  gate.ZI_error_ceil = gate.IZ_error_ceil + gate.ZI_error_rate;
  gate.ZZ_error_ceil = gate.ZI_error_ceil + gate.ZZ_error_rate;

  gate.IY_error_ceil = gate.ZZ_error_ceil + gate.IY_error_rate;
  gate.YI_error_ceil = gate.IY_error_ceil + gate.YI_error_rate;
  gate.YY_error_ceil = gate.YI_error_ceil + gate.YY_error_rate;
  return gate;
}

/*
void StationaryQubit::setEmissionPauliError(){
    if(par("GOD_Xerror") || par("GOD_Zerror")){
        //std::cout<<"node["<<node_address<<"] qnic["<<qnic_address<<"] Emitting from "<<this<<"X="<<par("GOD_Xerror").str()<<"Z="<<par("GOD_Zerror").str()<<"\n";
        error("There shouldn't be an error existing before photon emission. This error may have not been reinitialized since last use. Better check!");
    }
    double rand = dblrand();//Gives a random double between 0.0 ~ 1.0
    if(rand < emission_error.No_error_ceil){
               //Qubit will end up with no error
               //EV<<"No error :"<<rand<<" < "<<No_error_ceil<<"\n";
    }else if(emission_error.No_error_ceil <= rand && rand < emission_error.X_error_ceil && (emission_error.No_error_ceil!=emission_error.X_error_ceil)){
               //X error
                par("GOD_Xerror") = true;
                //EV<<"Xerror :"<<No_error_ceil<<"<="<<rand<<" < "<<X_error_ceil<<"\n";
    }else if(emission_error.X_error_ceil <= rand && rand < emission_error.Z_error_ceil && (emission_error.X_error_ceil!=emission_error.Z_error_ceil)){
               //Z error
                par("GOD_Zerror") = true;
               // EV<<"Zerror :"<<X_error_ceil<<"<="<<rand<<" < "<<Z_error_ceil<<"\n";
    }else if(emission_error.Z_error_ceil <= rand && rand < emission_error.Y_error_ceil && (emission_error.Z_error_ceil!=emission_error.Y_error_ceil)){
               //Y error
                par("GOD_Xerror") = true;
                par("GOD_Zerror") = true;
                //EV<<"Yerror :"<<Z_error_ceil<<"<="<<rand<<" < "<<Y_error_ceil<<"\n";
   }else{
       std::cout<<rand<<"\n";
       std::cout<<"emission_error.No_error_ceil = "<<emission_error.No_error_ceil<<"\n";
       std::cout<<"emission_error.X_error_ceil = "<<emission_error.X_error_ceil<<"\n";
       std::cout<<"emission_error.Y_error_ceil = "<<emission_error.Y_error_ceil<<"\n";
       std::cout<<"emission_error.Z_error_ceil = "<<emission_error.Z_error_ceil<<"\n";
       error("Either the error ceilings or the random double generator is wrong.");
   }
}
*/

bool StationaryQubit::measure_X() {
  // Need to add noise here later
  apply_single_qubit_gate_error(Measurement_error, this);
  return !par("GOD_Zerror");
}

/**
 *  Returns true if the measurement outcome was correct
 */
bool StationaryQubit::measure_Y() {
  // Need to add noise here later
  apply_single_qubit_gate_error(Measurement_error, this);
  bool error = true;
  if (par("GOD_Zerror") && par("GOD_Xerror")) {
    error = false;
  }
  if (!par("GOD_Zerror") && !par("GOD_Xerror")) {
    error = false;
  }
  return error;
  // return !(par("GOD_Zerror") || par("GOD_Xerror"));
}

bool StationaryQubit::measure_Z() {
  // Need to add noise here later
  apply_single_qubit_gate_error(Measurement_error, this);
  return !par("GOD_Xerror");
}

// Convert X to Z, and Z to X error. Therefore, Y error stays as Y.
void StationaryQubit::Hadamard_gate() {
  // Need to add noise here later
  apply_single_qubit_gate_error(Hgate_error, this);
  bool z = par("GOD_Zerror");
  par("GOD_Zerror") = par("GOD_Xerror");
  par("GOD_Xerror") = z;
}

void StationaryQubit::Z_gate() {
  // Need to add noise here later
  apply_single_qubit_gate_error(Zgate_error, this);
  par("GOD_Zerror") = !par("GOD_Zerror");
}

void StationaryQubit::X_gate() {
  // Need to add noise here later
  apply_single_qubit_gate_error(Xgate_error, this);
  par("GOD_Xerror") = !par("GOD_Xerror");
}

void StationaryQubit::CNOT_gate(StationaryQubit *control_qubit) {
  // Need to add noise here later
  apply_two_qubit_gate_error(CNOTgate_error, this, control_qubit);
  // std::cout<<"this X err = "<<this->par("GOD_Xerror").boolValue()<<"\n";

  if (control_qubit->par("GOD_Xerror")) {
    // X error propagates from control to target. If an X error is already present, then it cancels out.
    par("GOD_Xerror") = !par("GOD_Xerror");
  }

  if (par("GOD_Zerror")) {
    // Z error propagates from target to control. If an Z error is already present, then it cancels out.
    control_qubit->par("GOD_Zerror") = !control_qubit->par("GOD_Zerror");
  }
}

// This is invoked whenever a photon is emitted out from this particular qubit.
void StationaryQubit::setBusy() {
  isBusy = true;
  emitted_time = simTime();
  updated_time = simTime();  // Should be no error at this time.
  par("photon_emitted_at") = emitted_time.dbl();
  par("last_updated_at") = updated_time.dbl();
  par("isBusy") = true;
  // GUI part
  if (hasGUI()) {
    getDisplayString().setTagArg("i", 1, "red");
  }
}

// Re-initialization of this stationary qubit
// This is called at the beginning of the simulation (in initialization() above), and whenever it is reinitialized via the RealTimeController.
void StationaryQubit::setFree(bool consumed) {
  num_purified = 0;
  locked = false;
  locked_ruleset_id = -1;
  locked_rule_id = -1;
  action_index = -1;

  isBusy = false;
  allocated = false;
  emitted_time = -1;
  updated_time = -1;
  /**/
  partner_measured = false;
  completely_mixed = false;
  excited_or_relaxed = false;
  GOD_dm_Zerror = false;
  GOD_dm_Xerror = false;
  Density_Matrix_Collapsed << -111, -111, -111, -111;
  no_density_matrix_nullptr_entangled_partner_ok = false;
  par("photon_emitted_at") = emitted_time.dbl();
  par("last_updated_at") = updated_time.dbl();
  par("GOD_Xerror") = false;
  par("GOD_Zerror") = false;
  par("GOD_CMerror") = false;
  par("GOD_EXerror") = false;
  par("GOD_REerror") = false;
  par("GOD_CMerror") = false;
  par("isBusy") = false;
  par("GOD_entangled_stationaryQubit_address") = -1;
  par("GOD_entangled_node_address") = -1;
  par("GOD_entangled_qnic_address") = -1;
  par("GOD_entangled_qnic_type") = -1;
  entangled_partner = nullptr;
  EV << "!!!!!!!!!!!!!! Freeing this qubit!!!" << this << "\n";
  // GUI part
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

bool StationaryQubit::checkBusy() {
  Enter_Method("checkBusy()");
  return isBusy;
}

/*To avoid disturbing this qubit.*/
void StationaryQubit::Lock(unsigned long rs_id, int rule_id, int action_id) {
  if (rs_id == -1 || rule_id == -1 || action_id == -1) {
    error("ruleset_id || rule_id || action_id == -1");
  }
  locked = true;
  locked_ruleset_id = rs_id;  // Used to identify what this qubit is locked for.
  locked_rule_id = rule_id;
  action_index = action_id;
  // std::cout<<"*******************"<<this<<"in node["<<this->node_address<<"]Locked. Rsid="<<locked_ruleset_id<<" rid="<<locked_rule_id<<" aid="<<action_index<<"\n";

  if (hasGUI()) {
    bubble("Locked!");
    getDisplayString().setTagArg("i", 1, "purple");
  }
}

void StationaryQubit::Unlock() {
  locked = false;
  locked_ruleset_id = -1;  // Used to identify what this qubit is locked for.
  locked_rule_id = -1;
  action_index = -1;

  if (hasGUI()) {
    bubble("Unlocked!");
    getDisplayString().setTagArg("i", 1, "pink");
  }
}

bool StationaryQubit::isLocked() { return locked; }

void StationaryQubit::Allocate() {
  allocated = true;
  if (hasGUI()) {
    bubble("Allocated!");
    getDisplayString().setTagArg("i", 1, "purple");
  }
}

void StationaryQubit::Deallocate() { allocated = false; }

bool StationaryQubit::isAllocated() { return allocated; }

/**
 * \brief Generate photon entangled with the memory
 * \warning Shouldn't we destroy a possibly existing photon object before? <- No, I dont think so...
 */
PhotonicQubit *StationaryQubit::generateEntangledPhoton() {
  Enter_Method("generateEntangledPhoton()");
  photon = new PhotonicQubit("Photon");
  // To simulate the actual physical entangled partner, not what the system thinks!!! we need this.

  // This photon is entangled with.... node_address = node's index
  photon->setNodeEntangledWith(node_address);

  // qnic_address != qnic_index. qnic_index is not unique because there are 3 types.
  photon->setQNICEntangledWith(qnic_address);

  // stationaryQubit_address = StationaryQubit's index
  photon->setStationaryQubitEntangledWith(stationaryQubit_address);
  photon->setQNICtypeEntangledWith(qnic_type);
  photon->setEntangled_with(this);
  return photon;
}

/**
 * \brief Emit photon
 *
 * \param pulse: 0 for nothing, 1 for first, 2 for last, 3 for first and last
 *
 * The stationary qubit shouldn't be already busy.
 */
void StationaryQubit::emitPhoton(int pulse) {
  Enter_Method("emitPhoton()");
  if (checkBusy()) {
    error("Requested a photon emission to a busy qubit... this should not happen!");
    return;
  }
  PhotonicQubit *pk = generateEntangledPhoton();
  if (pulse & STATIONARYQUBIT_PULSE_BEGIN) pk->setFirst(true);
  if (pulse & STATIONARYQUBIT_PULSE_END) pk->setLast(true);
  if (pulse & STATIONARYQUBIT_PULSE_BOUND) pk->setKind(3);
  float jitter_timing = normal(0, std);
  float abso = fabs(jitter_timing);
  scheduleAt(simTime() + abso, pk);  // cannot send back in time, so only positive lag
}

// This gets direcltly invoked when darkcount happened in BellStateAnalyzer.cc.
void StationaryQubit::setCompletelyMixedDensityMatrix() {
  this->Density_Matrix_Collapsed << (double)1 / (double)2, 0, 0, (double)1 / (double)2;
  // std::cout<<"Dm completely mixed "<<this->Density_Matrix_Collapsed<<"\n";
  this->completely_mixed = true;
  this->excited_or_relaxed = false;

  if (this->entangled_partner != nullptr) {  // Eliminate entangled information
    this->entangled_partner->entangled_partner = nullptr;
    this->entangled_partner = nullptr;
  }
  this->par("GOD_CMerror") = true;
  this->par("GOD_EXerror") = false;
  this->par("GOD_REerror") = false;
  this->par("GOD_Xerror") = false;
  this->par("GOD_Zerror") = false;
  this->GOD_dm_Xerror = false;
  this->GOD_dm_Zerror = false;
  if (hasGUI()) {
    bubble("Completely mixed. darkcount");
    getDisplayString().setTagArg("i", 1, "black");
  }
}

// This gets invoked in memory error simulation or by BellStateAnalyzer if photonLoss + darkcount.
void StationaryQubit::setExcitedDensityMatrix() {
  Density_Matrix_Collapsed << 1, 0, 0, 0;  // Overwrite density matrix
  completely_mixed = false;
  excited_or_relaxed = true;  // It is excited

  par("GOD_EXerror") = true;
  par("GOD_REerror") = false;
  par("GOD_CMerror") = false;
  par("GOD_Xerror") = false;
  par("GOD_Zerror") = false;
  GOD_dm_Xerror = false;
  GOD_dm_Zerror = false;

  if (hasGUI()) {
    bubble("Completely mixed. darkcount");
    getDisplayString().setTagArg("i", 1, "white");
  }

  if (this->entangled_partner != nullptr) {  // If it used to be entangled...
    // error("What?");
    this->entangled_partner->updated_time = simTime();
    // For GUI
    this->entangled_partner->par("last_updated_at") = simTime().dbl();
    // This also eliminates the entanglement information.
    this->entangled_partner->setCompletelyMixedDensityMatrix();
  }  // else it is already not entangled. e.g. excited -> relaxed.
}

void StationaryQubit::setRelaxedDensityMatrix() {
  Density_Matrix_Collapsed << 0, 0, 0, 1;
  completely_mixed = false;
  excited_or_relaxed = true;
  par("GOD_EXerror") = false;
  par("GOD_REerror") = true;
  par("GOD_CMerror") = false;
  par("GOD_Xerror") = false;
  par("GOD_Zerror") = false;
  GOD_dm_Xerror = false;
  GOD_dm_Zerror = false;
  if (hasGUI()) {
    bubble("Completely mixed. darkcount");
    getDisplayString().setTagArg("i", 1, "white");
  }

  // Still entangled
  if (this->entangled_partner != nullptr) {
    this->entangled_partner->updated_time = simTime();
    // For GUI
    this->entangled_partner->par("last_updated_at") = simTime().dbl();
    this->entangled_partner->setCompletelyMixedDensityMatrix();
  }  // else it is already not entangled. e.g. excited -> relaxed.
}

void StationaryQubit::setEntangledPartnerInfo(StationaryQubit *partner) {
  // When BSA succeeds, this method gets invoked to store entangled partner information.
  // This will also be sent classically to the partner node afterwards.
  entangled_partner = partner;

  par("GOD_entangled_stationaryQubit_address") = partner->par("stationaryQubit_address");
  par("GOD_entangled_node_address") = partner->par("node_address");
  par("GOD_entangled_qnic_address") = partner->par("qnic_address");
  par("GOD_entangled_qnic_type") = partner->par("qnic_type");
}

/*Add another X error. If an X error already exists, then they cancel out*/
void StationaryQubit::addXerror() {
  // error("Huh...?");
  bool Xerr = this->par("GOD_Xerror");
  // Switches true to false or false to true
  this->par("GOD_Xerror") = !Xerr;
  // this->par("GOD_Xerror") = true;
}

/*Add another Z error. If an Z error already exists, then they cancel out*/
void StationaryQubit::addZerror() {
  bool Zerr = this->par("GOD_Zerror");
  // Switches true to false or false to true
  this->par("GOD_Zerror") = !Zerr;
  // this->par("GOD_Zerror") = true;
}

// Only tracks error propagation. If two booleans (Alice and Bob) agree (truetrue or falsefalse), keep the purified ebit.
bool StationaryQubit::Xpurify(StationaryQubit *resource_qubit /*Controlled*/) {
  // std::cout<<"X puri\n";
  // This could result in completelty mixed, excited, relaxed, which also affects the entangled partner.
  apply_memory_error(this);
  apply_memory_error(resource_qubit);
  /*Target qubit*/ this->CNOT_gate(resource_qubit /*controlled qubit*/);
  bool meas = this->measure_Z();
  return meas;
}

bool StationaryQubit::Zpurify(StationaryQubit *resource_qubit /*Target*/) {
  // std::cout<<"Z puri\n";
  apply_memory_error(this);  // This could result in completelty mixed, excited, relaxed, which also affects the entangled partner.
  apply_memory_error(resource_qubit);
  /*Target qubit*/ resource_qubit->CNOT_gate(this /*controlled qubit*/);
  this->Hadamard_gate();
  bool meas = this->measure_Z();
  return meas;
}

// Single qubit memory error based on Markov-Chain
void StationaryQubit::apply_memory_error(StationaryQubit *qubit) {
  if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok)
    error("This must not happen in apply memory error");

  // If no memory error occurs, or if the state is completely mixed, skip this memory error simulation.
  if (qubit->memory_err.error_rate == 0) {
    // error("memory error is set to 0. If on purpose, that is fine. Comment this out.");
    return;
  }

  // Check when the error got updated last time.
  // Errors will be performed depending on the difference between that time and the current time.
  double time_evolution = simTime().dbl() - qubit->updated_time.dbl();
  double time_evolution_microsec = time_evolution * 1000000 /** 100*/;
  if (time_evolution_microsec > 0) {
    // Perform Monte-Carlo error simulation on this qubit.
    bool has_x_err = qubit->par("GOD_Xerror");
    bool has_z_err = qubit->par("GOD_Zerror");
    bool is_excited = qubit->par("GOD_EXerror");
    bool is_relaxed = qubit->par("GOD_REerror");
    bool is_completely_mixed = qubit->par("GOD_CMerror");
    if (qubit->completely_mixed != is_completely_mixed) {
      error("[apply_memory_error] Completely mixed flag not matching");
    }
    if (qubit->excited_or_relaxed != is_excited && qubit->excited_or_relaxed != is_relaxed) {
      error("[apply_memory_error] Relaxed/Excited flag not matching");
    }

    bool skip_exponentiation = false;
    for (int i = 0; i < Memory_Transition_matrix.cols(); i++) {
      if (Memory_Transition_matrix(0, i) == 1) {
        // Do not to the exponentiation! Eigen will mess up the exponentiation anyway...
        skip_exponentiation = true;
        break;
      }
    }

    MatrixXd transition_mat(7, 7);
    if (!skip_exponentiation) {
      // calculate time evoluted error matrix: Q^(time_evolution_microsec) in Eq 5.3
      MatrixPower<MatrixXd> q_pow(Memory_Transition_matrix);
      transition_mat = q_pow(time_evolution_microsec);
    } else {
      transition_mat = Memory_Transition_matrix;
    }

    // validate transition_mat
    for (int r = 0; r < transition_mat.rows(); r++) {
      double col_sum = 0;
      for (int i = 0; i < transition_mat.cols(); i++) {
        col_sum += transition_mat(r, i);
      }
      if (col_sum > 1.01 || col_sum < 0.99) {
        std::cout << "col_sum = " << col_sum << std::endl;
        error("Row of the transition matrix does not sum up to 1.");
      }
    }

    if (std::isnan(transition_mat(0, 0))) {
      std::cout << "transition_mat: " << transition_mat << std::endl;
      error("Transition maatrix is NaN. This is Eigen's fault.");
    }

    // pi(0 ~ 6) vector in Eq 5.3
    MatrixXd pi_vector(1, 7);  // I, X, Z, Y, Ex, Re, Cm
    if (is_excited) {
      pi_vector << 0, 0, 0, 0, 1, 0, 0;  // excitation error
    } else if (is_relaxed) {
      pi_vector << 0, 0, 0, 0, 0, 1, 0;  // relaxation error
    } else if (is_completely_mixed) {
      pi_vector << 0, 0, 0, 0, 0, 0, 1;  // completely mixed error
    } else if (has_z_err && has_x_err) {
      pi_vector << 0, 0, 0, 1, 0, 0, 0;  // Y error
    } else if (has_z_err && !has_x_err) {
      pi_vector << 0, 0, 1, 0, 0, 0, 0;  // Z error
    } else if (!has_z_err && has_x_err) {
      pi_vector << 0, 1, 0, 0, 0, 0, 0;  // X error
    } else {
      pi_vector << 1, 0, 0, 0, 0, 0, 0;  // No error
    }
    // pi(t) in Eq 5.3
    // Clean, X, Z, Y, Excited, Relaxed
    MatrixXd output_vector(1, 6);
    // take error rate vector from DynamicTransitionMatrix Eq 5.3
    output_vector = pi_vector * transition_mat;

    /* this prepares the sectors for Monte-Carlo. later, we'll pick a random value and check with this sectors.
     *
     * 0.0    clean_ceil             z_ceil              excited_ceil                       1.0
     *  |          |                   |                      |                              |
     *  | No Error | X Error | Z Error | Y Error | Excitation | Relaxation | Cmpletely Mixed |
     *                       |                   |                         |
     *                    x_ceil               y_ceil                relaxed_ceil
     */
    double clean_ceil = output_vector(0, 0);
    double x_ceil = clean_ceil + output_vector(0, 1);
    double z_ceil = x_ceil + output_vector(0, 2);
    double y_ceil = z_ceil + output_vector(0, 3);
    double excited_ceil = y_ceil + output_vector(0, 4);
    double relaxed_ceil = excited_ceil + output_vector(0, 5);

    // Gives a random double between 0.0 ~ 1.0
    double rand = dblrand();

    if (rand < clean_ceil) {
      // Qubit will end up with no error
      qubit->par("GOD_Xerror") = false;
      qubit->par("GOD_Zerror") = false;
    } else if (clean_ceil <= rand && rand < x_ceil && (clean_ceil != x_ceil)) {
      // X error
      qubit->par("GOD_Xerror") = true;
      qubit->par("GOD_Zerror") = false;
      DEBUG_memory_X_count++;
    } else if (x_ceil <= rand && rand < z_ceil && (x_ceil != z_ceil)) {
      // Z error
      qubit->par("GOD_Xerror") = false;
      qubit->par("GOD_Zerror") = true;
      DEBUG_memory_Z_count++;
    } else if (z_ceil <= rand && rand < y_ceil && (z_ceil != y_ceil)) {
      // Y error
      qubit->par("GOD_Xerror") = true;
      qubit->par("GOD_Zerror") = true;
      DEBUG_memory_Y_count++;
    } else if (y_ceil <= rand && rand < excited_ceil && (y_ceil != excited_ceil)) {
      // Excitation error
      // Also sets the partner completely mixed if it used to be entangled.
      qubit->setExcitedDensityMatrix();
    } else if (excited_ceil <= rand && rand < relaxed_ceil && (excited_ceil != relaxed_ceil)) {
      // Excitation error
      // Also sets the partner completely mixed if it used to be entangled.
      qubit->setRelaxedDensityMatrix();
    } else {
      // Memory completely mixed error

      // If this qubit still used to be entangled with another qubit.
      if (qubit->entangled_partner != nullptr) {
        qubit->entangled_partner->updated_time = simTime();
        qubit->entangled_partner->par("last_updated_at") = simTime().dbl();
        // Break entanglement with partner. Overwrite its density matrix.
        qubit->entangled_partner->setCompletelyMixedDensityMatrix();
      }
      qubit->setCompletelyMixedDensityMatrix();
    }
  }
  qubit->updated_time = simTime();
  qubit->par("last_updated_at") = simTime().dbl();
}

Matrix2cd StationaryQubit::getErrorMatrix(StationaryQubit *qubit) {
  Matrix2cd err;

  if (qubit->par("GOD_CMerror") || qubit->par("GOD_REerror") || qubit->par("GOD_REerror")) {
    // std::cout<<"CMerror: "<<qubit<<" in node["<<node_address<<"]\n";
    // std::cout<<"***CHECK: "<<qubit<<" in node["<<node_address<<"]***\n";
    // std::cout<<"par cm = "<<qubit->par("GOD_CMerror").boolValue()<<", completely_mixed = "<<qubit->completely_mixed<<"\n";
    /// std::cout<<"par re= "<<qubit->par("GOD_REerror").boolValue()<<", par cm = "<<qubit->par("GOD_EXerror").boolValue()<<", re/ex = "<<qubit->excited_or_relaxed<<"\n";
    // std::cout<<"******************************\n";

    error("CMerror in getErrorMatrix. Not supposed to happen.");
  }

  if (qubit->par("GOD_Zerror") && qubit->par("GOD_Xerror")) {  // Y error on this qubit
    err = Pauli.Y;
    EV << "Y error"
       << "\n";
  } else if (qubit->par("GOD_Zerror") && !qubit->par("GOD_Xerror")) {  // Z error
    err = Pauli.Z;
    EV << "Z error"
       << "\n";
  } else if (!qubit->par("GOD_Zerror") && qubit->par("GOD_Xerror")) {  // X error
    err = Pauli.X;
    EV << "X error"
       << "\n";
  } else {
    err = Pauli.I;
    EV << "I error"
       << "\n";
  }
  return err;
}

// returns the density matrix of the Bell pair with error. This assumes that this is entangled with another stationary qubit.
// Measurement output will be based on this matrix, as long as it is still entnagled.
quantum_state StationaryQubit::getQuantumState() {
  if (this->excited_or_relaxed || this->entangled_partner->excited_or_relaxed) {
    error("Wrong");
  }
  // std::cout<<"!!!!CHECK: "<<this->entangled_partner<<" in node["<<this->entangled_partner->node_address<<"]!!!\n";
  // std::cout<<"par cm = "<<this->entangled_partner->par("GOD_CMerror").boolValue()<<", completely_mixed = "<<this->entangled_partner->completely_mixed<<"\n";
  // std::cout<<"par re= "<<this->entangled_partner->par("GOD_REerror").boolValue()<<", par cm = "<<this->entangled_partner->par("GOD_EXerror").boolValue()<<", re/ex =
  // "<<this->entangled_partner->excited_or_relaxed<<"\n"; std::cout<<"!!!!!!!!!!!!!!!!!!\n";

  Matrix4cd combined_errors = kroneckerProduct(getErrorMatrix(this), getErrorMatrix(entangled_partner)).eval();

  // If Pauli errors
  Vector4cd ideal_Bell_state(1 / sqrt(2), 0, 0, 1 / sqrt(2));  // Assumes that the state is a 2 qubit state |00> + |11>

  // std::cout<<"CMerror: "<<this<<" in node["<<node_address<<"]\n";
  // std::cout<<"~~~CHECK: "<<this<<" in node["<<node_address<<"]~~~\n";
  // std::cout<<"par cm = "<<this->par("GOD_CMerror").boolValue()<<", completely_mixed = "<<this->completely_mixed<<"\n";
  // std::cout<<"par re= "<<this->par("GOD_REerror").boolValue()<<", par cm = "<<this->par("GOD_EXerror").boolValue()<<", re/ex = "<<this->excited_or_relaxed<<"\n";
  // std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~\n";

  // Matrix4cd combined_errors = kroneckerProduct(getErrorMatrix(this),getErrorMatrix(entangled_partner)).eval();

  // EV<<"Combined errors  = "<<combined_errors<<"\n";
  Vector4cd actual_Bell_state = combined_errors * ideal_Bell_state;
  // EV<<"Current physical state is = "<<actual_Bell_state;
  Matrix4cd density_matrix = actual_Bell_state * actual_Bell_state.adjoint();
  // EV<<"dm = "<<density_matrix<<"\n";

  quantum_state q;
  q.state_in_density_matrix = density_matrix;
  q.state_in_ket = actual_Bell_state;
  return q;
}

void StationaryQubit::apply_single_qubit_gate_error(SingleGateErrorModel gate, StationaryQubit *qubit) {
  if (gate.pauli_error_rate == 0) {
    return;
  }
  double rand = dblrand();  // Gives a random double between 0.0 ~ 1.0

  if (rand <= gate.No_error_ceil) {
    // Do nothing
    // std::cout<<"Single qubit gate I error\n";
  } else if (gate.No_error_ceil < rand && rand <= gate.X_error_ceil && (gate.No_error_ceil != gate.X_error_ceil)) {
    // X error
    qubit->addXerror();
    // std::cout<<"Single qubit gate X error\n";
  } else if (gate.X_error_ceil < rand && rand <= gate.Z_error_ceil && (gate.X_error_ceil != gate.Z_error_ceil)) {
    // Z error
    qubit->addZerror();
    // std::cout<<"Single qubit gate Z error\n";
  } else {
    // Y error
    qubit->addZerror();
    qubit->addXerror();
    // std::cout<<"Single qubit gate Y error\n";
  }
}

void StationaryQubit::apply_two_qubit_gate_error(TwoQubitGateErrorModel gate, StationaryQubit *first_qubit, StationaryQubit *second_qubit) {
  if (gate.pauli_error_rate == 0) {
    return;
  }

  double rand = dblrand();  // Gives a random double between 0.0 ~ 1.0

  if (rand <= gate.No_error_ceil) {
    // Do nothing
  } else if (gate.No_error_ceil < rand && rand <= gate.IX_error_ceil && (gate.No_error_ceil != gate.IX_error_ceil)) {
    // IX error
    // error("IX");
    first_qubit->addXerror();
  } else if (gate.IX_error_ceil < rand && rand <= gate.XI_error_ceil && (gate.IX_error_ceil != gate.XI_error_ceil)) {
    // XI error
    // error("XI");
    second_qubit->addXerror();
  } else if (gate.XI_error_ceil < rand && rand <= gate.XX_error_ceil && (gate.XI_error_ceil != gate.XX_error_ceil)) {
    // XX error
    // error("XX");
    first_qubit->addXerror();
    second_qubit->addXerror();
  } else if (gate.XX_error_ceil < rand && rand <= gate.IZ_error_ceil && (gate.XX_error_ceil != gate.IZ_error_ceil)) {
    // IZ error
    // error("IZ");
    first_qubit->addZerror();
  } else if (gate.IZ_error_ceil < rand && rand <= gate.ZI_error_ceil && (gate.IZ_error_ceil != gate.ZI_error_ceil)) {
    // ZI error
    // error("ZI");
    second_qubit->addZerror();
  } else if (gate.ZI_error_ceil < rand && rand <= gate.ZZ_error_ceil && (gate.ZI_error_ceil != gate.ZZ_error_ceil)) {
    // ZZ error
    // error("ZZ");
    first_qubit->addZerror();
    second_qubit->addZerror();
  } else if (gate.ZZ_error_ceil < rand && rand <= gate.IY_error_ceil && (gate.ZZ_error_ceil != gate.IY_error_ceil)) {
    // IY error
    // error("IY");
    first_qubit->addXerror();
    first_qubit->addZerror();
  } else if (gate.IY_error_ceil < rand && rand <= gate.YI_error_ceil && (gate.IY_error_ceil != gate.YI_error_ceil)) {
    // YI error
    // error("YI");
    second_qubit->addXerror();
    second_qubit->addZerror();
  } else {
    // error("YY");
    // YY error
    first_qubit->addXerror();
    first_qubit->addZerror();
    second_qubit->addXerror();
    second_qubit->addZerror();
  }
}

measurement_outcome StationaryQubit::measure_density_independent() {
  // std::cout<<"\n\n\n\n\n\n\n\nMEASURING!!!\n";

  // if(this->getIndex() == 71 && this->node_address == 3)
  //	std::cout<<"---measuring "<<this<<" in node["<<node_address<<"]\n";
  // std::cout<<"---measuring "<<this<<" in qnic["<<qnic_index<<"] in node["<<node_address<<"]\n";
  if (this->entangled_partner == nullptr && this->Density_Matrix_Collapsed(0, 0).real() == -111) {
    // EV<<entangled_partner<<"\n";
    std::cout << Density_Matrix_Collapsed << "\n";
    std::cout << "Measuring" << this << "in node[" << node_address << "]\n";
    std::cout << this->getIndex() << "\n";
    error("Measuring a qubit that is not entangled with another qubit. Probably not what you want! Check whether address for each node is unique!!!");
  }
  measurement_operator this_measurement = Random_Measurement_Basis_Selection();  // Select basis randomly
  char Output;
  char Output_is_plus;

  // Add memory error depending on the idle time. If excited/relaxed, this will immediately break entanglement, leaving the other qubit as completely mixed.
  apply_memory_error(this);

  // Measurement gate error
  apply_single_qubit_gate_error(Measurement_error, this);

  // This becomes nullptr if this qubit got excited/relaxed or measured.
  if (this->entangled_partner != nullptr) {
    if (this->entangled_partner->entangled_partner == nullptr) {
      std::cout << "Entanglement not tracked well between partners." << this << " in node[" << node_address << "]\n";
      std::cout << "Partner must be " << this->entangled_partner << " in node[" << this->entangled_partner->node_address << "]\n";
      error("NO!");
    }
    if (this->partner_measured) error("Entangled partner not nullptr but partner already measured....? Probably wrong.");
    if (this->completely_mixed || this->excited_or_relaxed) {
      std::cout << "[Error]" << this << "\n";
      error("Entangled but completely mixed / Excited / Relaxed ? Probably wrong.");
    }
    // Also do the same on the partner if it is still entangled! This could break the entanglement due to relaxation/excitation error!
    apply_memory_error(this->entangled_partner);
  }

  /*-For debugging-*/
  char GOD_state = 'F';  // Completely mixed

  if (this->par("GOD_EXerror").boolValue())
    GOD_state = 'E';
  else if (this->par("GOD_EXerror").boolValue())
    GOD_state = 'R';
  else if (this->par("GOD_CMerror").boolValue())
    GOD_state = 'C';
  else if (!this->par("GOD_Xerror").boolValue() && this->par("GOD_Zerror").boolValue())  // To check stabilizers....
    GOD_state = 'Z';
  else if (this->par("GOD_Xerror").boolValue() && !this->par("GOD_Zerror").boolValue())
    GOD_state = 'X';
  else if (this->par("GOD_Xerror").boolValue() && this->par("GOD_Zerror").boolValue())
    GOD_state = 'Y';

  /*---------------*/

  if (this->completely_mixed != this->par("GOD_CMerror").boolValue()) {
    error("Cm track wrong\n");
  }
  if (this->excited_or_relaxed && !this->par("GOD_EXerror") && !this->par("GOD_REerror")) {
    std::cout << "this->excited_or_relaxed = " << this->excited_or_relaxed << ", !this->par(GOD_REerror)=" << !this->par("GOD_REerror").boolValue()
              << "!this->par(GOD_EXerror)=" << !this->par("GOD_EXerror").boolValue();
    error("Ex/Re track wrong\n");
  }
  // if there is an entanglement
  if (this->entangled_partner != nullptr) {
    // This qubit is nullptr
    if (this->entangled_partner->entangled_partner == nullptr) {
      error("Entangled_partner track wrong\n");
    }
    // check completely mixed tracking
    if (this->entangled_partner->completely_mixed != this->entangled_partner->par("GOD_CMerror").boolValue()) {
      error("Partner Cm track wrong\n");
    }
    // check excited and relaxation tracking
    if (this->entangled_partner->excited_or_relaxed && !this->entangled_partner->par("GOD_EXerror") && !this->entangled_partner->par("GOD_REerror")) {
      error("Partner Re/Ex track wrong\n");
    }
    if (this->entangled_partner->par("GOD_CMerror") || this->entangled_partner->par("GOD_REerror") || this->entangled_partner->par("GOD_EXerror")) {
      // error("Partner CM/Re/Ex track wrong\n");
    }
  }

  // if the partner qubit is measured,
  if (this->partner_measured || this->completely_mixed || this->excited_or_relaxed) {  // The case when the density matrix is completely local to this qubit.
    // if this qubit is said to be completely mixed and no set value
    if (this->completely_mixed && !this->par("GOD_CMerror")) {
      error("Mismatch between flags.");
    }
    if (this->Density_Matrix_Collapsed(0, 0).real() == -111) {  // We always need some kind of density matrix inside this if statement.
      error("Single qubit density matrix not stored properly after partner's measurement, excitation/relaxation error.");
    }
    bool Xerr = this->par("GOD_Xerror");
    bool Zerr = this->par("GOD_Zerror");
    // This qubit's density matrix was created when the partner measured his own.
    // Because this qubit can be measured after that, we need to update the stored density matrix according to new errors occurred due to memory error.

    if (Xerr != GOD_dm_Xerror) {  // Another X error to the dm.
      // error("NO");
      Density_Matrix_Collapsed = Pauli.X * Density_Matrix_Collapsed * Pauli.X.adjoint();
    }
    if (Zerr != GOD_dm_Zerror) {  // Another Z error to the dm.
      // error("NO!");
      Density_Matrix_Collapsed = Pauli.Z * Density_Matrix_Collapsed * Pauli.Z.adjoint();
    }

    // std::cout<<"Not entangled anymore. Density matrix is "<<Density_Matrix_Collapsed<<"\n";

    Complex Prob_plus = (Density_Matrix_Collapsed * this_measurement.plus.adjoint() * this_measurement.plus).trace();
    Complex Prob_minus = (Density_Matrix_Collapsed * this_measurement.minus.adjoint() * this_measurement.minus).trace();
    double dbl = dblrand();
    if (dbl < Prob_plus.real()) {
      Output = '+';
      Output_is_plus = true;
    } else {
      Output = '-';
      Output_is_plus = false;
    }
    // std::cout<<"\n This qubit was "<<this_measurement.basis<<"("<<Output<<"). \n";
  } else if (!this->partner_measured && !this->completely_mixed && !this->excited_or_relaxed && this->entangled_partner != nullptr) {
    // This is assuming that this is some other qubit is entangled. Only Pauli errors are assumed.
    quantum_state current_state = getQuantumState();
    EV << "Current entangled state is " << current_state.state_in_ket << "\n";

    bool Xerr = this->par("GOD_Xerror");
    bool Zerr = this->par("GOD_Zerror");
    // std::cout<<"Entangled state is "<<current_state.state_in_ket<<"\n";

    Complex Prob_plus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.plus, meas_op.identity).eval().adjoint() *
                        kroneckerProduct(this_measurement.plus, meas_op.identity).eval() * current_state.state_in_ket;
    Complex Prob_minus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.minus, meas_op.identity).eval().adjoint() *
                         kroneckerProduct(this_measurement.minus, meas_op.identity).eval() * current_state.state_in_ket;

    // std::cout<<"Measurement basis = "<<this_measurement.basis<<"P(+) = "<<Prob_plus.real()<<", P(-) = "<<Prob_minus.real()<<"\n";
    double dbl = dblrand();

    Vector2cd ms;
    if (dbl < Prob_plus.real()) {  // Measurement output was plus
      Output = '+';
      ms = this_measurement.plus_ket;
      Output_is_plus = true;
    } else {  // Otherwise, it was negative.
      Output = '-';
      ms = this_measurement.minus_ket;
      Output_is_plus = false;
    }
    // Now we have to calculate the density matrix of a single qubit that used to be entangled with this.
    Matrix2cd partners_dm, normalized_partners_dm;
    partners_dm =
        kroneckerProduct(ms.adjoint(), meas_op.identity).eval() * current_state.state_in_density_matrix * kroneckerProduct(ms.adjoint(), meas_op.identity).eval().adjoint();
    normalized_partners_dm = partners_dm / partners_dm.trace();
    EV << "kroneckerProduct(ms.adjoint(),meas_op.identity).eval() = " << kroneckerProduct(ms.adjoint(), meas_op.identity).eval() << "\n";
    EV << "dm = " << current_state.state_in_density_matrix << "\n";
    EV << "State was " << kroneckerProduct(ms.adjoint(), meas_op.identity).eval() * current_state.state_in_density_matrix << "\n";
    EV << "\n This qubit was " << this_measurement.basis << "(" << Output << "). Partner's dm is now = " << normalized_partners_dm << "\n";
    entangled_partner->Density_Matrix_Collapsed = normalized_partners_dm;

    // We actually do not need this as long as deleting entangled_partner completely is totally fine.
    entangled_partner->partner_measured = true;
    // if(entangled_partner->getIndex() == 71 && entangled_partner->node_address == 3)
    //	std::cout<<"-------------------"<<entangled_partner<<" in node["<<entangled_partner->node_address<<"] overwritten dm.\n";

    // Break entanglement.
    entangled_partner->entangled_partner = nullptr;
    // Save what error it had, when this density matrix was calculated.
    // Error may get updated in the future, so we need to track what error has been considered already in the dm.
    entangled_partner->GOD_dm_Xerror = entangled_partner->par("GOD_Xerror");
    entangled_partner->GOD_dm_Zerror = entangled_partner->par("GOD_Zerror");
  } else {
    error("Check condition in measure func.");
  }
  measurement_outcome o;
  o.basis = this_measurement.basis;
  o.outcome_is_plus = Output_is_plus;
  o.GOD_clean = GOD_state;
  return o;
}

measurement_operator StationaryQubit::Random_Measurement_Basis_Selection() {
  measurement_operator this_measurement;
  double dbl = dblrand();  // Random double value for random basis selection.
  EV << "Random dbl = " << dbl << "! \n ";

  if (dbl < ((double)1 / (double)3)) {  // X measurement!
    EV << "X measurement\n";
    this_measurement.plus = meas_op.X_basis.plus;
    this_measurement.minus = meas_op.X_basis.minus;
    this_measurement.basis = meas_op.X_basis.basis;
    this_measurement.plus_ket = meas_op.X_basis.plus_ket;
    this_measurement.minus_ket = meas_op.X_basis.minus_ket;
  } else if (dbl >= ((double)1 / (double)3) && dbl < ((double)2 / (double)3)) {
    EV << "Z measurement\n";
    this_measurement.plus = meas_op.Z_basis.plus;
    this_measurement.minus = meas_op.Z_basis.minus;
    this_measurement.basis = meas_op.Z_basis.basis;
    this_measurement.plus_ket = meas_op.Z_basis.plus_ket;
    this_measurement.minus_ket = meas_op.Z_basis.minus_ket;
  } else {
    EV << "Y measurement\n";
    this_measurement.plus = meas_op.Y_basis.plus;
    this_measurement.minus = meas_op.Y_basis.minus;
    this_measurement.basis = meas_op.Y_basis.basis;
    this_measurement.plus_ket = meas_op.Y_basis.plus_ket;
    this_measurement.minus_ket = meas_op.Y_basis.minus_ket;
  }
  return this_measurement;
}

// Assumes that this qubit is entangled with another one, as Bell pair 00+11. 1st qubit is self, 2nd is partner.
// When do we perform measurements? I think we can just ignore the success/fail of entanglement attempt, and measure it beforehand anyway. Waiting cause error.
// How do we know when to measure though?
// Return value: 1 if output is +, 0 if output is -.
/*std::bitset<1> StationaryQubit::measure_density(char basis_this_qubit){
    if(entangled_partner == nullptr){
        error("Measuring a qubit that is not entangled with another qubit. Not allowed!");
    }
    //if(entangled_partner->emitted_time=-1 && single_qubit_dm == null){
    //    error("Something is wrong.");
    }

    //todo Check if entangled state has collapsed already (partner qubit measured already).

    //if not, then measure it and get the output (density matrix required)!
    apply_memory_error(this);//Noise due to idle time in memory. This updates the par("GOD_Zerror") and par("GOD_Xerror") of this particular qubit.
    quantum_state current_state = getQuantumState();//Get the density matrix of the Bell pair that involves this particular qubit.
    measurement_output_probabilities p = getOutputProbabilities(current_state, basis_this_qubit);
    EV <<" P(++) = "<<p.probability_plus_plus<<", P(+-) = "<<p.probability_plus_minus<<", P(-+) = "<<p.probability_minus_plus<<", P(--) = "<<p.probability_minus_minus<<"\n";
    double rand = dblrand();//Gives a random double between 0.0 ~ 1.0

    std::bitset<2> output(0);//by default, output is -- (in binary 00)
    if(rand < p.probability_plus_plus){
        //Output is ++
        output.set(0);//00->01
        output.set(1);//01->11
        EV<<"Output is ++"<<output<<"\n";
    }else if(p.probability_plus_plus <= rand && rand < (p.probability_plus_plus+p.probability_plus_minus)){
        //Output is +-
        output.set(1);//00->10
        EV<<"Output is +-"<<output<<"\n";
    }else if((p.probability_plus_plus+p.probability_plus_minus) <= rand && rand < (p.probability_plus_plus+p.probability_plus_minus+p.probability_minus_plus)){
        //Output is -+
        output.set(0);//00->01
        EV<<"Output is -+"<<output<<"\n";
    }else{
        EV<<"Output is --"<<output<<"\n";
    }
    //return output.test(1);
}*/

}  // namespace modules
}  // namespace quisp
