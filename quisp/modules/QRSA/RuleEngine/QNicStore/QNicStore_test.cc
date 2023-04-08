#include "QNicStore.h"
#include <gtest/gtest.h>
#include <modules/Logger/DisabledLogger.h>
#include <modules/QNIC.h>
#include <omnetpp/cmodule.h>
#include <test_utils/TestUtils.h>
#include <utils/ComponentProvider.h>

namespace {
using namespace quisp_test;
using quisp::utils::ComponentProvider;
using namespace quisp::modules::Logger;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_N;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;
using quisp::modules::QNIC_type;

class Strategy : public TestComponentProviderStrategy {
 public:
  Strategy(std::vector<QNicSpec> specs) : TestComponentProviderStrategy(specs) {
    for (auto spec : specs) {
      qnic_modules.insert({{spec.type, spec.qnic_index}, new cModule()});
    }
  }
  std::map<std::pair<QNIC_type, int>, cModule*> qnic_modules;
  cModule* getQNIC(int qnic_index, QNIC_type qnic_type) override {
    auto it = qnic_modules.find({qnic_type, qnic_index});
    if (it == qnic_modules.end()) return nullptr;
    return it->second;
  }
};

class QNicStore : public quisp::modules::qnic_store::QNicStore {
 public:
  QNicStore(ComponentProvider& provider, int number_of_emitter_qnics, int number_of_receiver_qnics, int number_of_passive_receiver_qnics)
      : quisp::modules::qnic_store::QNicStore(provider, number_of_emitter_qnics, number_of_receiver_qnics, number_of_passive_receiver_qnics, new DisabledLogger{}) {}

  using quisp::modules::qnic_store::QNicStore::getQNic;
  using quisp::modules::qnic_store::QNicStore::qnics;
};

TEST(QNicStore, Init) {
  ComponentProvider provider(new cModule());
  std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 1}, {QNIC_E, 1, 3}, {QNIC_R, 0, 1}, {QNIC_RP, 0, 1}};
  int num_emitter_qnics = 2;
  int num_receiver_qnics = 1;
  int num_passive_receiver_qnics = 1;

  provider.setStrategy(std::make_unique<Strategy>(qnic_specs));
  QNicStore store(provider, num_emitter_qnics, num_receiver_qnics, num_passive_receiver_qnics);

  ASSERT_EQ(3, store.qnics.size());
  EXPECT_EQ(2, store.qnics.at(QNIC_E).size());
  EXPECT_EQ(1, store.qnics.at(QNIC_R).size());
  EXPECT_EQ(1, store.qnics.at(QNIC_RP).size());
}

TEST(QNicStore, CountFreeQubits) {
  ComponentProvider provider(new cModule());
  std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 1}, {QNIC_E, 1, 3}, {QNIC_R, 0, 1}, {QNIC_RP, 0, 1}};
  int num_emitter_qnics = 2;
  int num_receiver_qnics = 1;
  int num_passive_receiver_qnics = 1;

  provider.setStrategy(std::make_unique<Strategy>(qnic_specs));
  QNicStore store(provider, num_emitter_qnics, num_receiver_qnics, num_passive_receiver_qnics);

  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_E, 0));
  EXPECT_EQ(3, store.countNumFreeQubits(QNIC_E, 1));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_R, 0));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_RP, 0));
}

TEST(QNicStore, TakeFreeQubits) {
  ComponentProvider provider(new cModule());
  std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 1}, {QNIC_E, 1, 3}, {QNIC_R, 0, 1}, {QNIC_RP, 0, 1}};
  int num_emitter_qnics = 2;
  int num_receiver_qnics = 1;
  int num_passive_receiver_qnics = 1;

  provider.setStrategy(std::make_unique<Strategy>(qnic_specs));
  QNicStore store(provider, num_emitter_qnics, num_receiver_qnics, num_passive_receiver_qnics);

  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_E, 0));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_R, 0));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_RP, 0));
  EXPECT_EQ(3, store.countNumFreeQubits(QNIC_E, 1));
  EXPECT_NE(-1, store.takeFreeQubitIndex(QNIC_E, 1));
  EXPECT_EQ(2, store.countNumFreeQubits(QNIC_E, 1));
  EXPECT_NE(-1, store.takeFreeQubitIndex(QNIC_E, 1));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_E, 1));
  EXPECT_NE(-1, store.takeFreeQubitIndex(QNIC_E, 1));
  EXPECT_EQ(0, store.countNumFreeQubits(QNIC_E, 1));
  EXPECT_EQ(-1, store.takeFreeQubitIndex(QNIC_E, 1));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_E, 0));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_R, 0));
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_RP, 0));
}

TEST(QNicStore, SetQubitBusy) {
  ComponentProvider provider(new cModule());
  std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 1}, {QNIC_E, 1, 3}, {QNIC_R, 0, 1}, {QNIC_RP, 0, 1}};
  int num_emitter_qnics = 2;
  int num_receiver_qnics = 1;
  int num_passive_receiver_qnics = 1;

  provider.setStrategy(std::make_unique<Strategy>(qnic_specs));
  QNicStore store(provider, num_emitter_qnics, num_receiver_qnics, num_passive_receiver_qnics);

  EXPECT_EQ(3, store.countNumFreeQubits(QNIC_E, 1));
  store.setQubitBusy(QNIC_E, 1, 0, true);
  EXPECT_EQ(2, store.countNumFreeQubits(QNIC_E, 1));
  store.setQubitBusy(QNIC_E, 1, 1, true);
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_E, 1));
  store.setQubitBusy(QNIC_E, 1, 2, true);
  EXPECT_EQ(0, store.countNumFreeQubits(QNIC_E, 1));
  store.setQubitBusy(QNIC_E, 1, 2, false);
  EXPECT_EQ(1, store.countNumFreeQubits(QNIC_E, 1));
  EXPECT_THROW(store.setQubitBusy(QNIC_E, 1, 2, false), omnetpp::cRuntimeError);
}

TEST(QNicStore, GetQNicWithInvalidArgs) {
  ComponentProvider provider(new cModule());
  std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 1}, {QNIC_E, 1, 3}, {QNIC_R, 0, 1}, {QNIC_RP, 0, 1}};
  int num_emitter_qnics = 2;
  int num_receiver_qnics = 1;
  int num_passive_receiver_qnics = 1;

  provider.setStrategy(std::make_unique<Strategy>(qnic_specs));
  QNicStore store(provider, num_emitter_qnics, num_receiver_qnics, num_passive_receiver_qnics);
  EXPECT_THROW(store.getQNic(QNIC_E, 100), omnetpp::cRuntimeError);
  EXPECT_THROW(store.getQNic(QNIC_N, 0), omnetpp::cRuntimeError);
}

}  // namespace
