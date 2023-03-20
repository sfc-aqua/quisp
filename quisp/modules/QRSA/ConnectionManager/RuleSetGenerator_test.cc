#include <utility>

#include <gtest/gtest.h>
#include <omnetpp.h>
#include <nlohmann/json.hpp>

#include "ConnectionManager.h"
#include "RuleSetGenerator.h"
#include "messages/classical_messages.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "test_utils/UtilFunctions.h"

namespace {
using json = nlohmann::json;
using OriginalRSG = quisp::modules::ruleset_gen::RuleSetGenerator;
using quisp::modules::NULL_CONNECTION_SETUP_INFO;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_R;

using namespace quisp::messages;
using namespace quisp_test::utils;
using namespace quisp::rules;

class RuleSetGenerator : public OriginalRSG {
 public:
  RuleSetGenerator(QNodeAddr responder_addr) : OriginalRSG(responder_addr) {}
  using OriginalRSG::collectPath;
  using OriginalRSG::purifyRule;
  using OriginalRSG::swapRule;
  using OriginalRSG::tomographyRule;
};

class RuleSetGeneratorTest : public testing::Test {
 protected:
  void SetUp() {
    prepareSimulation();
    rsg = new RuleSetGenerator{responder_addr};
  }
  void TearDown() { delete rsg; }
  QNodeAddr responder_addr{5};
  RuleSetGenerator *rsg;
};

TEST_F(RuleSetGeneratorTest, generateSimpleSwappingRuleSets) {
  std::map<QNodeAddr, std::vector<std::unique_ptr<Rule>>> rules_map{};
  std::vector<QNodeAddr> path{QNodeAddr{1}, QNodeAddr{2}, QNodeAddr{3}, QNodeAddr{4}, QNodeAddr{5}};
  std::map<QNodeAddr, std::pair<QNodeAddr, QNodeAddr>> swapping_partners_table{
      {QNodeAddr{2}, {QNodeAddr{1}, QNodeAddr{3}}}, {QNodeAddr{4}, {QNodeAddr{3}, QNodeAddr{5}}}, {QNodeAddr{3}, {QNodeAddr{1}, QNodeAddr{5}}}};
  int shared_rule_tag = 0;
  int num_measure = 50;
  rsg->generateReverseSwapAtHalfRuleSets(0, 4, rules_map, path, shared_rule_tag);
  EXPECT_EQ(rules_map.size(), 5);
  EXPECT_EQ(rules_map.find(QNodeAddr{1})->second.size(), 2);
  {
    auto &rule = rules_map.find(QNodeAddr{1})->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 1);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, QNodeAddr{3});
  }

  EXPECT_EQ(rules_map.find(QNodeAddr{2})->second.size(), 1);
  {
    auto &rule = rules_map.find(QNodeAddr{2})->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 2);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, QNodeAddr{1});
    EXPECT_EQ(rule->qnic_interfaces.at(1).partner_addr, QNodeAddr{3});
  }

  EXPECT_EQ(rules_map.find(QNodeAddr{3})->second.size(), 3);
  {
    auto &rule = rules_map.find(QNodeAddr{3})->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 2);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, QNodeAddr{1});
    EXPECT_EQ(rule->qnic_interfaces.at(1).partner_addr, QNodeAddr{5});
  }

  EXPECT_EQ(rules_map.find(QNodeAddr{4})->second.size(), 1);
  {
    auto &rule = rules_map.find(QNodeAddr{4})->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 2);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, QNodeAddr{3});
    EXPECT_EQ(rule->qnic_interfaces.at(1).partner_addr, QNodeAddr{5});
  }

  EXPECT_EQ(rules_map.find(QNodeAddr{5})->second.size(), 2);
  {
    auto &rule = rules_map.find(QNodeAddr{5})->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 1);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, QNodeAddr{3});
  }
}

