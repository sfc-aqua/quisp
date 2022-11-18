#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include <utility>

#include <modules/Logger/DisabledLogger.h>
#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "RuleEngine.h"

#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/QRSA.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h"
#include "rules/Active/ActiveAction.h"
#include "rules/Active/ActiveRuleSet.h"

ACCESS_PRIVATE_FIELD(quisp::modules::EnoughResourceClause, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::EnoughResourceClause, int, num_resource_required);

ACCESS_PRIVATE_FIELD(quisp::modules::ActiveAction, unsigned long, ruleset_id);
ACCESS_PRIVATE_FIELD(quisp::modules::ActiveAction, int, rule_id);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, QNIC_type, qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, resource);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, trash_resource);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, purification_count);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, bool, X);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, bool, Z);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, num_purify);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, action_index);

ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_partner);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, self_left_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_qnic_address);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, left_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, self_left_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_resource);

ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_partner);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, self_right_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_qnic_address);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, right_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, self_right_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_resource);

ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, QNIC_type, qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, resource);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, src);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, dst);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, current_count);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, max_count);

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::rules;
using namespace quisp::rules::active::actions;
using quisp::rules::active::actions::ActiveAction;
using namespace quisp::modules;
using quisp::modules::qrsa::IQubitRecord;
using quisp::modules::qubit_record::QubitRecord;
using namespace quisp_test;
using namespace testing;
using quisp::modules::Logger::DisabledLogger;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr), routingDaemon(nullptr), hardwareMonitor(nullptr) {}
  Strategy(IStationaryQubit* _qubit, MockRoutingDaemon* routing_daemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller,
           std::vector<QNicSpec> qnic_specs)
      : TestComponentProviderStrategy(qnic_specs), mockQubit(_qubit), routingDaemon(routing_daemon), hardwareMonitor(hardware_monitor), realtimeController(realtime_controller) {}
  ~Strategy() {
    delete mockQubit;
    delete routingDaemon;
    delete hardwareMonitor;
    delete realtimeController;
  }
  IStationaryQubit* mockQubit = nullptr;
  MockRoutingDaemon* routingDaemon = nullptr;
  MockHardwareMonitor* hardwareMonitor = nullptr;
  MockRealTimeController* realtimeController = nullptr;
  IStationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockQubit(QNIC_E, 1);
    return mockQubit;
  };
  IRoutingDaemon* getRoutingDaemon() override { return routingDaemon; };
  IHardwareMonitor* getHardwareMonitor() override { return hardwareMonitor; };
  IRealTimeController* getRealTimeController() override { return realtimeController; };
  ILogger* getLogger() override { return new DisabledLogger{}; }
};

class RuleEngineTestTarget : public quisp::modules::RuleEngine {
 public:
  using quisp::modules::RuleEngine::constructActiveRuleSet;
  using quisp::modules::RuleEngine::constructRule;
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::qnic_store;
  using quisp::modules::RuleEngine::storeCheck_Purification_Agreement;
  using quisp::modules::RuleEngine::Unlock_resource_and_discard;
  using quisp::modules::RuleEngine::Unlock_resource_and_upgrade_stage;
  using quisp::modules::RuleEngine::updateResources_EntanglementSwapping;

  RuleEngineTestTarget(IStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller,
                       std::vector<QNicSpec> qnic_specs = {})
      : quisp::modules::RuleEngine() {
    setParInt(this, "address", 2);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 1);
    setParInt(this, "number_of_qnics", 1);
    setParInt(this, "total_number_of_qnics", 2);
    setName("rule_engine_test_target");
    provider.setStrategy(std::make_unique<Strategy>(mockQubit, routingdaemon, hardware_monitor, realtime_controller, qnic_specs));
    setComponentType(new TestModuleType("rule_engine_test"));
    qnic_store = std::make_unique<StrictMock<MockQNicStore>>();
  }
  // setter function for allResorces[qnic_type][qnic_index]
  void setAllResources(int partner_addr, IQubitRecord* qubit) { this->bell_pair_store.insertEntangledQubit(partner_addr, qubit); };
  void setTracker(int qnic_address, int shot_number, QubitAddr_cons qubit_address) { this->tracker[qnic_address].insert(std::make_pair(shot_number, qubit_address)); };

 private:
  FRIEND_TEST(RuleEngineTest, ESResourceUpdate);
  FRIEND_TEST(RuleEngineTest, trackerUpdate);
  friend class MockRoutingDaemon;
  friend class MockHardwareMonitor;
};

