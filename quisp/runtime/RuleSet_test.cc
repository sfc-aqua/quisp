#include "RuleSet.h"
#include <gtest/gtest.h>
#include "runtime/types.h"

namespace {
using namespace quisp::runtime;

TEST(RuntimeRuleSetTest, OneRule) {
  QubitId q0{0};
  QubitId q1{1};
  QNodeAddr partner1{1};
  QNodeAddr partner2{2};
  RuleSet rs{"test ruleset",
             {
                 Rule{"rule1", -1, -1,
                      Program{"condition",
                              {
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner1, 0}},
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, partner2, 0}},
                              }},
                      Program{"action", {}}},
             }};
  rs.finalize();

  EXPECT_EQ(rs.partner_initial_rule_table.size(), 2);
  auto it = rs.partner_initial_rule_table.find(partner1);
  EXPECT_EQ(it->second, 0);
  it = rs.partner_initial_rule_table.find(partner2);
  EXPECT_EQ(it->second, 0);

  // this rs has 2 partners
  EXPECT_EQ(rs.partners.size(), 2);
  EXPECT_NE(rs.partners.find(partner1), rs.partners.end());
  EXPECT_NE(rs.partners.find(partner2), rs.partners.end());

  // no next rule
  EXPECT_EQ(rs.next_rule_table.size(), 0);
}

TEST(RuntimeRuleSetTest, TwoRule) {
  QubitId q0{0};
  QubitId q1{1};
  QNodeAddr partner1{1};
  QNodeAddr partner2{2};
  RuleSet rs{"test ruleset",
             {
                 Rule{"rule1", -1, -1,
                      Program{"condition",
                              {
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner1, 0}},
                              }},
                      Program{"action", {}}},
                 Rule{"rule2", -1, -1,
                      Program{"condition",
                              {
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner1, 0}},
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, partner2, 0}},
                              }},
                      Program{"action", {}}},
             }};
  rs.finalize();

  {
    EXPECT_EQ(rs.partner_initial_rule_table.size(), 2);
    auto it = rs.partner_initial_rule_table.find(partner1);
    EXPECT_EQ(it->second, 0);
    it = rs.partner_initial_rule_table.find(partner2);
    EXPECT_EQ(it->second, 1);
  }

  // this rs has 2 partners
  EXPECT_EQ(rs.partners.size(), 2);
  EXPECT_NE(rs.partners.find(partner1), rs.partners.end());
  EXPECT_NE(rs.partners.find(partner2), rs.partners.end());

  {
    EXPECT_EQ(rs.next_rule_table.size(), 1);
    auto it = rs.next_rule_table.find({partner1, 0});
    EXPECT_EQ(it->second, 1);
    it = rs.next_rule_table.find({partner2, 0});
    EXPECT_EQ(it, rs.next_rule_table.end());
  }
}

TEST(RuntimeRuleSetTest, ThreeRule) {
  QubitId q0{0};
  QubitId q1{1};
  QubitId q2{2};
  QNodeAddr partner1{1};
  QNodeAddr partner2{2};
  QNodeAddr partner3{3};
  RuleSet rs{"test ruleset",
             {
                 Rule{"rule1", -1, -1,
                      Program{"condition",
                              {
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner1, 0}},
                              }},
                      Program{"action", {}}},
                 Rule{"rule2", -1, -1,
                      Program{"",
                              {
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, partner2, 0}},
                              }},
                      Program{"", {}}},
                 Rule{"rule3", -1, -1,
                      Program{"condition",
                              {
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner1, 0}},
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, partner2, 0}},
                                  INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q2, partner3, 0}},
                              }},
                      Program{"action", {}}},
             }};
  rs.finalize();

  {
    EXPECT_EQ(rs.partner_initial_rule_table.size(), 3);
    auto it = rs.partner_initial_rule_table.find(partner1);
    EXPECT_EQ(it->second, 0);
    it = rs.partner_initial_rule_table.find(partner2);
    EXPECT_EQ(it->second, 1);
    it = rs.partner_initial_rule_table.find(partner3);
    EXPECT_EQ(it->second, 2);
  }

  // this rs has 3 partners
  EXPECT_EQ(rs.partners.size(), 3);
  EXPECT_NE(rs.partners.find(partner1), rs.partners.end());
  EXPECT_NE(rs.partners.find(partner2), rs.partners.end());
  EXPECT_NE(rs.partners.find(partner3), rs.partners.end());

  {
    EXPECT_EQ(rs.next_rule_table.size(), 2);
    auto it = rs.next_rule_table.find({partner1, 0});
    EXPECT_EQ(it->second, 2);
    it = rs.next_rule_table.find({partner2, 0});
    EXPECT_EQ(it, rs.next_rule_table.end());
    it = rs.next_rule_table.find({partner2, 1});
    EXPECT_EQ(it->second, 2);
  }
}
}  // namespace
