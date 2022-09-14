#include "TransferMessage.cc"
#include <gtest/gtest.h>
#include <messages/classical_messages.h>

#include "test_utils/TestUtils.h"
namespace {
using namespace omnetpp;
using namespace quisp::rules::active::actions::base;
using namespace quisp::messages;

class TransferPurificationMessageTest : public ::testing::Test {
 protected:
  void SetUp() override {
    partner = 0;
    ruleset_id = 1234;
    rule_id = 1;
    shared_tag = 2;
    action_index = 3;
    kind = 4;
    is_output_plus = true;
    is_x_output_plus = false;
    is_z_output_plus = true;
    is_ds_x_output_plus = true;
    is_ds_z_output_plus = false;
    is_ds_output_plus = true;
  }
  int partner;
  unsigned long ruleset_id;
  int rule_id;
  int shared_tag;
  int action_index;
  int kind;
  bool is_output_plus;
  // for double purification
  bool is_x_output_plus;
  bool is_z_output_plus;
  // for double selection double purification
  bool is_ds_x_output_plus;
  bool is_ds_z_output_plus;
  // for double selection double purification second
  bool is_ds_output_plus;
};

TEST_F(TransferPurificationMessageTest, generatePurificationResultTest) {
  auto *pk = generatePurificationResult(partner, ruleset_id, rule_id, shared_tag, action_index, kind, is_output_plus);
  ASSERT_EQ(pk->getDestAddr(), partner);
  ASSERT_EQ(pk->getRuleset_id(), ruleset_id);
  ASSERT_EQ(pk->getRule_id(), rule_id);
  ASSERT_EQ(pk->getShared_tag(), shared_tag);
  ASSERT_EQ(pk->getAction_index(), action_index);
  ASSERT_EQ(pk->getKind(), kind);
  ASSERT_EQ(pk->getOutput_is_plus(), is_output_plus);
}

TEST_F(TransferPurificationMessageTest, generateDoublePurificationResultTest) {
  auto *pk = generateDoublePurificationResult(partner, ruleset_id, rule_id, shared_tag, action_index, kind, is_x_output_plus, is_z_output_plus);
  ASSERT_EQ(pk->getDestAddr(), partner);
  ASSERT_EQ(pk->getRuleset_id(), ruleset_id);
  ASSERT_EQ(pk->getRule_id(), rule_id);
  ASSERT_EQ(pk->getShared_tag(), shared_tag);
  ASSERT_EQ(pk->getAction_index(), action_index);
  ASSERT_EQ(pk->getKind(), kind);
  ASSERT_EQ(pk->getXOutput_is_plus(), is_x_output_plus);
  ASSERT_EQ(pk->getZOutput_is_plus(), is_z_output_plus);
}

TEST_F(TransferPurificationMessageTest, generateDoubleSelectionDoublePurificationResultTest) {
  auto *pk = generateDoubleSelectionDoublePurificationResult(partner, ruleset_id, rule_id, shared_tag, action_index, kind, is_x_output_plus, is_z_output_plus, is_ds_x_output_plus,
                                                             is_ds_z_output_plus);
  ASSERT_EQ(pk->getDestAddr(), partner);
  ASSERT_EQ(pk->getRuleset_id(), ruleset_id);
  ASSERT_EQ(pk->getRule_id(), rule_id);
  ASSERT_EQ(pk->getShared_tag(), shared_tag);
  ASSERT_EQ(pk->getAction_index(), action_index);
  ASSERT_EQ(pk->getKind(), kind);
  ASSERT_EQ(pk->getXOutput_is_plus(), is_x_output_plus);
  ASSERT_EQ(pk->getZOutput_is_plus(), is_z_output_plus);
  ASSERT_EQ(pk->getDS_XOutput_is_plus(), is_ds_x_output_plus);
  ASSERT_EQ(pk->getDS_ZOutput_is_plus(), is_ds_z_output_plus);
}

TEST_F(TransferPurificationMessageTest, generateDoubleSelectionDoublePurificationSecondResultTest) {
  auto *pk =
      generateDoubleSelectionDoublePurificationSecondResult(partner, ruleset_id, rule_id, shared_tag, action_index, kind, is_x_output_plus, is_z_output_plus, is_ds_output_plus);
  ASSERT_EQ(pk->getDestAddr(), partner);
  ASSERT_EQ(pk->getRuleset_id(), ruleset_id);
  ASSERT_EQ(pk->getRule_id(), rule_id);
  ASSERT_EQ(pk->getShared_tag(), shared_tag);
  ASSERT_EQ(pk->getAction_index(), action_index);
  ASSERT_EQ(pk->getKind(), kind);
  ASSERT_EQ(pk->getXOutput_is_plus(), is_x_output_plus);
  ASSERT_EQ(pk->getZOutput_is_plus(), is_z_output_plus);
  ASSERT_EQ(pk->getDS_Output_is_plus(), is_ds_output_plus);
}

class TransferMeasureResultMessageTest : public ::testing::Test {
 protected:
  void SetUp() override {
    source = 0;
    destination = 1;
    count = 1000;
    kind = 4;
    is_output_plus = false;
    basis = 'Y';
    god_clean = 'X';
    max_count = 1000;
  }
  int source;
  int destination;
  int count;
  int kind;
  bool is_output_plus;
  char basis;
  char god_clean;
  int max_count;
  simtime_t start;
};

TEST_F(TransferMeasureResultMessageTest, LinkTomographyResultGenerationTest) {
  auto *pk = generateLinkTomographyResult(source, destination, count, kind, is_output_plus, basis, god_clean, max_count, start);
  ASSERT_EQ(pk->getSrcAddr(), source);
  ASSERT_EQ(pk->getDestAddr(), destination);
  ASSERT_EQ(pk->getPartner_address(), source);
  ASSERT_EQ(pk->getCount_id(), count);
  ASSERT_EQ(pk->getKind(), kind);
  ASSERT_EQ(pk->getOutput_is_plus(), is_output_plus);
  ASSERT_EQ(pk->getMax_count(), max_count);
}

class TransferSwappingResultMessageTest : public ::testing::Test {
 protected:
  void SetUp() override {
    partners = {1, 3};
    qnic_ids = {10, 12};
    qnic_types = {QNIC_E, QNIC_R};
    qnic_addresses = {101, 103};
    qubit_indices = {0, 3};
    ruleset_id = 1234;
    rule_id = 0;
    shared_tag = 1;
    action_index = 2;
    kind = 3;
    operation_types = {1, 2};
  }
  std::vector<int> partners;
  std::vector<int> qnic_ids;
  std::vector<QNIC_type> qnic_types;
  std::vector<int> qnic_addresses;
  std::vector<int> qubit_indices;
  unsigned long ruleset_id;
  int rule_id;
  int shared_tag;
  int action_index;
  int kind;
  std::vector<int> operation_types = {1, 2};
};

TEST_F(TransferSwappingResultMessageTest, SwappingResultGenerationTest) {
  auto *pk = generateSwappingResult(partners, qnic_ids, qnic_types, qnic_addresses, qubit_indices, ruleset_id, rule_id, shared_tag, action_index, kind, operation_types);
  ASSERT_EQ(pk->getKind(), kind);
  ASSERT_EQ(pk->getRuleSet_id(), ruleset_id);
  ASSERT_EQ(pk->getRule_id(), rule_id);
  ASSERT_EQ(pk->getShared_tag(), shared_tag);
  ASSERT_EQ(pk->getAction_index(), action_index);

  ASSERT_EQ(pk->getLeft_Dest(), 1);
  ASSERT_EQ(pk->getOperation_type_left(), 1);
  ASSERT_EQ(pk->getNew_partner_left(), 3);
  ASSERT_EQ(pk->getNew_partner_qnic_index_left(), 12);
  ASSERT_EQ(pk->getNew_partner_qnic_type_left(), QNIC_R);
  ASSERT_EQ(pk->getNew_partner_qnic_address_left(), 103);
  ASSERT_EQ(pk->getMeasured_qubit_index_left(), 3);

  ASSERT_EQ(pk->getRight_Dest(), 3);
  ASSERT_EQ(pk->getOperation_type_right(), 2);
  ASSERT_EQ(pk->getNew_partner_right(), 1);
  ASSERT_EQ(pk->getNew_partner_qnic_index_right(), 10);
  ASSERT_EQ(pk->getNew_partner_qnic_type_right(), QNIC_E);
  ASSERT_EQ(pk->getNew_partner_qnic_address_right(), 101);
  ASSERT_EQ(pk->getMeasured_qubit_index_right(), 0);
}
}  // namespace