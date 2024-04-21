#include "RuleSetConverter.h"

#include <stdexcept>
#include <string>
#include <vector>

#include <omnetpp.h>

#include "runtime/Runtime.h"
#include "runtime/opcode.h"

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
    rs.rules.emplace_back(Rule{name, rule_data->send_tag, rule_data->receive_tag, condition, action});
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
    } else if (auto *c = dynamic_cast<const PurificationCorrelationClause *>(clause_ptr)) {
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
      opcodes.push_back(INSTR_GET_MESSAGE_SEQ_RegId_RegId_{{seq_no, msg_index}});
      opcodes.push_back(INSTR_BRANCH_IF_MESSAGE_FOUND_Label_{found_message_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});
      // FOUND_MESSAGE
      opcodes.push_back(INSTR_COUNT_MESSAGE_RegId_RegId_{{msg_count, seq_no}, found_message_label});
      opcodes.push_back(INSTR_BEQ_Label_RegId_int_{{find_qubit_label, msg_count, 2}});
      opcodes.push_back(INSTR_JMP_Label_{loop_label});
      // FIND_QUBIT
      opcodes.push_back(INSTR_GET_QUBIT_BY_SEQ_NO_RegId_QNodeAddr_RegId_{{qubit_id, c->partner_address, seq_no}, find_qubit_label});
      opcodes.push_back(INSTR_BRANCH_IF_QUBIT_FOUND_Label_{found_qubit_label});
      opcodes.push_back(INSTR_JMP_Label_{loop_label});
      // FOUND_QUBIT
      opcodes.push_back(INSTR_STORE_MemoryKey_RegId_{{key, seq_no}, found_qubit_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_PASSED});

      name += "PurificationCorrelation ";
    } else if (auto *c = dynamic_cast<const SwappingCorrectionClause *>(clause_ptr)) {
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
      opcodes.push_back(INSTR_GET_MESSAGE_SEQ_RegId_RegId_{{seq_no, msg_index}});
      opcodes.push_back(INSTR_BRANCH_IF_MESSAGE_FOUND_Label_{find_qubit_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_FAILED});
      // FIND_QUBIT
      opcodes.push_back(INSTR_GET_QUBIT_BY_SEQ_NO_RegId_QNodeAddr_RegId_{{qubit_id, c->partner_address, seq_no}, find_qubit_label});
      opcodes.push_back(INSTR_BRANCH_IF_QUBIT_FOUND_Label_{found_qubit_label});
      opcodes.push_back(INSTR_JMP_Label_{loop_label});
      // FOUND_QUBIT
      opcodes.push_back(INSTR_STORE_MemoryKey_RegId_{{key, seq_no}, found_qubit_label});
      opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::COND_PASSED});

      name += "SwappingCorrection ";
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
  if (auto *act = dynamic_cast<const PurificationCorrelation *>(data)) {
    return constructPurificationCorrelationAction(act);
  }
  if (auto *act = dynamic_cast<const SwappingCorrection *>(data)) {
    return constructSwappingCorrectionAction(act);
  }

  throw std::runtime_error("got invalid actions");
  return Program{"empty", {}};
}