// specifier for qnics in order to create qnic_record and qubit_record.
static const std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 2}, {QNIC_R, 0, 2}};

TEST(RuleEngineTest, activeRuleSetConstructionFromJson) {
  // translate static ruleset into active ruleset
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 0, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto serialized_ruleset = R"({
	"num_rules": 4,
	"owner_address": 2,
	"rules": [{
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}],
				"purification_type": "SINGLE_X"
			},
			"type": "purification"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 3,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 3,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "purification",
		"next_rule_id": 1,
		"rule_id": 0
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}]
			},
			"type": "wait"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 3,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					}
				},
				"type": "wait"
			}]
		},
		"interface": [{
			"partner_address": 3,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "wait",
		"next_rule_id": 2,
		"rule_id": 1
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}],
				"purification_type": "SINGLE_X"
			},
			"type": "purification"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 5,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 5,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "purification",
		"next_rule_id": 3,
		"rule_id": 2
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}],
				"num_measure": 0,
				"owner_address": 2
			},
			"type": "tomography"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 5,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 1,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}, {
				"options": {
					"interface": {
						"partner_address": 5,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_measure": 100
				},
				"type": "measure_count"
			}]
		},
		"interface": [{
			"partner_address": 5,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "tomography",
		"next_rule_id": -1,
		"rule_id": 3
	}],
	"ruleset_id": 1234
})"_json;

  RuleSet deserialized_ruleset;
  deserialized_ruleset.deserialize_json(serialized_ruleset);

  auto active_ruleset = rule_engine->constructActiveRuleSet(std::move(deserialized_ruleset));
  // check property of resulted
  ASSERT_NE(active_ruleset, nullptr);
  EXPECT_EQ(active_ruleset->size(), 4);
  auto ruleset_id = active_ruleset->ruleset_id;
  auto expected_ruleset_id = 1234;

  // checking the 1st rule of QNode2(initiator): if EnoughResource -> Purify
  {
    auto* rule = active_ruleset->rules.at(0).get();
    EXPECT_EQ(rule->ruleset_id, ruleset_id);
    ASSERT_EQ(rule->action_partners.size(), 1);
    // action partner must be the next neighbor qnode3 (this qnode is qnode2[initiator])
    // first action is the purification with the neighbor qnode
    EXPECT_EQ(rule->action_partners.at(0), 3);

    auto* action = dynamic_cast<PurifyAction*>(rule->action.get());
    EXPECT_NE(action, nullptr);
    EXPECT_EQ(access_private::rule_id(*action), rule->rule_id);
    EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
    EXPECT_EQ(access_private::partner(*action), 3);
    EXPECT_EQ(access_private::X(*action), true);
    EXPECT_EQ(access_private::Z(*action), false);
    EXPECT_EQ(access_private::qnic_id(*action), 11);
    EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
    EXPECT_EQ(access_private::resource(*action), 0);
    EXPECT_EQ(access_private::trash_resource(*action), 1);
    EXPECT_EQ(access_private::action_index(*action), 0);
    EXPECT_EQ(access_private::purification_count(*action), 1);
    EXPECT_EQ(access_private::num_purify(*action), 1);

    EXPECT_EQ(rule->condition->clauses.size(), 1);
    auto* clause = dynamic_cast<ActiveClause*>(rule->condition.get()->clauses.at(0));
    ASSERT_NE(clause, nullptr);

    auto* enough_resource_clause = dynamic_cast<EnoughResourceClause*>(clause);
    ASSERT_NE(enough_resource_clause, nullptr);
    EXPECT_EQ(access_private::partner(*enough_resource_clause), 3);
    EXPECT_EQ(access_private::num_resource_required(*enough_resource_clause), 2);
  }
  // checking the 2nd rule of QNode2(initiator): Wait
  {
    auto* rule = active_ruleset->rules.at(1).get();
    EXPECT_EQ(rule->name, "wait with 3 ");
    EXPECT_EQ(rule->ruleset_id, ruleset_id);
    ASSERT_EQ(rule->action_partners.size(), 1);
    EXPECT_EQ(rule->action_partners.at(0), 3);  // just wait QNode 3

    ASSERT_EQ(rule->condition->clauses.size(), 1);
    auto* clause = dynamic_cast<WaitClause*>(rule->condition->clauses.at(0));
    EXPECT_NE(clause, nullptr);

    auto* action = dynamic_cast<WaitAction*>(rule->action.get());
    EXPECT_NE(rule->action.get(), nullptr);
  }
  // checking the 3rd rule of QNode2(initiator): if EnoughResource -> Purify
  {
    auto* rule = active_ruleset->rules.at(2).get();
    EXPECT_EQ(rule->name, "purification with 5 ");
    EXPECT_EQ(rule->ruleset_id, ruleset_id);
    ASSERT_EQ(rule->action_partners.size(), 1);
    // action partner must be the qnode5(responder)
    // third action is the purification with the opposite end qnode
    EXPECT_EQ(rule->action_partners.at(0), 5);

    auto* action = dynamic_cast<PurifyAction*>(rule->action.get());
    EXPECT_NE(action, nullptr);
    EXPECT_EQ(access_private::rule_id(*action), rule->rule_id);
    EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
    EXPECT_EQ(access_private::partner(*action), 5);
    EXPECT_EQ(access_private::X(*action), true);
    EXPECT_EQ(access_private::Z(*action), false);
    EXPECT_EQ(access_private::qnic_id(*action), 11);
    EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
    EXPECT_EQ(access_private::resource(*action), 0);
    EXPECT_EQ(access_private::trash_resource(*action), 1);
    EXPECT_EQ(access_private::action_index(*action), 0);
    EXPECT_EQ(access_private::purification_count(*action), 1);
    EXPECT_EQ(access_private::num_purify(*action), 1);

    ASSERT_EQ(rule->condition->clauses.size(), 1);
    auto* clause = dynamic_cast<EnoughResourceClause*>(rule->condition.get()->clauses.at(0));
    ASSERT_NE(clause, nullptr);
    EXPECT_EQ(access_private::partner(*clause), 5);
    EXPECT_EQ(access_private::num_resource_required(*clause), 2);
  }

  // checking the 4th rule of QNode2(initiator): EnoughResource && MeasureCount -> Tomography
  {
    auto* rule = active_ruleset->rules.at(3).get();
    EXPECT_EQ(rule->name, "tomography with 5 ");
    EXPECT_EQ(rule->ruleset_id, ruleset_id);
    ASSERT_EQ(rule->action_partners.size(), 1);
    // action partner must be the qnode5(responder)
    // last action is the tomography with the opposite end qnode
    EXPECT_EQ(rule->action_partners.at(0), 5);
    auto* action = dynamic_cast<RandomMeasureAction*>(rule->action.get());
    EXPECT_NE(action, nullptr);
    EXPECT_EQ(access_private::partner(*action), 5);
    EXPECT_EQ(access_private::qnic_id(*action), 11);
    EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
    EXPECT_EQ(access_private::resource(*action), 0);
    EXPECT_EQ(access_private::src(*action), 2);
    EXPECT_EQ(access_private::dst(*action), 5);
    EXPECT_EQ(access_private::current_count(*action), 0);
    EXPECT_EQ(access_private::max_count(*action), 0);

    ASSERT_EQ(rule->condition->clauses.size(), 2);
    auto* measure_count_clause = dynamic_cast<MeasureCountClause*>(rule->condition.get()->clauses.at(1));
    ASSERT_NE(measure_count_clause, nullptr);
    EXPECT_EQ(measure_count_clause->max_count, 100);
    EXPECT_EQ(measure_count_clause->current_count, 0);
    auto* enough_resource_clause = dynamic_cast<EnoughResourceClause*>(rule->condition.get()->clauses.at(0));
    ASSERT_NE(enough_resource_clause, nullptr);
    EXPECT_EQ(access_private::partner(*enough_resource_clause), 5);
    EXPECT_EQ(access_private::num_resource_required(*enough_resource_clause), 1);
  }

  EXPECT_EQ(active_ruleset->rules.at(0)->next_rule_id, active_ruleset->rules.at(1)->rule_id);
  EXPECT_EQ(active_ruleset->rules.at(1)->next_rule_id, active_ruleset->rules.at(2)->rule_id);
  EXPECT_EQ(active_ruleset->rules.at(2)->next_rule_id, active_ruleset->rules.at(3)->rule_id);
  EXPECT_EQ(active_ruleset->rules.at(3)->next_rule_id, -1);
  delete mockHardwareMonitor;
  delete routingdaemon;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, ESResourceUpdate) {
  // 1 (wait) -- 2(ES) -- 3(wait)
  // from wait to next rule
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 0, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, realtime_controller, qnic_specs};

  auto info = std::make_unique<ConnectionSetupInfo>();
  info->qnic.type = QNIC_E;
  info->qnic.index = 0;

  unsigned long mock_ruleset_id = 10;
  int mock_rule_id = 0;
  int mock_next_rule_id = 1;
  int shared_tag = 3;

  swapping_result swapr;
  swapr.id.ruleset_id = mock_ruleset_id;
  swapr.id.rule_id = mock_rule_id;
  swapr.id.shared_tag = shared_tag;
  swapr.new_partner = 3;
  swapr.swapper_addr = 2;
  swapr.operation_type = 0;
  swapr.new_partner_qnic_address = 1;
  swapr.new_partner_qnic_index = 1;
  swapr.new_partner_qnic_type = QNIC_E;
  swapr.measured_qubit_index = 1;

  EXPECT_CALL(*routingdaemon, return_QNIC_address_to_destAddr(swapr.new_partner)).WillOnce(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, findConnectionInfoByQnicAddr(1)).Times(1).WillOnce(Return(ByMove(std::move(info))));
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 1)).Times(1).WillOnce(Return(qubit_record.get()));
  EXPECT_CALL(*realtime_controller, assertNoEntanglement(qubit_record.get())).Times(1);
  // 0. set ruleset
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  auto* rs = new ActiveRuleSet(mock_ruleset_id, mock_rule_id);  // ruleset_id, ruleset_owner, partners
  auto wait_rule = std::make_unique<ActiveRule>(mock_ruleset_id, mock_rule_id, shared_tag);
  wait_rule->next_rule_id = mock_next_rule_id;
  wait_rule->action_partners.push_back(swapr.swapper_addr);
  rs->addRule(std::move(wait_rule));
  auto next_rule = std::make_unique<ActiveRule>(mock_ruleset_id, mock_next_rule_id, 0);
  rs->addRule(std::move(next_rule));

  rule_engine->rp.insert(rs);
  rule_engine->rp[0]->getRule(0)->addResource(1, mockQubit1);
  ASSERT_EQ(rule_engine->rp[0]->getRule(0)->resources.size(), 1);
  ASSERT_EQ(rule_engine->rp[0]->getRule(1)->resources.size(), 0);
  rule_engine->updateResources_EntanglementSwapping(swapr);
  // 1. remove from previous rule
  ASSERT_EQ(rule_engine->rp[0]->getRule(0)->resources.size(), 0);
  // // 2. add to the next rule
  ASSERT_EQ(rule_engine->rp[0]->getRule(1)->resources.size(), 1);
  delete mockHardwareMonitor;
  delete routingdaemon;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, resourceAllocation) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit_record0 = new QubitRecord(QNIC_E, 3, 0, logger.get());
  auto* qubit_record1 = new QubitRecord(QNIC_E, 3, 1, logger.get());
  auto* qubit_record2 = new QubitRecord(QNIC_E, 3, 2, logger.get());
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, nullptr, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  rule_engine->setAllResources(0, qubit_record0);
  rule_engine->setAllResources(1, qubit_record1);
  rule_engine->setAllResources(2, qubit_record2);
  auto* rs = new ActiveRuleSet(0, 0);
  auto rule = std::make_unique<ActiveRule>(0, 0, 0);
  // owner address,
  auto* action = new RandomMeasureAction(0, 0, 0, 1, QNIC_E, 3, 1, 10);

  rule->setAction(action);
  rule->action_partners = {1};
  rs->addRule(std::move(rule));
  rule_engine->rp.insert(rs);

  rule_engine->ResourceAllocation(QNIC_E, 3);
  EXPECT_TRUE(qubit_record1->isAllocated());

  // resource allocation assigns a corresponding qubit to action's resource
  auto& _rs = rule_engine->rp[0];
  EXPECT_NE(_rs, nullptr);
  EXPECT_EQ(_rs->size(), 1);
  auto& _rule = _rs->getRule(0);
  EXPECT_FALSE(_rule == nullptr);
  EXPECT_EQ(_rule->resources.size(), 1);
  delete mockHardwareMonitor;
  delete routingdaemon;
}

