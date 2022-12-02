#include "ConnectionManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <messages/classical_messages.h>
#include <modules/QNIC.h>
#include <modules/QRSA/HardwareMonitor/IHardwareMonitor.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace {
using namespace omnetpp;
using namespace quisp_test;
using namespace testing;
using namespace quisp::messages;
using namespace quisp::modules;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_type;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(IRoutingDaemon *_routing_daemon, IHardwareMonitor *_hardware_monitor) : routing_daemon(_routing_daemon), hardware_monitor(_hardware_monitor) {}
  Strategy() {}
  ~Strategy() {}
  IRoutingDaemon *getRoutingDaemon() override { return routing_daemon; }
  IHardwareMonitor *getHardwareMonitor() override { return hardware_monitor; }
  IRoutingDaemon *routing_daemon = nullptr;
  IHardwareMonitor *hardware_monitor = nullptr;
};

class ConnectionManagerTestTarget : public quisp::modules::ConnectionManager {
 public:
  using quisp::modules::ConnectionManager::isQnicBusy;
  using quisp::modules::ConnectionManager::par;
  using quisp::modules::ConnectionManager::parsePurType;
  using quisp::modules::ConnectionManager::purification_type;
  using quisp::modules::ConnectionManager::releaseQnic;
  using quisp::modules::ConnectionManager::reserved_qnics;
  using quisp::modules::ConnectionManager::reserveQnic;
  using quisp::modules::ConnectionManager::respondToRequest;
  using quisp::modules::ConnectionManager::respondToRequest_deprecated;
  ConnectionManagerTestTarget(IRoutingDaemon *routing_daemon, IHardwareMonitor *hardware_monitor)
      : quisp::modules::ConnectionManager(), toRouterGate(new TestGate(this, "RouterPort$o")) {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    setParBool(this, "simultaneous_es_enabled", false);
    setParBool(this, "entanglement_swapping_with_purification", false);
    setParInt(this, "num_remote_purification", 1);
    setParStr(this, "purification_type_cm", "SINGLE_X");
    setParDouble(this, "threshold_fidelity", 0);
    setParInt(this, "seed_cm", 0);

    this->provider.setStrategy(std::make_unique<Strategy>(routing_daemon, hardware_monitor));
    setComponentType(new module_type::TestModuleType("test cm"));
  }
  ConnectionManagerTestTarget() : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>());
    setComponentType(new module_type::TestModuleType("test cm"));
  }
  cGate *gate(const char *gatename, int index = -1) override {
    if (strcmp(gatename, "RouterPort$o") != 0) {
      throw cRuntimeError("unknown gate called");
    }
    return toRouterGate;
  };
  TestGate *toRouterGate;
  unsigned long createUniqueId() override { return 1234; };
};

TEST(ConnectionManagerTest, Init) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}

TEST(ConnectionManagerTest, parsePurType) {
  prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  auto *connection_manager = new ConnectionManagerTestTarget(routing_daemon, hardware_monitor);

  auto pur_type = connection_manager->parsePurType("SINGLE_X");
  EXPECT_EQ(pur_type, PurType::SINGLE_X);

  pur_type = connection_manager->parsePurType("SINGLE_Z");
  EXPECT_EQ(pur_type, PurType::SINGLE_Z);
  pur_type = connection_manager->parsePurType("DOUBLE");
  EXPECT_EQ(pur_type, PurType::DOUBLE);
  pur_type = connection_manager->parsePurType("DOUBLE_INV");
  EXPECT_EQ(pur_type, PurType::DOUBLE_INV);
  pur_type = connection_manager->parsePurType("DSSA");
  EXPECT_EQ(pur_type, PurType::DSSA);
  pur_type = connection_manager->parsePurType("DSSA_INV");
  EXPECT_EQ(pur_type, PurType::DSSA_INV);
  pur_type = connection_manager->parsePurType("DSDA");
  EXPECT_EQ(pur_type, PurType::DSDA);
  pur_type = connection_manager->parsePurType("DSDA_INV");
  EXPECT_EQ(pur_type, PurType::DSDA_INV);
  pur_type = connection_manager->parsePurType("DSDA_SECOND");
  EXPECT_EQ(pur_type, PurType::DSDA_SECOND);
  pur_type = connection_manager->parsePurType("DSDA_SECOND_INV");
  EXPECT_EQ(pur_type, PurType::DSDA_SECOND_INV);
  // unknown purification name
  pur_type = connection_manager->parsePurType("DSDA_SECOND_INV_T");
  EXPECT_EQ(pur_type, PurType::INVALID);
}

