#pragma once

#include <runtime/Runtime.h>
#include <runtime/types.h>
#include <utils/ComponentProvider.h>
#include <stdexcept>

#include "RuleEngine.h"
#include "messages/purification_messages_m.h"

namespace quisp::modules::runtime_callback {

using namespace quisp::runtime;
using quisp::modules::RuleEngine;
using quisp::runtime::QNodeAddr;

struct RuntimeCallback : public quisp::runtime::Runtime::ICallBack {
  RuntimeCallback(RuleEngine *re) : rule_engine(re), provider(re->provider) {}

  MeasurementOutcome measureQubitRandomly(IQubitRecord *) override { throw std::runtime_error("not implemented yet"); }

  void gateX(IQubitRecord *qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    assert(qubit != nullptr);
    qubit->xGate();
  }

  void gateZ(IQubitRecord *qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    assert(qubit != nullptr);
    qubit->zGate();
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
                                MeasurementOutcome outcome, bool is_finished) override {
    throw std::runtime_error("not implemented yet");

    LinkTomographyResult *pk = new LinkTomographyResult{"LinkTomographyResult"};
    auto src = rule_engine->parentAddress;
    pk->setSrcAddr(src);
    pk->setDestAddr(partner_addr.val);
    // pk->setCount_id(current_count);
    pk->setPartner_address(src);  // Partner's partner is self/src
    pk->setKind(6);
    pk->setOutput_is_plus(outcome.outcome_is_plus);
    pk->setBasis(outcome.basis);
    pk->setGOD_clean(outcome.GOD_clean);
    // if (is_finished) {
    // pk->setFinish(simTime() - start);
    // pk->setMax_count(max_count);
    // }
    // // The cPacket *pk is a single packet forwarded to the neighbor. But this node's HardwareMonitor also needs to store the result.
    LinkTomographyResult *pk_for_self = pk->dup();
    pk_for_self->setPartner_address(pk->getDestAddr());
    pk_for_self->setDestAddr(pk->getSrcAddr());
    rule_engine->send(pk, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void sendPurificationResult(const unsigned long ruleset_id, const runtime::Rule &rule, const int action_index, const QNodeAddr partner_addr, bool result) override {
    auto *pkt = new PurificationResult{"PurificationResult"};
    pkt->setSrcAddr(rule_engine->parentAddress);
    pkt->setDestAddr(partner_addr.val);
    pkt->setKind(7);
    pkt->setAction_index(action_index);
    pkt->setRule_id(rule.id);
    pkt->setRuleset_id(ruleset_id);
    pkt->setShared_tag(rule.shared_tag);
    pkt->setOutput_is_plus(result);
    PurificationResult *pk_for_self = pkt->dup();
    pk_for_self->setDestAddr(rule_engine->parentAddress);
    rule_engine->send(pkt, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void freeAndResetQubit(IQubitRecord *qubit) override {
    auto *stat_qubit = rule_engine->provider.getStationaryQubit((qubit));
    // HACK: comes from the original PurifyAction.cc.
    // we're freeing the qubit but its entangled_partner will be freed later.
    // to pass the validation in RuleEngine::freeFailedQubits_and_AddAsResource for next round,
    // break the entanglement manually.
    if (stat_qubit->entangled_partner != nullptr && stat_qubit->entangled_partner->entangled_partner != nullptr) {
      stat_qubit->entangled_partner->no_density_matrix_nullptr_entangled_partner_ok = true;
      stat_qubit->entangled_partner->entangled_partner = nullptr;
    }
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
  RuleEngine *rule_engine;
  utils::ComponentProvider &provider;
};

}  // namespace quisp::modules::runtime_callback
