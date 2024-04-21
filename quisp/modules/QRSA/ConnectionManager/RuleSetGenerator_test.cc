#include <utility>

#include <gtest/gtest.h>
#include <omnetpp.h>
#include <nlohmann/json.hpp>

#include "ConnectionManager.h"
#include "RuleSetGenerator.h"
#include "messages/classical_messages.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "test_utils/TestUtilFunctions.h"

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
  RuleSetGenerator(int responder_addr) : OriginalRSG(responder_addr) {}
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
  int responder_addr = 5;
  RuleSetGenerator *rsg;
};

TEST_F(RuleSetGeneratorTest, generateSimpleSwappingRuleSets) {
  std::map<int, std::vector<std::unique_ptr<Rule>>> rules_map{};
  std::vector<int> path{1, 2, 3, 4, 5};
  std::map<int, std::pair<int, int>> swapping_partners_table{{2, {1, 3}}, {4, {3, 5}}, {3, {1, 5}}};
  int shared_rule_tag = 0;
  int num_measure = 50;
  rsg->generateReverseSwapAtHalfRuleSets(0, 4, rules_map, path, shared_rule_tag);
  EXPECT_EQ(rules_map.size(), 5);
  EXPECT_EQ(rules_map.find(1)->second.size(), 2);
  {
    auto &rule = rules_map.find(1)->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 1);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, 3);
  }

  EXPECT_EQ(rules_map.find(2)->second.size(), 1);
  {
    auto &rule = rules_map.find(2)->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 2);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, 1);
    EXPECT_EQ(rule->qnic_interfaces.at(1).partner_addr, 3);
  }

  EXPECT_EQ(rules_map.find(3)->second.size(), 3);
  {
    auto &rule = rules_map.find(3)->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 2);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, 1);
    EXPECT_EQ(rule->qnic_interfaces.at(1).partner_addr, 5);
  }

  EXPECT_EQ(rules_map.find(4)->second.size(), 1);
  {
    auto &rule = rules_map.find(4)->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 2);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, 3);
    EXPECT_EQ(rule->qnic_interfaces.at(1).partner_addr, 5);
  }

  EXPECT_EQ(rules_map.find(5)->second.size(), 2);
  {
    auto &rule = rules_map.find(5)->second.at(0);
    EXPECT_EQ(rule->qnic_interfaces.size(), 1);
    EXPECT_EQ(rule->qnic_interfaces.at(0).partner_addr, 3);
  }
}

