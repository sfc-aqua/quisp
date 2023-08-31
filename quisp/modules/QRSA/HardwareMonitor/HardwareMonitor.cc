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
#include "rules/RuleSet.h"
#include "utils/HelperFunctions.h"
#include "utils/ITomographyManager.h"
#include "utils/TomographyManager.h"

using namespace quisp::messages;
using namespace quisp::rules;
using Eigen::Matrix4cd;
using Eigen::Vector4cd;
using quisp::utils::HelperFunctions;
using quisp::utils::TomographyManager;

namespace quisp::modules {

HardwareMonitor::HardwareMonitor() : provider(utils::ComponentProvider{this}) {}
HardwareMonitor::~HardwareMonitor() {}

// HardwareMonitor is also responsible for calculating the rssi/oka's protocol/fidelity calculate and give it to the RoutingDaemon
void HardwareMonitor::initialize(int stage) {
  EV_INFO << "HardwareMonitor booted\n";

  routing_daemon = provider.getRoutingDaemon();
  my_address = provider.getNodeAddr();

  // remove double quotes at the beginning and end
  tomography_output_filename = par("tomography_output_filename").str();
  tomography_output_filename = tomography_output_filename.substr(1, tomography_output_filename.length() - 2);

  // tomography parameters
  do_link_level_tomography = par("link_tomography");
  num_purification = par("initial_purification");
  x_purification = par("x_purification");
  z_purification = par("z_purification");
  purification_type = par("purification_type");
  num_measure = par("num_measure");

  if (stage == 0) {
    return;
  }

  tomography_manager = std::unique_ptr<TomographyManager>();

  auto neighbor_addresses = routing_daemon->getNeighborAddresses();

  // Initialize link costs
  for (auto neighbor : neighbor_addresses) {
    // Values should be updated after link tomography
    link_cost_table[neighbor] = 1;
  }

  if (do_link_level_tomography) {
    for (auto neighbor_address : neighbor_addresses) {
      if (my_address > neighbor_address) {
        auto *pk = new LinkTomographyRequest("LinkTomographyRequest");
        pk->setDestAddr(neighbor_address);
        pk->setSrcAddr(my_address);
        pk->setKind(6);
        send(pk, "RouterPort$o");
      }
    }
  }
}

void HardwareMonitor::handleMessage(cMessage *msg) {
  if (auto *request = dynamic_cast<LinkTomographyRequest *>(msg)) {
    // Get link tomography request from neighbor node
    auto interface_info = routing_daemon->getQuantumInterfaceInfo(request->getSrcAddr());

    // Send ack to source
    LinkTomographyAck *pk = new LinkTomographyAck("LinkTomographyAck");
    pk->setSrcAddr(my_address);
    pk->setDestAddr(request->getSrcAddr());
    pk->setKind(6);
    pk->setQnic_index(interface_info.qnic.index);
    pk->setQnic_type(interface_info.qnic.type);

    send(pk, "RouterPort$o");
    delete request;
    return;
  }

  if (auto *ack = dynamic_cast<LinkTomographyAck *>(msg)) {
    // Received acknowledegement from neighbor

    int partner_address = ack->getSrcAddr();
    auto my_qnic_info = routing_daemon->getQuantumInterfaceInfo(partner_address);

    // RuleSet for partner node
    long ruleset_id = HelperFunctions::createUniqueId(this->getRNG(0), my_address, simTime());
    sendLinkTomographyRuleSet(my_address, partner_address, my_qnic_info.qnic.type, my_qnic_info.qnic.index, ruleset_id);
    // RuleSet for this node
    QNIC_type partner_qnic_type = ack->getQnic_type();
    int partner_qnic_index = ack->getQnic_index();
    sendLinkTomographyRuleSet(partner_address, my_address, partner_qnic_type, partner_qnic_index, ruleset_id);
    delete ack;
    return;
  }

  if (auto *result = dynamic_cast<LinkTomographyResult *>(msg)) {
    // Get link tomography result and make a record for it
    int partner = result->getPartner_address();

    auto quantum_interface_info = routing_daemon->getQuantumInterfaceInfo(partner);

    auto qnic_id = quantum_interface_info.qnic.index;
    auto tomography_round = result->getCount_id();
    auto measurement_basis = result->getBasis();
    auto tomography_outcome = result->getOutput_is_plus();
    auto god_clean = result->getGOD_clean();
    // Remember current tomography partners for showing results
    tomography_partners.insert(std::make_tuple(qnic_id, partner));

    if (result->getSrcAddr() == my_address) {
      // Result from my self
      // Pass result to the tomography manager
      tomography_manager->addLocalResult(qnic_id, partner, tomography_round, measurement_basis, tomography_outcome, god_clean);
    } else {
      // Result from partner
      tomography_manager->addPartnerResult(qnic_id, partner, tomography_round, measurement_basis, tomography_outcome, god_clean);
    }

    if (result->getFinish() != -1) {
      // Finish tomography and record tomography stats
      tomography_manager->setStats(qnic_id, partner, result->getFinish(), (double)result->getMax_count() / result->getFinish().dbl(), result->getMax_count());
    }
    delete result;
    return;
  }
}

double HardwareMonitor::getLinkCost(int neighbor_address) {
  if (!link_cost_table.count(neighbor_address)) {
    error("Link cost for neighbor %d not found", neighbor_address);
  }
  return link_cost_table[neighbor_address];
}

void HardwareMonitor::finish() {
  std::string file_name = tomography_output_filename;
  std::string df = "default";
  if (file_name.compare(df) == 0) {
    std::cout << df << "==" << file_name << "\n";
    file_name = std::string("Tomography_") + std::string(getSimulation()->getNetworkType()->getFullName());
  } else {
    std::cout << df << "!=" << file_name << "\n";
  }
  std::string file_name_dm = file_name + std::string("_dm");
  std::ofstream tomography_stats_file(file_name, std::ios_base::app);
  std::ofstream tomography_dm(file_name_dm, std::ios_base::app);
  std::cout << "Opened new file to write.\n";

  for (auto partner_key : tomography_partners) {
    auto qnic_id = std::get<0>(partner_key);
    auto partner = std::get<1>(partner_key);
    Matrix4cd extended_density_matrix_reconstructed = tomography_manager->reconstructDensityMatrix(qnic_id, partner);

    auto fidelity = tomography_manager->calcFidelity(qnic_id, partner);
    auto [x_error, y_error, z_error] = tomography_manager->calcErrorRate(qnic_id, partner);
    auto tomography_stats = tomography_manager->getStats(qnic_id, partner);
    double link_cost;
    // TODO currently, it's just placed. consider how to culculate this
    double denom = fidelity * fidelity * tomography_stats.bell_pair_per_sec;
    if (denom != 0) {
      link_cost = (double)1 / denom;
    } else {
      link_cost = 1;
    }
    // density matrix output
    tomography_dm << "Node (Address: " << my_address << ") <--->"
                  << "Node (Address: " << partner << ")\n";
    tomography_dm << "REAL\n";
    tomography_dm << extended_density_matrix_reconstructed.real() << "\n";
    tomography_dm << "IMAGINARY\n";
    tomography_dm << extended_density_matrix_reconstructed.imag() << "\n";

    auto [god_clean_pair_total, god_x_pair_total, god_y_pair_total, god_z_pair_total] = tomography_manager->calcGodPairCount(qnic_id, partner);
    // link stats output
    tomography_stats_file << "Node (Address: " << my_address << "<-->QuantumChannel{cost=" << link_cost << ";fidelity=" << fidelity
                          << ";bellpair_per_sec=" << tomography_stats.bell_pair_per_sec << ";tomography_time=" << tomography_stats.tomography_time
                          << ";tomography_measurements=" << tomography_stats.total_measurement_count << "; GOD_clean_pair_total=" << god_clean_pair_total
                          << "; GOD_X_pair_total=" << god_x_pair_total << "; GOD_Y_pair_total=" << god_y_pair_total << "; GOD_Z_pair_total=" << god_z_pair_total << ";}<-->"
                          << "Node (Address: " << my_address << ")"
                          << "; F=" << fidelity << "; X=" << x_error << "; Z=" << z_error << "; Y=" << y_error << endl;
    // this is a temporary implementation so that the e2e-test can read fidelity and error rates
    std::cout << "Node (Address: " << my_address << "<-->QuantumChannel{cost=" << link_cost << ";fidelity=" << fidelity
              << ";bellpair_per_sec=" << tomography_stats.bell_pair_per_sec << ";}<-->"
              << "Node (Address: " << partner << "); Fidelity=" << fidelity << "; Xerror=" << x_error << "; Zerror=" << z_error << "; Yerror=" << y_error << endl;
  }
  tomography_stats_file.close();
  tomography_dm.close();
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
void HardwareMonitor::sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id) {
  LinkTomographyRuleSet *pk = new LinkTomographyRuleSet("LinkTomographyRuleSet");
  pk->setDestAddr(my_address);
  pk->setSrcAddr(partner_address);
  pk->setNumber_of_measuring_resources(num_measure);
  pk->setKind(6);

  auto ruleset = tomography_manager->createLinkTomographyRuleSet(my_address, partner_address, qnic_type, qnic_index, ruleset_id, num_purification, purification_type,
                                                                 x_purification, z_purification, num_measure);
  pk->setRuleSet(ruleset);
  send(pk, "RouterPort$o");
}
}  // namespace quisp::modules
