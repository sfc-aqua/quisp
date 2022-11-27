#include <gtest/gtest.h>
#include <modules/Logger/DisabledLogger.h>
#include <omnetpp/cmodule.h>
#include <test_utils/TestUtils.h>
#include <utils/ComponentProvider.h>
#include "QNicRecord.h"

namespace {
using namespace quisp_test;
using quisp::utils::ComponentProvider;
using namespace quisp::modules::qnic_record;
using namespace quisp::modules::Logger;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;

TEST(QNicRecord, InitWithoutQubits) {
  ComponentProvider provider(new cModule());
  std::vector<QNicSpec> qnic_specs = {};

  provider.setStrategy(std::make_unique<TestComponentProviderStrategy>(qnic_specs));
  int qnic_index = 3;
  auto qnic_type = QNIC_R;
  QNicRecord record(provider, qnic_index, qnic_type, new DisabledLogger{});
  EXPECT_EQ(qnic_index, record.index);
  EXPECT_EQ(qnic_type, record.type);
  EXPECT_EQ(0, record.countNumFreeQubits());
}

TEST(QNicRecord, InitWithQubits) {
  ComponentProvider provider(new cModule());
  int qnic_index = 3;
  auto qnic_type = QNIC_E;
  std::vector<QNicSpec> qnic_specs = {{qnic_type, qnic_index, 5}};
  provider.setStrategy(std::make_unique<TestComponentProviderStrategy>(qnic_specs));

  QNicRecord record(provider, qnic_index, qnic_type, new DisabledLogger{});
  EXPECT_EQ(qnic_index, record.index);
  EXPECT_EQ(qnic_type, record.type);
  EXPECT_EQ(5, record.countNumFreeQubits());
}

TEST(QNicRecord, TakeFreeQubit) {
  ComponentProvider provider(new cModule());
  int qnic_index = 3;
  auto qnic_type = QNIC_E;
  std::vector<QNicSpec> qnic_specs = {{qnic_type, qnic_index, 3}};
  provider.setStrategy(std::make_unique<TestComponentProviderStrategy>(qnic_specs));

  QNicRecord record(provider, qnic_index, qnic_type, new DisabledLogger{});
  EXPECT_EQ(3, record.countNumFreeQubits());
  EXPECT_NE(-1, record.takeFreeQubitIndex());
  EXPECT_EQ(2, record.countNumFreeQubits());
  EXPECT_NE(-1, record.takeFreeQubitIndex());
  EXPECT_EQ(1, record.countNumFreeQubits());
  EXPECT_NE(-1, record.takeFreeQubitIndex());
  EXPECT_EQ(0, record.countNumFreeQubits());
  EXPECT_EQ(-1, record.takeFreeQubitIndex());
}

TEST(QNicRecord, SetQubitBusy) {
  ComponentProvider provider(new cModule());
  int qnic_index = 3;
  auto qnic_type = QNIC_E;
  std::vector<QNicSpec> qnic_specs = {{qnic_type, qnic_index, 3}};
  provider.setStrategy(std::make_unique<TestComponentProviderStrategy>(qnic_specs));

  QNicRecord record(provider, qnic_index, qnic_type, new DisabledLogger{});
  EXPECT_EQ(3, record.countNumFreeQubits());
  record.setQubitBusy(0, true);
  EXPECT_EQ(2, record.countNumFreeQubits());
  record.setQubitBusy(1, true);
  EXPECT_EQ(1, record.countNumFreeQubits());
  record.setQubitBusy(2, true);
  EXPECT_EQ(0, record.countNumFreeQubits());
  record.setQubitBusy(2, false);
  EXPECT_EQ(1, record.countNumFreeQubits());
}

TEST(QNicRecord, SetQubitBusyWithInvalidIndex) {
  ComponentProvider provider(new cModule());
  int qnic_index = 3;
  auto qnic_type = QNIC_E;
  std::vector<QNicSpec> qnic_specs = {{qnic_type, qnic_index, 3}};
  provider.setStrategy(std::make_unique<TestComponentProviderStrategy>(qnic_specs));

  QNicRecord record(provider, qnic_index, qnic_type, new DisabledLogger{});
  EXPECT_THROW(record.setQubitBusy(100, true), omnetpp::cRuntimeError);
}

}  // namespace