TEST(RuleEngineTest, trackerUpdate) {
  // 1. initialize tracker
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController, qnic_specs};
  rule_engine->initialize();
  for (int i = 0; i < rule_engine->number_of_qnics_all; i++) {
    EXPECT_EQ(rule_engine->tracker[i].size(), 0);  // tracker is properly initialized?
  }
  // set tracker accessible false at qnic 0
  rule_engine->tracker_accessible.at(0) = false;
  // 2. start emission (check records) add records
  // TODO: actual BSM notification should be introduced here
  QubitAddr_cons addr(1, 0, 0);  // parent_address, qnic_index, qubit_index
  rule_engine->setTracker(0, 0, addr);
  EXPECT_EQ(rule_engine->tracker[0].size(), 1);
  // check if the tracker is blocked properly
  EXPECT_FALSE(rule_engine->tracker_accessible[0]);
  EXPECT_TRUE(rule_engine->tracker_accessible[1]);
  // 3. clear tracker and check flag is reset
  rule_engine->clearTrackerTable(0, 0);  // source address, qnic address
  EXPECT_TRUE(rule_engine->tracker_accessible[0]);
  EXPECT_TRUE(rule_engine->tracker_accessible[1]);
  // clered table
  EXPECT_EQ(rule_engine->tracker[0].size(), 0);
  EXPECT_EQ(rule_engine->tracker[1].size(), 0);
  delete routingdaemon;
  delete mockHardwareMonitor;
  delete mockRealTimeController;
}