TEST_F(RuleSetGeneratorTest, Simple) {
  auto *req = new ConnectionSetupRequest();
  // qnic_index(id)     11       12           13       14           15       16
  // [QNode2](qnic_addr:101) -- (102)[QNode3](103) -- (104)[QNode4](105) -- (106)[QNode5(test target)]
  req->setActual_destAddr(5);
  req->setActual_srcAddr(2);
  req->setDestAddr(5);
  req->setSrcAddr(4);
  req->setStack_of_QNICsArraySize(3);
  req->setStack_of_QNodeIndexesArraySize(3);
  req->setStack_of_QNodeIndexes(0, 2);
  req->setStack_of_QNodeIndexes(1, 3);
  req->setStack_of_QNodeIndexes(2, 4);
  req->setStack_of_QNICs(0, QNicPairInfo{NULL_CONNECTION_SETUP_INFO.qnic, {.type = QNIC_E, .index = 11, .address = 101}});
  req->setStack_of_QNICs(1, QNicPairInfo{{.type = QNIC_E, .index = 12, .address = 102}, {.type = QNIC_E, .index = 13, .address = 103}});
  req->setStack_of_QNICs(2, QNicPairInfo{{.type = QNIC_E, .index = 14, .address = 104}, {.type = QNIC_E, .index = 15, .address = 105}});
  auto rulesets = rsg->generateRuleSets(req, 1234);
  EXPECT_EQ(rulesets.size(), 4);
  {
    auto ruleset = rulesets.find(2)->second;
    auto expected_ruleset = R"({
  "num_rules": 2,
  "owner_address": 2,
  "rules": [
    {
      "action": {
        "options": {
          "interface": [
            {
              "partner_address": 3
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
                "partner_address": 3
              },
              "shared_rule_tag": 1
            },
            "type": "swapping_correction"
          }
        ]
      },
      "interface": [
        {
          "partner_address": 3
        }
      ],
      "name": "swapping correction from 3",
      "receive_tag": 1,
      "send_tag": -1
    },
    {
      "action": {
        "options": {
          "interface": [
            {
              "partner_address": 5
            }
          ],
          "num_measure": 0,
          "owner_address": 2
        },
        "type": "tomography"
      },
      "condition": {
        "clauses": [
          {
            "options": {
              "interface": {
                "partner_address": 5
              },
              "num_resource": 1
            },
            "type": "enough_resource"
          },
          {
            "options": {
              "interface": {
                "partner_address": 5
              },
              "num_measure": 0
            },
            "type": "measure_count"
          }
        ]
      },
      "interface": [
        {
          "partner_address": 5
        }
      ],
      "name": "tomography with address 5",
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
  int partner_addr = 1;
  PurType purification_type = PurType::SINGLE_SELECTION_XZ_PURIFICATION;

  auto purification_rule = rsg->purifyRule(partner_addr, purification_type, 15);
  auto serialized = purification_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
   "name":"purification with 1",
   "send_tag": 15,
   "receive_tag": -1,
   "interface":[
     {"partner_address": 1}
   ],
   "condition":{
      "clauses":[
         {
            "type":"enough_resource",
            "options":{
               "num_resource":3,
               "interface":{
                 "partner_address":1
                }
            }
         }
      ]
   },
   "action":{
      "type":"purification",
      "options":{
         "purification_type":"SINGLE_SELECTION_XZ_PURIFICATION",
         "shared_rule_tag": 15,
         "interface": [
           {"partner_address":1}
          ]
      }
   }
})"_json;
  EXPECT_EQ(serialized, expected);
}

TEST_F(RuleSetGeneratorTest, SwapRule) {
  // rule arguments
  std::pair<int, int> partner_addr{1, 3};
  std::vector<QNIC_type> qnic_type = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {4, 5};
  std::vector<QNIC_type> remote_qnic_type = {QNIC_R, QNIC_E};
  std::vector<int> remote_qnic_id = {3, 6};
  std::vector<int> remote_qnic_address = {11, 12};

  auto swap_rule = rsg->swapRule(partner_addr, 14);

  auto serialized = swap_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
   "name": "swap between 1 and 3",
   "send_tag": 14,
   "receive_tag": -1,
   "interface":[
     {"partner_address": 1},
     {"partner_address": 3}
   ],
   "condition":{
      "clauses":[
         {
            "type":"enough_resource",
            "options":{
               "num_resource":1,
               "interface": {
                 "partner_address":1
               }
            }
         },
         {
            "type":"enough_resource",
            "options":{
               "num_resource":1,
               "interface":{
                 "partner_address":3
               }
            }
         }
      ]
   },
   "action":{
      "type":"swapping",
      "options":{
        "interface":[
          {"partner_address": 1},
          {"partner_address": 3}
        ],
        "remote_interface": [
          {"partner_address": 1},
          {"partner_address": 3}
        ],
        "shared_rule_tag": 14
      }
   }
})"_json;
  EXPECT_EQ(serialized, expected);
}

TEST_F(RuleSetGeneratorTest, tomographyRule) {
  // rule arguments
  int partner_addr = 1;
  int owner_addr = 2;
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
          "partner_address": 1
        }
      ],
      "num_measure": 5000,
      "owner_address": 2
    },
    "type": "tomography"
  },
  "condition": {
    "clauses": [
      {
        "options": {
          "interface": {
            "partner_address": 1
          },
          "num_resource": 1
        },
        "type": "enough_resource"
      },
      {
        "options": {
          "interface": {
            "partner_address": 1
          },
          "num_measure": 5000
        },
        "type": "measure_count"
      }
    ]
  },
  "interface": [
    {
      "partner_address": 1
    }
  ],
  "name": "tomography with address 1",
  "receive_tag": 3,
  "send_tag": 3
})"_json;
  EXPECT_EQ(serialized, expected);
}
}  // namespace
