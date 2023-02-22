#include "RuleSetConverter.h"

#include <stdexcept>
#include <string>
#include <vector>
#include "omnetpp/cexception.h"
#include "runtime/types.h"

#include <rules/Action.h>
#include <rules/Clause.h>
#include <runtime/Runtime.h>

namespace quisp::rules::rs_converter {

using runtime::InstructionTypes;

using namespace runtime;

RuleSet RuleSetConverter::construct(const RSData &data) {
  RuleSet rs;
  rs.id = data.ruleset_id;
  rs.owner_addr = data.owner_addr;
  auto &rules_data = data.rules;
  if (data.rules.size() == 0) throw omnetpp::cRuntimeError("empty ruleset");
  for (auto &rule_data : rules_data) {
    std::string name = rule_data->name + " with ";
    for (auto &interface : rule_data->qnic_interfaces) {
      name += std::to_string(interface.partner_addr) + "";
    }
    auto condition = constructCondition(rule_data->condition.get());
    auto action = constructAction(rule_data->action.get());
    auto terminate_condition = constructTerminateCondition(rule_data->condition.get());
    if (terminate_condition.opcodes.size() > 0) {
      rs.termination_condition = terminate_condition;
    }
    rs.rules.emplace_back(Rule{name, rule_data->shared_tag, condition, action});
  }
  return rs;
}

Program RuleSetConverter::constructTerminateCondition(const ConditionData *data) {
  if (data == nullptr) {
    return Program{"no terminate condition", {}};
  }
  auto opcodes = std::vector<InstructionTypes>{};
  std::string name;
  int i = 0;
  for (auto &clause_data : data->clauses) {
    i++;
    auto clause_ptr = clause_data.get();
    if (auto *c = dynamic_cast<const MeasureCountConditionClause *>(clause_ptr)) {
      /*
      LOAD count MemoryKey("count")
      BLT CONTINUE count max_count
      RET RS_TERMINATED
    CONTINUE:
      NOP
      */
      auto count = RegId::REG2;
      MemoryKey count_key{"measure_count" + std::to_string(i)};
      name += "MeasureCountCondition ";

      Label continue_label{std::string("CONTINUE_") + std::to_string(i)};
      opcodes.push_back(INSTR_LOAD_RegId_MemoryKey_{{count, count_key}});
      opcodes.push_back(INSTR_BLT_Label_RegId_int_{{continue_label, count, c->num_measure}});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::RS_TERMINATED});
      opcodes.push_back(INSTR_NOP_None_{{None}, continue_label});
    }
  }
  return Program{name, opcodes};
}