TEST(RuleEngineTest, storeCheckPurificationAgreement_no_process) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  purification_result result{
      .outcome = true,
  };
  rule_engine->storeCheck_Purification_Agreement(result);
  delete hardware_monitor;
}

TEST(RuleEngineTest, storeCheckPurificationAgreement_running_process) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;
  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  int target_rule_id = 10;
  auto rule1 = new ActiveRule(ruleset_id, target_rule_id, 0);
  auto rule2 = new ActiveRule(ruleset_id, 11, 1);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_id;
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule1));
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule2));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);

  purification_result result{
      .id = {.ruleset_id = ruleset_id, .rule_id = rule1->rule_id, .index = action_index},
      .outcome = true,
  };

  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);

  EXPECT_EQ(rule_engine->Purification_table.size(), 0);
  // got the result from the node itself
  rule_engine->storeCheck_Purification_Agreement(result);

  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);
  EXPECT_EQ(rule_engine->Purification_table.size(), 1);

  // got the same result from the opposite node
  // and then the resource will be upgrade.
  // but obviously we should separate this into 2 methods.
  rule_engine->storeCheck_Purification_Agreement(result);
  EXPECT_EQ(rule1->resources.size(), 0);
  EXPECT_EQ(rule2->resources.size(), 1);
  delete qubit;
  delete hardware_monitor;
}

