#pragma once

#include <omnetpp.h>
#include <sstream>
#include <stdexcept>

#include <messages/classical_messages.h>
#include <runtime/Runtime.h>
#include <runtime/types.h>
#include <utils/ComponentProvider.h>

#include "RuleEngine.h"

namespace quisp::modules::runtime_callback {

using namespace quisp::runtime;
using quisp::modules::RuleEngine;
using quisp::runtime::QNodeAddr;
using namespace quisp::messages;

struct RuntimeCallback : public quisp::runtime::Runtime::ICallBack {
  RuntimeCallback(RuleEngine *re) : rule_engine(re), provider(re->provider) {}

  MeasurementOutcome measureQubitRandomly(IQubitRecord *qubit_rec) override {
    auto qubit = provider.getStationaryQubit(qubit_rec);
    return qubit->measure_density_independent();
  }

  MeasurementOutcome measureQubitX(IQubitRecord *qubit_rec) override {
    auto qubit = provider.getStationaryQubit(qubit_rec);
    return MeasurementOutcome{.basis = 'X', .outcome_is_plus = qubit->localMeasureX() == types::EigenvalueResult::PLUS_ONE};
  }

  MeasurementOutcome measureQubitZ(IQubitRecord *qubit_rec) override {
    auto qubit = provider.getStationaryQubit(qubit_rec);
    return MeasurementOutcome{.basis = 'Z', .outcome_is_plus = qubit->localMeasureZ() == types::EigenvalueResult::PLUS_ONE};
  }

  void gateX(IQubitRecord *qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    assert(qubit != nullptr);
    qubit->X_gate();
  }

  void gateZ(IQubitRecord *qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    assert(qubit != nullptr);
    qubit->Z_gate();
  }

  void gateCNOT(IQubitRecord *control_qubit_rec, IQubitRecord *target_qubit_rec) override {
    auto *control_qubit = provider.getStationaryQubit(control_qubit_rec);
    auto *target_qubit = provider.getStationaryQubit(target_qubit_rec);
    assert(control_qubit != nullptr);
    assert(target_qubit != nullptr);
    target_qubit->CNOT_gate(control_qubit);
  }

  bool purifyX(IQubitRecord *qubit_rec, IQubitRecord *trash_qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    auto *trash_qubit = provider.getStationaryQubit(trash_qubit_rec);
    assert(qubit != nullptr);
    assert(trash_qubit != nullptr);
    return trash_qubit->Xpurify(qubit);
  }

  bool purifyZ(IQubitRecord *qubit_rec, IQubitRecord *trash_qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    auto *trash_qubit = provider.getStationaryQubit(trash_qubit_rec);
    assert(qubit != nullptr);
    assert(trash_qubit != nullptr);
    return trash_qubit->Zpurify(qubit);
  }