Program RuleSetConverter::constructCondition(const ConditionData *data) {
  if (data == nullptr) {
    return Program{"no condition", {}};
  }
  auto opcodes = std::vector<InstructionTypes>{};
  std::string name;
  int i = 0;
  for (auto &clause_data : data->clauses) {
    i++;
    auto clause_ptr = clause_data.get();
    if (auto *c = dynamic_cast<const EnoughResourceConditionClause *>(clause_ptr)) {
      auto counter = RegId::REG0;
      auto qubit_id = RegId::REG1;

      Label loop_label{std::string("LOOP_") + std::to_string(i)};
      Label found_qubit_label{std::string("FOUND_QUBIT_") + std::to_string(i)};
      Label passed_label{std::string("PASSED_") + std::to_string(i)};

      /*
        SET qubit_id -1
        SET counter 0
      LOOP:
        INC qubit_id
        GET_QUBIT qubit_id partner_addr qubit_id
        BRANCH_IF_QUBIT_FOUND FOUND_QUBIT
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

      opcodes.push_back(INSTR_INC_RegId_{qubit_id, loop_label});
      opcodes.push_back(INSTR_GET_QUBIT_RegId_QNodeAddr_RegId_{{qubit_id, c->partner_address, qubit_id}});
      opcodes.push_back(INSTR_BRANCH_IF_QUBIT_FOUND_Label_{found_qubit_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});

      opcodes.push_back(INSTR_INC_RegId_{{counter}, found_qubit_label});

      opcodes.push_back(INSTR_BEQ_Label_RegId_int_{{passed_label, counter, c->num_resource}});
      opcodes.push_back(INSTR_JMP_Label_{loop_label});
      opcodes.push_back(INSTR_NOP_None_{nullptr, passed_label});

      name += "EnoughResource ";
    } else if (auto *c = dynamic_cast<const FidelityConditionClause *>(clause_ptr)) {
      // XXX: no impl in the original
      throw std::runtime_error("FidelityCondition has not implemented yet");
    } else if (auto *c = dynamic_cast<const WaitPurificationClause *>(clause_ptr)) {
      /*
        SET msg_index -1
        SET seq_no -1
        SET msg_count -1
        SET qubit_id -1
      LOOP:
        INC msg_index
        GET_MESSAGE_SEQ msg_index seq_no
        BRANCH_IF_MESSAGE_FOUND FOUND_MESSAGE
        RET COND_FAILED
      FOUND_MESSAGE:
        COUNT_MESSAGE seq_no msg_count
        BEQ FIND_QUBIT msg_count 2
        JMP LOOP
      FIND_QUBIT:
        GET_QUBIT_BY_SEQ_NO qubit_id partner_addr seq_no
        BRANCH_IF_QUBIT_FOUND FOUND_QUBIT
        JMP LOOP
      FOUND_QUBIT:
        STORE "purification_<shared_rule_tag>_seq_no" seq_no
        RET COND_PASSED
      */
      auto msg_index = RegId::REG0;
      auto seq_no = RegId::REG1;
      auto msg_count = RegId::REG2;
      auto qubit_id = RegId::REG3;
      MemoryKey key{"purification_" + std::to_string(c->shared_rule_tag) + "_seq_no"};

      Label loop_label{std::string("LOOP_") + std::to_string(i)};
      Label found_message_label{std::string("FOUND_MESSAGE_") + std::to_string(i)};
      Label find_qubit_label{std::string("FIND_QUBIT_") + std::to_string(i)};
      Label found_qubit_label{std::string("FOUND_QUBIT_") + std::to_string(i)};
      // variable init
      opcodes.push_back(INSTR_SET_RegId_int_{{msg_index, -1}});
      opcodes.push_back(INSTR_SET_RegId_int_{{seq_no, -1}});
      opcodes.push_back(INSTR_SET_RegId_int_{{msg_count, -1}});
      opcodes.push_back(INSTR_SET_RegId_int_{{qubit_id, -1}});
      // LOOP
      opcodes.push_back(INSTR_INC_RegId_{{msg_index}, {loop_label}});
      opcodes.push_back(INSTR_GET_MESSAGE_SEQ_RegId_RegId_{{msg_index, seq_no}});
      opcodes.push_back(INSTR_BRANCH_IF_MESSAGE_FOUND_Label_{found_message_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});
      // FOUND_MESSAGE
      opcodes.push_back(INSTR_COUNT_MESSAGE_RegId_RegId_{{seq_no, msg_count}, found_message_label});
      opcodes.push_back(INSTR_BEQ_Label_RegId_int_{{find_qubit_label, msg_count, 2}});
      opcodes.push_back(INSTR_JMP_Label_{loop_label});
      // FIND_QUBIT
      opcodes.push_back(INSTR_GET_QUBIT_BY_SEQ_NO_RegId_QNodeAddr_RegId_{{qubit_id, c->partner_address, seq_no}, find_qubit_label});
      opcodes.push_back(INSTR_BRANCH_IF_QUBIT_FOUND_Label_{found_qubit_label});
      opcodes.push_back(INSTR_JMP_Label_{loop_label});
      // FOUND_QUBIT
      opcodes.push_back(INSTR_STORE_MemoryKey_RegId_{{key, seq_no}, found_qubit_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_PASSED});

    } else if (auto *c = dynamic_cast<const WaitSwappingClause *>(clause_ptr)) {
      /*
        SET msg_index -1
        SET seq_no -1
        SET msg_count -1
        SET qubit_id -1
      LOOP:
        INC msg_index
        GET_MESSAGE_SEQ msg_index seq_no
        BRANCH_IF_MESSAGE_FOUND FIND_QUBIT
        RET COND_FAILED
      FIND_QUBIT:
        GET_QUBIT_BY_SEQ_NO qubit_id partner_addr seq_no
        BRANCH_IF_QUBIT_FOUND FOUND_QUBIT
        JMP LOOP
      FOUND_QUBIT:
        STORE "swapping_<shared_rule_tag>_seq_no" seq_no
        RET COND_PASSED
      */
      auto msg_index = RegId::REG0;
      auto seq_no = RegId::REG1;
      auto msg_count = RegId::REG2;
      auto qubit_id = RegId::REG3;
      MemoryKey key{"swapping_" + std::to_string(c->shared_rule_tag) + "_seq_no"};

      Label loop_label{std::string("LOOP_") + std::to_string(i)};
      Label found_message_label{std::string("FOUND_MESSAGE_") + std::to_string(i)};
      Label find_qubit_label{std::string("FIND_QUBIT_") + std::to_string(i)};
      Label found_qubit_label{std::string("FOUND_QUBIT_") + std::to_string(i)};
      // variable init
      opcodes.push_back(INSTR_SET_RegId_int_{{msg_index, -1}});
      opcodes.push_back(INSTR_SET_RegId_int_{{seq_no, -1}});
      opcodes.push_back(INSTR_SET_RegId_int_{{msg_count, -1}});
      opcodes.push_back(INSTR_SET_RegId_int_{{qubit_id, -1}});
      // LOOP
      opcodes.push_back(INSTR_INC_RegId_{{msg_index}, {loop_label}});
      opcodes.push_back(INSTR_GET_MESSAGE_SEQ_RegId_RegId_{{msg_index, seq_no}});
      opcodes.push_back(INSTR_BRANCH_IF_MESSAGE_FOUND_Label_{find_qubit_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});
      // FIND_QUBIT
      opcodes.push_back(INSTR_GET_QUBIT_BY_SEQ_NO_RegId_QNodeAddr_RegId_{{qubit_id, c->partner_address, seq_no}, find_qubit_label});
      opcodes.push_back(INSTR_BRANCH_IF_QUBIT_FOUND_Label_{found_qubit_label});
      opcodes.push_back(INSTR_JMP_Label_{loop_label});
      // FOUND_QUBIT
      opcodes.push_back(INSTR_STORE_MemoryKey_RegId_{{key, seq_no}, found_qubit_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_PASSED});
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
      MemoryKey count_key{"measure_count" + std::to_string(i)};
      Label passed_label{std::string("PASSED_") + std::to_string(i)};
      opcodes.push_back(INSTR_LOAD_RegId_MemoryKey_{{count, count_key}});
      opcodes.push_back(INSTR_BLT_Label_RegId_int_{{passed_label, count, c->num_measure}});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});
      opcodes.push_back(INSTR_INC_RegId_{count, passed_label});
      opcodes.push_back(INSTR_STORE_MemoryKey_RegId_{{count_key, count}});
      name += "MeasureCountCondition ";
    }
  }
  opcodes.push_back(INSTR_RET_ReturnCode_{{ReturnCode::COND_PASSED}});
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
  if (auto *act = dynamic_cast<const WaitPurification *>(data)) {
    return constructWaitPurificationAction(act);
  }
  if (auto *act = dynamic_cast<const WaitSwapping *>(data)) {
    return constructWaitSwappingAction(act);
  }

  throw std::runtime_error("got invalid actions");
  return Program{"empty", {}};
}