Program RuleSetConverter::constructEntanglementSwappingAction(const EntanglementSwapping *act) {
  /*
    qubit: q0, q1
    reg: pauli_op_left, pauli_op_right, seq_no
    key: "sent_swap_message_{shared_rule}"
  START
    SET pauli_op_left  0
    SET pauli_op_right 0
    SET seq_no 1
    LOAD seq_no "sent_swap_message_{shared_rule}" // if the key has not been set the value stays as is
    GET_QUBIT q0 left_partner  0
    GET_QUBIT q1 right_partner 0
    GATE_CNOT q0 q1
    MEASURE pauli_op_left 0 q0 x
    MEASURE pauli_op_left 1 q1 z
    FREE_QUBIT q0
    FREE_QUBIT q1
    SEND_SWAPPING_RESULT left_partner right_partner pauli_op_left  seq_no
    SEND_SWAPPING_RESULT right_partner left_partner pauli_op_right seq_no
    INC seq_no
    STORE "sent_swap_message_{shared_rule}" seq_no
  */
  auto left_interface = act->qnic_interfaces.at(0);
  auto right_interface = act->qnic_interfaces.at(1);
  QubitId q0{0};
  QubitId q1{1};
  QNodeAddr left_partner_addr{left_interface.partner_addr};
  QNodeAddr right_partner_addr{right_interface.partner_addr};
  RegId op_left = RegId::REG0;
  RegId op_right = RegId::REG1;
  RegId seq_no = RegId::REG2;
  MemoryKey seq_key{"sent_swap_message_" + std::to_string(act->shared_rule_tag)};

  std::vector<InstructionTypes> opcodes = {
      // clang-format off
    INSTR_SET_RegId_int_{{op_left, 0}},
    INSTR_SET_RegId_int_{{op_right, 0}},
    INSTR_SET_RegId_int_{{seq_no, 1}},
    INSTR_LOAD_RegId_MemoryKey_{{seq_no, seq_key}},
    INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, left_partner_addr, 0}},
    INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q1, right_partner_addr, 0}},
    INSTR_GATE_CNOT_QubitId_QubitId_{{q0, q1}},
    INSTR_MEASURE_RegId_int_QubitId_Basis_{{op_left, 0, q0, Basis::X}},
    INSTR_MEASURE_RegId_int_QubitId_Basis_{{op_left, 1, q1, Basis::Z}},
    INSTR_FREE_QUBIT_QubitId_{{q0}},
    INSTR_FREE_QUBIT_QubitId_{{q1}},
    INSTR_SEND_SWAPPING_RESULT_QNodeAddr_RegId_QNodeAddr_RegId_{{left_partner_addr, op_left, right_partner_addr, seq_no}},
    INSTR_SEND_SWAPPING_RESULT_QNodeAddr_RegId_QNodeAddr_RegId_{{right_partner_addr, op_right, left_partner_addr, seq_no}},
    INSTR_INC_RegId_{{seq_no}},
    INSTR_STORE_MemoryKey_RegId_{{seq_key, seq_no}}
      // clang-format on
  };
  return Program{
      "EntanglementSwapping",
      opcodes,
  };
}
Program RuleSetConverter::constructPurificationAction(const Purification *act) {
  auto pur_type = act->purification_type;
  if (pur_type == rules::PurType::SINGLE_SELECTION_X_PURIFICATION || pur_type == rules::PurType::SINGLE_SELECTION_Z_PURIFICATION ||
      pur_type == rules::PurType::SINGLE_SELECTION_Y_PURIFICATION) {
    /*
      qubitId: qubit, trash_qubit
      Reg: result, seq_no // the sequence number of the qubit in the next rule
    START:
      SET seq_no 1 // sequence_number starts at 1
      LOAD seq_no "sent_purification_message_{shared_rule}" // if it has not been set the value stays as is
      GET_QUBIT qubit partner_addr 0
      GET_QUBIT trash_qubit partner_addr 1
      PURIFY_X/Y/Z result qubit trash_qubit // perform the circuit [0/1] as output
      PROMOTE qubit
      FREE_QUBIT trash_qubit // free the measured qubits
      SEND_PURIFICATION_RESULT partner_addr result seq_no
      INC seq_no
      STORE "sent_purificaiton_message_{shared_rule}" seq_no
    */
    QubitId qubit{0};
    QubitId trash_qubit{1};
    RegId measure_result = RegId::REG0;
    RegId seq_no = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey seq_no_key{"sent_purification_message_" + std::to_string(act->shared_rule_tag)};

    std::string program_name;
    InstructionTypes purify_instruction = (InstructionTypes)INSTR_PURIFY_X_RegId_int_QubitId_QubitId_{{measure_result, 0, qubit, trash_qubit}};
    if (pur_type == rules::PurType::SINGLE_SELECTION_X_PURIFICATION) {
      purify_instruction = (InstructionTypes)INSTR_PURIFY_X_RegId_int_QubitId_QubitId_{{measure_result, 0, qubit, trash_qubit}};
      program_name = "X Purification";
    } else if (pur_type == rules::PurType::SINGLE_SELECTION_Y_PURIFICATION) {
      program_name = "Y Purification";
      purify_instruction = (InstructionTypes)INSTR_PURIFY_Y_RegId_int_QubitId_QubitId_{{measure_result, 0, qubit, trash_qubit}};
    } else {
      program_name = "Z Purification";
      purify_instruction = (InstructionTypes)INSTR_PURIFY_Z_RegId_int_QubitId_QubitId_{{measure_result, 0, qubit, trash_qubit}};
    }
    std::vector<InstructionTypes> opcodes{
        INSTR_SET_RegId_int_{{seq_no, 1}},
        INSTR_LOAD_RegId_MemoryKey_{{seq_no, seq_no_key}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit, partner_addr, 1}},
        purify_instruction,
        INSTR_PROMOTE_QubitId_{{qubit}},
        INSTR_FREE_QUBIT_QubitId_{{trash_qubit}},
        INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_RegId_PurType_{{partner_addr, measure_result, seq_no, pur_type}},
        INSTR_INC_RegId_{seq_no},
        INSTR_STORE_MemoryKey_RegId_{{seq_no_key, seq_no}},
    };
    return Program{program_name, opcodes};
  }

  // single selection double purification;
  // (i.e., reducing both X & Z errors but without checking error propagation from trash_qubits back to keep qubit)
  if (pur_type == rules::PurType::SINGLE_SELECTION_XZ_PURIFICATION || pur_type == rules::PurType::SINGLE_SELECTION_ZX_PURIFICATION) {
    /*
      qubitId: qubit, trash_qubit_x, trash_qubit_z
      Reg: result, seq_no // the sequence number of the qubit in the next rule
    START:
      SET seq_no 1 // sequence_number starts at 1
      LOAD seq_no "sent_purification_message_{shared_rule}" // if it has not been set the value stays as is
      GET_QUBIT qubit partner_addr 0
      GET_QUBIT trash_qubit_x partner_addr 1
      GET_QUBIT trash_qubit_z partner_addr 2
      # if SINGLE_SELECTION_XZ_PURIFICATION:
        PURIFY_X result 0 qubit trash_qubit_x
        PURIFY_Z result 1 qubit trash_qubit_z
      # else: // just change the order, no reason to also change the bitset index
        PURIFY_Z result 1 qubit trash_qubit_z
        PURIFY_X result 0 qubit trash_qubit_x
      PROMOTE qubit
      FREE_QUBIT trash_qubit_x
      FREE_QUBIT trash_qubit_z
      SEND_PURIFICATION_RESULT partner_addr result seq_no
      INC seq_no
      STORE "sent_purificaiton_message_{shared_rule}" seq_no
    */
    QubitId qubit{0};
    QubitId trash_qubit_x{1};
    QubitId trash_qubit_z{2};
    RegId measure_result = RegId::REG0;
    RegId seq_no = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey seq_no_key{"sent_purification_message_" + std::to_string(act->shared_rule_tag)};

    std::string program_name = "Single Selection Double Purification XZ";
    InstructionTypes purify_instruction_1 = (InstructionTypes)INSTR_PURIFY_X_RegId_int_QubitId_QubitId_{{measure_result, 0, qubit, trash_qubit_x}};
    InstructionTypes purify_instruction_2 = (InstructionTypes)INSTR_PURIFY_Z_RegId_int_QubitId_QubitId_{{measure_result, 1, qubit, trash_qubit_z}};
    ;
    if (pur_type == rules::PurType::SINGLE_SELECTION_ZX_PURIFICATION) {
      program_name = "Single Selection Double Purification ZX (Inverse)";
      std::swap(purify_instruction_1, purify_instruction_2);
    }
    std::vector<InstructionTypes> opcodes{
        INSTR_SET_RegId_int_{{seq_no, 1}},
        INSTR_LOAD_RegId_MemoryKey_{{seq_no, seq_no_key}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_x, partner_addr, 1}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_z, partner_addr, 2}},
        purify_instruction_1,
        purify_instruction_2,
        INSTR_PROMOTE_QubitId_{{qubit}},
        INSTR_FREE_QUBIT_QubitId_{{trash_qubit_x}},
        INSTR_FREE_QUBIT_QubitId_{{trash_qubit_z}},
        INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_RegId_PurType_{{partner_addr, measure_result, seq_no, pur_type}},
        INSTR_INC_RegId_{seq_no},
        INSTR_STORE_MemoryKey_RegId_{{seq_no_key, seq_no}},
    };
    return Program{program_name, opcodes};
  }

  // https://arxiv.org/abs/0811.2639 (Fujii & Yamamoto double selection (single error) purification)
  // The naming is misleading,
  // TODO: change purification type naming
  // DOUBLE_SELECTION_XZ_PURIFICATION -> double selection X purification
  // DOUBLE_SELECTION_ZX_PURIFICATION -> double selection Z purification
  if (pur_type == rules::PurType::DOUBLE_SELECTION_X_PURIFICATION || pur_type == rules::PurType::DOUBLE_SELECTION_Z_PURIFICATION) {
    /*
      qubitId: qubit, trash_qubit_z, trash_qubit_x
      Reg: result, seq_no // the sequence number of the qubit in the next rule
    START:
      SET seq_no 1 // sequence_number starts at 1
      LOAD seq_no "sent_purification_message_{shared_rule}" // if it has not been set the value stays as is
      GET_QUBIT qubit partner_addr 0
      GET_QUBIT trash_qubit_z partner_addr 1
      GET_QUBIT trash_qubit_x partner_addr 1
      # if DOUBLE_SELECTION_X_PURIFICATION (double selection X purification) :
        CNOT qubit trash_qubit_z
        CNOT trash_qubit_x trash_qubit_z
        MEASURE result 0 trash_qubit_z Z
        MEASURE result 1 trash_qubit_x X
      # if DOUBLE_SELECTION_Z_PURIFICATION (double selection Z purification):
        CNOT trash_qubit_x qubit
        CNOT trash_qubit_x trash_qubit_z
        MEASURE result 0 trash_qubit_z Z
        MEASURE result 1 trash_qubit_x X
      PROMOTE qubit
      FREE_QUBIT trash_qubit_z
      FREE_QUBIT trash_qubit_x
      SEND_PURIFICATION_RESULT partner_addr result seq_no
      INC seq_no
      STORE "sent_purificaiton_message_{shared_rule}" seq_no
    */
    QubitId qubit{0};
    QubitId trash_qubit_z{1};
    QubitId trash_qubit_x{2};
    RegId measure_result = RegId::REG0;
    RegId seq_no = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey seq_no_key{"sent_purification_message_" + std::to_string(act->shared_rule_tag)};

    std::string program_name = "Double Selection Single Purification X";
    InstructionTypes first_cnot = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{qubit, trash_qubit_z}};
    if (pur_type == rules::PurType::DOUBLE_SELECTION_Z_PURIFICATION) {
      program_name = "Double Selection Single Purification Z";
      first_cnot = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{trash_qubit_x, qubit}};
    }
    std::vector<InstructionTypes> opcodes{
        INSTR_SET_RegId_int_{{seq_no, 1}},
        INSTR_LOAD_RegId_MemoryKey_{{seq_no, seq_no_key}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_z, partner_addr, 1}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{trash_qubit_x, partner_addr, 2}},
        first_cnot,
        INSTR_GATE_CNOT_QubitId_QubitId_{{trash_qubit_x, trash_qubit_z}},
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 0, trash_qubit_z, Basis::Z}},
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 1, trash_qubit_x, Basis::X}},
        INSTR_PROMOTE_QubitId_{{qubit}},
        INSTR_FREE_QUBIT_QubitId_{{trash_qubit_z}},
        INSTR_FREE_QUBIT_QubitId_{{trash_qubit_x}},
        INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_RegId_PurType_{{partner_addr, measure_result, seq_no, pur_type}},
        INSTR_INC_RegId_{seq_no},
        INSTR_STORE_MemoryKey_RegId_{{seq_no_key, seq_no}},
    };
    return Program{program_name, opcodes};
  }

  if (pur_type == rules::PurType::DOUBLE_SELECTION_X_PURIFICATION_SINGLE_SELECTION_Z_PURIFICATION ||
      pur_type == rules::PurType::DOUBLE_SELECTION_Z_PURIFICATION_SINGLE_SELECTION_X_PURIFICATION) {
    /*
      qubitId: qubit, dssp_z, dssp_x, sssp_q;
      Reg: result, seq_no // the sequence number of the qubit in the next rule
    START:
      SET seq_no 1 // sequence_number starts at 1
      LOAD seq_no "sent_purification_message_{shared_rule}" // if it has not been set the value stays as is
      GET_QUBIT qubit partner_addr 0
      GET_QUBIT dssp_z partner_addr 1
      GET_QUBIT dssp_x partner_addr 2
      GET_QUBIT sssp_q  partner_addr 3
      # if DOUBLE_SELECTION_X_PURIFICATION_SINGLE_SELECTION_Z_PURIFICATION (double selection X purification -> single selection single purification Z) :
        CNOT qubit dssp_z               << diff
        CNOT dssp_x dssp_z
        CNOT sssp_q qubit               << diff
        MEASURE result 0 dssp_z Z
        MEASURE result 1 dssp_x X
        MEASURE result 2 sssp_q X       << diff
      # if DOUBLE_SELECTION_Z_PURIFICATION_SINGLE_SELECTION_X_PURIFICATION (double selection Z purification -> double selection single purification X):
        CNOT dssp_x qubit               << diff
        CNOT dssp_x dssp_z
        CNOT qubit sssp_q               << diff
        MEASURE result 0 dssp_z Z
        MEASURE result 1 dssp_x X
        MEASURE result 2 sssp_q Z       << diff
      PROMOTE qubit
      FREE_QUBIT dssp_z
      FREE_QUBIT dssp_x
      FREE_QUBIT sssp_q
      SEND_PURIFICATION_RESULT partner_addr result seq_no
      INC seq_no
      STORE "sent_purificaiton_message_{shared_rule}" seq_no
    */
    QubitId qubit{0};
    QubitId dssp_z{1};
    QubitId dssp_x{2};
    QubitId sssp_q{3};
    RegId measure_result = RegId::REG0;
    RegId seq_no = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey seq_no_key{"sent_purification_message_" + std::to_string(act->shared_rule_tag)};

    std::string program_name = "Ds-Sp X followed by Ss-Sp Z";
    InstructionTypes first_cnot = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{qubit, dssp_z}};
    InstructionTypes last_cnot = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{sssp_q, qubit}};
    InstructionTypes sssp_measure = (InstructionTypes)INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 2, sssp_q, Basis::X}};
    if (pur_type == rules::PurType::DOUBLE_SELECTION_Z_PURIFICATION_SINGLE_SELECTION_X_PURIFICATION) {
      program_name = "Ds-Sp Z followed by Ss-Sp X";
      first_cnot = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{dssp_x, qubit}};
      last_cnot = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{qubit, sssp_q}};
      sssp_measure = (InstructionTypes)INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 2, sssp_q, Basis::Z}};
    }
    std::vector<InstructionTypes> opcodes{
        INSTR_SET_RegId_int_{{seq_no, 1}},
        INSTR_LOAD_RegId_MemoryKey_{{seq_no, seq_no_key}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{dssp_z, partner_addr, 1}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{dssp_x, partner_addr, 2}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{sssp_q, partner_addr, 3}},
        first_cnot,
        INSTR_GATE_CNOT_QubitId_QubitId_{{dssp_x, dssp_z}},
        last_cnot,
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 0, dssp_z, Basis::Z}},
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 1, dssp_x, Basis::X}},
        sssp_measure,
        INSTR_PROMOTE_QubitId_{{qubit}},
        INSTR_FREE_QUBIT_QubitId_{{dssp_z}},
        INSTR_FREE_QUBIT_QubitId_{{dssp_x}},
        INSTR_FREE_QUBIT_QubitId_{{sssp_q}},
        INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_RegId_PurType_{{partner_addr, measure_result, seq_no, pur_type}},
        INSTR_INC_RegId_{seq_no},
        INSTR_STORE_MemoryKey_RegId_{{seq_no_key, seq_no}},
    };
    return Program{program_name, opcodes};
  }

  if (pur_type == rules::PurType::DOUBLE_SELECTION_XZ_PURIFICATION || pur_type == rules::PurType::DOUBLE_SELECTION_ZX_PURIFICATION) {
    /*
      qubitId: qubit, dssp_1_z, dssp_1_x, dssp_2_x, dssp_2_z;
      Reg: result, seq_no // the sequence number of the qubit in the next rule
    START:
      SET seq_no 1 // sequence_number starts at 1
      LOAD seq_no "sent_purification_message_{shared_rule}" // if it has not been set the value stays as is
      GET_QUBIT qubit partner_addr 0
      GET_QUBIT dssp_1_x partner_addr 1
      GET_QUBIT dssp_1_z partner_addr 2
      GET_QUBIT dssp_2_x partner_addr 3
      GET_QUBIT dssp_2_z partner_addr 4
      # if DOUBLE_SELECTION_XZ_PURIFICATION (double selection X purification -> double selection Z purification) :
        CNOT qubit dssp_1_z            << cnot_1
        CNOT dssp_1_x dssp_1_z         << cnot_2
        MEASURE result 0 dssp_1_z Z
        MEASURE result 1 dssp_1_x X

        CNOT dssp_2_x qubit            << cnot_3
        CNOT dssp_2_x dssp_2_z         << cnot_4
        MEASURE result 2 dssp_2_z Z
        MEASURE result 3 dssp_2_x X
      # if DOUBLE_SELECTION_ZX_PURIFICATION (double selection Z purification -> double selection X purification):
        # measurement index stay the same for simplicity
        CNOT dssp_2_x qubit            << cnot_1
        CNOT dssp_2_x dssp_2_z         << cnot_2
        MEASURE result 2 dssp_2_z Z
        MEASURE result 3 dssp_2_x X

        CNOT qubit dssp_1_z            << cnot_3
        CNOT dssp_1_x dssp_1_z         << cnot_4
        MEASURE result 0 dssp_1_z Z
        MEASURE result 1 dssp_1_x X
      PROMOTE qubit
      FREE_QUBIT dssp_1_z
      FREE_QUBIT dssp_1_x
      FREE_QUBIT dssp_2_z
      FREE_QUBIT dssp_2_x
      SEND_PURIFICATION_RESULT partner_addr result seq_no
      INC seq_no
      STORE "sent_purificaiton_message_{shared_rule}" seq_no
    */
    QubitId qubit{0};
    QubitId dssp_1_z{1};
    QubitId dssp_1_x{2};
    QubitId dssp_2_z{3};
    QubitId dssp_2_x{4};
    RegId measure_result = RegId::REG0;
    RegId seq_no = RegId::REG1;

    auto &interface = act->qnic_interfaces.at(0);
    QNodeAddr partner_addr{interface.partner_addr};
    MemoryKey seq_no_key{"sent_purification_message_" + std::to_string(act->shared_rule_tag)};

    std::string program_name = "Ds-Sp X followed by Ds-Sp Z";
    InstructionTypes cnot_1 = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{qubit, dssp_1_z}};
    InstructionTypes cnot_2 = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{dssp_1_x, dssp_1_z}};
    InstructionTypes cnot_3 = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{dssp_2_x, qubit}};
    InstructionTypes cnot_4 = (InstructionTypes)INSTR_GATE_CNOT_QubitId_QubitId_{{dssp_2_x, dssp_2_z}};
    if (pur_type == rules::PurType::DOUBLE_SELECTION_X_PURIFICATION_SINGLE_SELECTION_Z_PURIFICATION) {
      program_name = "Ds-Sp Z followed by Ds-Sp Z";
      std::swap(cnot_1, cnot_3);
      std::swap(cnot_2, cnot_4);
    }
    std::vector<InstructionTypes> opcodes{
        INSTR_SET_RegId_int_{{seq_no, 1}},
        INSTR_LOAD_RegId_MemoryKey_{{seq_no, seq_no_key}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{qubit, partner_addr, 0}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{dssp_1_z, partner_addr, 1}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{dssp_1_x, partner_addr, 2}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{dssp_2_z, partner_addr, 3}},
        INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{dssp_2_x, partner_addr, 4}},
        cnot_1,
        cnot_2,
        cnot_3,
        cnot_4,
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 0, dssp_1_z, Basis::Z}},
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 1, dssp_1_x, Basis::X}},
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 3, dssp_2_z, Basis::Z}},
        INSTR_MEASURE_RegId_int_QubitId_Basis_{{measure_result, 4, dssp_2_x, Basis::X}},
        INSTR_PROMOTE_QubitId_{{qubit}},
        INSTR_FREE_QUBIT_QubitId_{{dssp_1_z}},
        INSTR_FREE_QUBIT_QubitId_{{dssp_1_x}},
        INSTR_FREE_QUBIT_QubitId_{{dssp_2_z}},
        INSTR_FREE_QUBIT_QubitId_{{dssp_2_x}},
        INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_RegId_PurType_{{partner_addr, measure_result, seq_no, pur_type}},
        INSTR_INC_RegId_{seq_no},
        INSTR_STORE_MemoryKey_RegId_{{seq_no_key, seq_no}},
    };
    return Program{program_name, opcodes};
  };

  std::cout << const_cast<Purification *>(act)->serialize_json() << std::endl;
  throw std::runtime_error("pur not implemented");
  return Program{"Purification", {}};
}