TEST(ConnectionManagerTest, RespondToRequest) {
  auto *sim = prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  auto *connection_manager = new ConnectionManagerTestTarget(routing_daemon, hardware_monitor);
  sim->registerComponent(connection_manager);
  connection_manager->par("address") = 5;
  connection_manager->par("entanglement_swapping_with_purification") = true;

  connection_manager->callInitialize();
  auto *req = new ConnectionSetupRequest;

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
  req->setStack_of_QNICs(0, QNIC_pair_info{.fst = NULL_CONNECTION_SETUP_INFO.qnic, .snd = {.type = QNIC_E, .index = 11, .address = 101}});
  req->setStack_of_QNICs(1, QNIC_pair_info{.fst = {.type = QNIC_E, .index = 12, .address = 102}, .snd = {.type = QNIC_E, .index = 13, .address = 103}});
  req->setStack_of_QNICs(2, QNIC_pair_info{.fst = {.type = QNIC_E, .index = 14, .address = 104}, .snd = {.type = QNIC_E, .index = 15, .address = 105}});
  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(5)).Times(1).WillOnce(Return(-1));
  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(106));
  auto src_info = new ConnectionSetupInfo{.qnic = {.type = QNIC_E, .index = 16, .address = 106}, .neighbor_address = 4, .quantum_link_cost = 10};
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(106)).Times(1).WillOnce(Return(ByMove(std::unique_ptr<ConnectionSetupInfo>(src_info))));

  sim->setContext(connection_manager);
  connection_manager->respondToRequest(req);
  auto gate = connection_manager->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 4);
  // checking the ruleset for QNode2(initiator)
  {
    auto *packetFor2 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[0]);
    ASSERT_NE(packetFor2, nullptr);
    EXPECT_EQ(packetFor2->getDestAddr(), 2);
    auto ruleset = packetFor2->getRuleSet();  // json serialized ruleset
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset["rules"].size(), 4);
    auto expected_ruleset = R"({
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
    "shared_tag": 5,
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
    "shared_tag": 6,
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
					"num_measure": 0
				},
				"type": "measure_count"
			}]
		},
		"interface": [{
			"partner_address": 5,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 7,
		"name": "tomography",
		"next_rule_id": -1,
		"rule_id": 3
	}],
	"ruleset_id": 1234
})"_json;
    EXPECT_EQ(expected_ruleset, ruleset);
  }

  // checking the ruleset for QNode3 (swapper)
  {
    auto *packetFor3 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[1]);
    ASSERT_NE(packetFor3, nullptr);
    EXPECT_EQ(packetFor3->getDestAddr(), 3);
    auto ruleset = packetFor3->getRuleSet();  // json serialized ruleset
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset["rules"].size(), 5);

    auto expected_ruleset = R"({
	"num_rules": 5,
	"owner_address": 3,
	"rules": [{
		"action": {
			"options": {
				"interface": [{
					"partner_address": 2,
					"qnic_id": 12,
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
						"partner_address": 2,
						"qnic_id": 12,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 2,
			"qnic_id": 12,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "purification",
		"next_rule_id": 4,
		"rule_id": 0
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 4,
					"qnic_id": 13,
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
						"partner_address": 4,
						"qnic_id": 13,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 4,
			"qnic_id": 13,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 1,
		"name": "purification",
		"next_rule_id": 2,
		"rule_id": 1
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 4,
					"qnic_id": 13,
					"qnic_type": "QNIC_E"
				}]
			},
			"type": "wait"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 4,
						"qnic_id": 13,
						"qnic_type": "QNIC_E"
					}
				},
				"type": "wait"
			}]
		},
		"interface": [{
			"partner_address": 4,
			"qnic_id": 13,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 3,
		"name": "wait",
		"next_rule_id": 3,
		"rule_id": 2
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5,
					"qnic_id": 13,
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
						"qnic_id": 13,
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
			"qnic_id": 13,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 4,
		"name": "purification",
		"next_rule_id": 4,
		"rule_id": 3
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 2,
					"qnic_id": 12,
					"qnic_type": "QNIC_E"
				}, {
					"partner_address": 5,
					"qnic_id": 13,
					"qnic_type": "QNIC_E"
				}],
				"remote_interface": [{
					"partner_address": 2,
					"qnic_address": 101,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}, {
					"partner_address": 5,
					"qnic_address": 106,
					"qnic_id": 16,
					"qnic_type": "QNIC_E"
				}]
			},
			"type": "swapping"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 2,
						"qnic_id": 12,
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
						"qnic_id": 13,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 1,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 2,
			"qnic_id": 12,
			"qnic_type": "QNIC_E"
		},
    {
			"partner_address": 5,
			"qnic_id": 13,
			"qnic_type": "QNIC_E"
    }],
    "shared_tag": 5,
		"name": "swapping",
		"next_rule_id": -1,
		"rule_id": 4
	}],
	"ruleset_id": 1234
})"_json;
    EXPECT_EQ(expected_ruleset, ruleset);
  }

  // checking the ruleset for QNode4 (swapper)
  {
    auto *packetFor4 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[2]);
    ASSERT_NE(packetFor4, nullptr);
    EXPECT_EQ(packetFor4->getDestAddr(), 4);
    auto ruleset = packetFor4->getRuleSet();  // json serialized ruleset
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset["rules"].size(), 3);

    // rule1 (id: 0) : purification with 3, next to 2
    // rule2 (id: 1): purification with 5, next to 2
    // rule3 (id: 2): swapping with [3, 5], next to -1
    auto expected_ruleset = R"({
	"num_rules": 3,
	"owner_address": 4,
	"rules": [{
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 14,
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
						"qnic_id": 14,
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
			"qnic_id": 14,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 1,
		"name": "purification",
		"next_rule_id": 2,
		"rule_id": 0
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5,
					"qnic_id": 15,
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
						"qnic_id": 15,
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
			"qnic_id": 15,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 2,
		"name": "purification",
		"next_rule_id": 2,
		"rule_id": 1
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 14,
					"qnic_type": "QNIC_E"
				}, {
					"partner_address": 5,
					"qnic_id": 15,
					"qnic_type": "QNIC_E"
				}],
				"remote_interface": [{
					"partner_address": 3,
					"qnic_address": 103,
					"qnic_id": 13,
					"qnic_type": "QNIC_E"
				}, {
					"partner_address": 5,
					"qnic_address": 106,
					"qnic_id": 16,
					"qnic_type": "QNIC_E"
				}]
			},
			"type": "swapping"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 3,
						"qnic_id": 14,
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
						"qnic_id": 15,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 1,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 3,
			"qnic_id": 14,
			"qnic_type": "QNIC_E"
		}, {
			"partner_address": 5,
			"qnic_id": 15,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 3,
		"name": "swapping",
		"next_rule_id": -1,
		"rule_id": 2
	}],
	"ruleset_id": 1234
})"_json;
    EXPECT_EQ(expected_ruleset, ruleset);
  }

  // checking the ruleset for QNode5 (swapper)
  {
    auto *packetFor5 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[3]);
    ASSERT_NE(packetFor5, nullptr);
    EXPECT_EQ(packetFor5->getDestAddr(), 5);
    auto ruleset = packetFor5->getRuleSet();  // json serialized ruleset
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset["rules"].size(), 6);

    // rule1 (id: 0): purification with 4, to (id: 1)
    // rule2 (id: 1): wait with 4, to (id: 2)
    // rule3 (id: 2): purification with 3, to (id: 3)
    // rule4 (id: 3): wait with 3, to (id: 4)
    // rule5 (id: 4): purification with 1, to (id: 5)
    // rule6 (id: 5): tomography with 1, to (id: -1)
    auto expected_ruleset = R"({
	"num_rules": 6,
	"owner_address": 5,
	"rules": [{
		"action": {
			"options": {
				"interface": [{
					"partner_address": 4,
					"qnic_id": 16,
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
						"partner_address": 4,
						"qnic_id": 16,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 4,
			"qnic_id": 16,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 2,
		"name": "purification",
		"next_rule_id": 1,
		"rule_id": 0
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 4,
					"qnic_id": 16,
					"qnic_type": "QNIC_E"
				}]
			},
			"type": "wait"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 4,
						"qnic_id": 16,
						"qnic_type": "QNIC_E"
					}
				},
				"type": "wait"
			}]
		},
		"interface": [{
			"partner_address": 4,
			"qnic_id": 16,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 3,
		"name": "wait",
		"next_rule_id": 2,
		"rule_id": 1
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 16,
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
						"qnic_id": 16,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
    "shared_tag": 4,
		"interface": [{
			"partner_address": 3,
			"qnic_id": 16,
			"qnic_type": "QNIC_E"
		}],
		"name": "purification",
		"next_rule_id": 3,
		"rule_id": 2
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 16,
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
						"qnic_id": 16,
						"qnic_type": "QNIC_E"
					}
				},
				"type": "wait"
			}]
		},
		"interface": [{
			"partner_address": 3,
			"qnic_id": 16,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 5,
		"name": "wait",
		"next_rule_id": 4,
		"rule_id": 3
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 2,
					"qnic_id": 16,
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
						"partner_address": 2,
						"qnic_id": 16,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 2,
			"qnic_id": 16,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 6,
		"name": "purification",
		"next_rule_id": 5,
		"rule_id": 4
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 2,
					"qnic_id": 16,
					"qnic_type": "QNIC_E"
				}],
				"num_measure": 0,
				"owner_address": 5
			},
			"type": "tomography"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 2,
						"qnic_id": 16,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 1,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}, {
				"options": {
					"interface": {
						"partner_address": 2,
						"qnic_id": 16,
						"qnic_type": "QNIC_E"
					},
					"num_measure": 0
				},
				"type": "measure_count"
			}]
		},
		"interface": [{
			"partner_address": 2,
			"qnic_id": 16,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 7,
		"name": "tomography",
		"next_rule_id": -1,
		"rule_id": 5
	}],
	"ruleset_id": 1234
})"_json;
    EXPECT_EQ(expected_ruleset, ruleset);
  }
  delete routing_daemon;
  delete hardware_monitor;
}