TEST(RuleEngineTest, freeConsumedResource) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  int qnic_index = 7;
  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit = new MockQubit(QNIC_E, qnic_index);
  auto* qubit_record = new QubitRecord(QNIC_E, qnic_index, 1, logger.get());
  qubit_record->setBusy(true);
  qubit->fillParams();
  qubit_record->markRuleApplied(0);
  EXPECT_FALSE(!qubit_record->isRuleApplied(0));

  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qubit_record, false)).Times(1).WillOnce(Return());
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, qnic_index, 1)).Times(1).WillOnce(Return(qubit_record));
  rule_engine->freeConsumedResource(qnic_index, qubit, QNIC_E);
  EXPECT_TRUE(!qubit_record->isRuleApplied(0));
  EXPECT_FALSE(qubit_record->isBusy());
  delete qubit;
  delete hardware_monitor;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, unlockResourceAndDiscard) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;

  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, {}};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;
  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  int target_rule_id = 10;
  int shared_tag = 3;
  auto rule1 = new ActiveRule(ruleset_id, target_rule_id, shared_tag);
  auto rule2 = new ActiveRule(ruleset_id, 11, 4);
  int qnic_index = 17;
  auto* qubit = new MockQubit(QNIC_E, qnic_index);
  auto* qubit_record = new QubitRecord(QNIC_E, qnic_index, 1, new DisabledLogger{});
  qubit_record->setBusy(true);
  qubit->fillParams();
  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_id;
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule1));
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule2));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, qnic_index, 1)).Times(1).WillOnce(Return(qubit_record));

  qubit_record->markRuleApplied(0);
  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);
  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qubit_record, false)).Times(1).WillOnce(Return());
  rule_engine->Unlock_resource_and_discard(ruleset_id, target_rule_id, shared_tag, action_index);

  EXPECT_EQ(rule1->resources.size(), 0);
  EXPECT_EQ(rule2->resources.size(), 0);
  EXPECT_FALSE(qubit_record->isBusy());

  delete qubit;
  delete hardware_monitor;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;

  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  int target_rule_id = 10;
  int shared_tag = 0;
  auto rule1 = new ActiveRule(ruleset_id, target_rule_id, shared_tag);
  auto rule2 = new ActiveRule(ruleset_id, 11, 1);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_id;
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule1));
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule2));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);

  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);

  // the rule engine brings the qubit from rule1 to rule2
  rule_engine->Unlock_resource_and_upgrade_stage(ruleset_id, target_rule_id, shared_tag, action_index);

  EXPECT_EQ(rule1->resources.size(), 0);
  ASSERT_EQ(rule2->resources.size(), 1);
  auto it = rule2->resources.begin();
  EXPECT_EQ(it->first, partner_addr);
  EXPECT_EQ(it->second, qubit);

  delete qubit;
  delete hardware_monitor;
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage_without_next_rule) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;

  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  int target_rule_id = 10;
  int shared_tag = 3;
  auto rule = new ActiveRule(ruleset_id, target_rule_id, shared_tag);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule->addResource(partner_addr, qubit);
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);
  EXPECT_EQ(rule->resources.size(), 1);
  EXPECT_THROW({ rule_engine->Unlock_resource_and_upgrade_stage(ruleset_id, target_rule_id, shared_tag, action_index); }, cRuntimeError);

  delete qubit;
  delete hardware_monitor;
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage_without_process) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  EXPECT_NO_THROW({ rule_engine->Unlock_resource_and_upgrade_stage(101, 102, 103, 104); });
  delete hardware_monitor;
}