Program RuleSetConverter::constructPurificationCorrelationAction(const PurificationCorrelation *act) {
  /*
    qubit_id: qubit
    Reg: seq_no, result_0, result_1
  START
    LOAD seq_no "purification_<shared_rule_tag>_seq_no"
    GET_QUBIT_BY_SEQ_NO q0 <partner_addr> seq
    GET_MESSAGE seq_no 0 result_0
    GET_MESSAGE seq_no 1 result_1
    DELETE_MESSAGE seq_no
    BEQ RESULT_MATCH result_0 result_1
    FREE_QUBIT q0
    RET NONE // result not match
  RESULT_MATCH:
    PROMOTE q0
  */
  // init
  QubitId qubit{0};
  auto seq_no = RegId::REG0;
  auto result_0 = RegId::REG1;
  auto result_1 = RegId::REG2;
  QNodeAddr partner_address = act->qnic_interfaces[0].partner_addr;
  MemoryKey key{"purification_" + std::to_string(act->shared_rule_tag) + "_seq_no"};
  // label
  Label result_match_label{"result_match"};
  Label result_not_match_label{"result_not_match"};
  // start of program
  std::vector<InstructionTypes> opcodes;
  opcodes.push_back(INSTR_LOAD_RegId_MemoryKey_{{seq_no, key}});
  opcodes.push_back(INSTR_GET_QUBIT_BY_SEQ_NO_QubitId_QNodeAddr_RegId_{{qubit, partner_address, seq_no}});
  opcodes.push_back(INSTR_GET_MESSAGE_RegId_RegId_int_{{result_0, seq_no, 0}});
  opcodes.push_back(INSTR_GET_MESSAGE_RegId_RegId_int_{{result_1, seq_no, 1}});
  opcodes.push_back(INSTR_DELETE_MESSAGE_RegId_{seq_no});
  opcodes.push_back(INSTR_BEQ_Label_RegId_RegId_{{result_match_label, result_0, result_1}});
  opcodes.push_back(INSTR_FREE_QUBIT_QubitId_{qubit});
  opcodes.push_back(INSTR_RET_ReturnCode_{ReturnCode::NONE});
  // RESULT MATCH
  opcodes.push_back(INSTR_PROMOTE_QubitId_{qubit, result_match_label});
  return Program{"PurificationCorrelation", opcodes};
}

