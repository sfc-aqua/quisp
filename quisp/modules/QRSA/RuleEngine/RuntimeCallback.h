#pragma once

#include <omnetpp.h>
#include <sstream>
#include <stdexcept>

#include <messages/classical_messages.h>
#include <runtime/Runtime.h>
#include <runtime/types.h>
#include <utils/ComponentProvider.h>

#include "RuleEngine.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/RuleEngine/QubitRecord/IQubitRecord.h"

namespace quisp::modules::runtime_callback {

using namespace quisp::runtime;
using quisp::modules::RuleEngine;
using quisp::runtime::QNodeAddr;
using namespace quisp::messages;

struct RuntimeCallback : public quisp::runtime::Runtime::ICallBack {
  RuntimeCallback(RuleEngine *re) : rule_engine(re), provider(re->provider) {}

  MeasurementOutcome measureQubitRandomly(IQubitRecord *qubit_rec) override {
    auto qubit = provider.getStationaryQubit(qubit_rec);
    return qubit->measureRandomPauliBasis();
  }

  MeasurementOutcome measureQubitX(IQubitRecord *qubit_rec) override {
    auto qubit = provider.getStationaryQubit(qubit_rec);
    return MeasurementOutcome{.basis = 'X', .outcome_is_plus = qubit->measureX() == types::EigenvalueResult::PLUS_ONE};
  }

  MeasurementOutcome measureQubitZ(IQubitRecord *qubit_rec) override {
    auto qubit = provider.getStationaryQubit(qubit_rec);
    return MeasurementOutcome{.basis = 'Z', .outcome_is_plus = qubit->measureZ() == types::EigenvalueResult::PLUS_ONE};
  }

  MeasurementOutcome measureQubitY(IQubitRecord *qubit_rec) override {
    auto qubit = provider.getStationaryQubit(qubit_rec);
    return MeasurementOutcome{.basis = 'Y', .outcome_is_plus = qubit->measureY() == types::EigenvalueResult::PLUS_ONE};
  }

  void gateX(IQubitRecord *qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    assert(qubit != nullptr);
    qubit->gateX();
  }

  void gateZ(IQubitRecord *qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    assert(qubit != nullptr);
    qubit->gateZ();
  }

  void gateY(IQubitRecord *qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    assert(qubit != nullptr);
    qubit->gateY();
  }

  void gateCNOT(IQubitRecord *control_qubit_rec, IQubitRecord *target_qubit_rec) override {
    auto *control_qubit = provider.getStationaryQubit(control_qubit_rec);
    auto *target_qubit = provider.getStationaryQubit(target_qubit_rec);
    assert(control_qubit != nullptr);
    assert(target_qubit != nullptr);
    control_qubit->gateCNOT(target_qubit);
  }

  int purifyX(IQubitRecord *qubit_rec, IQubitRecord *trash_qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    auto *trash_qubit = provider.getStationaryQubit(trash_qubit_rec);
    assert(qubit != nullptr);
    assert(trash_qubit != nullptr);
    qubit->gateCNOT(trash_qubit);
    return trash_qubit->measureZ() == types::EigenvalueResult::PLUS_ONE ? 0 : 1;
  }

  int purifyZ(IQubitRecord *qubit_rec, IQubitRecord *trash_qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    auto *trash_qubit = provider.getStationaryQubit(trash_qubit_rec);
    assert(qubit != nullptr);
    assert(trash_qubit != nullptr);
    trash_qubit->gateCNOT(qubit);
    return trash_qubit->measureX() == types::EigenvalueResult::PLUS_ONE ? 0 : 1;
  }

  int purifyY(IQubitRecord *qubit_rec, IQubitRecord *trash_qubit_rec) override {
    auto *qubit = provider.getStationaryQubit(qubit_rec);
    auto *trash_qubit = provider.getStationaryQubit(trash_qubit_rec);
    assert(qubit != nullptr);
    assert(trash_qubit != nullptr);

    trash_qubit->gateSdg();
    qubit->gateSdg();
    trash_qubit->gateCNOT(qubit);
    qubit->gateS();
    return trash_qubit->measureX() == types::EigenvalueResult::PLUS_ONE ? 0 : 1;
  }

  void updateQubitPartner(IQubitRecord *qubit, QNodeAddr new_partner_addr) override {
    // TODO: complete this
    // change the bell pair store
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

  void sendPurificationResult(const unsigned long ruleset_id, int shared_rule_tag, const QNodeAddr partner_addr, int measurement_result, int purification_protocol) override {
    auto *pkt = new PurificationResult{"PurificationResult"};
    pkt->setSrcAddr(rule_engine->parentAddress);
    pkt->setDestAddr(partner_addr.val);
    pkt->setKind(7);
    // TODO: COMPLETE THIS
    auto *pk_for_self = pkt->dup();
    pk_for_self->setDestAddr(rule_engine->parentAddress);
    rule_engine->send(pkt, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void sendSwappingResults(const unsigned long ruleset_id, const runtime::Rule &rule, const QNodeAddr left_partner_addr, int left_op, const QNodeAddr right_partner_addr,
                           int right_op) override {
    /**
     * what we need is just the ruleset id, shared_rule_tag (so we know which rule to apply), and resource_id (sequence number)
     *
     */

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
    pkt_for_left->setMeasured_qubit_index(left_qubit_index);

    // packet for right node
    pkt_for_right->setDestAddr(right_partner_addr.val);
    pkt_for_right->setOperation_type(right_op);
    pkt_for_right->setNew_partner(left_partner_addr.val);
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
