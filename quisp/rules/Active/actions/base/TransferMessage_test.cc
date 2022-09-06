#include "TransferMessage.cc"
#include <gtest/gtest.h>
#include <messages/classical_messages.h>

#include "test_utils/TestUtils.h"
namespace {
using namespace omnetpp;
using namespace quisp::rules::active::actions::base;
using namespace quisp::messages;

class TransferMessageTest : public ::testing::Test {
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

TEST_F(TransferMessageTest, generatePurificationResultTest) {
  auto *pk = generatePurificationResult(partner, ruleset_id, rule_id, shared_tag, action_index, kind, is_output_plus);
  ASSERT_EQ(pk->getDestAddr(), partner);
  ASSERT_EQ(pk->getRuleset_id(), ruleset_id);
  ASSERT_EQ(pk->getRule_id(), rule_id);
  ASSERT_EQ(pk->getShared_tag(), shared_tag);
  ASSERT_EQ(pk->getAction_index(), action_index);
  ASSERT_EQ(pk->getKind(), kind);
  ASSERT_EQ(pk->getOutput_is_plus(), is_output_plus);
}

TEST_F(TransferMessageTest, generateDoublePurificationResultTest) {
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

TEST_F(TransferMessageTest, generateDoubleSelectionDoublePurificationResultTest) {
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

TEST_F(TransferMessageTest, generateDoubleSelectionDoublePurificationSecondResultTest) {
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
}  // namespace