Program RuleSetConverter::constructSwappingCorrectionAction(const SwappingCorrection *act) {
  /*
    qubit_id: qubit
    Reg: seq_no, pauli_op, new_partner_addr
  // start of the program
    LOAD seq_no "swapping_<shared_rule_tag>_seq_no"
    GET_QUBIT_BY_SEQ_NO q0 <partner_addr> seq
    GET_MESSAGE seq_no 0 pauli_op new_partner_addr
    DELETE_MESSAGE seq_no
    BEQ PAULI_Z pauli_op 1
    BEQ PAULI_X pauli_op 2
    BEQ PAULI_Y pauli_op 3
    JMP UPDATE_PARTER
  PAULI_Z
    GATE_Z qubit
    JMP UPDATE_PARTNER
  PAULI_X
    GATE_X qubit
    JMP UPDATE_PARTNER
  PAULI_Y
    GATE_Y qubit
  UPDATE_PARTNER
    PROMOTE qubit new_partner_addr
  */
  QubitId qubit{0};
  auto seq_no = RegId::REG0;
  auto pauli_op = RegId::REG1;
  auto new_partner_addr = RegId::REG2;
  QNodeAddr partner_address = act->qnic_interfaces[0].partner_addr;
  MemoryKey key{"swapping_" + std::to_string(act->shared_rule_tag) + "_seq_no"};
  // label
  Label pauli_x_label{"pauli_x"};
  Label pauli_y_label{"pauli_y"};
  Label pauli_z_label{"pauli_z"};
  Label update_partner_label{"update_partner"};
  // start of program
  std::vector<InstructionTypes> opcodes;
  opcodes.push_back(INSTR_LOAD_RegId_MemoryKey_{{seq_no, key}});
  opcodes.push_back(INSTR_GET_QUBIT_BY_SEQ_NO_QubitId_QNodeAddr_RegId_{{qubit, partner_address, seq_no}});
  opcodes.push_back(INSTR_GET_MESSAGE_RegId_RegId_RegId_int_{{pauli_op, new_partner_addr, seq_no, 0}});
  opcodes.push_back(INSTR_DELETE_MESSAGE_RegId_{seq_no});
  opcodes.push_back(INSTR_BEQ_Label_RegId_int_{{pauli_z_label, pauli_op, 1}});
  opcodes.push_back(INSTR_BEQ_Label_RegId_int_{{pauli_x_label, pauli_op, 2}});
  opcodes.push_back(INSTR_BEQ_Label_RegId_int_{{pauli_y_label, pauli_op, 3}});
  opcodes.push_back(INSTR_JMP_Label_{{update_partner_label}});
  // PAULI_Z
  opcodes.push_back(INSTR_GATE_Z_QubitId_{qubit, pauli_z_label});
  opcodes.push_back(INSTR_JMP_Label_{update_partner_label});
  // PAULI_X
  opcodes.push_back(INSTR_GATE_X_QubitId_{qubit, pauli_x_label});
  opcodes.push_back(INSTR_JMP_Label_{update_partner_label});
  // PAULI_Y
  opcodes.push_back(INSTR_GATE_Y_QubitId_{qubit, pauli_y_label});
  // UPDATE_PARTNER
  opcodes.push_back(INSTR_PROMOTE_QubitId_RegId_{{qubit, new_partner_addr}, update_partner_label});
  // END
  return Program{"SwappingCorrection", opcodes};
}

Program RuleSetConverter::constructTomographyAction(const Tomography *act) {
  /*
    LOAD count "count"
    GET_QUBIT q0 partner_addr qubit_resource_index
    BRANCH_IF_QUBIT_FOUND QUBIT_FOUND
    RET ERROR
  QUBIT_FOUND:
    MEASURE_RANDOM "outcome" q0
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
  INSTR_ERROR_String_{"Qubit not found for measurement"},
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