Program RuleSetConverter::constructEntanglementSwappingAction(const EntanglementSwapping *act) {
  /*
  GET_QUBIT q0 left_partner 0
  GET_QUBIT q1 right_partner 0
  GATE_CNOTE q0 q1
  MEASURE r0 q0
  MEASURE r1 q1
  FREE_QUBIT q0
  FREE_QUBIT q1
  SEND_SWAPPING_RESULT
  */
  auto left_interface = act->qnic_interfaces.at(0);
  auto right_interface = act->qnic_interfaces.at(1);
  QubitId q0{0};
  QubitId q1{1};
  QNodeAddr left_partner_addr{left_interface.partner_addr};
  QNodeAddr right_partner_addr{right_interface.partner_addr};
  MemoryKey result_left{"result_left"};
  MemoryKey result_right{"result_right"};
  auto op_left = RegId::REG0;
  auto op_right = RegId::REG1;

  return Program{
      "EntanglementSwapping",
      {
          // clang-format off
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, left_partner_addr, 0}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, right_partner_addr, 0}},
INSTR_GATE_CNOT_QubitId_QubitId_{{q0, q1}},
INSTR_MEASURE_MemoryKey_QubitId_Basis_{{result_left, q0, Basis::X}},
INSTR_MEASURE_MemoryKey_QubitId_Basis_{{result_right, q1, Basis::Z}},
INSTR_FREE_QUBIT_QubitId_{q0},
INSTR_FREE_QUBIT_QubitId_{q1},
INSTR_LOAD_LEFT_OP_RegId_MemoryKey_{{op_left, result_left}},
INSTR_LOAD_RIGHT_OP_RegId_MemoryKey_{{op_right, result_right}},
INSTR_SEND_SWAPPING_RESULT_QNodeAddr_RegId_QNodeAddr_RegId_{{left_partner_addr, op_left, right_partner_addr, op_right}},
          // clang-format on
      },
  };
}
Program RuleSetConverter::constructPurificationAction(const Purification *act) {
  auto pur_type = act->purification_type;
  if (pur_type == rules::PurType::SINGLE_X || pur_type == rules::PurType::SINGLE_Z || pur_type == rules::PurType::SINGLE_Y) {
    /*
    SET action_index 0
    LOAD action_index "action_index_{partner_addr}"
    GET_QUBIT qubit partner_addr 0
    GET_QUBIT trash_qubit partner_addr 1
    PURIFY_X/Z measure_result qubit trash_qubit
    FREE_QUBIT trash_qubit
    LOCK_QUBIT qubit action_index
    SEND_PURIFICATION_RESULT partner_addr measure_result action_index
    INC action_index
    STORE "action_index_{partner_addr}" action_index
    */
    QubitId qubit{0};
    QubitId trash_qubit{1};
    RegId measure_result = RegId::REG0;
    RegId action_index = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey action_index_key{"action_index_" + std::to_string(interface.partner_addr)};
    MemoryKey qubit_index_key{"qubit_index"};
    MemoryKey trash_qubit_index_key{"trash_qubit_index"};

    std::string program_name;
    if (pur_type == rules::PurType::SINGLE_X) {
      program_name = "X Purification";
    } else if (pur_type == rules::PurType::SINGLE_Y) {
      program_name = "Y Purification";
    } else {
      program_name = "Z Purification";
    }

    return Program{program_name,
                   {
                       // clang-format off
INSTR_SET_RegId_int_{{action_index, 0}},
INSTR_LOAD_RegId_MemoryKey_{{action_index, action_index_key}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit, partner_addr, 1}},
(pur_type == rules::PurType::SINGLE_X) /* else SINGLE_Z */?
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result, qubit, trash_qubit}} :
  (pur_type == rules::PurType::SINGLE_Z) ?
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result, qubit, trash_qubit}} :
  (InstructionTypes)INSTR_PURIFY_Y_RegId_QubitId_QubitId_{{measure_result, qubit, trash_qubit}},