TEST(RuleEngineTest, updateAndCheckAppliedRule) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto* qubit_record1 = new QubitRecord(QNIC_E, 7, 0);
  auto* qubit_record2 = new QubitRecord(QNIC_E, 11, 0);
  EXPECT_TRUE(!qubit_record1->isRuleApplied(1));
  qubit_record1->markRuleApplied(1);
  EXPECT_FALSE(!qubit_record1->isRuleApplied(1));
  EXPECT_TRUE(!qubit_record1->isRuleApplied(2));
  EXPECT_TRUE(!qubit_record2->isRuleApplied(1));

  delete hardware_monitor;
}

TEST(RuleEngineTest, checkAppliedRule) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* qubit_record = new QubitRecord(QNIC_E, 7, 1);
  EXPECT_TRUE(!qubit_record->isRuleApplied(1));
  qubit_record->markRuleApplied(1);
  EXPECT_FALSE(!qubit_record->isRuleApplied(1));

  qubit_record->clearAppliedRules();
  EXPECT_TRUE(!qubit_record->isRuleApplied(1));

  delete qubit;
  delete qubit_record;
  delete hardware_monitor;
}

TEST(RuleEngineTest, updateResourcesEntanglementSwappingWithoutRuleSet) {
  /* setup components */
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 0, 0);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 0)).Times(3).WillRepeatedly(Return(qubit_record.get()));
  EXPECT_CALL(*realtime_controller, assertNoEntanglement(qubit_record.get())).Times(3);
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  {  // swap result doesn't need an action
    swapping_result result{.new_partner = 2, .operation_type = 0};
    EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyXGate(_)).Times(0);
    EXPECT_CALL(*realtime_controller, applyZGate(_)).Times(0);
    rule_engine->updateResources_EntanglementSwapping(result);
  }
  {  // swap result needs to apply X gate
    swapping_result result{.new_partner = 2, .operation_type = 1};
    EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyXGate(qubit_record.get())).Times(1);
    EXPECT_CALL(*realtime_controller, applyZGate(_)).Times(0);
    rule_engine->updateResources_EntanglementSwapping(result);
  }
  {  // swap result needs to apply Z gate
    swapping_result result{.new_partner = 2, .operation_type = 2};
    EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyZGate(qubit_record.get())).Times(1);
    EXPECT_CALL(*realtime_controller, applyXGate(_)).Times(0);
    rule_engine->updateResources_EntanglementSwapping(result);
  }
  delete qubit;
  delete hardware_monitor;
  delete routing_daemon;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}