TEST(ConnectionManagerTest, GetQNICInterface) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}

TEST(ConnectionManagerTest, QnicReservation) {
  prepareSimulation();
  auto *connection_manager = new ConnectionManagerTestTarget();

  int qnic_address = 13, qnic_address2 = 15;
  // qnic reservation
  EXPECT_EQ(connection_manager->reserved_qnics.size(), 0);
  connection_manager->reserveQnic(qnic_address);
  EXPECT_EQ(connection_manager->reserved_qnics.size(), 1);
  EXPECT_EQ(connection_manager->reserved_qnics.at(0), qnic_address);
  EXPECT_TRUE(connection_manager->isQnicBusy(qnic_address));
  EXPECT_FALSE(connection_manager->isQnicBusy(qnic_address2));
  connection_manager->reserveQnic(qnic_address2);
  EXPECT_EQ(connection_manager->reserved_qnics.size(), 2);
  EXPECT_EQ(connection_manager->reserved_qnics.at(1), qnic_address2);
  EXPECT_TRUE(connection_manager->isQnicBusy(qnic_address));
  EXPECT_TRUE(connection_manager->isQnicBusy(qnic_address2));

  // qnic release
  connection_manager->releaseQnic(qnic_address);
  EXPECT_EQ(connection_manager->reserved_qnics.size(), 1);
  EXPECT_EQ(connection_manager->reserved_qnics.at(0), qnic_address2);
  EXPECT_FALSE(connection_manager->isQnicBusy(qnic_address));
  EXPECT_TRUE(connection_manager->isQnicBusy(qnic_address2));
  connection_manager->releaseQnic(qnic_address2);
  EXPECT_EQ(connection_manager->reserved_qnics.size(), 0);
  EXPECT_FALSE(connection_manager->isQnicBusy(qnic_address));
  EXPECT_FALSE(connection_manager->isQnicBusy(qnic_address2));
}
}  // namespace