INSTR_LOCK_QUBIT_QubitId_RegId_{{qubit, action_index}},
INSTR_FREE_QUBIT_QubitId_{{trash_qubit}},
// TODO: SEND PURIFICATION RESULT
INSTR_INC_RegId_{action_index},
INSTR_STORE_MemoryKey_RegId_{{action_index_key, action_index}},
                       // clang-format on
                   }};
  }

  // https://arxiv.org/abs/0811.2639
  if (pur_type == rules::PurType::DOUBLE || pur_type == rules::PurType::DOUBLE_INV) {
    /*
    SET action_index 0
    LOAD action_index "action_index_{partner_addr}"
    GET_QUBIT qubit partner_addr 0
    GET_QUBIT trash_qubit_x partner_addr 1
    GET_QUBIT trash_qubit_z partner_addr 2
    PURIFY_X measure_result_x qubit trash_qubit_x
    PURIFY_Z measure_result_z qubit trash_qubit_z
    FREE_QUBIT trash_qubit_x
    FREE_QUBIT trash_qubit_z
    LOCK_QUBIT qubit action_index
    SEND_PURIFICATION_RESULT partner_addr measure_result action_index
    INC action_index
    STORE "action_index_{partner_addr}" action_index
    */
    QubitId qubit{0};
    QubitId trash_qubit_x{1};
    QubitId trash_qubit_z{2};
    RegId measure_result_x = RegId::REG0;
    RegId measure_result_z = RegId::REG2;
    RegId action_index = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey action_index_key{"action_index_double_" + std::to_string(interface.partner_addr)};
    MemoryKey qubit_index_key{"qubit_index"};
    MemoryKey trash_qubit_index_key{"trash_qubit_index"};

    return Program{
        "Double Purification",
        {
            // clang-format off
INSTR_SET_RegId_int_{{action_index, 0}},
INSTR_LOAD_RegId_MemoryKey_{{action_index, action_index_key}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_x, partner_addr, 1}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_z, partner_addr, 2}},
(pur_type == rules::PurType::DOUBLE) /* else DOUBLE_INV */?
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, qubit, trash_qubit_x}} :
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, qubit, trash_qubit_z}},
(pur_type == rules::PurType::DOUBLE) /* else DOUBLE_INV */?
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, qubit, trash_qubit_z}} :
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, qubit, trash_qubit_x}},
INSTR_LOCK_QUBIT_QubitId_RegId_{{qubit, action_index}},
INSTR_FREE_QUBIT_QubitId_{{trash_qubit_x}},
INSTR_FREE_QUBIT_QubitId_{{trash_qubit_z}},
// TODO: SEND PURIFICATION RESULT
INSTR_INC_RegId_{action_index},
INSTR_STORE_MemoryKey_RegId_{{action_index_key, action_index}},
            // clang-format on
        }};
  }

  if (pur_type == rules::PurType::DSSA || pur_type == rules::PurType::DSSA_INV) {
    /*
  SET action_index 0
  LOAD action_index "action_index_{partner_addr}"
  GET_QUBIT qubit partner_addr 0
  GET_QUBIT trash_qubit_x partner_addr 1
  GET_QUBIT trash_qubit_z partner_addr 2
#if DSSA:
  PURIFY_X measure_result_x qubit trash_qubit_x
  PURIFY_Z measure_result_z trash_qubit_x trash_qubit_z
#elseif DSSA_INV:
  PURIFY_Z measure_result_z qubit trash_qubit_z
  PURIFY_X measure_result_x trash_qubit_z trash_qubit_x
#endif:
  FREE_QUBIT trash_qubit_x
  FREE_QUBIT trash_qubit_z
  LOCK_QUBIT qubit action_index
  SEND_PURIFICATION_RESULT partner_addr measure_result action_index
  INC action_index
  STORE "action_index_{partner_addr}" action_index
  */
    QubitId qubit{0};
    QubitId trash_qubit_x{1};
    QubitId trash_qubit_z{2};
    RegId measure_result_x = RegId::REG0;
    RegId measure_result_z = RegId::REG2;
    RegId action_index = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey action_index_key{"action_index_dssa_" + std::to_string(interface.partner_addr)};
    MemoryKey qubit_index_key{"qubit_index"};
    MemoryKey trash_qubit_index_key{"trash_qubit_index"};

    return Program{
        "Double Selection Purification",
        {
            // clang-format off
INSTR_SET_RegId_int_{{action_index, 0}},
INSTR_LOAD_RegId_MemoryKey_{{action_index, action_index_key}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_x, partner_addr, 1}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_z, partner_addr, 2}},
(pur_type == rules::PurType::DSSA) /* else DSSA_INV */?
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, qubit, trash_qubit_x}} :
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, qubit, trash_qubit_z}},
(pur_type == rules::PurType::DSSA) /* else DSSA_INV */?
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, trash_qubit_x, trash_qubit_z}} :
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, trash_qubit_z, trash_qubit_x}},
INSTR_LOCK_QUBIT_QubitId_RegId_{{qubit, action_index}},
INSTR_FREE_QUBIT_QubitId_{{trash_qubit_x}},
INSTR_FREE_QUBIT_QubitId_{{trash_qubit_z}},
// TODO: SEND PURIFICATION RESULT
INSTR_INC_RegId_{action_index},
INSTR_STORE_MemoryKey_RegId_{{action_index_key, action_index}},
            // clang-format on
        }};
  }

  if (pur_type == rules::PurType::DSDA_SECOND || pur_type == rules::PurType::DSDA_SECOND_INV) {
    /*
  SET action_index 0
  LOAD action_index "action_index_{partner_addr}"
  GET_QUBIT qubit partner_addr 0
  GET_QUBIT trash_qubit_x partner_addr 1
  GET_QUBIT trash_qubit_z partner_addr 2
  GET_QUBIT ds_trash_qubit partner_addr 3
#if DSDA_SECOND:
  PURIFY_X measure_result_x     qubit         trash_qubit_x
  PURIFY_Z measure_result_z     qubit         trash_qubit_z
  PURIFY_X ds_measure_result  trash_qubit_z ds_trash_qubit
#elseif DSSA_INV:
  PURIFY_Z measure_result_x     qubit         trash_qubit_z
  PURIFY_X measure_result_z     qubit         trash_qubit_x
  PURIFY_Z ds_measure_result  trash_qubit_z ds_trash_qubit
#endif:
  FREE_QUBIT trash_qubit_x
  FREE_QUBIT trash_qubit_z
  FREE_QUBIT ds_trash_qubit_z
  LOCK_QUBIT qubit action_index
  SEND_PURIFICATION_RESULT partner_addr measure_result_z measure_result_x ds_measure_result_z action_index
  INC action_index
  STORE "action_index_{partner_addr}" action_index
  */
    QubitId qubit{0};
    QubitId trash_qubit_x{1};
    QubitId trash_qubit_z{2};
    QubitId ds_trash_qubit{3};
    RegId measure_result_x = RegId::REG0;
    RegId measure_result_z = RegId::REG2;
    RegId ds_measure_result = RegId::REG3;
    RegId action_index = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey action_index_key{"action_index_dssa_" + std::to_string(interface.partner_addr)};
    MemoryKey qubit_index_key{"qubit_index"};
    MemoryKey trash_qubit_index_key{"trash_qubit_index"};

    return Program{
        "Double Selection Purification",
        {
            // clang-format off
INSTR_SET_RegId_int_{{action_index, 0}},
INSTR_LOAD_RegId_MemoryKey_{{action_index, action_index_key}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_x, partner_addr, 1}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_z, partner_addr, 2}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{ds_trash_qubit, partner_addr, 3}},
(pur_type == rules::PurType::DSDA_SECOND) /* else DSDA_SECOND_INV */?
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, qubit, trash_qubit_x}} :
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, qubit, trash_qubit_z}},
(pur_type == rules::PurType::DSDA_SECOND) /* else DSDA_SECOND_INV */?
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, qubit, trash_qubit_z}} :
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, qubit, trash_qubit_x}},
(pur_type == rules::PurType::DSDA_SECOND) /* else DSDA_SECOND_INV */?
  (InstructionTypes)INSTR_PURIFY_X_RegId_QubitId_QubitId_{{ds_measure_result, trash_qubit_z, ds_trash_qubit}} :
  (InstructionTypes)INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{ds_measure_result, trash_qubit_x, ds_trash_qubit}},