TEST_F(RuleSetGeneratorTest, Simple) {
  auto *req = new ConnectionSetupRequest();
  // qnic_index(id)     11       12           13       14           15       16
  // [QNode2](qnic_addr:101) -- (102)[QNode3](103) -- (104)[QNode4](105) -- (106)[QNode5(test target)]
  req->setActual_destAddr(QNodeAddr{5});
  req->setActual_srcAddr(QNodeAddr{2});
  req->setDestAddr(QNodeAddr{5});
  req->setSrcAddr(QNodeAddr{4});
  req->setStack_of_QNodeIndexesArraySize(3);
  req->setStack_of_QNodeIndexes(0, QNodeAddr{2});
  req->setStack_of_QNodeIndexes(1, QNodeAddr{3});
  req->setStack_of_QNodeIndexes(2, QNodeAddr{4});
  auto rulesets = rsg->generateRuleSets(req, 1234);
  EXPECT_EQ(rulesets.size(), 4);
  {
    auto ruleset = rulesets.find(QNodeAddr{2})->second;
    auto expected_ruleset = R"({
  "num_rules": 2,
  "owner_address": "0.2",
  "rules": [
    {
      "action": {
        "options": {
          "interface": [
            {
              "partner_address": "0.3"
            }
          ],
          "shared_rule_tag": 1
        },
        "type": "swapping_correction"
      },
      "condition": {
        "clauses": [
          {
            "options": {
              "interface": {
                "partner_address": "0.3"
              },
              "shared_rule_tag": 1
            },
            "type": "swapping_correction"
          }
        ]
      },
      "interface": [
        {
          "partner_address": "0.3"
        }
      ],
      "name": "swapping correction from 0.3",
      "receive_tag": 1,
      "send_tag": -1
    },
    {
      "action": {
        "options": {
          "interface": [
            {
              "partner_address": "0.5"
            }
          ],
          "num_measure": 0,
          "owner_address": "0.2"
        },
        "type": "tomography"
      },
      "condition": {
        "clauses": [
          {
            "options": {
              "interface": {
                "partner_address": "0.5"
              },
              "num_resource": 1
            },
            "type": "enough_resource"
          },
          {
            "options": {
              "interface": {
                "partner_address": "0.5"
              },
              "num_measure": 0
            },
            "type": "measure_count"
          }
        ]
      },
      "interface": [
        {
          "partner_address": "0.5"
        }
      ],
      "name": "tomography with address 0.5",
      "receive_tag": 3,
      "send_tag": 3
    }
  ],
  "ruleset_id": 1234
})"_json;
    EXPECT_EQ(expected_ruleset, ruleset);
  }
}

TEST_F(RuleSetGeneratorTest, PurificationRule) {
  // rule arguments
  QNodeAddr partner_addr{1};
  PurType purification_type = PurType::DOUBLE;

  auto purification_rule = rsg->purifyRule(partner_addr, purification_type, 15);
  auto serialized = purification_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
   "name":"purification with 0.1",
   "send_tag": 15,
   "receive_tag": -1,
   "interface":[
     {"partner_address": "0.1"}
   ],
   "condition":{
      "clauses":[
         {
            "type":"enough_resource",
            "options":{
               "num_resource": 3,
               "interface":{
                 "partner_address": "0.1"
                }
            }
         }
      ]
   },
   "action":{
      "type":"purification",
      "options":{
         "purification_type":"DOUBLE",
         "shared_rule_tag": 15,
         "interface": [
           {"partner_address": "0.1"}
          ]
      }
   }
})"_json;
  EXPECT_EQ(serialized, expected);
}

TEST_F(RuleSetGeneratorTest, SwapRule) {
  // rule arguments
  std::pair<QNodeAddr, QNodeAddr> partner_addr{1, 3};
  std::vector<QNIC_type> qnic_type = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {4, 5};
  std::vector<QNIC_type> remote_qnic_type = {QNIC_R, QNIC_E};
  std::vector<int> remote_qnic_id = {3, 6};
  std::vector<int> remote_qnic_address = {11, 12};

  auto swap_rule = rsg->swapRule(partner_addr, 14);

  auto serialized = swap_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
   "name": "swap between 0.1 and 0.3",
   "send_tag": 14,
   "receive_tag": -1,
   "interface":[
     {"partner_address": "0.1"},
     {"partner_address": "0.3"}
   ],
   "condition":{
      "clauses":[
         {
            "type":"enough_resource",
            "options":{
               "num_resource":1,
               "interface": {
                 "partner_address": "0.1"
               }
            }
         },
         {
            "type":"enough_resource",
            "options":{
               "num_resource":1,
               "interface":{
                 "partner_address": "0.3"
               }
            }
         }
      ]
   },
   "action":{
      "type":"swapping",
      "options":{
        "interface":[
          {"partner_address": "0.1"},
          {"partner_address": "0.3"}
        ],
        "remote_interface": [
          {"partner_address": "0.1"},
          {"partner_address": "0.3"}
        ],
        "shared_rule_tag": 14
      }
   }
})"_json;
  EXPECT_EQ(serialized, expected);
}

TEST_F(RuleSetGeneratorTest, tomographyRule) {
  // rule arguments
  QNodeAddr partner_addr{1};
  QNodeAddr owner_addr{2};
  int num_measurement = 5000;
  int shared_tag = 3;

  auto tomography_rule = rsg->tomographyRule(partner_addr, owner_addr, num_measurement, shared_tag);

  auto serialized = tomography_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
  "action": {
    "options": {
      "interface": [
        {
          "partner_address": "0.1"
        }
      ],
      "num_measure": 5000,
      "owner_address": "0.2"
    },
    "type": "tomography"
  },
  "condition": {
    "clauses": [
      {
        "options": {
          "interface": {
            "partner_address": "0.1"
          },
          "num_resource": 1
        },
        "type": "enough_resource"
      },
      {
        "options": {
          "interface": {
            "partner_address": "0.1"
          },
          "num_measure": 5000
        },
        "type": "measure_count"
      }
    ]
  },
  "interface": [
    {
      "partner_address": "0.1"
    }
  ],
  "name": "tomography with address 0.1",
  "receive_tag": 3,
  "send_tag": 3
})"_json;
  EXPECT_EQ(serialized, expected);
}
}  // namespace