TEST(RuleEngineTest, updateResourcesEntanglementSwappingWithRuleSet) {
  /* setup components */
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 7, 0);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 0)).Times(1).WillRepeatedly(Return(qubit_record.get()));
  EXPECT_CALL(*realtime_controller, assertNoEntanglement(qubit_record.get())).Times(1);
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  unsigned long ruleset_id = 3;
  int rule_id = 0;
  int shared_tag = 3;
  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_id);
  {  // generate RuleSet
    auto rule = std::make_unique<ActiveRule>(ruleset_id, rule_id, 0);
    rule->next_rule_id = rule_id + 1;
    rule->action_partners.push_back(1);
    rule->action_partners.push_back(2);
    rule->addResource(2, qubit);
    rule->shared_tag = shared_tag;
    auto next_rule = std::make_unique<ActiveRule>(ruleset_id, rule_id + 1, 0);

    ruleset->addRule(std::move(rule));
    ruleset->addRule(std::move(next_rule));
    rule_engine->rp.insert(ruleset);
    EXPECT_EQ(ruleset->rules.at(0)->resources.size(), 1);
    EXPECT_EQ(ruleset->rules.at(1)->resources.size(), 0);
  }

  swapping_result result{
      .id = {.ruleset_id = ruleset_id, .rule_id = rule_id, .shared_tag = shared_tag, .index = 0},
      .new_partner = 2,
      .operation_type = 0,
      .swapper_addr = 1,
  };
  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
  auto info = std::make_unique<ConnectionSetupInfo>();
  info->qnic.type = QNIC_E;
  info->qnic.index = 0;
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
  EXPECT_CALL(*qubit, X_gate()).Times(0);
  EXPECT_CALL(*qubit, Z_gate()).Times(0);
  rule_engine->updateResources_EntanglementSwapping(result);

  // check whether the qubit is promoted or not
  EXPECT_EQ(ruleset->rules.at(0)->resources.size(), 0);
  EXPECT_EQ(ruleset->rules.at(1)->resources.size(), 1);

  delete qubit;
  delete hardware_monitor;
  delete routing_daemon;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, generateActiveRuleSetFromRuleSet) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 7, 0);
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  // prepare (static) ruleset being sent by responder
  unsigned long ruleset_id = 1234;
  int owner_address = 2;
  // ruleset creation
  RuleSet ruleset(ruleset_id, owner_address);  // static ruleset
  ruleset.ruleset_id = ruleset_id;
  ruleset.owner_addr = owner_address;

  auto purify_rule = std::make_unique<Rule>(0, QNIC_E, 0, 0, false);
  purify_rule->setName("purification");
  auto pur_condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, QNIC_E, 0);
  pur_condition->addClause(std::move(enough_resource_clause));
  purify_rule->setCondition(std::move(pur_condition));
  auto pur_action = std::make_unique<Purification>(PurType::DSDA, 0, QNIC_E, 0);
  purify_rule->setAction(std::move(pur_action));
  ruleset.addRule(std::move(purify_rule));
  // swapping rule
  auto swapping_rule = std::make_unique<Rule>(0, QNIC_E, 0, 0, false);
  swapping_rule->setName("swapping");
  auto swap_condition = std::make_unique<Condition>();
  auto enough_resource_clause_left = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, QNIC_E, 0);
  auto enough_resource_clause_right = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, QNIC_E, 0);
  swap_condition->addClause(std::move(enough_resource_clause_left));
  swap_condition->addClause(std::move(enough_resource_clause_right));
  swapping_rule->setCondition(std::move(swap_condition));
  std::vector<int> partners = {0, 0};
  std::vector<QNIC_type> qnic_type = {QNIC_E, QNIC_E};
  std::vector<int> qnic_id = {0, 0};
  std::vector<QNIC_type> remote_qnic_type = {QNIC_E, QNIC_E};
  std::vector<int> remote_qnic_id = {0, 0};
  std::vector<int> remote_qnic_address = {0, 0};
  auto swap_action = std::make_unique<EntanglementSwapping>(partners, qnic_type, qnic_id, remote_qnic_type, remote_qnic_id, remote_qnic_address);
  swapping_rule->setAction(std::move(swap_action));
  ruleset.addRule(std::move(swapping_rule));
  // wait rule
  auto wait_rule = std::make_unique<Rule>(0, QNIC_E, 0, 0, false);
  wait_rule->setName("wait");
  auto wait_condition = std::make_unique<Condition>();
  auto wait_clause = std::make_unique<WaitConditionClause>(0, QNIC_E, 0);
  wait_condition->addClause(std::move(wait_clause));
  wait_rule->setCondition(std::move(wait_condition));
  auto wait_action = std::make_unique<Wait>(0, QNIC_E, 0);
  wait_rule->setAction(std::move(wait_action));
  ruleset.addRule(std::move(wait_rule));
  // tomography rule
  auto tomography_rule = std::make_unique<Rule>(0, QNIC_E, 0, 0, true);
  tomography_rule->setName("tomography");
  auto tomo_condition = std::make_unique<Condition>();
  auto enough_resource_clause_tomo = std::make_unique<EnoughResourceConditionClause>(0, 0, 0, QNIC_E, 0);
  tomo_condition->addClause(std::move(enough_resource_clause_tomo));
  tomography_rule->setCondition(std::move(tomo_condition));
  auto tomo_action = std::make_unique<Tomography>(0, 0, 0, QNIC_E, 0);
  tomography_rule->setAction(std::move(tomo_action));
  ruleset.addRule(std::move(tomography_rule));

  // return active ruleset corresponding to input ruleset
  auto active_ruleset = rule_engine->constructActiveRuleSet(std::move(ruleset));
  EXPECT_EQ(active_ruleset->ruleset_id, ruleset_id);
  EXPECT_EQ(active_ruleset->rules.size(), 4);
  auto rule0 = std::move(active_ruleset->getRule(0));
  EXPECT_EQ(rule0->rule_id, 0);
  EXPECT_EQ(rule0->name, "purification with 0 ");
  auto rule1 = std::move(active_ruleset->getRule(1));
  EXPECT_EQ(rule1->rule_id, 1);
  EXPECT_EQ(rule1->name, "swapping with 0 ");
  auto rule2 = std::move(active_ruleset->getRule(2));
  EXPECT_EQ(rule2->rule_id, 2);
  EXPECT_EQ(rule2->name, "wait with 0 ");
  auto rule3 = std::move(active_ruleset->getRule(3));
  EXPECT_EQ(rule3->rule_id, 3);
  EXPECT_EQ(rule3->name, "tomography with 0 ");
}