INSTR_LOCK_QUBIT_QubitId_RegId_{{qubit, action_index}},
INSTR_FREE_QUBIT_QubitId_{{trash_qubit_x}},
INSTR_FREE_QUBIT_QubitId_{{trash_qubit_z}},
INSTR_FREE_QUBIT_QubitId_{{ds_trash_qubit}},
// TODO: SEND PURIFICATION RESULT
INSTR_INC_RegId_{action_index},
INSTR_STORE_MemoryKey_RegId_{{action_index_key, action_index}},
            // clang-format on
        }};
  }

  if (pur_type == rules::PurType::DSDA || pur_type == rules::PurType::DSDA_INV) {
    /*
   SET action_index 0
   LOAD action_index "action_index_{partner_addr}"
   GET_QUBIT qubit partner_addr 0
   GET_QUBIT trash_qubit_x partner_addr 1
   GET_QUBIT trash_qubit_z partner_addr 2
   GET_QUBIT ds_trash_qubit_x partner_addr 3
   GET_QUBIT ds_trash_qubit_z partner_addr 4
 #if DSDA:
   PURIFY_X measure_result_x qubit trash_qubit_x
   PURIFY_Z ds_measure_result_z trash_qubit_x ds_trash_qubit_z
   PURIFY_Z measure_result_z qubit trash_qubit_z
   PURIFY_X ds_measure_result_x trash_qubit_z ds_trash_qubit_x
 #elseif DSDA_INV:
   PURIFY_Z measure_result_z qubit trash_qubit_z
   PURIFY_X ds_measure_result_x trash_qubit_z ds_trash_qubit_x
   PURIFY_X measure_result_x qubit trash_qubit_x
   PURIFY_Z ds_measure_result_z trash_qubit_x ds_trash_qubit_z
 #endif
   FREE_QUBIT trash_qubit_x
   FREE_QUBIT trash_qubit_z
   FREE_QUBIT ds_trash_qubit_x
   FREE_QUBIT ds_trash_qubit_z
   LOCK_QUBIT qubit action_index
   SEND_PURIFICATION_RESULT partner_addr measure_result_z measure_result_x ds_measure_result_z ds_measure_result_x action_index
   INC action_index
   STORE "action_index_{partner_addr}" action_index
   */
    QubitId qubit{0};
    QubitId trash_qubit_x{1};
    QubitId trash_qubit_z{2};
    QubitId ds_trash_qubit_x{3};
    QubitId ds_trash_qubit_z{4};
    RegId measure_result_x = RegId::REG0;
    RegId measure_result_z = RegId::REG2;
    RegId ds_measure_result_x = RegId::REG3;
    RegId ds_measure_result_z = RegId::REG4;
    RegId action_index = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey action_index_key{"action_index_dsda_" + std::to_string(interface.partner_addr)};
    MemoryKey qubit_index_key{"qubit_index"};
    MemoryKey trash_qubit_index_key{"trash_qubit_index"};
    std::string action_name = "Double Selection Dual Action";
    std::vector<InstructionTypes> opcodes = {
        INSTR_SET_RegId_int_{{action_index, 0}},
        INSTR_LOAD_RegId_MemoryKey_{{action_index, action_index_key}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_x, partner_addr, 1}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_z, partner_addr, 2}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{ds_trash_qubit_x, partner_addr, 3}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{ds_trash_qubit_z, partner_addr, 4}},
    };

    std::vector<InstructionTypes> v;
    if (pur_type == rules::PurType::DSDA) {
      v = {
          INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, qubit, trash_qubit_x}},
          INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{ds_measure_result_z, trash_qubit_x, ds_trash_qubit_z}},
          INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, qubit, trash_qubit_z}},
          INSTR_PURIFY_X_RegId_QubitId_QubitId_{{ds_measure_result_x, trash_qubit_z, ds_trash_qubit_x}},
      };
    } else {  // DSDA_INV
      action_name += "_INV";
      v = {
          INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{measure_result_z, qubit, trash_qubit_z}},
          INSTR_PURIFY_X_RegId_QubitId_QubitId_{{ds_measure_result_x, trash_qubit_z, ds_trash_qubit_x}},
          INSTR_PURIFY_X_RegId_QubitId_QubitId_{{measure_result_x, qubit, trash_qubit_x}},
          INSTR_PURIFY_Z_RegId_QubitId_QubitId_{{ds_measure_result_z, trash_qubit_x, ds_trash_qubit_z}},
      };
    }
    opcodes.insert(opcodes.end(), v.begin(), v.end());
    v = {
        INSTR_LOCK_QUBIT_QubitId_RegId_{{qubit, action_index}},
        INSTR_FREE_QUBIT_QubitId_{{trash_qubit_x}},
        INSTR_FREE_QUBIT_QubitId_{{trash_qubit_z}},
        INSTR_FREE_QUBIT_QubitId_{{ds_trash_qubit_x}},
        INSTR_FREE_QUBIT_QubitId_{{ds_trash_qubit_z}},
        // TODO: SEND PURIFICATION RESULT
        INSTR_INC_RegId_{action_index},
        INSTR_STORE_MemoryKey_RegId_{{action_index_key, action_index}},
    };
    opcodes.insert(opcodes.end(), v.begin(), v.end());

    return Program{action_name, opcodes};
  }

  std::cout << const_cast<Purification *>(act)->serialize_json() << std::endl;
  throw std::runtime_error("pur not implemented");
  return Program{"Purification", {}};
}

