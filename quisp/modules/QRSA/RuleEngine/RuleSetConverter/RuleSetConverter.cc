#include "RuleSetConverter.h"

#include <stdexcept>
#include <string>
#include <vector>
#include "runtime/types.h"

#include <rules/Action.h>
#include <rules/Clause.h>
#include <runtime/Runtime.h>

namespace quisp::modules::rs_converter {

using runtime::InstructionTypes;

using namespace runtime;

RuleSet RuleSetConverter::construct(const RSData &data) {
  RuleSet rs;
  rs.id = data.ruleset_id;
  rs.owner_addr = data.owner_addr;
  auto &rules_data = data.rules;
  for (auto &rule_data : rules_data) {
    auto condition = constructCondition(rule_data->condition.get());
    auto action = constructAction(rule_data->action.get());
    rs.rules.emplace_back(Rule{rule_data->name, rule_data->shared_tag, condition, action});
    // std::cout << const_cast<RSData &>(data).serialize_json() << std::endl;
  }
  return rs;
}

Program RuleSetConverter::constructCondition(const ConditionData *data) {
  auto opcodes = std::vector<InstructionTypes>{};
  std::string name;
  for (auto &clause_data : data->clauses) {
    auto clause_ptr = clause_data.get();
    if (auto *c = dynamic_cast<const EnoughResourceConditionClause *>(clause_ptr)) {
      auto counter = RegId::REG0;
      auto qubit_id = RegId::REG1;
      /*
        SET qubit_id -1
        SET counter 0
      LOOP:
        INC qubit_id
        GET_QUBIT qubit_id partner_addr qubit_id
        BNERR FOUND_QUBIT
        RET COND_FAILED
      FOUND_QUBIT:
        BRANCH_IF_LOCKED qubit_id LOOP
        INC counter
        BEQ counter num_resource_required PASSED
        JMP LOOP
      PASSED:
        RET COND_PASSED
      */
      opcodes.push_back(INSTR_SET_RegId_int_{{counter, 0}});
      opcodes.push_back(INSTR_SET_RegId_int_{{qubit_id, -1}});

      opcodes.push_back(INSTR_INC_RegId_{qubit_id, "LOOP"});
      opcodes.push_back(INSTR_GET_QUBIT_RegId_QNodeAddr_RegId_{{qubit_id, c->partner_address, qubit_id}});
      opcodes.push_back(INSTR_BNERR_Label_{Label{"FOUND_QUBIT"}});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});

      opcodes.push_back(INSTR_BRANCH_IF_LOCKED_Label_RegId_{{Label{"LOOP"}, qubit_id}, "FOUND_QUBIT"});
      opcodes.push_back(INSTR_INC_RegId_{{counter}});
      opcodes.push_back(INSTR_BEQ_Label_RegId_int_{{Label{"PASSED"}, counter, c->num_resource}});
      opcodes.push_back(INSTR_JMP_Label_{Label{"LOOP"}});
      opcodes.push_back(INSTR_NOP_None_{None, "PASSED"});

      name += "EnoughResource ";
    } else if (auto *c = dynamic_cast<const FidelityConditionClause *>(clause_ptr)) {
      // XXX: no impl for now
      name += "FidelityCondition ";
    } else if (auto *c = dynamic_cast<const WaitConditionClause *>(clause_ptr)) {
      name += "Wait ";
    } else if (auto *c = dynamic_cast<const MeasureCountConditionClause *>(clause_ptr)) {
      /*
      LOAD count MemoryKey("count")
      BLT PASSED count max_count
      RET COND_FAILED
    PASSED:
      INC count
      STORE MemoryKey("count") count
      RET COND_PASSED
      */
      auto count = RegId::REG2;
      MemoryKey count_key{"measure_count"};
      opcodes.push_back(INSTR_LOAD_RegId_MemoryKey_{{count, count_key}});
      opcodes.push_back(INSTR_BLT_Label_RegId_int_{{Label{"PASSED"}, count, c->num_measure}});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});
      opcodes.push_back(INSTR_INC_RegId_{count, "PASSED"});
      opcodes.push_back(INSTR_STORE_MemoryKey_RegId_{{count_key, count}});
      opcodes.push_back(INSTR_RET_ReturnCode_{{ReturnCode::COND_PASSED}});
      name += "MeasureCountCondition ";
    }
  }
  return Program{name, opcodes};
}