TEST(RuleEngineTest, activeRuleSetGenerationDifferentOwnerExceptions) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 7, 0);
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  unsigned long ruleset_id = 1234;
  int owner_address = 3;  // different from parent address

  RuleSet ruleset(ruleset_id, owner_address);  // static ruleset
  ruleset.ruleset_id = ruleset_id;
  ruleset.owner_addr = owner_address;

  EXPECT_THROW(rule_engine->constructActiveRuleSet(std::move(ruleset)), omnetpp::cRuntimeError);
}

TEST(RuleEngineTest, activeRuleSetGenerationNoConditionExceptions) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 7, 0);
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto purify_rule = std::make_unique<Rule>(0, QNIC_E, 0, 0, false);
  purify_rule->setName("purification");
  auto pur_condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, QNIC_E, 0);
  auto pur_action = std::make_unique<Purification>(PurType::DSDA, 0, QNIC_E, 0);
  purify_rule->setAction(std::move(pur_action));

  auto active_purify_rule = std::make_unique<ActiveRule>(1234, 0, 0);
  // No condition set error
  EXPECT_THROW(rule_engine->constructRule(std::move(active_purify_rule), std::move(purify_rule), 1234), omnetpp::cRuntimeError);
}

TEST(RuleEngineTest, activeRuleSetGenerationNoActionExceptions) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 7, 0);
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto purify_rule = std::make_unique<Rule>(0, QNIC_E, 0, 0, false);
  purify_rule->setName("purification");
  auto pur_condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, QNIC_E, 0);
  pur_condition->addClause(std::move(enough_resource_clause));
  purify_rule->setCondition(std::move(pur_condition));

  auto active_purify_rule = std::make_unique<ActiveRule>(1234, 0, 0);
  // No action set error
  EXPECT_THROW(rule_engine->constructRule(std::move(active_purify_rule), std::move(purify_rule), 1234), omnetpp::cRuntimeError);
}

}  // namespace
