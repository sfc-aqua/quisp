/** \file HardwareMonitor.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief HardwareMonitor
 */
#include "HardwareMonitor.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>

#include "classical_messages_m.h"

namespace quisp {
namespace modules {

using namespace rules;

// HardwareMonitor is also responsible for calculating the rssi/oka's protocol/fidelity calculate and give it to the RoutingDaemon
void HardwareMonitor::initialize(int stage) {
  EV_INFO << "HardwareMonitor booted\n";

  output_count initial;
  initial.minus_minus = 0;
  initial.minus_plus = 0;
  initial.plus_minus = 0;
  initial.plus_plus = 0;
  initial.total_count = 0;

  Pauli.X << 0, 1, 1, 0;
  Pauli.Y << 0, Complex(0, -1), Complex(0, 1), 0;
  Pauli.Z << 1, 0, 0, -1;
  Pauli.I << 1, 0, 0, 1;

  num_qnic_rp = par("number_of_qnics_rp");
  num_qnic_r = par("number_of_qnics_r");
  num_qnic = par("number_of_qnics");
  num_qnic_total = num_qnic + num_qnic_r + num_qnic_rp;

  /* This is used to keep your own tomography data, and also to match and store the received partner's tomography data */
  // Assumes link tomography only between neighbors.
  all_temporal_tomography_output_holder = new Temporal_Tomography_Output_Holder[num_qnic_total];
  all_temporal_tomography_runningtime_holder = new link_cost[num_qnic_total];

  /* Once all_temporal_tomography_output_holder is filled in, those data are summarized into basis based measurement outcome table.
   * This accumulates the number of ++, +-, -+ and -- for each basis combination.*/

  // Raw count table for tomography per link/qnic
  tomography_data = new raw_data[num_qnic_total];

  for (int i = 0; i < num_qnic_total; i++) {
    tomography_data[i].insert(std::make_pair("XX", initial));
    tomography_data[i].insert(std::make_pair("XY", initial));
    tomography_data[i].insert(std::make_pair("XZ", initial));
    tomography_data[i].insert(std::make_pair("ZX", initial));
    tomography_data[i].insert(std::make_pair("ZY", initial));
    tomography_data[i].insert(std::make_pair("ZZ", initial));
    tomography_data[i].insert(std::make_pair("YX", initial));
    tomography_data[i].insert(std::make_pair("YY", initial));
    tomography_data[i].insert(std::make_pair("YZ", initial));
    all_temporal_tomography_runningtime_holder[i].Bellpair_per_sec = -1;
    all_temporal_tomography_runningtime_holder[i].tomography_measurements = -1;
    all_temporal_tomography_runningtime_holder[i].tomography_time = -1;
  }

  /*This keeps which node is connected to which local qnic.*/
  tomography_output_filename = par("tomography_output_filename").str();
  file_dir_name = par("file_dir_name").str();
  do_link_level_tomography = par("link_tomography");
  num_purification = par("initial_purification");
  X_Purification = par("X_purification");
  Z_Purification = par("Z_purification");
  Purification_type = par("Purification_type");
  num_measure = par("num_measure");
  my_address = par("address");

  if (stage == 0) {
    return;
  }

  prepareNeighborTable();
  WATCH_MAP(neighbor_table);

  if (do_link_level_tomography) {
    for (auto it = neighbor_table.cbegin(); it != neighbor_table.cend(); ++it) {
      // You don't want 2 separate tomography processes to run for each link.
      // Not a very good solution, but makes sure that only 1 request per link is generated.
      if (my_address > it->second.neighborQNode_address) {
        EV << "Generating tomography rules... for node " << it->second.neighborQNode_address << "\n";
        LinkTomographyRequest *pk = new LinkTomographyRequest("LinkTomographyRequest");
        pk->setDestAddr(it->second.neighborQNode_address);
        pk->setSrcAddr(my_address);
        pk->setKind(6);
        send(pk, "RouterPort$o");
      }
    }
  }
}

unsigned long HardwareMonitor::createUniqueId() {
  auto time = SimTime().str();
  auto address = std::to_string(my_address);
  auto random = std::to_string(intuniform(0, 10000000));
  auto hash_seed = address + time + random;
  std::hash<std::string> hash_fn;
  size_t t = hash_fn(hash_seed);
  unsigned long ruleset_id = static_cast<long>(t);
  std::cout << "Hash is " << hash_seed << ", t = " << t << ", long = " << ruleset_id << "\n";
  return ruleset_id;
}

std::unique_ptr<InterfaceInfo> HardwareMonitor::findInterfaceByNeighborAddr(int neighbor_address) {
  for (auto it = neighbor_table.cbegin(); it != neighbor_table.cend(); ++it) {
    if (it->second.neighborQNode_address == neighbor_address) {
      // return unique_ptr<InterfaceInfo>(new InterfaceInfo(it->second));
      return std::make_unique<InterfaceInfo>(it->second);
    }
  }
  return nullptr;
}

void HardwareMonitor::handleMessage(cMessage *msg) {
  if (dynamic_cast<LinkTomographyRequest *>(msg) != nullptr) {
    /* Received a tomography request from neighbor */
    LinkTomographyRequest *request = check_and_cast<LinkTomographyRequest *>(msg);

    auto info = findInterfaceByNeighborAddr(request->getSrcAddr());
    if (info == nullptr) {
      error("1. Something is wrong when finding out local qnic address from neighbor address in neighbor_table.");
    }

    /*Prepare an acknowledgment*/
    LinkTomographyAck *pk = new LinkTomographyAck("LinkTomographyAck");
    pk->setSrcAddr(my_address);
    pk->setDestAddr(request->getSrcAddr());
    pk->setKind(6);
    pk->setQnic_index(info->qnic.index);
    pk->setQnic_type(info->qnic.type);

    send(pk, "RouterPort$o");
    return;
  }

  if (dynamic_cast<LinkTomographyAck *>(msg) != nullptr) {
    /*Received an acknowledgment for tomography from neighbor.*/
    LinkTomographyAck *ack = check_and_cast<LinkTomographyAck *>(msg);

    /*Create and send RuleSets*/
    int partner_address = ack->getSrcAddr();

    auto my_qnic_info = findInterfaceByNeighborAddr(partner_address);
    if (my_qnic_info == nullptr) {
      error("2. Something is wrong when finding out local qnic address from neighbor address in neighbor_table.");
    }

    // RuleSets sent for this node and the partner node.
    long RuleSet_id = createUniqueId();
    sendLinkTomographyRuleSet(my_address, partner_address, my_qnic_info->qnic.type, my_qnic_info->qnic.index, RuleSet_id);

    QNIC_type partner_qnic_type = ack->getQnic_type();
    int partner_qnic_index = ack->getQnic_index();
    sendLinkTomographyRuleSet(partner_address, my_address, partner_qnic_type, partner_qnic_index, RuleSet_id);
    return;
  }

  if (dynamic_cast<LinkTomographyResult *>(msg) != nullptr) {
    /*Link tomography measurement result/basis from neighbor received.*/
    LinkTomographyResult *result = check_and_cast<LinkTomographyResult *>(msg);

    // Get QNIC info from neighbor address.
    QNIC local_qnic = search_QNIC_from_Neighbor_QNode_address(result->getPartner_address());
    auto it = all_temporal_tomography_output_holder[local_qnic.address].find(result->getCount_id());
    if (it != all_temporal_tomography_output_holder[local_qnic.address].end()) {
      EV << "Data already found.";
      tomography_outcome temp = it->second;
      if (result->getSrcAddr() == my_address) {
        temp.my_basis = result->getBasis();
        temp.my_output_is_plus = result->getOutput_is_plus();
        temp.my_GOD_clean = result->getGOD_clean();
      } else {
        temp.partner_basis = result->getBasis();
        temp.partner_output_is_plus = result->getOutput_is_plus();
        temp.partner_GOD_clean = result->getGOD_clean();
      }
      it->second = temp;
    } else {
      EV << "Fresh data";
      tomography_outcome temp;
      if (result->getSrcAddr() == my_address) {
        temp.my_basis = result->getBasis();
        temp.my_output_is_plus = result->getOutput_is_plus();
        temp.my_GOD_clean = result->getGOD_clean();
      } else {
        temp.partner_basis = result->getBasis();
        temp.partner_output_is_plus = result->getOutput_is_plus();
        temp.partner_GOD_clean = result->getGOD_clean();
      }
      all_temporal_tomography_output_holder[local_qnic.address].insert(std::make_pair(result->getCount_id(), temp));
    }

    if (result->getFinish() != -1) {
      // Pick the slower tomography time MIN(self,partner).
      if (all_temporal_tomography_runningtime_holder[local_qnic.address].tomography_time < result->getFinish()) {
        all_temporal_tomography_runningtime_holder[local_qnic.address].Bellpair_per_sec = (double)result->getMax_count() / result->getFinish().dbl();
        all_temporal_tomography_runningtime_holder[local_qnic.address].tomography_measurements = result->getMax_count();
        all_temporal_tomography_runningtime_holder[local_qnic.address].tomography_time = result->getFinish();

        // std::cout<<"Tomo done "<<local_qnic.address<<", in
        // node["<<my_address<<"] \n";
        StopEmitting *pk = new StopEmitting("StopEmitting");
        pk->setQnic_address(local_qnic.address);
        pk->setDestAddr(my_address);
        pk->setSrcAddr(my_address);
        send(pk, "RouterPort$o");
      }
    }
    return;
  }
}

void HardwareMonitor::finish() {
  // std::string file_name =
  // std::string("Tomography_")+std::string(getSimulation()->getNetworkType()->getFullName());

  std::string file_name = tomography_output_filename;
  std::string df = "\"default\"";
  if (file_name.compare(df) == 0) {
    std::cout << df << "==" << file_name << "\n";
    file_name = std::string("Tomography_") + std::string(getSimulation()->getNetworkType()->getFullName());
  } else {
    std::cout << df << "!=" << file_name << "\n";
  }

  std::string file_name_dm = file_name + std::string("_dm");

  std::ofstream tomography_stats(file_name, std::ios_base::app);
  std::ofstream tomography_dm(file_name_dm, std::ios_base::app);
  std::cout << "Opened new file to write.\n";

  // EV<<"This is just a test!\n";

  // EV<<"num_qnic_total = "<<num_qnic_total;
  for (int i = 0; i < num_qnic_total; i++) {
    int meas_total = 0;
    int GOD_clean_pair_total = 0;
    int GOD_X_pair_total = 0;
    int GOD_Z_pair_total = 0;
    int GOD_Y_pair_total = 0;

    // std::cout<<"\n \n \n \n \n QNIC["<<i<<"] \n";
    for (auto it = all_temporal_tomography_output_holder[i].cbegin(); it != all_temporal_tomography_output_holder[i].cend(); ++it) {
      // EV <<"Count["<< it->first << "] = " << it->second.my_basis << ", " <<
      // it->second.my_output_is_plus << ", " << it->second.partner_basis << ",
      // "  << it->second.partner_output_is_plus << " " << "\n";
      std::string basis_combination = "";
      basis_combination += it->second.my_basis;
      basis_combination += it->second.partner_basis;
      if (tomography_data[i].count(basis_combination) != 1) {
        // EV<<it->second.my_basis<<", "<<it->second.partner_basis<<" =
        // "<<basis_combination<<"\n";
        error("Basis combination for tomography not found\n");
      }
      tomography_data[i][basis_combination].total_count++;
      meas_total++;

      EV << it->second.my_GOD_clean << "," << it->second.partner_GOD_clean << "\n";
      if ((it->second.my_GOD_clean == 'F' && it->second.partner_GOD_clean == 'F') || (it->second.my_GOD_clean == 'X' && it->second.partner_GOD_clean == 'X') ||
          (it->second.my_GOD_clean == 'Z' && it->second.partner_GOD_clean == 'Z') || (it->second.my_GOD_clean == 'Y' && it->second.partner_GOD_clean == 'Y')) {
        GOD_clean_pair_total++;
      } else if ((it->second.my_GOD_clean == 'X' && it->second.partner_GOD_clean == 'F') || (it->second.my_GOD_clean == 'F' && it->second.partner_GOD_clean == 'X')) {
        GOD_X_pair_total++;
      } else if ((it->second.my_GOD_clean == 'Z' && it->second.partner_GOD_clean == 'F') || (it->second.my_GOD_clean == 'F' && it->second.partner_GOD_clean == 'Z')) {
        GOD_Z_pair_total++;
      } else if ((it->second.my_GOD_clean == 'Y' && it->second.partner_GOD_clean == 'F') || (it->second.my_GOD_clean == 'F' && it->second.partner_GOD_clean == 'Y')) {
        GOD_Y_pair_total++;
      }

      if (it->second.my_output_is_plus && it->second.partner_output_is_plus) {
        tomography_data[i][basis_combination].plus_plus++;
        // std::cout<<"basis_combination(++)="<<basis_combination <<" is now
        // "<<tomography_data[i][basis_combination].plus_plus<<"\n";
      } else if (it->second.my_output_is_plus && !it->second.partner_output_is_plus) {
        tomography_data[i][basis_combination].plus_minus++;
        // std::cout<<"basis_combination(++)="<<basis_combination <<" is now
        // "<<tomography_data[i][basis_combination].plus_minus<<"\n";
      } else if (!it->second.my_output_is_plus && it->second.partner_output_is_plus) {
        tomography_data[i][basis_combination].minus_plus++;
        // std::cout<<"basis_combination(++)="<<basis_combination <<" is now
        // "<<tomography_data[i][basis_combination].minus_plus<<"\n";
      } else if (!it->second.my_output_is_plus && !it->second.partner_output_is_plus) {
        tomography_data[i][basis_combination].minus_minus++;
        // std::cout<<"basis_combination(++)="<<basis_combination <<" is now
        // "<<tomography_data[i][basis_combination].minus_minus<<"\n";
      } else
        error("This should not happen though..... ?");
    }
    // For each qnic/link, reconstruct the dm.
    Matrix4cd density_matrix_reconstructed = reconstruct_Density_Matrix(i);

    // todo: Will need to clean this up in a separate function
    Vector4cd Bellpair;
    Bellpair << 1 / sqrt(2), 0, 0, 1 / sqrt(2);
    Matrix4cd density_matrix_ideal = Bellpair * Bellpair.adjoint();
    double fidelity = (density_matrix_reconstructed.real() * density_matrix_ideal.real()).trace();

    Vector4cd Bellpair_X;
    Bellpair_X << 0, 1 / sqrt(2), 1 / sqrt(2), 0;
    Matrix4cd density_matrix_X = Bellpair_X * Bellpair_X.adjoint();
    double Xerr_rate = (density_matrix_reconstructed.real() * density_matrix_X.real()).trace();
    EV << "Xerr = " << Xerr_rate << "\n";

    Vector4cd Bellpair_Z;
    Bellpair_Z << 1 / sqrt(2), 0, 0, -1 / sqrt(2);
    Matrix4cd density_matrix_Z = Bellpair_Z * Bellpair_Z.adjoint();
    double Zerr_rate = (density_matrix_reconstructed.real() * density_matrix_Z.real()).trace();
    Complex checkZ = Bellpair_Z.adjoint() * density_matrix_reconstructed * Bellpair_Z;
    EV << "Zerr = " << Zerr_rate << " or, " << checkZ.real() << "+" << checkZ.imag() << "\n";

    Vector4cd Bellpair_Y;
    Bellpair_Y << 0, Complex(0, 1 / sqrt(2)), Complex(0, -1 / sqrt(2)), 0;
    Matrix4cd density_matrix_Y = Bellpair_Y * Bellpair_Y.adjoint();
    double Yerr_rate = (density_matrix_reconstructed.real() * density_matrix_Y.real()).trace();
    EV << "Yerr = " << Yerr_rate << "\n";

    double bellpairs_per_sec = 10;
    double link_cost = (double)100000000 / (fidelity * fidelity * all_temporal_tomography_runningtime_holder[i].Bellpair_per_sec);
    if (link_cost < 1) {
      link_cost = 1;
    }
    auto info = findConnectionInfoByQnicAddr(i);
    if (info == nullptr) {
      error("info not found");
    }
    InterfaceInfo interface = getQnicInterfaceByQnicAddr(info->qnic.index, info->qnic.type);
    cModule *this_node = this->getParentModule()->getParentModule();
    cModule *neighbor_node = interface.qnic.pointer->gate("qnic_quantum_port$o")->getNextGate()->getNextGate()->getOwnerModule();
    cChannel *channel = interface.qnic.pointer->gate("qnic_quantum_port$o")->getNextGate()->getChannel();
    double dis = channel->par("distance");

    /*if(this_node->getModuleType() == QNodeType &&
    neighbor_node->getModuleType() == QNodeType){ if(my_address >
    inf.neighbor_address){ return;
        }
    }*/

    tomography_dm << this_node->getFullName() << "<--->" << neighbor_node->getFullName() << "\n";
    tomography_dm << "REAL\n";
    tomography_dm << density_matrix_reconstructed.real() << "\n";
    tomography_dm << "IMAGINARY\n";
    tomography_dm << density_matrix_reconstructed.imag() << "\n";

    std::cout << this_node->getFullName() << "<-->QuantumChannel{cost=" << link_cost << ";distance=" << dis << "km;fidelity=" << fidelity
              << ";bellpair_per_sec=" << bellpairs_per_sec << ";}<-->" << neighbor_node->getFullName() << "; F=" << fidelity << "; X=" << Xerr_rate << "; Z=" << Zerr_rate
              << "; Y=" << Yerr_rate << endl;
    tomography_stats << this_node->getFullName() << "<-->QuantumChannel{cost=" << link_cost << ";distance=" << dis << "km;fidelity=" << fidelity
                     << ";bellpair_per_sec=" << all_temporal_tomography_runningtime_holder[i].Bellpair_per_sec
                     << ";tomography_time=" << all_temporal_tomography_runningtime_holder[i].tomography_time
                     << ";tomography_measurements=" << all_temporal_tomography_runningtime_holder[i].tomography_measurements << ";actualmeas=" << meas_total
                     << "; GOD_clean_pair_total=" << GOD_clean_pair_total << "; GOD_X_pair_total=" << GOD_X_pair_total << "; GOD_Y_pair_total=" << GOD_Y_pair_total
                     << "; GOD_Z_pair_total=" << GOD_Z_pair_total << ";}<-->" << neighbor_node->getFullName() << "; F=" << fidelity << "; X=" << Xerr_rate << "; Z=" << Zerr_rate
                     << "; Y=" << Yerr_rate << endl;
  }

  tomography_stats.close();
  tomography_dm.close();
  std::cout << "Closed file to write.\n";
}

Matrix4cd HardwareMonitor::reconstruct_Density_Matrix(int qnic_id) {
  // II
  double S00 = 1.0;
  double S01 = (double)tomography_data[qnic_id]["XX"].plus_plus / (double)tomography_data[qnic_id]["XX"].total_count -
               (double)tomography_data[qnic_id]["XX"].plus_minus / (double)tomography_data[qnic_id]["XX"].total_count +
               (double)tomography_data[qnic_id]["XX"].minus_plus / (double)tomography_data[qnic_id]["XX"].total_count -
               (double)tomography_data[qnic_id]["XX"].minus_minus / (double)tomography_data[qnic_id]["XX"].total_count;
  double S02 = (double)tomography_data[qnic_id]["YY"].plus_plus / (double)tomography_data[qnic_id]["YY"].total_count -
               (double)tomography_data[qnic_id]["YY"].plus_minus / (double)tomography_data[qnic_id]["YY"].total_count +
               (double)tomography_data[qnic_id]["YY"].minus_plus / (double)tomography_data[qnic_id]["YY"].total_count -
               (double)tomography_data[qnic_id]["YY"].minus_minus / (double)tomography_data[qnic_id]["YY"].total_count;
  double S03 = (double)tomography_data[qnic_id]["ZZ"].plus_plus / (double)tomography_data[qnic_id]["ZZ"].total_count -
               (double)tomography_data[qnic_id]["ZZ"].plus_minus / (double)tomography_data[qnic_id]["ZZ"].total_count +
               (double)tomography_data[qnic_id]["ZZ"].minus_plus / (double)tomography_data[qnic_id]["ZZ"].total_count -
               (double)tomography_data[qnic_id]["ZZ"].minus_minus / (double)tomography_data[qnic_id]["ZZ"].total_count;
  // XX
  double S10 = (double)tomography_data[qnic_id]["XX"].plus_plus / (double)tomography_data[qnic_id]["XX"].total_count +
               (double)tomography_data[qnic_id]["XX"].plus_minus / (double)tomography_data[qnic_id]["XX"].total_count -
               (double)tomography_data[qnic_id]["XX"].minus_plus / (double)tomography_data[qnic_id]["XX"].total_count -
               (double)tomography_data[qnic_id]["XX"].minus_minus / (double)tomography_data[qnic_id]["XX"].total_count;
  double S11 = (double)tomography_data[qnic_id]["XX"].plus_plus / (double)tomography_data[qnic_id]["XX"].total_count -
               (double)tomography_data[qnic_id]["XX"].plus_minus / (double)tomography_data[qnic_id]["XX"].total_count -
               (double)tomography_data[qnic_id]["XX"].minus_plus / (double)tomography_data[qnic_id]["XX"].total_count +
               (double)tomography_data[qnic_id]["XX"].minus_minus / (double)tomography_data[qnic_id]["XX"].total_count;
  double S12 = (double)tomography_data[qnic_id]["XY"].plus_plus / (double)tomography_data[qnic_id]["XY"].total_count -
               (double)tomography_data[qnic_id]["XY"].plus_minus / (double)tomography_data[qnic_id]["XY"].total_count -
               (double)tomography_data[qnic_id]["XY"].minus_plus / (double)tomography_data[qnic_id]["XY"].total_count +
               (double)tomography_data[qnic_id]["XY"].minus_minus / (double)tomography_data[qnic_id]["XY"].total_count;
  double S13 = (double)tomography_data[qnic_id]["XZ"].plus_plus / (double)tomography_data[qnic_id]["XZ"].total_count -
               (double)tomography_data[qnic_id]["XZ"].plus_minus / (double)tomography_data[qnic_id]["XZ"].total_count -
               (double)tomography_data[qnic_id]["XZ"].minus_plus / (double)tomography_data[qnic_id]["XZ"].total_count +
               (double)tomography_data[qnic_id]["XZ"].minus_minus / (double)tomography_data[qnic_id]["XZ"].total_count;
  // YY
  double S20 = (double)tomography_data[qnic_id]["YY"].plus_plus / (double)tomography_data[qnic_id]["YY"].total_count +
               (double)tomography_data[qnic_id]["YY"].plus_minus / (double)tomography_data[qnic_id]["YY"].total_count -
               (double)tomography_data[qnic_id]["YY"].minus_plus / (double)tomography_data[qnic_id]["YY"].total_count -
               (double)tomography_data[qnic_id]["YY"].minus_minus / (double)tomography_data[qnic_id]["YY"].total_count;
  double S21 = (double)tomography_data[qnic_id]["YX"].plus_plus / (double)tomography_data[qnic_id]["YX"].total_count -
               (double)tomography_data[qnic_id]["YX"].plus_minus / (double)tomography_data[qnic_id]["YX"].total_count -
               (double)tomography_data[qnic_id]["YX"].minus_plus / (double)tomography_data[qnic_id]["YX"].total_count +
               (double)tomography_data[qnic_id]["YX"].minus_minus / (double)tomography_data[qnic_id]["YX"].total_count;
  double S22 = (double)tomography_data[qnic_id]["YY"].plus_plus / (double)tomography_data[qnic_id]["YY"].total_count -
               (double)tomography_data[qnic_id]["YY"].plus_minus / (double)tomography_data[qnic_id]["YY"].total_count -
               (double)tomography_data[qnic_id]["YY"].minus_plus / (double)tomography_data[qnic_id]["YY"].total_count +
               (double)tomography_data[qnic_id]["YY"].minus_minus / (double)tomography_data[qnic_id]["YY"].total_count;
  double S23 = (double)tomography_data[qnic_id]["YZ"].plus_plus / (double)tomography_data[qnic_id]["YZ"].total_count -
               (double)tomography_data[qnic_id]["YZ"].plus_minus / (double)tomography_data[qnic_id]["YZ"].total_count -
               (double)tomography_data[qnic_id]["YZ"].minus_plus / (double)tomography_data[qnic_id]["YZ"].total_count +
               (double)tomography_data[qnic_id]["YZ"].minus_minus / (double)tomography_data[qnic_id]["YZ"].total_count;
  // ZZ
  double S30 = (double)tomography_data[qnic_id]["ZZ"].plus_plus / (double)tomography_data[qnic_id]["ZZ"].total_count +
               (double)tomography_data[qnic_id]["ZZ"].plus_minus / (double)tomography_data[qnic_id]["ZZ"].total_count -
               (double)tomography_data[qnic_id]["ZZ"].minus_plus / (double)tomography_data[qnic_id]["ZZ"].total_count -
               (double)tomography_data[qnic_id]["ZZ"].minus_minus / (double)tomography_data[qnic_id]["ZZ"].total_count;
  double S31 = (double)tomography_data[qnic_id]["ZX"].plus_plus / (double)tomography_data[qnic_id]["ZX"].total_count -
               (double)tomography_data[qnic_id]["ZX"].plus_minus / (double)tomography_data[qnic_id]["ZX"].total_count -
               (double)tomography_data[qnic_id]["ZX"].minus_plus / (double)tomography_data[qnic_id]["ZX"].total_count +
               (double)tomography_data[qnic_id]["ZX"].minus_minus / (double)tomography_data[qnic_id]["ZX"].total_count;
  double S32 = (double)tomography_data[qnic_id]["ZY"].plus_plus / (double)tomography_data[qnic_id]["ZY"].total_count -
               (double)tomography_data[qnic_id]["ZY"].plus_minus / (double)tomography_data[qnic_id]["ZY"].total_count -
               (double)tomography_data[qnic_id]["ZY"].minus_plus / (double)tomography_data[qnic_id]["ZY"].total_count +
               (double)tomography_data[qnic_id]["ZY"].minus_minus / (double)tomography_data[qnic_id]["ZY"].total_count;
  double S33 = (double)tomography_data[qnic_id]["ZZ"].plus_plus / (double)tomography_data[qnic_id]["ZZ"].total_count -
               (double)tomography_data[qnic_id]["ZZ"].plus_minus / (double)tomography_data[qnic_id]["ZZ"].total_count -
               (double)tomography_data[qnic_id]["ZZ"].minus_plus / (double)tomography_data[qnic_id]["ZZ"].total_count +
               (double)tomography_data[qnic_id]["ZZ"].minus_minus / (double)tomography_data[qnic_id]["ZZ"].total_count;
  double S = (double)tomography_data[qnic_id]["XX"].plus_plus / (double)tomography_data[qnic_id]["XX"].total_count +
             (double)tomography_data[qnic_id]["XX"].plus_minus / (double)tomography_data[qnic_id]["XX"].total_count +
             (double)tomography_data[qnic_id]["XX"].minus_plus / (double)tomography_data[qnic_id]["XX"].total_count +
             (double)tomography_data[qnic_id]["XX"].minus_minus / (double)tomography_data[qnic_id]["XX"].total_count;

  EV << S00 << ", " << S01 << ", " << S02 << ", " << S03 << "\n";
  EV << S10 << ", " << S11 << ", " << S12 << ", " << S13 << "\n";
  EV << S20 << ", " << S21 << ", " << S22 << ", " << S23 << "\n";
  EV << S30 << ", " << S31 << ", " << S32 << ", " << S33 << "\n";

  Matrix4cd density_matrix_reconstructed =
      (double)1 / (double)4 *
      (S01 * kroneckerProduct(Pauli.I, Pauli.X).eval() + S02 * kroneckerProduct(Pauli.I, Pauli.Y).eval() + S03 * kroneckerProduct(Pauli.I, Pauli.Z).eval() +
       S10 * kroneckerProduct(Pauli.X, Pauli.I).eval() + S11 * kroneckerProduct(Pauli.X, Pauli.X).eval() + S12 * kroneckerProduct(Pauli.X, Pauli.Y).eval() +
       S13 * kroneckerProduct(Pauli.X, Pauli.Z).eval() + S20 * kroneckerProduct(Pauli.Y, Pauli.I).eval() + S21 * kroneckerProduct(Pauli.Y, Pauli.X).eval() +
       S22 * kroneckerProduct(Pauli.Y, Pauli.Y).eval() + S23 * kroneckerProduct(Pauli.Y, Pauli.Z).eval() + S30 * kroneckerProduct(Pauli.Z, Pauli.I).eval() +
       S31 * kroneckerProduct(Pauli.Z, Pauli.X).eval() + S32 * kroneckerProduct(Pauli.Z, Pauli.Y).eval() + S33 * kroneckerProduct(Pauli.Z, Pauli.Z).eval() +
       S * kroneckerProduct(Pauli.I, Pauli.I).eval());

  EV << "DM = " << density_matrix_reconstructed << "\n";
  return density_matrix_reconstructed;
  /*
  Vector4cd Bellpair;
  Bellpair << 1/sqrt(2), 0, 0, 1/sqrt(2);
  Matrix4cd density_matrix_ideal = Bellpair*Bellpair.adjoint();
  double fidelity = (density_matrix_reconstructed.real()*
  density_matrix_ideal.real() ).trace();
  //double Xerr = (density_matrix_reconstructed.real()*
  (density_matrix_ideal.real()) ).trace();

  EV<<"FOR QNIC["<<qnic_id<<"] \n";
  EV<<"F = "<<fidelity<<"\n";

  Vector4cd Bellpair_X;
  Bellpair_X << 0,1/sqrt(2), 1/sqrt(2),0;
  Matrix4cd density_matrix_X = Bellpair_X*Bellpair_X.adjoint();
  double Xerr_rate = (density_matrix_reconstructed.real()*
  density_matrix_X.real() ).trace(); EV<<"Xerr = "<<Xerr_rate<<"\n";

  Vector4cd Bellpair_Z;
  Bellpair_Z << 1/sqrt(2),0,0,-1/sqrt(2);
  Matrix4cd density_matrix_Z = Bellpair_Z*Bellpair_Z.adjoint();
  double Zerr_rate = (density_matrix_reconstructed.real()*
  density_matrix_Z.real() ).trace(); Complex checkZ =
  Bellpair_Z.adjoint()*density_matrix_reconstructed*Bellpair_Z; EV<<"Zerr =
  "<<Zerr_rate<<" or, "<<checkZ.real()<<"+"<<checkZ.imag()<<"\n";

  Vector4cd Bellpair_Y;
  Bellpair_Y << 0,Complex(0,1/sqrt(2)),Complex(0,-1/sqrt(2)),0;
  Matrix4cd density_matrix_Y = Bellpair_Y*Bellpair_Y.adjoint();
  double Yerr_rate = (density_matrix_reconstructed.real()*
  density_matrix_Y.real() ).trace(); EV<<"Yerr = "<<Yerr_rate<<"\n";

  tomography_stats << "F = "<<fidelity<<" X = "<<Xerr_rate<<" Z ="<<Zerr_rate<<"
  Y = "<<Yerr_rate<<endl;

  double bellpairs_per_sec = 10;
  double link_cost =(double)1/(fidelity*fidelity*bellpairs_per_sec);
  writeToFile_Topology_with_LinkCost(qnic_id, link_cost, fidelity,
  bellpairs_per_sec);

  Vector4cd Bellpair_Y2;
  Bellpair_Y2 << 0,Complex(0,-1/sqrt(2)),Complex(0,1/sqrt(2)),0;
  Matrix4cd density_matrix_Y2 = Bellpair_Y2*Bellpair_Y2.adjoint();
  double Yerr_rate2 = (density_matrix_reconstructed.real()*
  density_matrix_Y2.real() ).trace(); EV<<"Yerr = "<<Yerr_rate2<<"\n";*/
}

void HardwareMonitor::writeToFile_Topology_with_LinkCost(int qnic_id, double link_cost, double fidelity, double bellpair_per_sec) {
  auto info = findConnectionInfoByQnicAddr(qnic_id);
  if (info == nullptr) {
    error("qnic info not found");
  }
  InterfaceInfo interface = getQnicInterfaceByQnicAddr(info->qnic.index, info->qnic.type);
  cModule *this_node = this->getParentModule()->getParentModule();
  cModule *neighbor_node = interface.qnic.pointer->gate("qnic_quantum_port$o")->getNextGate()->getNextGate()->getOwnerModule();
  cChannel *channel = interface.qnic.pointer->gate("qnic_quantum_port$o")->getNextGate()->getChannel();
  double dis = channel->par("distance");
  if (neighbor_node->getModuleType() != QNodeType && neighbor_node->getModuleType() != HoMType && neighbor_node->getModuleType() != SPDCType)
    error("Module Type not recognized when writing to file...");

  if (neighbor_node->getModuleType() == QNodeType) {
    if (my_address > info->neighbor_address) {
      std::cout << "\n"
                << this_node->getFullName() << "<--> QuantumChannel{ cost = " << link_cost << "; distance = " << dis << "km; fidelity = " << fidelity
                << "; bellpair_per_sec = " << bellpair_per_sec << ";} <-->" << neighbor_node->getFullName() << "\n";
    }
  } else {
    std::cout << "\n"
              << this_node->getFullName() << "<--> QuantumChannel{ cost = " << link_cost << "; distance = " << dis << "km; fidelity = " << fidelity
              << "; bellpair_per_sec = " << bellpair_per_sec << ";} <-->" << neighbor_node->getFullName() << "\n";
  }
}

// Excludes Hom, Epps and other intermediate nodes.
QNIC HardwareMonitor::search_QNIC_from_Neighbor_QNode_address(int neighbor_address) {
  for (auto it = neighbor_table.cbegin(); it != neighbor_table.cend(); ++it) {
    if (it->second.neighborQNode_address == neighbor_address) {
      return it->second.qnic;
    }
  }

  error(
      "Something is wrong when looking for QNIC info from neighbor QNode "
      "address. Tomography is also only available between neighbor.");
}

/**
A complex function defining RuleSets for purification and tomography
on the link.  This function creates one rule per purification.  As the
work proceeds, a resource gets promoted from rule to rule (on
purification success), so if you ask for three rounds of purification,
it will emit three purification rules.

For example, with 2002, the first instance of "first stage X
purification" (Rule0) includes allocating the resources from the base
pair pool, executing the purification circuit (including measurement),
exchanging the result messages, comparing and either promoting or
discarding, so a one-way classical messaging latency is incurred here.

Then, the "second stage Z purification" (Rule1, the first time through
the loop) begins by drawing two Bell pairs that have each been
promoted by the first X purification (rule 0).  An additional one-way
latency is incurred here.

These actions are alternated initial_purification times, for a total
of 2n rules (and 2n times the one-way latency).  Note that the
semantics of initial_purification vary depending on the
purification_type.  In the descriptions below, $n$ is
initial_purification.

Pumping doesn't really work because of the way resources are
controlled as they are promoted from rule to rule.  At the moment,
base Bell pairs (those created directly by the link) exist in a pool,
ordered by age.  Over in Action.cc, you will find
Action::getResource_fromTop().  This selects the oldest Bell pair.  At
the moment, only the first rule (Rule0) draws from this pool; however,
pumping would require that later rules also be able to draw from the
pool.

A purification scheme must be characterized by both the circuit being
executed, and the scheduling discipline for selecting the inputs to
the circuit.  The scheduling discipline in theory can be pumping,
symmetric tree (perfect binary tree), or banded, and should also
specify how the resources are sorted.  Currently, this is hard-coded
to select oldest first, and is geared toward symmetric tree.
  **/
void HardwareMonitor::sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long RuleSet_id) {
  LinkTomographyRuleSet *pk = new LinkTomographyRuleSet("LinkTomographyRuleSet");
  pk->setDestAddr(my_address);
  pk->setSrcAddr(partner_address);
  pk->setNumber_of_measuring_resources(num_measure);
  pk->setKind(6);

  // Tomography between this node and the sender of Ack.
  RuleSet *tomography_RuleSet = new RuleSet(RuleSet_id, my_address, partner_address);
  EV_INFO << "Creating rules now ruleset_id = " << RuleSet_id << ", partner_address = " << partner_address << "\n";

  int rule_index = 0;

  if (num_purification > 0) {
    if (Purification_type == 2002) {  // Performs both X and Z purification for each n.
      /// # Purification_type 2002: #
      /// - name: Ss-Sp / perfect binary tree, even rounds
      /// - rounds: 2n
      /// - input Bell pairs per round: 2
      /// - total Bell pairs: 2^(2n)
      /// - circuit: Fig. 6.3 in Takaaki's master's thesis
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Ss-Sp is single selection, single error purification.
      /// Between rounds, Hadamard gates are applied
      /// to switch basis, creating alternating
      /// rounds of X and Z purification.
      ///
      /// The only difference between 2002 and 3003
      /// is the semantics of initial_purification.
      /// Here, each iteration results in two rules,
      /// guaranteeing an even number of rounds.
      ///
      /// X always goes first.
      /// ![](../img/PhysRevA.100.052320-Fig11.png)
      for (int i = 0; i < num_purification; i++) {
        // First stage X purification
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 2);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        Action *purify_action = new PurifyAction(RuleSet_id, rule_index, true, false, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
        Purification->setAction(purify_action);
        rule_index++;
        tomography_RuleSet->addRule(Purification);

        // Second stage Z purification (Using X purified resources)
        Purification = new Rule(RuleSet_id, rule_index);
        Purification_condition = new Condition();
        resource_clause = new EnoughResourceClause(partner_address, 2);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        purify_action = new PurifyAction(RuleSet_id, rule_index, false, true, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
        Purification->setAction(purify_action);
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 3003) {
      /// # Purification_type 3003: #
      /// - name: Ss-Sp / perfect binary tree, odd or even rounds
      /// - rounds: n
      /// - input Bell pairs per round: 2
      /// - total Bell pairs: 2^n
      /// - circuit: Fig. 6.3 in Takaaki's master's thesis
      /// - scheduling: perfect binary (symmetric) tree
      /// ## description: ##
      /// Ss-Sp is single selection, single error purification.
      /// Between rounds, Hadamard gates are applied
      /// to switch basis, creating alternating
      /// rounds of X and Z purification.
      ///
      /// The only difference between 2002 and 3003
      /// is the semantics of initial_purification.
      /// Here, each iteration results in one rule,
      /// X for even-numbered rounds (counting from zero),
      /// Z for odd-numbered ones, so it is possible to
      /// do XZX or XZXZX (but not ZXZ or ZXZXZ).
      /// ![](../img/PhysRevA.100.052320-Fig11.png)
      // First stage X purification
      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 2);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);

        if (i % 2 == 0) {
          // X purification
          Action *purify_action = new PurifyAction(RuleSet_id, rule_index, true, false, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
          Purification->setAction(purify_action);
        } else {
          // Z purification
          Action *purify_action = new PurifyAction(RuleSet_id, rule_index, false, true, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
          Purification->setAction(purify_action);
        }
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 1001) {
      /// # Purification_type 1001: #
      /// - name: Ss-Dp XZ Purification
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: Fig. 12 in arXiv:1904.08605
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Both X and Z purification in a single action.  If A
      /// is the pair being purified, and C and E are tools,
      /// CNOT(A,C), MEAS(C), CNOT(E,A), MEAS(E)
      /// then select after comparing outcomes.
      /// Note that bases are not flipped between rounds.
      /// Similar to 1221.
      /// ![](../img/PhysRevA.100.052320-Fig12.png)
      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        Action *purify_action = new DoublePurifyAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
        Purification->setAction(purify_action);
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 1221) {
      /// # Purification_type 1221: #
      /// - name: Ss-Dp XZ, ZX alternating
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: *almost* Fig. 12 from arXiv:1904.08605, but order
      /// of CNOTs reversed in alternating rounds
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Almost the same as 1001, but first round
      /// is XZ, second round is ZX.  Results in better alternating
      /// error suppression, but still not great.
      /// ![](../img/PhysRevA.100.052320-Fig12.png)
      for (int i = 0; i < num_purification; i++) {
        if (i % 2 == 0) {
          Rule *Purification = new Rule(RuleSet_id, rule_index);
          Condition *Purification_condition = new Condition();
          Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
          Purification_condition->addClause(resource_clause);
          Purification->setCondition(Purification_condition);
          Action *purify_action = new DoublePurifyAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
          Purification->setAction(purify_action);
          rule_index++;
          tomography_RuleSet->addRule(Purification);
        } else {
          Rule *Purification = new Rule(RuleSet_id, rule_index);
          Condition *Purification_condition = new Condition();
          Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
          Purification_condition->addClause(resource_clause);
          Purification->setCondition(Purification_condition);
          Action *purify_action = new DoublePurifyActionInv(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
          Purification->setAction(purify_action);
          rule_index++;
          tomography_RuleSet->addRule(Purification);
        }
      }
    } else if (Purification_type == 1011) {
      /// # Purification_type 1011: #
      /// - name: Ds-Sp: Fujii-san's Double selection purification
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: Fig. 13 in arXiv:1904.08605
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Similar to 1001 and 1221 except that the control and target
      /// of the first CNOT are flipped, corresponding to Fujii-san's
      /// paper (PRA 80, 042308).
      /// Every round is identical.
      /// Note there is no basis change between rounds.
      /// ![](../img/arxiv.1904.08605-Fig13.png)
      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        Action *purify_action = new DoubleSelectionAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
        Purification->setAction(purify_action);
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 1021) {  // Fujii-san's Double selection purification
      /// # Purification_type 1021: #
      /// - name: Ds-Sp: Fujii-san's Double selection purification (alternating)
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: *almost* Fig. 13 in arXiv:1904.08605, except that
      /// the order of the CNOTs alternates between rounds
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Similar to 1011, almost corresponding to Fujii-san's paper (PRA 80,
      /// 042308). Note there is no basis change between rounds, but that the
      /// first round is XZ, second is ZX.
      /// ![](../img/arxiv.1904.08605-Fig13.png)
      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        if (i % 2 == 0) {
          Action *purify_action = new DoubleSelectionAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
          Purification->setAction(purify_action);
        } else {
          Action *purify_action = new DoubleSelectionActionInv(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
          Purification->setAction(purify_action);
        }
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 1031) {
      /// # Purification_type 1031: #
      /// - name: Ds-Dp: full double selection purification (alternating)
      /// - rounds: n
      /// - input Bell pairs per round: 5
      /// - total Bell pairs: 5^n
      /// - circuit: Fig. 14 in arXiv:1904.08605, except that
      /// the order of the CNOTs alternates between rounds
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// A combination of 1001 and 1011 (Figs. 12 & 13).  Resource requirements
      /// are high; two rounds of this requires 25 Bell pairs.  With a low base
      /// Bell pair generation rate and realistic memory decoherence, this will
      /// be impractical.
      /// ![](../img/arxiv.1904.08605-Fig14.png)
      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 5);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        if (i % 2 == 0) {
          Action *purify_action = new DoubleSelectionDualAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2, 3, 4);
          Purification->setAction(purify_action);
        } else {
          Action *purify_action = new DoubleSelectionDualActionInv(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2, 3, 4);
          Purification->setAction(purify_action);
        }
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 1061) {
      /// # Purification_type 1061: #
      /// - name: half double selection, half single selection
      /// - rounds: n
      /// - input Bell pairs per round: 4
      /// - total Bell pairs: 4^n
      /// - circuit: no figure available
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Does double selection on X, single selection on Z
      /// Switches bases between rounds.
      /// Investigated for possibly highly asymmetric X/Z error rates in base
      /// Bell pairs. Initial results weren't very promised, not extensively
      /// used.
      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 4);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        if (i % 2 == 0) {
          Action *purify_action = new DoubleSelectionDualActionSecond(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2, 3);
          Purification->setAction(purify_action);
        } else {
          Action *purify_action = new DoubleSelectionDualActionSecondInv(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2, 3);
          Purification->setAction(purify_action);
        }
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 5555) {  // Predefined purification method
      /// # Purification_type 5555: #
      /// - name: Switching (B)
      /// - rounds: n
      /// - input Bell pairs per round: 3 in first two rounds, then 2
      /// - total Bell pairs: (complicated)
      /// - circuit: Fig. 21, case B in arXiv:1904.08605
      /// - scheduling: symmetric tree (*)
      /// ## description: ##
      /// Two rounds of Ds-Sp, then Ss-Sp.
      /// The point of this was to show that you don't have to stick with one
      /// scheme, but can use different schemes in different rounds.
      for (int i = 0; i < 2; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);
        if (i % 2 == 0) {
          Action *purify_action = new DoubleSelectionAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
          Purification->setAction(purify_action);
        } else {
          Action *purify_action = new DoubleSelectionActionInv(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
          Purification->setAction(purify_action);
        }
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }

      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 2);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);

        if (i % 2 == 0) {  // X purification
          Action *purify_action = new PurifyAction(RuleSet_id, rule_index, true, false, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
          Purification->setAction(purify_action);
        } else {  // Z purification
          Action *purify_action = new PurifyAction(RuleSet_id, rule_index, false, true, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
          Purification->setAction(purify_action);
        }
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }
    } else if (Purification_type == 5556) {  // Predefined purification method
      /// # Purification_type 5556: #
      /// - name: Switching (A)
      /// - rounds: n
      /// - input Bell pairs per round: 3 in first round, then 2
      /// - total Bell pairs: (complicated)
      /// - circuit: Fig. 21, case A in arXiv:1904.08605
      /// - scheduling: symmetric tree (*)
      /// ## description: ##
      /// One round of Ds-Sp, then Ss-Sp.
      /// The point of this was to show that you don't have to stick with one
      /// scheme, but can use different schemes in different rounds.
      Rule *Purification = new Rule(RuleSet_id, rule_index);
      Condition *Purification_condition = new Condition();
      Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
      Purification_condition->addClause(resource_clause);
      Purification->setCondition(Purification_condition);
      Action *purify_action = new DoubleSelectionAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
      Purification->setAction(purify_action);
      rule_index++;
      tomography_RuleSet->addRule(Purification);

      for (int i = 0; i < num_purification; i++) {
        Rule *Purification = new Rule(RuleSet_id, rule_index);
        Condition *Purification_condition = new Condition();
        Clause *resource_clause = new EnoughResourceClause(partner_address, 2);
        Purification_condition->addClause(resource_clause);
        Purification->setCondition(Purification_condition);

        if (i % 2 == 0) {
          // X purification
          Action *purify_action = new PurifyAction(RuleSet_id, rule_index, false, true, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
          Purification->setAction(purify_action);
        } else {
          // Z purification
          Action *purify_action = new PurifyAction(RuleSet_id, rule_index, true, false, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
          Purification->setAction(purify_action);
        }
        rule_index++;
        tomography_RuleSet->addRule(Purification);
      }

    } else if ((X_Purification && !Z_Purification) || (!X_Purification && Z_Purification)) {  // X or Z purification. Out-dated syntax.
      /// # Purification_type default: #
      /// - name: Boolean-driven (obsolete)
      /// - rounds: 1
      /// - input Bell pairs: 2 or 3
      /// - total Bell pairs: 2 or 3
      /// - circuit: <reference a figure>
      /// - scheduling: (commonly pumping, symmetric tree, or banded)
      /// ## description: ##
      /// uses X_Purification and Z_purification booleans, but is obsolete.
      /// Creates a single purification only, or a single round of double
      /// purification. Use of this for new work is deprecated.
      Rule *Purification = new Rule(RuleSet_id, rule_index);
      Condition *Purification_condition = new Condition();
      Clause *resource_clause = new EnoughResourceClause(partner_address, 2);
      Purification_condition->addClause(resource_clause);
      Purification->setCondition(Purification_condition);
      Action *purify_action = new PurifyAction(RuleSet_id, rule_index, X_Purification, Z_Purification, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
      Purification->setAction(purify_action);
      rule_index++;
      tomography_RuleSet->addRule(Purification);
    } else {  // X, Z double purification
      error("syntax outdate or purification id not recognized.");
      Rule *Purification = new Rule(RuleSet_id, rule_index);
      Condition *Purification_condition = new Condition();
      Clause *resource_clause = new EnoughResourceClause(partner_address, 3);
      Purification_condition->addClause(resource_clause);
      Purification->setCondition(Purification_condition);
      Action *purify_action = new DoublePurifyAction(RuleSet_id, rule_index, partner_address, qnic_type, qnic_index, 0, 1, 2);
      Purification->setAction(purify_action);
      rule_index++;
      tomography_RuleSet->addRule(Purification);
    }

    // Let's make nodes select measurement basis randomly, because it it easier.
    Rule *Random_measure_tomo = new Rule(RuleSet_id, rule_index);

    // Technically, there is no condition because an available resource is
    // guaranteed whenever the rule is ran.
    Condition *total_measurements = new Condition();

    // 3000 measurements in total. There are 3*3 = 9 patterns of measurements.
    // So each combination must perform 3000/9 measurements.
    Clause *measure_count_clause = new MeasureCountClause(num_measure, partner_address, qnic_type, qnic_index, 0);
    total_measurements->addClause(measure_count_clause);
    Random_measure_tomo->setCondition(total_measurements);

    // Measure the local resource between it->second.neighborQNode_address.
    quisp::rules::Action *measure = new RandomMeasureAction(partner_address, qnic_type, qnic_index, 0, my_address, num_measure);
    Random_measure_tomo->setAction(measure);
    //---------
    // Add the rule to the RuleSet
    tomography_RuleSet->addRule(Random_measure_tomo);
    //---------------------------
    pk->setRuleSet(tomography_RuleSet);
    send(pk, "RouterPort$o");

  } else {  // RuleSet with no purification. Pure measurement only link level
            // tomography.
    //-------------
    //-First rule-

    // Let's make nodes select measurement basis randomly, because it it easier.
    Rule *Random_measure_tomo = new Rule(RuleSet_id, 0);
    // Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
    Condition *total_measurements = new Condition();

    // 3000 measurements in total. There are 3*3 = 9 patterns of measurements.
    // So each combination must perform 3000/9 measurements.
    Clause *measure_count_clause = new MeasureCountClause(num_measure, partner_address, qnic_type, qnic_index, 0);
    Clause *resource_clause = new EnoughResourceClause(partner_address, 1);
    total_measurements->addClause(measure_count_clause);
    total_measurements->addClause(resource_clause);
    Random_measure_tomo->setCondition(total_measurements);

    // Measure the local resource between it->second.neighborQNode_address.
    quisp::rules::Action *measure = new RandomMeasureAction(partner_address, qnic_type, qnic_index, 0, my_address, num_measure);
    Random_measure_tomo->setAction(measure);
    //---------
    // Add the rule to the RuleSet
    tomography_RuleSet->addRule(Random_measure_tomo);
    tomography_RuleSet->finalize();
    //---------------------------
    pk->setRuleSet(tomography_RuleSet);
    send(pk, "RouterPort$o");
  }
}

int HardwareMonitor::getQnicNumQubits(int qnic_index, QNIC_type qnic_type) {
  Enter_Method("checkNumBuff()");
  auto qnic = getQnic(qnic_index, qnic_type);
  return qnic->par("numBuffer");
}

cModule *HardwareMonitor::getQnic(int qnic_index, QNIC_type qnic_type) {
  if (qnic_type >= QNIC_N) {
    error("invalid qnic type: %d", qnic_type);
  }

  cModule *qnic = getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index);
  if (qnic == nullptr) {
    error("qnic(index: %d) not found.", qnic_index);
  }
  return qnic;
}

InterfaceInfo HardwareMonitor::getQnicInterfaceByQnicAddr(int qnic_index, QNIC_type qnic_type) {
  cModule *local_qnic = getQnic(qnic_index, qnic_type);
  InterfaceInfo inf;
  inf.qnic.pointer = local_qnic;
  inf.qnic.address = local_qnic->par("self_qnic_address");
  inf.qnic.index = qnic_index;
  inf.qnic.type = qnic_type;
  inf.buffer_size = local_qnic->par("numBuffer");

  // Just read link cost from channel parameter for now as a dummy (or as an initialization).
  // int cost = local_qnic->gate("qnic_quantum_port$o")->getNextGate()->getChannel()->par("cost");
  // This is false because the channel may only be between the node and HOM.

  // Dummy it up. This cost must be the cost based on the neighboring QNode
  // (excluding SPDC and HOM nodes)
  inf.link_cost = 1;

  return inf;
}

std::unique_ptr<ConnectionSetupInfo> HardwareMonitor::findConnectionInfoByQnicAddr(int qnic_address) {
  for (auto it = neighbor_table.cbegin(); it != neighbor_table.cend(); ++it) {
    if (it->second.qnic.address == qnic_address) {
      auto info = std::make_unique<ConnectionSetupInfo>();
      info->qnic.type = it->second.qnic.type;
      info->qnic.index = it->second.qnic.index;
      info->qnic.address = it->second.qnic.address;
      info->neighbor_address = it->second.neighborQNode_address;
      info->quantum_link_cost = it->second.link_cost;
      return info;
    }
  }
  return nullptr;
}

// This neighbor table includes all neighbors of qnic, qnic_r and qnic_rp
void HardwareMonitor::prepareNeighborTable() {
  // Traverse through all local qnics to check where they are connected to.
  // HoM and EPPS will be ignored in this case.
  for (int index = 0; index < num_qnic; index++) {
    InterfaceInfo inf = getQnicInterfaceByQnicAddr(index, QNIC_E);
    auto n_inf = getNeighbor(inf.qnic.pointer);
    int neighborNodeAddress = n_inf->address;  // get the address of the Node nearby.
    inf.neighborQNode_address = n_inf->neighborQNode_address;
    neighbor_table[neighborNodeAddress] = inf;
  }
  for (int index = 0; index < num_qnic_r; index++) {
    InterfaceInfo inf = getQnicInterfaceByQnicAddr(index, QNIC_R);
    auto n_inf = getNeighbor(inf.qnic.pointer);
    int neighborNodeAddress = n_inf->address;  // get the address of the Node nearby.
    inf.neighborQNode_address = n_inf->neighborQNode_address;
    neighbor_table[neighborNodeAddress] = inf;
  }
  for (int index = 0; index < num_qnic_rp; index++) {
    InterfaceInfo inf = getQnicInterfaceByQnicAddr(index, QNIC_RP);
    auto n_inf = getNeighbor(inf.qnic.pointer);
    int neighborNodeAddress = n_inf->address;  // get the address of the Node nearby.
    inf.neighborQNode_address = n_inf->neighborQNode_address;
    neighbor_table[neighborNodeAddress] = inf;
  }
}

// This method finds out the address of the neighboring node with respect to the
// local unique qnic address.
std::unique_ptr<NeighborInfo> HardwareMonitor::getNeighbor(cModule *qnic_module) {
  // qnic_quantum_port$o is connected to the node's outermost quantum_port
  cGate *gate = qnic_module->gate("qnic_quantum_port$o")->getNextGate();
  cGate *neighbor_gate = gate->getNextGate();

  // Owner could be HoM, EPPS, QNode
  const cModule *neighbor_node = neighbor_gate->getOwnerModule();
  if (neighbor_node == nullptr) {
    error("neighbor nod not found.");
  }
  auto neighbor_info = createNeighborInfo(*neighbor_node);
  return neighbor_info;
}

cModule *HardwareMonitor::getQNode() {
  // We know that Connection manager is not the QNode, so start from the parent.
  cModule *currentModule = getParentModule();
  try {
    // Assumes the node in a network has a type QNode
    while (currentModule->getModuleType() != QNodeType) {
      currentModule = currentModule->getParentModule();
    }
    return currentModule;
  } catch (std::exception &e) {
    error(
        "No module with QNode type found. Have you changed the type name in "
        "ned file?");
    endSimulation();
  }
}

std::unique_ptr<NeighborInfo> HardwareMonitor::createNeighborInfo(const cModule &thisNode) {
  cModuleType *type = thisNode.getModuleType();

  auto inf = std::make_unique<NeighborInfo>();
  inf->type = type;
  inf->address = thisNode.par("address");

  if (type == QNodeType) {
    inf->neighborQNode_address = thisNode.par("address");
    inf->address = thisNode.par("address");
    return inf;
  }

  if (type == HoMType) {
    EV_DEBUG << thisNode.getModuleType()->getFullName() << " == " << HoMType->getFullName() << "\n";
    cModule *controller = thisNode.getSubmodule("Controller");
    if (controller == nullptr) {
      error("HoM Controller not found");
    }

    int address_one = controller->par("neighbor_address");
    int address_two = controller->par("neighbor_address_two");
    int myaddress = par("address");

    EV_DEBUG << "myaddress = " << myaddress << ", address = " << address_one << ", address_two = " << address_two << " in " << controller->getFullName() << "\n";

    if (address_one == -1 && address_two == -1) {
      error("HoM Controller is not initialized properly");
    }

    if (address_one == myaddress) {
      inf->neighborQNode_address = address_two;
    } else if (address_two == myaddress) {
      inf->neighborQNode_address = address_one;
    }

    return inf;
  }

  if (type == SPDCType) {
    error("TO BE IMPLEMENTED");
  }

  error(
      "This simulator only recognizes the following network level node "
      "types: QNode, EPPS and HoM. Not %s",
      thisNode.getClassName());
}

NeighborTable HardwareMonitor::passNeighborTable() {
  Enter_Method("passNeighborTable()");
  return neighbor_table;
}

}  // namespace modules
}  // namespace quisp

namespace std {
std::stringstream &operator<<(std::stringstream &os, const quisp::modules::NeighborInfo &v) {
  os << "neighborInfo(addr: " << v.address << ", neighborQNodeAddr: " << v.neighborQNode_address;
  return os;
}
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const quisp::modules::InterfaceInfo &v) {
  os << "InterfaceInf(neighborQNodeAddr: " << v.neighborQNode_address << ", qnic.addr: " << v.qnic.address << ")";
  return os;
}
}  // namespace std
