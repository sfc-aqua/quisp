#pragma once

#include <runtime/Runtime.h>
#include "RuleEngine.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::runtime_callback {

using namespace quisp::runtime;
using quisp::modules::RuleEngine;

struct RuntimeCallback : public quisp::runtime::Runtime::ICallBack {
  RuntimeCallback(RuleEngine *re) : rule_engine(re), provider(re->provider) {}

  MeasurementOutcome measureQubitRandomly(IQubitRecord *) override {}

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

  void sendLinkTomographyResult(runtime::QNodeAddr partner_addr, int count, MeasurementOutcome outcome, bool is_finished) override {
    LinkTomographyResult *pk = new LinkTomographyResult;
    // pk->setSrcAddr(src);
    // pk->setDestAddr(dst);
    // pk->setCount_id(current_count);
    // pk->setPartner_address(src);  // Partner's partner is self/src
    // pk->setKind(6);
    // pk->setOutput_is_plus(o.outcome_is_plus);
    // pk->setBasis(o.basis);
    // pk->setGOD_clean(o.GOD_clean);
    // if (current_count == max_count) {
    //   pk->setFinish(simTime() - start);
    //   pk->setMax_count(max_count);
    // }
    // // The cPacket *pk is a single packet forwarded to the neighbor. But this node's HardwareMonitor also needs to store the result.
    LinkTomographyResult *pk_for_self = pk->dup();
    pk_for_self->setPartner_address(pk->getDestAddr());
    pk_for_self->setDestAddr(pk->getSrcAddr());
    rule_engine->send(pk, "RouterPort$o");
    rule_engine->send(pk_for_self, "RouterPort$o");
  }

  void freeAndResetQubit(IQubitRecord *) override{};

  RuleEngine *rule_engine;
  utils::ComponentProvider &provider;
};

}  // namespace quisp::modules::runtime_callback
