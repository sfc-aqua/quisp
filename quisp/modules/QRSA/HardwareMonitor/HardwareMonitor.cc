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
#include "utils/TomographyManager.h"

using namespace quisp::messages;
using namespace quisp::rules;
using Eigen::Matrix4cd;
using Eigen::Vector4cd;
using quisp::utils::HelperFunctions;

namespace quisp::modules {

HardwareMonitor::HardwareMonitor() : provider(utils::ComponentProvider{this}) {}
HardwareMonitor::~HardwareMonitor() {}

// HardwareMonitor is also responsible for calculating the rssi/oka's protocol/fidelity calculate and give it to the RoutingDaemon
void HardwareMonitor::initialize(int stage) {
  EV_INFO << "HardwareMonitor booted\n";
  routing_daemon = provider.getRoutingDaemon();

  num_qnic_rp = par("number_of_qnics_rp");
  num_qnic_r = par("number_of_qnics_r");
  num_qnic = par("number_of_qnics");

  /*This keeps which node is connected to which local qnic.*/
  tomography_output_filename = par("tomography_output_filename").str();
  // remove double quotes at the beginning and end
  tomography_output_filename = tomography_output_filename.substr(1, tomography_output_filename.length() - 2);
  file_dir_name = par("file_dir_name").str();
  do_link_level_tomography = par("link_tomography");
  num_purification = par("initial_purification");
  x_purification = par("x_purification");
  z_purification = par("z_purification");
  purification_type = par("purification_type");
  num_measure = par("num_measure");
  my_address = provider.getNodeAddr();

  if (stage == 0) {
    return;
  }

  prepareNeighborTable();
  WATCH_MAP(neighbor_table);

  auto neighbor_addresses = routing_daemon->getNeighborAddresses();

  // Initialize link costs
  for (auto neighbor : neighbor_addresses) {
    // Values will be updated after link tomography
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

double HardwareMonitor::getLinkCost(int neighbor_address) {
  if (!link_cost_table.count(neighbor_address)) {
    error("Link cost for neighbor %d not found", neighbor_address);
  }
  return link_cost_table[neighbor_address];
}

void HardwareMonitor::handleMessage(cMessage *msg) {
  if (auto *request = dynamic_cast<LinkTomographyRequest *>(msg)) {
    /* Received a tomography request from neighbor */

    auto interface_info = routing_daemon->getQuantumInterfaceInfo(request->getSrcAddr());

    /*Prepare an acknowledgment*/
    LinkTomographyAck *pk = new LinkTomographyAck("LinkTomographyAck");
    pk->setSrcAddr(my_address);
    pk->setDestAddr(request->getSrcAddr());
    pk->setKind(6);
    pk->setQnic_index(interface_info->qnic.index);
    pk->setQnic_type(interface_info->qnic.type);

    send(pk, "RouterPort$o");
    delete request;
    return;
  }

  if (auto *ack = dynamic_cast<LinkTomographyAck *>(msg)) {
    /*Received an acknowledgment for tomography from neighbor.*/

    /*Create and send RuleSets*/
    int partner_address = ack->getSrcAddr();

    auto my_qnic_info = routing_daemon->getQuantumInterfaceInfo(partner_address);

    // RuleSets sent for this node and the partner node.
    long ruleset_id = HelperFunctions::createUniqueId(this->getRNG(0), my_address, simTime());
    sendLinkTomographyRuleSet(my_address, partner_address, my_qnic_info->qnic.type, my_qnic_info->qnic.index, ruleset_id);

    QNIC_type partner_qnic_type = ack->getQnic_type();
    int partner_qnic_index = ack->getQnic_index();
    sendLinkTomographyRuleSet(partner_address, my_address, partner_qnic_type, partner_qnic_index, ruleset_id);
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

    auto qnic_id = local_qnic.index;
    auto partner = partner_addr;
    auto tomography_round = result->getCount_id();
    auto measurement_basis = result->getBasis();
    auto tomography_outcome = result->getOutput_is_plus();
    auto god_clean = result->getGOD_clean();
    tomography_partners.insert(std::make_tuple(qnic_id, partner));
    if (result->getSrcAddr() == my_address) {
      // Result from my self
      // Pass result to the tomography manager
      tomography_manager.addLocalResult(qnic_id, partner, tomography_round, measurement_basis, tomography_outcome, god_clean);
    } else {
      // Result from partner
      tomography_manager.addPartnerResult(qnic_id, partner, tomography_round, measurement_basis, tomography_outcome, god_clean);
    }

    if (result->getFinish() != -1) {
      // Finish tomography and record tomography stats
      tomography_manager.setStats(qnic_id, partner, result->getFinish(), (double)result->getMax_count() / result->getFinish().dbl(), result->getMax_count());
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
  std::ofstream tomography_stats_file(file_name, std::ios_base::app);
  std::ofstream tomography_dm(file_name_dm, std::ios_base::app);
  std::cout << "Opened new file to write.\n";

  for (auto partner_key : tomography_partners) {
    auto qnic_id = std::get<0>(partner_key);
    auto partner = std::get<1>(partner_key);
    Matrix4cd extended_density_matrix_reconstructed = tomography_manager.reconstructDensityMatrix(qnic_id, partner);

    auto fidelity = tomography_manager.calcFidelity(qnic_id, partner);
    auto [x_error, y_error, z_error] = tomography_manager.calcErrorRate(qnic_id, partner);
    auto tomography_stats = tomography_manager.getStats(qnic_id, partner);
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

    auto [god_clean_pair_total, god_x_pair_total, god_y_pair_total, god_z_pair_total] = tomography_manager.calcGodPairCount(qnic_id, partner);
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
  if (provider.isQNodeType(neighbor_node_type) && provider.isBSANodeType(neighbor_node_type) && provider.isSPDCNodeType(neighbor_node_type)) {
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
void HardwareMonitor::sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id) {
  LinkTomographyRuleSet *pk = new LinkTomographyRuleSet("LinkTomographyRuleSet");
  pk->setDestAddr(my_address);
  pk->setSrcAddr(partner_address);
  pk->setNumber_of_measuring_resources(num_measure);
  pk->setKind(6);

  auto ruleset = tomography_manager.createLinkTomographyRuleSet(my_address, partner_address, qnic_type, qnic_index, ruleset_id, num_purification, purification_type, x_purification,
                                                                z_purification, num_measure);
  pk->setRuleSet(ruleset);
  send(pk, "RouterPort$o");
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
  // (excluding SPDC and BSA nodes)
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

  if (provider.isSPDCNodeType(type)) {
    error("TO BE IMPLEMENTED");
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