Program RuleSetConverter::constructWaitPurificationAction(const WaitPurification *act) {
  /*

  */
  return Program{"Wait_Purification", {}};
}

Program RuleSetConverter::constructWaitSwappingAction(const WaitSwapping *act) { return Program{"Wait_Swapping", {}}; }

Program RuleSetConverter::constructTomographyAction(const Tomography *act) {
  /*
  LOAD count "count"
  GET_QUBIT q0 partner_addr qubit_resource_index
  BRANCH_IF_QUBIT_FOUND QUBIT_FOUND
  RET ERROR
QUBIT_FOUND:
  MEASURE_RONDOM "outcome" q0
  INC count
  STORE "count" count
  FREE_QUBIT q0
  SEND_LINK_TOMOGRAPHY_RESULT partner_addr count "outcome" max_count
  */
  QubitId q0{0};
  MemoryKey outcome_key{"outcome"};
  MemoryKey count_key{"count"};
  Label qubit_found_label{"qubit_found"};
  auto count = RegId::REG0;
  int max_count = act->num_measurement;
  auto &qnic = act->qnic_interfaces.at(0);
  QNodeAddr partner_addr = qnic.partner_addr;
  auto qubit_resource_index = 0;
  simtime_t start_time = act->start_time;
  if (start_time == -1) {
    start_time = simTime();
  }
  return Program{
      "Tomography",
      {
          // clang-format off
INSTR_LOAD_RegId_MemoryKey_{{count, count_key}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, qubit_resource_index}},
INSTR_BRANCH_IF_QUBIT_FOUND_Label_{qubit_found_label},
INSTR_ERROR_String_{"Qubit not found for mesaurement"},
INSTR_MEASURE_RANDOM_MemoryKey_QubitId_{{outcome_key, q0}, qubit_found_label},
INSTR_INC_RegId_{count},
INSTR_STORE_MemoryKey_RegId_{{count_key, count}},
INSTR_FREE_QUBIT_QubitId_{q0},
INSTR_SEND_LINK_TOMOGRAPHY_RESULT_QNodeAddr_RegId_MemoryKey_int_Time_{{partner_addr, count, outcome_key, max_count, start_time}}
          // clang-format on
      },
  };
}
}  // namespace quisp::rules::rs_converter