Program RuleSetConverter::constructAction(const ActionData *data) {
  if (auto *act = dynamic_cast<const Purification *>(data)) {
    return constructPurificationAction(act);
  }
  if (auto *act = dynamic_cast<const EntanglementSwapping *>(data)) {
    return constructEntanglementSwappingAction(act);
  }
  if (auto *act = dynamic_cast<const Tomography *>(data)) {
    return constructTomographyAction(act);
  }
  if (auto *act = dynamic_cast<const Wait *>(data)) {
    return constructWaitAction(act);
  }

  throw std::runtime_error("got invalid actions");
  return Program{"empty", {}};
}

Program RuleSetConverter::constructEntanglementSwappingAction(const EntanglementSwapping *act) {
  /*
  GET_QUBIT q0 left_partner 0
  GET_QUBIT q1 right_partner 1
  GATE_CNOTE q0 q1
  MEASURE r0 q0
  MEASURE r1 q1
  FREE_QUBIT q0
  FREE_QUBIT q1
  */
  auto left_interface = act->qnic_interfaces.at(0);
  auto right_interface = act->qnic_interfaces.at(1);
  QubitId q0{0};
  QubitId q1{1};
  QNodeAddr left_partner_addr{left_interface.partner_addr};
  QNodeAddr right_partner_addr{right_interface.partner_addr};
  return Program{"EntanglementSwapping",
                 {

                     INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, left_partner_addr, 0}}, INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, right_partner_addr, 1}},
                     // INSTR_GATE_CNOT_QubitId_QubitId_{{q0, q1}},
                     // INSTR_MEASURE_X_QubitId_
                     // INSTR_MEASURE_Z_QubitId_

                 }};
}
Program RuleSetConverter::constructPurificationAction(const Purification *act) {
  //{"options":{"interface":[{"partner_address":3,"qnic_id":0,"qnic_type":"QNIC_E"}],"purification_type":"SINGLE_X"},"type":"purification"}
  if (act->purification_type == rules::PurType::SINGLE_X) {
    QubitId qubit{0};
    QubitId trash_qubit{1};
    RegId measure_result = RegId::REG0;
    QNodeAddr partner_addr{act->qnic_interfaces.at(0).partner_addr};
    return Program{"Purification",
                   {INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}}, INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit, partner_addr, 1}},
                    INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result, qubit, trash_qubit}}, INSTR_FREE_QUBIT_QubitId_{{trash_qubit}}, INSTR_LOCK_QUBIT_QubitId_{{qubit}},
                    INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_{{partner_addr, measure_result}}}};
  }
  std::cout << const_cast<Purification *>(act)->serialize_json() << std::endl;
  throw std::runtime_error("pur not implemented");
  return Program{"Purification", {}};
}
Program RuleSetConverter::constructWaitAction(const Wait *act) {
  // todo: maybe promote qubit to the next rule
  return Program{"Wait", {}};
}

Program RuleSetConverter::constructTomographyAction(const Tomography *act) {
  auto q0 = 0;
  auto count = RegId::REG0;
  int max_count = act->num_measurement;
  auto &qnic = act->qnic_interfaces.at(0);
  QNodeAddr partner_addr = qnic.partner_addr;
  auto qubit_resource_index = 0;
  return Program{"Tomography",
                 {
                     // clang-format off
INSTR_LOAD_RegId_MemoryKey_{{count, MemoryKey{"count"}}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, qubit_resource_index}},
INSTR_BNERR_Label_{Label{"L1"}},
INSTR_ERROR_String_{"Qubit not found for mesaurement"},
INSTR_MEASURE_RANDOM_MemoryKey_QubitId_{{MemoryKey{"outcome"}, q0}, "L1"},
INSTR_INC_RegId_{count},
INSTR_STORE_MemoryKey_RegId_{{MemoryKey{"count"}, count}},
INSTR_FREE_QUBIT_QubitId_{q0},
INSTR_SEND_LINK_TOMOGRAPHY_RESULT_QNodeAddr_RegId_MemoryKey_int_{{partner_addr, count,MemoryKey{"outcome"}, max_count}}
                     // clang-format on
                 }};
}
}  // namespace quisp::modules::rs_converter
