#include <messages/classical_messages.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>
#include "GeneralizedSwappingAction.h"

using quisp::types::MeasureZResult;

namespace quisp {
namespace rules {
namespace actions {

GeneralizedSwappingAction::GeneralizedSwappingAction(unsigned long RuleSet_id, int rule_index,
                                                      std::vector<int> partners,
                                                      std::vector<int> associated_end_nodes,
                                                      std::vector<QNIC_type> types,
                                                      std::vector<int> ids, std::vector<int> addresses,
                                                      std::vector<int> resources, std::vector<int> self_ids,
                                                      std::vector<QNIC_type> self_types, std::string label, int size_tree) {
  this->ruleset_id = RuleSet_id;
  this->rule_id = rule_index;
  this->associated_end_nodes = associated_end_nodes;
  this->partners = partners;
  this->qnic_types = types;
  this->qnic_ids = ids;
  this->qnic_addresses = addresses;
  this->resources = resources;
  this->self_qnic_ids = self_ids;
  this->self_qnic_types = self_types;
  this->label = label;
  this->size_tree_leafless = size_tree;
}

// TODO: completely mixed
cPacket *GeneralizedSwappingAction::run(cModule *re) {
  float success_probability = 1.0;
  std::vector<int> indexes;
  std::map<IStationaryQubit *, IStationaryQubit*> qubits_pair;
  std::vector<IStationaryQubit*> qubits;


  for (int i = 0; i < partners.size(); i++) {

    //EV_INFO << "choppons la ressource " << resources.at(i) << " avec le partenaire " << partners.at(i) << "\n";

    IStationaryQubit *qubit = getResource(resources.at(i), partners.at(i));


    if (qubit == nullptr) {
      Error *package = new Error;
      package->setError_text("Not enough resource found for GeneralizedEntanglementSwapping! This shouldn't happen!");
      return (package);
    }
    IStationaryQubit *entangled_qubit = qubit->entangled_partner;
    //EV_INFO << "Le entangled partner " << entangled_qubit->node_address << "\n";
    qubits_pair.insert(std::make_pair(qubit, entangled_qubit));
    qubits.push_back(qubit);
    if (qnic_ids.at(i) < 0) {
      Error *package = new Error;
      package->setError_text("QNICs are not found!");
      return (package);
    }
  }

  IStationaryQubit *father_qubit = qubits.back();

  GeneralizedSwappingResult *packet = new GeneralizedSwappingResult;

  packet->setRuleSet_id(ruleset_id);
  packet->setRule_id(rule_id);
  packet->setAction_index(action_index);
  packet->setSize_of_arrays(partners.size());
  packet->setMeasurement_resultsArraySize(partners.size());
  packet->setResponder_destsArraySize(partners.size());

  for (int i = 0; i < partners.size() - 1; i++) {
    qubits[i]->CNOT_gate(father_qubit);
    qubits[i]->entangled_partner->label = label;
    EV_INFO << "QBIT " << qubits[i]->entangled_partner->stationaryQubit_address << " at adress " << qubits[i]->node_address << "with label " << qubits[i]->entangled_partner->label
            << "\n";
    packet->setMeasurement_results(i, (int)qubits[i]->measure_Z());
    packet->setMeasurement_results(i, 1);
    EV_INFO << "Correction (Z) " << packet->getMeasurement_results(i) << "\n";
    packet->setResponder_dests(i, associated_end_nodes[i]);
  }

  qubits[partners.size() - 1]->entangled_partner->label = label;
  EV_INFO << "QBIT " << qubits[partners.size() - 1]->entangled_partner->stationaryQubit_address << " at adress " << qubits[partners.size() - 1]->node_address << "with label "
          << qubits[partners.size() - 1]->entangled_partner->label << "\n";
  EV_INFO << "Correction (X) " << packet->getMeasurement_results(partners.size() - 1) << "\n";
  packet->setMeasurement_results(partners.size() - 1, (int)father_qubit->measure_X());
  packet->setResponder_dests(partners.size() - 1, associated_end_nodes.back());

  packet->setSize_of_tree_leafless(size_tree_leafless);
  packet->setLabel(label.c_str());
  
  IRuleEngine *rule_engine = check_and_cast<IRuleEngine *>(re);
  for (auto it = qubits_pair.begin(); it != qubits_pair.end(); ++it) {
    //it->second->setEntangledPartnerInfo(father_qubit->entangled_partner);
    removeResource_fromRule(it->first);
  }
  // CM: For now we impose a success
  /*if ((std::rand() / RAND_MAX) < success_probability)
  {
    for (auto it = qubits_pair.begin(); it != qubits_pair.end(); ++it)
    {
      it->second->setEntangledPartnerInfo(it->first);
      removeResource_fromRule(it->first);
    }
  }
  else
  {
    for (auto it = qubits_pair.begin(); it != qubits_pair.end(); ++it) {
      removeResource_fromRule(it->second);
      removeResource_fromRule(it->first);
    }
  }*/

  for (int i = 0; i < partners.size(); i++)
  {
    rule_engine->freeConsumedResource(self_qnic_ids.at(i), qubits.at(i), self_qnic_types.at(i));
    indexes.push_back(qubits_pair.at(qubits.at(i))->stationaryQubit_address);
  }
  
  return (packet);
    // result packet
  //
  /*SwappingResult *pk = new SwappingResult;
  // no destination here. In RuleEngine, it's set.
  // this setKind() doesn't seem to have any effect; set instead in void RuleEngine::traverseThroughAllProcesses2()
  pk->setKind(5);
  pk->setRuleSet_id(ruleset_id);
  pk->setRule_id(rule_id);
  pk->setAction_index(action_index);
  pk->setOperation_type_left(operation_type_left);  // operation type for left node
  pk->setOperation_type_right(operation_type_right);  // operation type for right node
  // These information are cropped in the RuleEngine.
  pk->setLeft_Dest(left_partner);  // this might not require but just in case
  pk->setRight_Dest(right_partner);

  pk->setNew_partner_left(right_partner);
  pk->setNew_partner_qnic_index_left(right_qnic_id);
  pk->setNew_partner_qnic_type_left(right_qnic_type);
  pk->setNew_partner_qnic_address_left(right_qnic_address);
  pk->setMeasured_qubit_index_left(lindex);  // here is wrong;

  pk->setNew_partner_right(left_partner);
  pk->setNew_partner_qnic_index_right(left_qnic_id);
  pk->setNew_partner_qnic_type_right(left_qnic_type);
  pk->setNew_partner_qnic_address_right(left_qnic_address);
  pk->setMeasured_qubit_index_right(rindex);*/
  //return pk;
}

}  // namespace actions
}  // namespace rules
}  // namespace quisp
