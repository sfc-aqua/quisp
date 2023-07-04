/** \file HardwareMonitor.cc
 *
 *  \brief HardwareMonitor
 */
#include "HardwareMonitor.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <omnetpp/cexception.h>
#include <unsupported/Eigen/KroneckerProduct>
#include <unsupported/Eigen/MatrixFunctions>

#include "messages/classical_messages.h"
#include "modules/PhysicalConnection/BSA/BSAController.h"
#include "modules/PhysicalConnection/BSA/BellStateAnalyzer.h"
#include "modules/PhysicalConnection/EPPS/EPPSController.h"
#include "rules/RuleSet.h"

using namespace quisp::messages;
using namespace quisp::rules;
using Eigen::Matrix4cd;
using Eigen::Vector4cd;

namespace quisp::modules {

HardwareMonitor::HardwareMonitor() : provider(utils::ComponentProvider{this}) {}
HardwareMonitor::~HardwareMonitor() {}

// HardwareMonitor is also responsible for calculating the rssi/oka's protocol/fidelity calculate and give it to the RoutingDaemon
void HardwareMonitor::initialize(int stage) {
  EV_INFO << "HardwareMonitor booted\n";
  routing_daemon = provider.getRoutingDaemon();

  Pauli.X << 0, 1, 1, 0;
  Pauli.Y << 0, std::complex<double>(0, -1), std::complex<double>(0, 1), 0;
  Pauli.Z << 1, 0, 0, -1;
  Pauli.I << 1, 0, 0, 1;

  num_qnic_rp = par("number_of_qnics_rp");
  num_qnic_r = par("number_of_qnics_r");
  num_qnic = par("number_of_qnics");
  num_qnic_total = num_qnic + num_qnic_r + num_qnic_rp;

  num_end_nodes = routing_daemon->getNumEndNodes();

  /* This is used to keep your own tomography data, and also to match and store the received partner's tomography data */
  // Assumes link tomography only between neighbors.
  temporal_tomography_output = new TomographyOutcomeTable[num_qnic_total];
  tomography_runningtime_holder = new LinkCostMap[num_qnic_total];

  /*This keeps which node is connected to which local qnic.*/
  tomography_output_filename = par("tomography_output_filename").str();
  // remove double quotes at the beginning and end
  tomography_output_filename = tomography_output_filename.substr(1, tomography_output_filename.length() - 2);
  file_dir_name = par("file_dir_name").str();
  do_link_level_tomography = par("link_tomography");
  num_purification = par("initial_purification");
  X_Purification = par("x_purification");
  Z_Purification = par("z_purification");
  purification_type = par("purification_type");
  num_measure = par("num_measure");
  my_address = provider.getNodeAddr();

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
  if (auto *request = dynamic_cast<LinkTomographyRequest *>(msg)) {
    /* Received a tomography request from neighbor */

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
    delete request;
    return;
  }

  if (auto *ack = dynamic_cast<LinkTomographyAck *>(msg)) {
    /*Received an acknowledgment for tomography from neighbor.*/

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
    delete ack;
    return;
  }

  if (auto *result = dynamic_cast<LinkTomographyResult *>(msg)) {
    /*Link tomography measurement result/basis from neighbor received.*/
    int partner_addr = result->getPartner_address();
    // Get QNIC info from neighbor address.
    int qnic_addr_to_partner = routing_daemon->findQNicAddrByDestAddr(partner_addr);
    auto local_qnic_info = findConnectionInfoByQnicAddr(qnic_addr_to_partner);
    if (local_qnic_info == nullptr) {
      error("local qnic info should not be null");
    }
    InterfaceInfo inter_info = getQnicInterfaceByQnicAddr(local_qnic_info->qnic.index, local_qnic_info->qnic.type);
    QNIC local_qnic = inter_info.qnic;

    // 1. find partner
    auto partner_outputs_iter = temporal_tomography_output[local_qnic.address].find(partner_addr);
    if (partner_outputs_iter != temporal_tomography_output[local_qnic.address].end()) {
      // partner info found in this output
      auto partner_output_iter = temporal_tomography_output[local_qnic.address][partner_addr].find(result->getCount_id());
      if (partner_output_iter != temporal_tomography_output[local_qnic.address][partner_addr].end()) {
        EV << "Tomography data already found. Updating with result from partner\n";
        TomographyOutcome temp = partner_output_iter->second;
        if (result->getSrcAddr() == my_address) {
          temp.my_basis = result->getBasis();
          temp.my_output_is_plus = result->getOutput_is_plus();
          temp.my_GOD_clean = result->getGOD_clean();
        } else {
          temp.partner_basis = result->getBasis();
          temp.partner_output_is_plus = result->getOutput_is_plus();
          temp.partner_GOD_clean = result->getGOD_clean();
        }
        partner_output_iter->second = temp;
      } else {
        EV << "Fresh tomography data with partner :" << partner_addr << "\n";
        TomographyOutcome temp;
        if (result->getSrcAddr() == my_address) {
          temp.my_basis = result->getBasis();
          temp.my_output_is_plus = result->getOutput_is_plus();
          temp.my_GOD_clean = result->getGOD_clean();
        } else {
          temp.partner_basis = result->getBasis();
          temp.partner_output_is_plus = result->getOutput_is_plus();
          temp.partner_GOD_clean = result->getGOD_clean();
        }
        temporal_tomography_output[local_qnic.address][partner_addr].insert(std::make_pair(result->getCount_id(), temp));
      }
    } else {
      // no partner info found in this output
      EV << "No partner information found with partner: " << partner_addr << "\n";
      TomographyOutcome temp;
      if (result->getSrcAddr() == my_address) {
        temp.my_basis = result->getBasis();
        temp.my_output_is_plus = result->getOutput_is_plus();
        temp.my_GOD_clean = result->getGOD_clean();
      } else {
        temp.partner_basis = result->getBasis();
        temp.partner_output_is_plus = result->getOutput_is_plus();
        temp.partner_GOD_clean = result->getGOD_clean();
      }
      // If this partner is new, then initialize tables
      std::map<int, TomographyOutcome> temp_result;
      temp_result.insert(std::make_pair(result->getCount_id(), temp));
      /* temporal_tomography_output is filled in, those data are summarized into basis based measurement outcome table.
       * This accumulates the number of ++, +-, -+ and -- for each basis combination.*/
      temporal_tomography_output[local_qnic.address].insert(std::make_pair(partner_addr, temp_result));
      // NOTE: if you do buffer based multiplex and tomogrpahy need hack here
      qnic_partner_map.insert(std::make_pair(local_qnic.address, partner_addr));

      // initialize link cost
      LinkCost temp_cost;
      temp_cost.Bellpair_per_sec = -1;
      temp_cost.tomography_measurements = -1;
      temp_cost.tomography_time = -1;
      tomography_runningtime_holder[local_qnic.address].insert(std::make_pair(partner_addr, temp_cost));
    }

    if (result->getFinish() != -1) {
      EV << "finish? " << result->getFinish() << "\n";
      EV << "tomography_time: " << tomography_runningtime_holder[local_qnic.address][partner_addr].tomography_time << std::endl;
      // Pick the slower tomography time MIN(self,partner).
      if (tomography_runningtime_holder[local_qnic.address][partner_addr].tomography_time < result->getFinish()) {
        tomography_runningtime_holder[local_qnic.address][partner_addr].Bellpair_per_sec = (double)result->getMax_count() / result->getFinish().dbl();
        tomography_runningtime_holder[local_qnic.address][partner_addr].tomography_measurements = result->getMax_count();
        tomography_runningtime_holder[local_qnic.address][partner_addr].tomography_time = result->getFinish();

        StopEmitting *pk = new StopEmitting("StopEmitting");
        pk->setQnic_address(local_qnic.address);
        pk->setDestAddr(my_address);
        pk->setSrcAddr(my_address);
        send(pk, "RouterPort$o");
      }
    }
    delete result;
    return;
  }
}

void HardwareMonitor::finish() {
  EV << "Finishing Hardware Monitor\n";
  // file name
  std::string file_name = tomography_output_filename;
  std::string df = "default";
  if (file_name.compare(df) == 0) {
    std::cout << df << "==" << file_name << "\n";
    file_name = std::string("Tomography_") + std::string(getSimulation()->getNetworkType()->getFullName());
  } else {
    std::cout << df << "!=" << file_name << "\n";
  }
  std::string file_name_dm = file_name + std::string("_dm");
  std::ofstream tomography_stats(file_name, std::ios_base::app);
  std::ofstream tomography_dm(file_name_dm, std::ios_base::app);
  std::cout << "Opened new file to write. Address is " << my_address << "\n";

  // here generate tomography data storage
  tomography_data = new RawData[num_qnic_total];

  OutputCount initial;
  initial.minus_minus = 0;
  initial.minus_plus = 0;
  initial.plus_minus = 0;
  initial.plus_plus = 0;
  initial.total_count = 0;
  for (auto it = qnic_partner_map.begin(); it != qnic_partner_map.end(); ++it) {
    int qnic_id = it->first;
    int part = it->second;
    tomography_data[qnic_id][part].insert(std::make_pair("XX", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("XY", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("XZ", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("ZX", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("ZY", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("ZZ", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("YX", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("YY", initial));
    tomography_data[qnic_id][part].insert(std::make_pair("YZ", initial));
  }

  for (auto it = qnic_partner_map.begin(); it != qnic_partner_map.end(); it++) {
    int qnic = it->first;
    int partner_address = it->second;
    // qnic index
    //  - partner address
    //  - - measurement counts
    // qnic index
    // initial variables for this tomography partner
    int meas_total = 0;  // total number of measurement
    int GOD_clean_pair_total = 0;  // clean pair?
    int GOD_X_pair_total = 0;
    int GOD_Z_pair_total = 0;
    int GOD_Y_pair_total = 0;

    for (auto it = temporal_tomography_output[qnic][partner_address].begin(); it != temporal_tomography_output[qnic][partner_address].end(); it++) {
      std::string basis_combination = "";
      basis_combination += it->second.my_basis;
      basis_combination += it->second.partner_basis;
      if (tomography_data[qnic][partner_address].count(basis_combination) != 1) {
        error("Basis combination for tomography with partner: %d at %d is not found", partner_address, qnic);
      }
      tomography_data[qnic][partner_address][basis_combination].total_count++;
      // the number of total measurement
      meas_total++;

      EV_DEBUG << it->second.my_GOD_clean << "," << it->second.partner_GOD_clean << "\n";
      // count for ideal state?
      // clean pair ... no error bell pairs
      // X pair ... X error bell pairs?
      // Y pair ... Y error bell pairs?
      // Z pair ... Z error bell pairs?
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

      // empirical result
      if (it->second.my_output_is_plus && it->second.partner_output_is_plus) {
        // mine: +, partner: +
        tomography_data[qnic][partner_address][basis_combination].plus_plus++;
      } else if (it->second.my_output_is_plus && !it->second.partner_output_is_plus) {
        // mine: +, partner: -
        tomography_data[qnic][partner_address][basis_combination].plus_minus++;
      } else if (!it->second.my_output_is_plus && it->second.partner_output_is_plus) {
        // mine: -, partner: +
        tomography_data[qnic][partner_address][basis_combination].minus_plus++;
      } else if (!it->second.my_output_is_plus && !it->second.partner_output_is_plus) {
        // mine: -, partner: -
        tomography_data[qnic][partner_address][basis_combination].minus_minus++;
      } else {
        error("This should not happen though..... ?");
      }
    }  // end for
    Matrix4cd extended_density_matrix_reconstructed = reconstruct_density_matrix(qnic, partner_address);

    Vector4cd Bellpair;
    Bellpair << 1 / sqrt(2), 0, 0, 1 / sqrt(2);
    Matrix4cd density_matrix_ideal = Bellpair * Bellpair.adjoint();
    double fidelity = (extended_density_matrix_reconstructed.real() * density_matrix_ideal.real()).trace();

    Vector4cd Bellpair_X;
    Bellpair_X << 0, 1 / sqrt(2), 1 / sqrt(2), 0;
    Matrix4cd density_matrix_X = Bellpair_X * Bellpair_X.adjoint();
    double Xerr_rate = (extended_density_matrix_reconstructed.real() * density_matrix_X.real()).trace();
    EV << "Xerr = " << Xerr_rate << "\n";

    Vector4cd Bellpair_Z;
    Bellpair_Z << 1 / sqrt(2), 0, 0, -1 / sqrt(2);
    Matrix4cd density_matrix_Z = Bellpair_Z * Bellpair_Z.adjoint();
    double Zerr_rate = (extended_density_matrix_reconstructed.real() * density_matrix_Z.real()).trace();
    std::complex<double> checkZ = Bellpair_Z.adjoint() * extended_density_matrix_reconstructed * Bellpair_Z;
    EV << "Zerr = " << Zerr_rate << " or, " << checkZ.real() << "+" << checkZ.imag() << "\n";

    Vector4cd Bellpair_Y;
    Bellpair_Y << 0, std::complex<double>(0, 1 / sqrt(2)), std::complex<double>(0, -1 / sqrt(2)), 0;
    Matrix4cd density_matrix_Y = Bellpair_Y * Bellpair_Y.adjoint();
    double Yerr_rate = (extended_density_matrix_reconstructed.real() * density_matrix_Y.real()).trace();
    EV << "Yerr = " << Yerr_rate << "\n";

    // FIXME should be updated
    double denom = fidelity * fidelity * tomography_runningtime_holder[qnic][partner_address].Bellpair_per_sec;
    double link_cost;
    // TODO currently, it's just placed. consider how to culculate this
    if (denom != 0) {
      link_cost = (double)1 / denom;
    } else {
      link_cost = 1;
    }
    auto info = findConnectionInfoByQnicAddr(qnic);
    if (info == nullptr) {
      error("info not found");
    }
    // outputs
    InterfaceInfo interface = getQnicInterfaceByQnicAddr(info->qnic.index, info->qnic.type);
    cModule *this_node = this->getParentModule()->getParentModule();
    cModule *partner_node = getQNodeWithAddress(partner_address);
    cChannel *channel = interface.qnic.pointer->gate("qnic_quantum_port$o")->getNextGate()->getChannel();
    double dis = channel->par("distance");
    if (partner_node == nullptr) {
      error("here, partner node is null");
    }
    // density matrix output
    tomography_dm << this_node->getFullName() << "<--->" << partner_node->getFullName() << "\n";
    tomography_dm << "REAL\n";
    tomography_dm << extended_density_matrix_reconstructed.real() << "\n";
    tomography_dm << "IMAGINARY\n";
    tomography_dm << extended_density_matrix_reconstructed.imag() << "\n";

    // link stats output
    tomography_stats << this_node->getFullName() << "<-->QuantumChannel{cost=" << link_cost << ";distance=" << dis << "km;fidelity=" << fidelity
                     << ";bellpair_per_sec=" << tomography_runningtime_holder[qnic][partner_address].Bellpair_per_sec
                     << ";tomography_time=" << tomography_runningtime_holder[qnic][partner_address].tomography_time
                     << ";tomography_measurements=" << tomography_runningtime_holder[qnic][partner_address].tomography_measurements << ";actual_meas=" << meas_total
                     << "; GOD_clean_pair_total=" << GOD_clean_pair_total << "; GOD_X_pair_total=" << GOD_X_pair_total << "; GOD_Y_pair_total=" << GOD_Y_pair_total
                     << "; GOD_Z_pair_total=" << GOD_Z_pair_total << ";}<-->" << partner_node->getFullName() << "; F=" << fidelity << "; X=" << Xerr_rate << "; Z=" << Zerr_rate
                     << "; Y=" << Yerr_rate << endl;
    // this is a temporary implementation so that the e2e-test can read fidelity and error rates
    std::cout << this_node->getFullName() << "<-->QuantumChannel{cost=" << link_cost << ";distance=" << dis << "km;fidelity=" << fidelity
              << ";bellpair_per_sec=" << tomography_runningtime_holder[qnic][partner_address].Bellpair_per_sec << ";}<-->" << partner_node->getFullName()
              << "; Fidelity=" << fidelity << "; Xerror=" << Xerr_rate << "; Zerror=" << Zerr_rate << "; Yerror=" << Yerr_rate << endl;
  }
  tomography_stats.close();
  tomography_dm.close();
  std::cout << "Closed file to write.\n";
}

Matrix4cd HardwareMonitor::reconstruct_density_matrix(int qnic_id, int partner) {
  // II
  auto data = tomography_data[qnic_id][partner];
  double S00 = 1.0;
  double S01 = (double)data["XX"].plus_plus / (double)data["XX"].total_count - (double)data["XX"].plus_minus / (double)data["XX"].total_count +
               (double)data["XX"].minus_plus / (double)data["XX"].total_count - (double)data["XX"].minus_minus / (double)data["XX"].total_count;
  if (std::isnan(S01)) {
    EV << "total count: " << (double)data["XX"].total_count << "\n";
    error("S01 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S02 = (double)data["YY"].plus_plus / (double)data["YY"].total_count - (double)data["YY"].plus_minus / (double)data["YY"].total_count +
               (double)data["YY"].minus_plus / (double)data["YY"].total_count - (double)data["YY"].minus_minus / (double)data["YY"].total_count;
  if (std::isnan(S02)) {
    error("S02 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S03 = (double)data["ZZ"].plus_plus / (double)data["ZZ"].total_count - (double)data["ZZ"].plus_minus / (double)data["ZZ"].total_count +
               (double)data["ZZ"].minus_plus / (double)data["ZZ"].total_count - (double)data["ZZ"].minus_minus / (double)data["ZZ"].total_count;
  if (std::isnan(S03)) {
    error("S03 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  // XX
  double S10 = (double)data["XX"].plus_plus / (double)data["XX"].total_count + (double)data["XX"].plus_minus / (double)data["XX"].total_count -
               (double)data["XX"].minus_plus / (double)data["XX"].total_count - (double)data["XX"].minus_minus / (double)data["XX"].total_count;
  if (std::isnan(S10)) {
    error("S10 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S11 = (double)data["XX"].plus_plus / (double)data["XX"].total_count - (double)data["XX"].plus_minus / (double)data["XX"].total_count -
               (double)data["XX"].minus_plus / (double)data["XX"].total_count + (double)data["XX"].minus_minus / (double)data["XX"].total_count;
  if (std::isnan(S11)) {
    error("S11 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S12 = (double)data["XY"].plus_plus / (double)data["XY"].total_count - (double)data["XY"].plus_minus / (double)data["XY"].total_count -
               (double)data["XY"].minus_plus / (double)data["XY"].total_count + (double)data["XY"].minus_minus / (double)data["XY"].total_count;
  if (std::isnan(S12)) {
    error("S12 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S13 = (double)data["XZ"].plus_plus / (double)data["XZ"].total_count - (double)data["XZ"].plus_minus / (double)data["XZ"].total_count -
               (double)data["XZ"].minus_plus / (double)data["XZ"].total_count + (double)data["XZ"].minus_minus / (double)data["XZ"].total_count;
  if (std::isnan(S13)) {
    error("S13 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  // YY
  double S20 = (double)data["YY"].plus_plus / (double)data["YY"].total_count + (double)data["YY"].plus_minus / (double)data["YY"].total_count -
               (double)data["YY"].minus_plus / (double)data["YY"].total_count - (double)data["YY"].minus_minus / (double)data["YY"].total_count;
  if (std::isnan(S20)) {
    error("S20 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S21 = (double)data["YX"].plus_plus / (double)data["YX"].total_count - (double)data["YX"].plus_minus / (double)data["YX"].total_count -
               (double)data["YX"].minus_plus / (double)data["YX"].total_count + (double)data["YX"].minus_minus / (double)data["YX"].total_count;
  if (std::isnan(S21)) {
    error("S21 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S22 = (double)data["YY"].plus_plus / (double)data["YY"].total_count - (double)data["YY"].plus_minus / (double)data["YY"].total_count -
               (double)data["YY"].minus_plus / (double)data["YY"].total_count + (double)data["YY"].minus_minus / (double)data["YY"].total_count;
  if (std::isnan(S22)) {
    error("S22 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S23 = (double)data["YZ"].plus_plus / (double)data["YZ"].total_count - (double)data["YZ"].plus_minus / (double)data["YZ"].total_count -
               (double)data["YZ"].minus_plus / (double)data["YZ"].total_count + (double)data["YZ"].minus_minus / (double)data["YZ"].total_count;
  if (std::isnan(S23)) {
    error("S23 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  // ZZ
  double S30 = (double)data["ZZ"].plus_plus / (double)data["ZZ"].total_count + (double)data["ZZ"].plus_minus / (double)data["ZZ"].total_count -
               (double)data["ZZ"].minus_plus / (double)data["ZZ"].total_count - (double)data["ZZ"].minus_minus / (double)data["ZZ"].total_count;
  if (std::isnan(S30)) {
    error("S30 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S31 = (double)data["ZX"].plus_plus / (double)data["ZX"].total_count - (double)data["ZX"].plus_minus / (double)data["ZX"].total_count -
               (double)data["ZX"].minus_plus / (double)data["ZX"].total_count + (double)data["ZX"].minus_minus / (double)data["ZX"].total_count;
  if (std::isnan(S31)) {
    error("S31 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S32 = (double)data["ZY"].plus_plus / (double)data["ZY"].total_count - (double)data["ZY"].plus_minus / (double)data["ZY"].total_count -
               (double)data["ZY"].minus_plus / (double)data["ZY"].total_count + (double)data["ZY"].minus_minus / (double)data["ZY"].total_count;
  if (std::isnan(S32)) {
    error("S32 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }
  double S33 = (double)data["ZZ"].plus_plus / (double)data["ZZ"].total_count - (double)data["ZZ"].plus_minus / (double)data["ZZ"].total_count -
               (double)data["ZZ"].minus_plus / (double)data["ZZ"].total_count + (double)data["ZZ"].minus_minus / (double)data["ZZ"].total_count;
  if (std::isnan(S33)) {
    error("S33 error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }

  double S = (double)data["XX"].plus_plus / (double)data["XX"].total_count + (double)data["XX"].plus_minus / (double)data["XX"].total_count +
             (double)data["XX"].minus_plus / (double)data["XX"].total_count + (double)data["XX"].minus_minus / (double)data["XX"].total_count;
  if (std::isnan(S)) {
    error(" final S error at node %d qnic: %d, with partner: %d", my_address, qnic_id, partner);
  }

  EV << S00 << ", " << S01 << ", " << S02 << ", " << S03 << "\n";
  EV << S10 << ", " << S11 << ", " << S12 << ", " << S13 << "\n";
  EV << S20 << ", " << S21 << ", " << S22 << ", " << S23 << "\n";
  EV << S30 << ", " << S31 << ", " << S32 << ", " << S33 << "\n";

  Matrix4cd extended_density_matrix_reconstructed =
      (double)1 / (double)4 *
      (S01 * kroneckerProduct(Pauli.I, Pauli.X).eval() + S02 * kroneckerProduct(Pauli.I, Pauli.Y).eval() + S03 * kroneckerProduct(Pauli.I, Pauli.Z).eval() +
       S10 * kroneckerProduct(Pauli.X, Pauli.I).eval() + S11 * kroneckerProduct(Pauli.X, Pauli.X).eval() + S12 * kroneckerProduct(Pauli.X, Pauli.Y).eval() +
       S13 * kroneckerProduct(Pauli.X, Pauli.Z).eval() + S20 * kroneckerProduct(Pauli.Y, Pauli.I).eval() + S21 * kroneckerProduct(Pauli.Y, Pauli.X).eval() +
       S22 * kroneckerProduct(Pauli.Y, Pauli.Y).eval() + S23 * kroneckerProduct(Pauli.Y, Pauli.Z).eval() + S30 * kroneckerProduct(Pauli.Z, Pauli.I).eval() +
       S31 * kroneckerProduct(Pauli.Z, Pauli.X).eval() + S32 * kroneckerProduct(Pauli.Z, Pauli.Y).eval() + S33 * kroneckerProduct(Pauli.Z, Pauli.Z).eval() +
       S * kroneckerProduct(Pauli.I, Pauli.I).eval());
  EV << "DM = " << extended_density_matrix_reconstructed << "\n";
  return extended_density_matrix_reconstructed;
}

void HardwareMonitor::writeToFile_Topology_with_LinkCost(int qnic_id, double link_cost, double fidelity, double bellpair_per_sec) {
  auto info = findConnectionInfoByQnicAddr(qnic_id);
  if (info == nullptr) {
    error("qnic info not found");
  }
  InterfaceInfo interface = getQnicInterfaceByQnicAddr(info->qnic.index, info->qnic.type);
  cModule *const this_node = provider.getQNode();
  cModule *const neighbor_node = provider.getNeighborNode(interface.qnic.pointer);
  const cModuleType *const neighbor_node_type = neighbor_node->getModuleType();
  cChannel *channel = interface.qnic.pointer->gate("qnic_quantum_port$o")->getNextGate()->getChannel();
  double dis = channel->par("distance");
  if (provider.isQNodeType(neighbor_node_type) && provider.isBSANodeType(neighbor_node_type) && provider.isEPPSNodeType(neighbor_node_type)) {
    error("Module Type not recognized when writing to file...");
  }

  if (provider.isQNodeType(neighbor_node_type)) {
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
  auto *tomography_RuleSet = new RuleSet(RuleSet_id, my_address);
  EV_INFO << "Creating rules now ruleset_id = " << RuleSet_id << ", partner_address = " << partner_address << "\n";

  int shared_tag = 0;
  std::string rule_name;
  std::vector<int> partners = {partner_address};

  if (num_purification > 0) {
    if (purification_type == 2002) {  // Performs both X and Z purification for each n.
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
        {
          rule_name = "X purification with: " + std::to_string(partner_address);
          auto rule = constructPurifyRule(rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        }
        // Second stage Z purification (Using X purified resources)
        {
          rule_name = "Z purification with: " + std::to_string(partner_address);
          auto rule = constructPurifyRule(rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 3003) {
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
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "X purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Z purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1001) {
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
        rule_name = "Double purification with: " + std::to_string(partner_address);
        auto rule = constructPurifyRule(rule_name, PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag);
        tomography_RuleSet->addRule(std::move(rule));
        tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag++));
      }
    } else if (purification_type == 1221) {
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
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double purification Inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DOUBLE_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DOUBLE_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1011) {
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
        rule_name = "Double Selection with: " + std::to_string(partner_address);
        auto rule = constructPurifyRule(rule_name, PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag);
        tomography_RuleSet->addRule(std::move(rule));
        tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
      }
    } else if (purification_type == 1021) {  // Fujii-san's Double selection purification
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
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double selection with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double selection Inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DSSA_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1031) {
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
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double selection Dual action with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DSDA, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double selection Dual action Inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DSDA_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1061) {
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
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double selection Dual action second with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DSDA_SECOND, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSDA_SECOND, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double selection Dual action second inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::DSDA_SECOND_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(
              constructCorrelationCheckRule("purification correlation check", PurType::DSDA_SECOND_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 5555) {  // Predefined purification method
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
        if (i % 2 == 0) {
          rule_name = "Double selection action with: " + std::to_string(partner_address);
        } else {
          rule_name = "Double selection action inverse with: " + std::to_string(partner_address);
        }
        auto rule = std::make_unique<Rule>(my_address, shared_tag, shared_tag);
        rule->setName(rule_name);
        auto condition = std::make_unique<Condition>();
        auto resource_clause = std::make_unique<EnoughResourceConditionClause>(3, partner_address);
        condition->addClause(std::move(resource_clause));
        rule->setCondition(std::move(condition));
        if (i % 2 == 0) {
          auto purify_action = std::make_unique<Purification>(PurType::DSSA, partner_address, shared_tag);
          rule->setAction(std::move(purify_action));
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          auto purify_action = std::make_unique<Purification>(PurType::DSDA_INV, partner_address, shared_tag);
          rule->setAction(std::move(purify_action));
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSDA_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }

      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "X Purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Z Purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 5556) {  // Predefined purification method
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
      rule_name = "Double selection action with: " + std::to_string(partner_address);
      auto rule = constructPurifyRule(rule_name, PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag);
      tomography_RuleSet->addRule(std::move(rule));
      tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));

      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Z purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "X purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_RuleSet->addRule(std::move(rule));
          tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        }
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
      rule_name = "Single purification with: " + std::to_string(partner_address);
      auto rule = constructPurifyRule(rule_name, (X_Purification ? PurType::SINGLE_X : PurType::SINGLE_Z), partner_address, qnic_type, qnic_index, shared_tag);
      tomography_RuleSet->addRule(std::move(rule));
      tomography_RuleSet->addRule(constructCorrelationCheckRule("purification correlation check", (X_Purification ? PurType::SINGLE_X : PurType::SINGLE_Z), partner_address,
                                                                qnic_type, qnic_index, shared_tag++));
    } else {  // X, Z double purification
      error("syntax outdate or purification id not recognized.");
    }

    // Let's make nodes select measurement basis randomly, because it it easier.
    auto rule = std::make_unique<Rule>(my_address, shared_tag, shared_tag);
    rule->setName("tomography");

    auto condition = std::make_unique<Condition>();

    // 1 qubit resource required to perform tomography action
    auto res_check_clause = std::make_unique<EnoughResourceConditionClause>(1, partner_address);
    condition->addClause(std::move(res_check_clause));

    // 3000 measurements in total. There are 3*3 = 9 patterns of measurements.
    // So each combination must perform 3000/9 measurements.
    auto measure_count_clause = std::make_unique<MeasureCountConditionClause>(num_measure, partner_address);
    condition->addClause(std::move(measure_count_clause));
    rule->setCondition(std::move(condition));

    // Measure the local resource between it->second.neighborQNode_address.
    auto measure_action = std::make_unique<Tomography>(num_measure, my_address, partner_address);
    measure_action->start_time = simTime();
    rule->setAction(std::move(measure_action));

    tomography_RuleSet->addRule(std::move(rule));
    pk->setRuleSet(tomography_RuleSet);
    send(pk, "RouterPort$o");
  } else {
    // RuleSet with no purification. Pure measurement only link level tomography.

    auto rule = std::make_unique<Rule>(my_address, shared_tag, shared_tag);
    auto condition = std::make_unique<Condition>();
    auto res_check_clause = std::make_unique<EnoughResourceConditionClause>(1, partner_address);
    auto measure_count_clause = std::make_unique<MeasureCountConditionClause>(num_measure, partner_address);
    condition->addClause(std::move(res_check_clause));
    condition->addClause(std::move(measure_count_clause));
    rule->setCondition(std::move(condition));

    // Measure the local resource between it->second.neighborQNode_address.
    auto measure = std::make_unique<Tomography>(num_measure, my_address, partner_address);
    measure->start_time = simTime();
    rule->setAction(std::move(measure));

    tomography_RuleSet->addRule(std::move(rule));

    pk->setRuleSet(tomography_RuleSet);
    send(pk, "RouterPort$o");
  }
}

std::unique_ptr<Rule> HardwareMonitor::constructPurifyRule(const std::string &rule_name, const rules::PurType pur_type, const int partner_address, const QNIC_type qnic_type,
                                                           const int qnic_index, const int send_tag) const {
  int required_qubits = 0;
  switch (pur_type) {
    case PurType::SINGLE_X:
    case PurType::SINGLE_Z:
    case PurType::SINGLE_Y:
      required_qubits = 2;
      break;
    case PurType::DOUBLE:
    case PurType::DOUBLE_INV:
    case PurType::DSSA:
    case PurType::DSSA_INV:
      required_qubits = 3;
      break;
    case PurType::DSDA:
    case PurType::DSDA_INV:
      required_qubits = 5;
      break;
    case PurType::DSDA_SECOND:
    case PurType::DSDA_SECOND_INV:
      required_qubits = 4;
      break;
    case PurType::INVALID:
    default:
      error("got invalid purification type");
  }
  auto rule = std::make_unique<Rule>(my_address, send_tag, -1);
  rule->setName(rule_name);
  auto condition = std::make_unique<Condition>();
  auto resource_clause = std::make_unique<EnoughResourceConditionClause>(required_qubits, partner_address);
  condition->addClause(std::move(resource_clause));
  rule->setCondition(std::move(condition));
  auto purify_action = std::make_unique<Purification>(pur_type, partner_address, send_tag);
  rule->setAction(std::move(purify_action));
  return rule;
}

std::unique_ptr<Rule> HardwareMonitor::constructCorrelationCheckRule(const std::string &rule_name, const rules::PurType pur_type, const int partner_address,
                                                                     const QNIC_type qnic_type, const int qnic_index, const int receive_tag) const {
  auto correlation_rule = std::make_unique<Rule>(partner_address, -1, receive_tag);

  auto condition = std::make_unique<Condition>();
  auto correlation_clause = std::make_unique<PurificationCorrelationClause>(partner_address, receive_tag);
  condition->addClause(std::move(correlation_clause));

  auto action = std::make_unique<PurificationCorrelation>(partner_address, receive_tag);

  correlation_rule->setCondition(std::move(condition));
  correlation_rule->setAction(std::move(action));
  return correlation_rule;
}

int HardwareMonitor::getQnicNumQubits(int qnic_index, QNIC_type qnic_type) {
  Enter_Method("checkNumBuff()");
  auto qnic = getQnic(qnic_index, qnic_type);
  return qnic->par("num_buffer");
}

cModule *HardwareMonitor::getQnic(int qnic_index, QNIC_type qnic_type) {
  if (qnic_type >= QNIC_N) {
    error("invalid qnic type: %d", qnic_type);
  }

  cModule *qnic = provider.getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index);
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
  inf.buffer_size = local_qnic->par("num_buffer");

  // Just read link cost from channel parameter for now as a dummy (or as an initialization).
  // int cost = local_qnic->gate("qnic_quantum_port$o")->getNextGate()->getChannel()->par("cost");
  // This is false because the channel may only be between the node and BSA.

  // Dummy it up. This cost must be the cost based on the neighboring QNode
  // (excluding EPPS and BSA nodes)
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
  // BSA and EPPS will be ignored in this case.
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

  // Owner could be BSA, EPPS, QNode
  const cModule *neighbor_node = neighbor_gate->getOwnerModule();
  if (neighbor_node == nullptr) {
    error("neighbor node not found.");
  }
  auto neighbor_info = createNeighborInfo(*neighbor_node);
  return neighbor_info;
}

cModule *HardwareMonitor::getQNodeWithAddress(int address) {
  cTopology *topo = new cTopology("topo");
  // veryfication?
  topo->extractByParameter("included_in_topology", "\"yes\"");
  int addr;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    addr = (int)node->getModule()->par("address");
    EV_DEBUG << "End node address is " << addr << "\n";
    if (addr == address) {
      auto *mod = node->getModule();
      delete topo;
      return mod;
    }
  }
  delete topo;
}

std::unique_ptr<NeighborInfo> HardwareMonitor::createNeighborInfo(const cModule &thisNode) {
  cModuleType *type = thisNode.getModuleType();

  auto inf = std::make_unique<NeighborInfo>();
  inf->address = thisNode.par("address");

  if (provider.isQNodeType(type)) {
    inf->neighborQNode_address = thisNode.par("address");
    inf->address = thisNode.par("address");
    return inf;
  }

  if (provider.isBSANodeType(type)) {
    auto *controller = dynamic_cast<BSAController *>(thisNode.getSubmodule("bsa_controller"));
    if (controller == nullptr) {
      error("BSA controller not found");
    }

    int address_one = controller->getExternalAdressFromPort(0);
    int address_two = controller->getExternalAdressFromPort(1);
    int myaddress = provider.getNodeAddr();

    EV_DEBUG << "myaddress = " << myaddress << ", address = " << address_one << ", address_two = " << address_two << " in " << controller->getFullName() << "\n";

    if (address_one == -1 && address_two == -1) {
      error("BSA Controller is not initialized properly");
    }

    if (address_one == myaddress) {
      inf->neighborQNode_address = address_two;
    } else if (address_two == myaddress) {
      inf->neighborQNode_address = address_one;
    }

    return inf;
  }

  if (provider.isEPPSNodeType(type)) {
    auto *controller = dynamic_cast<EPPSController *>(thisNode.getSubmodule("epps_controller"));
    if (controller == nullptr) {
      error("EPPS controller not found");
    }

    int address_one = controller->getExternalAdressFromPort(0);
    int address_two = controller->getExternalAdressFromPort(1);
    int myaddress = provider.getNodeAddr();

    EV_DEBUG << "myaddress = " << myaddress << ", address = " << address_one << ", address_two = " << address_two << " in " << controller->getFullName() << "\n";

    if (address_one == -1 && address_two == -1) {
      error("EPPS Controller is not initialized properly");
    }

    if (address_one == myaddress) {
      inf->neighborQNode_address = address_two;
    } else if (address_two == myaddress) {
      inf->neighborQNode_address = address_one;
    }

    return inf;
  }

  error(
      "This simulator only recognizes the following network level node "
      "types: QNode, EPPS and BSA. Not %s",
      thisNode.getClassName());
}

}  // namespace quisp::modules

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