  void sendLinkTomographyResult(const unsigned long ruleset_id, const runtime::Rule &rule, const int action_index, const runtime::QNodeAddr partner_addr, int count,
                                MeasurementOutcome outcome, int max_count, SimTime start_time) override {
    LinkTomographyResult *pk = new LinkTomographyResult{"LinkTomographyResult"};
    auto src = rule_engine->parentAddress;
    pk->setSrcAddr(src);
    pk->setDestAddr(partner_addr.val);
    pk->setCount_id(count);
    pk->setPartner_address(src);  // Partner's partner is self/src
    pk->setKind(6);
    pk->setOutput_is_plus(outcome.outcome_is_plus);
    pk->setBasis(outcome.basis);
    pk->setGOD_clean(outcome.GOD_clean);
    if (count == max_count) {
      pk->setFinish(simTime() - start_time);
      pk->setMax_count(max_count);
    }
    // // The cPacket *pk is a single packet forwarded to the neighbor. But this node's HardwareMonitor also needs to store the result.
    LinkTomographyResult *pk_for_self = pk->dup();
    pk_for_self->setPartner_address(pk->getDestAddr());
    pk_for_self->setDestAddr(pk->getSrcAddr());
    rule_engine->send(pk, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void sendSinglePurificationResult(const unsigned long ruleset_id, const runtime::Rule &rule, const int action_index, const QNodeAddr partner_addr, bool result,
                                    int pur_type) override {
    auto *pkt = new PurificationResult{"PurificationResult"};
    pkt->setSrcAddr(rule_engine->parentAddress);
    pkt->setDestAddr(partner_addr.val);
    pkt->setKind(7);
    pkt->setAction_index(action_index);
    pkt->setRule_id(rule.id);
    pkt->setRuleset_id(ruleset_id);
    pkt->setShared_tag(rule.shared_tag);
    pkt->setOutput_is_plus(result);
    pkt->setPurType(pur_type);
    auto *pk_for_self = pkt->dup();
    pk_for_self->setDestAddr(rule_engine->parentAddress);
    rule_engine->send(pkt, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void sendDoublePurificationResult(const unsigned long ruleset_id, const runtime::Rule &rule, const int action_index, const QNodeAddr partner_addr, bool result_z, bool result_x,
                                    int pur_type) override {
    auto *pkt = new DoublePurificationResult{"DoublePurificationResult"};
    pkt->setSrcAddr(rule_engine->parentAddress);
    pkt->setDestAddr(partner_addr.val);
    pkt->setKind(7);
    pkt->setAction_index(action_index);
    pkt->setRule_id(rule.id);
    pkt->setRuleset_id(ruleset_id);
    pkt->setShared_tag(rule.shared_tag);
    pkt->setXOutput_is_plus(result_x);
    pkt->setZOutput_is_plus(result_z);
    pkt->setPurType(pur_type);
    auto *pk_for_self = pkt->dup();
    pk_for_self->setDestAddr(rule_engine->parentAddress);
    rule_engine->send(pkt, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void sendTriplePurificationResult(const unsigned long ruleset_id, const runtime::Rule &rule, const int action_index, const QNodeAddr partner_addr, bool result_z, bool result_x,
                                    bool result_ds, int pur_type) override {
    auto *pkt = new DS_DoublePurificationSecondResult{"DS_DoublePurificationSecondResult"};
    pkt->setSrcAddr(rule_engine->parentAddress);
    pkt->setDestAddr(partner_addr.val);
    pkt->setKind(7);
    pkt->setAction_index(action_index);
    pkt->setRule_id(rule.id);
    pkt->setRuleset_id(ruleset_id);
    pkt->setShared_tag(rule.shared_tag);
    pkt->setXOutput_is_plus(result_x);
    pkt->setZOutput_is_plus(result_z);
    pkt->setDS_Output_is_plus(result_ds);
    pkt->setPurType(pur_type);
    auto *pk_for_self = pkt->dup();
    pk_for_self->setDestAddr(rule_engine->parentAddress);
    rule_engine->send(pkt, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void sendQuadruplePurificationResult(const unsigned long ruleset_id, const runtime::Rule &rule, const int action_index, const QNodeAddr partner_addr, bool result_z,
                                       bool result_x, bool result_ds_z, bool result_ds_x, int pur_type) override {
    auto *pkt = new DS_DoublePurificationResult{"DS_DoublePurificationResult"};
    pkt->setSrcAddr(rule_engine->parentAddress);
    pkt->setDestAddr(partner_addr.val);
    pkt->setKind(7);
    pkt->setAction_index(action_index);
    pkt->setRule_id(rule.id);
    pkt->setRuleset_id(ruleset_id);
    pkt->setShared_tag(rule.shared_tag);
    pkt->setXOutput_is_plus(result_x);
    pkt->setZOutput_is_plus(result_z);
    pkt->setDS_ZOutput_is_plus(result_ds_z);
    pkt->setDS_XOutput_is_plus(result_ds_x);
    pkt->setPurType(pur_type);
    auto *pk_for_self = pkt->dup();
    pk_for_self->setDestAddr(rule_engine->parentAddress);
    rule_engine->send(pkt, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void sendSwappingResults(const unsigned long ruleset_id, const runtime::Rule &rule, const QNodeAddr left_partner_addr, int left_op, const QNodeAddr right_partner_addr,
                           int right_op) override {
    auto src_addr = rule_engine->parentAddress;

    SwappingResult *pkt_for_left = new SwappingResult("SwappingResult(Left)");
    pkt_for_left->setRuleSet_id(ruleset_id);
    pkt_for_left->setRule_id(rule.id);
    pkt_for_left->setShared_tag(rule.shared_tag);
    pkt_for_left->setKind(5);  // cyan
    pkt_for_left->setSrcAddr(src_addr);

    SwappingResult *pkt_for_right = pkt_for_left->dup();
    pkt_for_right->setName("SwappingResult(Right)");

    // packet for left node
    pkt_for_left->setDestAddr(left_partner_addr.val);
    pkt_for_left->setOperation_type(left_op);
    pkt_for_left->setNew_partner(right_partner_addr.val);
    // HACK: see hackSwappingPartners method
    pkt_for_left->setMeasured_qubit_index(left_qubit_index);

    // packet for right node
    pkt_for_right->setDestAddr(right_partner_addr.val);
    pkt_for_right->setOperation_type(right_op);
    pkt_for_right->setNew_partner(left_partner_addr.val);
    // HACK: see hackSwappingPartners method
    pkt_for_right->setMeasured_qubit_index(right_qubit_index);

    rule_engine->send(pkt_for_left, "RouterPort$o");
    rule_engine->send(pkt_for_right, "RouterPort$o");
  }

  void freeAndResetQubit(IQubitRecord *qubit) override {
    auto *stat_qubit = rule_engine->provider.getStationaryQubit((qubit));
    rule_engine->freeConsumedResource(qubit->getQNicIndex(), stat_qubit, qubit->getQNicType());
  };

  bool isQubitLocked(IQubitRecord *const qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    return qubit->isLocked();
  }

  void lockQubit(IQubitRecord *const qubit_rec, unsigned long rs_id, int rule_id, int action_index) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    qubit->Lock(rs_id, rule_id, action_index);
  }
  int getActionIndex(IQubitRecord *const qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    return qubit->action_index;
  }

  void hackSwappingPartners(IQubitRecord *const left_qubit_rec, IQubitRecord *const right_qubit_rec) override {
    // HACK: this comes from the original SwappingAction.cc
    // manipulate entangled partners to reproduce the situation of entanglement swapping
    // this will be not used if we implement more realistic qubit backend
    // auto *left_qubit = provider.getStationaryQubit(left_qubit_rec);
    // auto *right_qubit = provider.getStationaryQubit(right_qubit_rec);
    // auto left_partner_qubit = left_qubit->entangled_partner;
    // auto right_partner_qubit = right_qubit->entangled_partner;
    // if (right_partner_qubit == nullptr) throw std::runtime_error("invalid right partner qubit");
    // if (left_partner_qubit == nullptr) throw std::runtime_error("invalid left partner qubit");
    // right_partner_qubit->setEntangledPartnerInfo(left_partner_qubit);
    // left_partner_qubit->setEntangledPartnerInfo(right_partner_qubit);

    // HACK: this is also comes from the original SwappingAction.cc
    // at the both partner nodes, they need know which qubits are swapped.
    // so here these qubit indices are stored and later sendSwappingResults method uses it
    // this must be tracked in another way because we can't know these information
    // from the actual qubits in real world
    // right_qubit_index = right_partner_qubit->stationary_qubit_address;
    // left_qubit_index = left_partner_qubit->stationary_qubit_address;
  }

  void hackBreakEntanglement(IQubitRecord *qubit) override{
      // auto *stat_qubit = rule_engine->provider.getStationaryQubit((qubit));
      // HACK: comes from the original PurifyAction.cc.
      // we're freeing the qubit but its entangled_partner will be freed later.
      // to pass the validation in RuleEngine::freeFailedQubits_and_AddAsResource for next round,
      // break the entanglement manually.
      // if (stat_qubit->entangled_partner != nullptr && stat_qubit->entangled_partner->entangled_partner != nullptr) {
      //   stat_qubit->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
      //   stat_qubit->entangled_partner->entangled_partner = nullptr;
      // }
  };

  std::string getNodeInfo() override {
    std::stringstream ss;
    ss << "QNodeAddr:" << std::to_string(rule_engine->parentAddress) << ", event #" << std::to_string(omnetpp::getSimulation()->getEventNumber());
    return ss.str();
  }

  RuleEngine *rule_engine;
  utils::ComponentProvider &provider;
  int right_qubit_index = -1;
  int left_qubit_index = -1;
};

}  // namespace quisp::modules::runtime_callback
