#include <stdexcept>
#include <variant>

#include "InstructionVisitor.h"
#include "Runtime.h"
#include "Value.h"
#include "omnetpp/cexception.h"
#include "types.h"

namespace quisp::runtime {

Runtime::Runtime(const Runtime& rt) : Runtime() {
  visitor = rt.visitor;
  visitor.runtime = this;
  callback = rt.callback;
  rule_id = rt.rule_id;
  qubits = rt.qubits;
  memory = rt.memory;
  ruleset = rt.ruleset;
  partners = rt.partners;
  terminated = rt.terminated;
  debugging = rt.debugging;
}

Runtime::Runtime() : visitor(InstructionVisitor{this}) {}
Runtime::Runtime(const RuleSet& ruleset, ICallBack* cb) : visitor(InstructionVisitor{this}), callback(cb) { assignRuleSet(ruleset); }
Runtime& Runtime::operator=(Runtime&& rt) {
  visitor = rt.visitor;
  visitor.runtime = this;
  callback = rt.callback;
  rule_id = rt.rule_id;
  qubits = std::move(rt.qubits);
  memory = std::move(rt.memory);
  ruleset = std::move(rt.ruleset);
  partners = std::move(rt.partners);
  terminated = rt.terminated;
  debugging = rt.debugging;
  return *this;
}
Runtime::~Runtime() {}

void Runtime::exec() {
  if (terminated) return;
  cleanup();
  debugging = ruleset.debugging;
  if (debugging) {
    std::cout << "Run RuleSet: " << ruleset.name << "\n";
  }
  for (auto& rule : ruleset.rules) {
    rule_id = rule.id;
    debugging = rule.debugging || ruleset.debugging;
    while (true) {
      if (debugging) {
        debugRuntimeState();
        std::cout << "Run Rule(" << rule.id << "): " << rule.name << ", " << callback->getNodeInfo() << "\n";
      }
      execProgram(rule.condition);
      if (debugging) std::cout << return_code << std::endl;
      if (return_code == ReturnCode::COND_FAILED) {
        break;
      }
      execProgram(rule.action);
      execProgram(ruleset.termination_condition);
      if (return_code == ReturnCode::RS_TERMINATED) {
        terminated = true;
        return;
      }
    }
  }
}

void Runtime::execProgram(const Program& program) {
  label_map = &program.label_map;
  auto& opcodes = program.opcodes;
  auto len = opcodes.size();

  cleanup();
  for (pc = 0; pc < len; pc++) {
    if (should_exit) break;
    if (program.debugging || debugging) {
      debugSource(program);
      debugRuntimeState();
    }
    execInstruction(opcodes[pc]);
  }

  if (program.debugging || debugging) {
    debugRuntimeState();
  }

  if (return_code == ReturnCode::ERROR) {
    std::cout << "Uncaught Error >>>>>> " << callback->getNodeInfo() << std::endl;
    debugRuntimeState();
    debugSource(program);
    throw std::runtime_error("uncaught error");
  }
}

void Runtime::cleanup() {
  for (auto& reg : registers) {
    reg.value = 0;
  }
  pc = 0;
  named_qubits.clear();
  should_exit = false;
  qubit_found = false;
  return_code = ReturnCode::NONE;
}

void Runtime::execInstruction(const InstructionTypes& instruction) { std::visit(visitor, instruction); }

void Runtime::assignRuleSet(const RuleSet& rs) {
  ruleset = rs;
  ruleset.finalize();
  partners = ruleset.partners;
}

void Runtime::assignQubitToRuleSet(QNodeAddr partner_addr, IQubitRecord* qubit_record) {
  auto it = ruleset.partner_initial_rule_table.find(partner_addr);
  assert(it != ruleset.partner_initial_rule_table.end());
  qubits.emplace(std::make_pair(partner_addr, it->second), qubit_record);
}

QubitResources::iterator Runtime::findQubit(int target_rule_id, int shared_tag, int action_index) {
  runtime::QubitResources::iterator qubit_key;
  for (auto it = qubits.begin(); it != qubits.end(); it++) {
    auto& [addr, current_rule_id] = it->first;
    if (current_rule_id != target_rule_id) continue;
    if (callback->getActionIndex(it->second) == action_index) {
      return it;
    }
  }
  throw cRuntimeError("Qubit not found: (rule_id: %d, shared_tag: %d, action_index: %d)", target_rule_id, shared_tag, action_index);
}

void Runtime::promoteQubit(QubitResources::iterator iter) {
  auto [partner_addr, current_rule_id] = iter->first;
  auto it = ruleset.next_rule_table.find({partner_addr, current_rule_id});
  assert(it != ruleset.next_rule_table.end());
  auto next_rule_id = it->second;
  auto* qubit = iter->second;
  qubits.erase(iter);
  qubits.emplace(std::make_pair(partner_addr, next_rule_id), qubit);
}
void Runtime::promoteQubitWithNewPartner(IQubitRecord* qubit_record, QNodeAddr new_partner_addr) {
  QubitResources::iterator qubit_iter;
  bool found = false;
  for (auto it = qubits.begin(); it != qubits.end(); it++) {
    if (it->second == qubit_record) {
      qubit_iter = it;
      found = true;
      break;
    }
  }
  assert(found);
  qubits.erase(qubit_iter);
  auto it = ruleset.partner_initial_rule_table.find(new_partner_addr);
  assert(it != ruleset.partner_initial_rule_table.end());
  auto next_rule_id = it->second;
  qubits.emplace(std::make_pair(new_partner_addr, next_rule_id), qubit_record);
}
void Runtime::assignQubitToRule(QNodeAddr partner_addr, RuleId rule_id, IQubitRecord* qubit_record) { qubits.emplace(std::make_pair(partner_addr, rule_id), qubit_record); }
const Register& Runtime::getReg(RegId reg_id) const { return registers[(int)reg_id]; }
int32_t Runtime::getRegVal(RegId reg_id) const { return registers[(int)reg_id].value; }
void Runtime::setRegVal(RegId reg_id, int32_t val) { registers[(int)reg_id].value = val; }
void Runtime::setQubit(IQubitRecord* qubit_ref, QubitId qubit_id) {
  assert(qubit_ref != nullptr);
  named_qubits.insert({qubit_id, qubit_ref});
}

IQubitRecord* Runtime::getQubitByPartnerAddr(QNodeAddr partner_addr, int index) {
  int i = 0;
  for (auto it = qubits.begin(); it != qubits.end(); it++) {
    if (it->first.first == partner_addr && it->first.second == rule_id && !callback->isQubitLocked(it->second)) {
      if (index == i) return it->second;
      i++;
    }
  }
  return nullptr;
}

IQubitRecord* Runtime::getQubitByQubitId(QubitId id) const {
  auto it = named_qubits.find(id);
  if (it != named_qubits.end()) {
    return it->second;
  }
  return nullptr;
}

void Runtime::jumpTo(const Label& label) {
  auto it = label_map->find(label);
  if (it != label_map->end()) {
    // pc will be incremeted before executing the next line
    pc = it->second - 1;
  }
}

void Runtime::storeVal(MemoryKey key, MemoryValue val) { memory.insert_or_assign(key, val); }
void Runtime::loadVal(MemoryKey key, RegId reg_id) {
  auto it = memory.find(key);
  if (it != memory.end()) {
    setRegVal(reg_id, it->second.intValue());
  }
}

MemoryValue Runtime::loadVal(MemoryKey key) {
  auto it = memory.find(key);
  if (it == memory.end()) throw std::runtime_error("the value is empty for the key");
  return it->second;
}

void Runtime::measureQubit(QubitId qubit_id, MemoryKey memory_key, Basis basis) {
  auto qubit_ref = getQubitByQubitId(qubit_id);
  if (qubit_ref == nullptr) {
    return;
  }
  if (basis == Basis::RANDOM) {
    auto outcome = callback->measureQubitRandomly(qubit_ref);
    storeVal(memory_key, MemoryValue{outcome});
    return;
  }
  if (basis == Basis::X) {
    storeVal(memory_key, MemoryValue(callback->measureQubitX(qubit_ref)));
    return;
  }
  if (basis == Basis::Z) {
    storeVal(memory_key, MemoryValue(callback->measureQubitZ(qubit_ref)));
    return;
  }
  std::runtime_error("measure qubit with the specified basis is not implemented yet");
}

void Runtime::freeQubit(QubitId qubit_id) {
  auto qubit_ref = getQubitByQubitId(qubit_id);
  if (qubit_ref == nullptr) {
    return;
  }
  callback->freeAndResetQubit(qubit_ref);
  auto named_qubit = named_qubits.find(qubit_id);
  named_qubits.erase(named_qubit);
  for (auto i = qubits.begin(); i != qubits.end(); i++) {
    if (i->second == qubit_ref) {
      qubits.erase(i);
      return;
    }
  }
  throw std::runtime_error("unknown qubit_ref");
}

void Runtime::gateX(QubitId qubit_id) {
  auto qubit_ref = getQubitByQubitId(qubit_id);
  if (qubit_ref == nullptr) {
    return;
  }
  callback->gateX(qubit_ref);
}

void Runtime::gateZ(QubitId qubit_id) {
  auto qubit_ref = getQubitByQubitId(qubit_id);
  if (qubit_ref == nullptr) {
    return;
  }
  callback->gateZ(qubit_ref);
}

void Runtime::gateY(QubitId qubit_id) {
  auto qubit_ref = getQubitByQubitId(qubit_id);
  if (qubit_ref == nullptr) {
    return;
  }
  callback->gateY(qubit_ref);
}

void Runtime::gateCNOT(QubitId control_qubit_id, QubitId target_qubit_id) {
  auto control_qubit = getQubitByQubitId(control_qubit_id);
  auto target_qubit = getQubitByQubitId(target_qubit_id);
  if (control_qubit == nullptr) return;
  if (target_qubit == nullptr) return;
  callback->gateCNOT(control_qubit, target_qubit);
}

void Runtime::purifyX(RegId result_reg_id, QubitId qubit_id, QubitId trash_qubit_id) {
  auto qubit = getQubitByQubitId(qubit_id);
  auto trash_qubit = getQubitByQubitId(trash_qubit_id);
  if (qubit == nullptr) return;
  if (trash_qubit == nullptr) return;
  bool result = callback->purifyX(qubit, trash_qubit);
  setRegVal(result_reg_id, result);
}

void Runtime::purifyZ(RegId result_reg_id, QubitId qubit_id, QubitId trash_qubit_id) {
  auto qubit = getQubitByQubitId(qubit_id);
  auto trash_qubit = getQubitByQubitId(trash_qubit_id);
  if (qubit == nullptr) return;
  if (trash_qubit == nullptr) return;
  bool result = callback->purifyZ(qubit, trash_qubit);
  setRegVal(result_reg_id, result);
}

void Runtime::purifyY(RegId result_reg_id, QubitId qubit_id, QubitId trash_qubit_id) {
  auto qubit = getQubitByQubitId(qubit_id);
  auto trash_qubit = getQubitByQubitId(trash_qubit_id);
  if (qubit == nullptr) return;
  if (trash_qubit == nullptr) return;
  bool result = callback->purifyY(qubit, trash_qubit);
  setRegVal(result_reg_id, result);
}

bool Runtime::isQubitLocked(IQubitRecord* const qubit) { return callback->isQubitLocked(qubit); }
void Runtime::debugRuntimeState() {
  std::cout << "\n---------runtime-state---------"
            << "\npc: " << pc << ", rule_id: " << rule_id << ", qubit_found: " << (qubit_found ? "true" : "false");
  std::cout << "\nReg0: " << registers[0].value << ", Reg1: " << registers[1].value << ", Reg2: " << registers[2].value << ", Reg3: " << registers[3].value
            << ", Reg4: " << registers[4].value << "\n----------memory------------\n";
  for (auto it : memory) {
    std::cout << "  " << it.first << ": " << it.second << "\n";
  }
  std::cout << "\n----------qubits---------\n";
  for (auto& [key, qubit] : qubits) {
    //// (partner's qnode addr, assigned RuleId) => [local half of the bell pair qubit record]
    auto& [partner_addr, rule_id] = key;
    auto locked = callback->isQubitLocked(qubit);
    std::cout << "  Qubit(qnic:" << qubit->getQNicIndex() << ", qubit_index:" << qubit->getQubitIndex() << "):" << partner_addr << " rule_id:" << rule_id << ", locked:" << locked
              << ", busy:" << qubit->isBusy() << "\n";
  }

  std::cout << "\n--------named-qubits---------\n";
  for (auto& [qubit_id, qubit] : named_qubits) {
    std::cout << "  QubitId(" << qubit_id.val << "): Qubit(qnic: " << qubit->getQNicIndex() << ", index: " << qubit->getQubitIndex() << "):\n";
  }
  std::cout << "----------------------------------------\n\n" << std::endl;
}

void Runtime::debugSource(const Program& program) const {
  auto len = program.opcodes.size();
  std::cout << program.name << " " << callback->getNodeInfo() << "\n";
  for (int i = 0; i < len; i++) {
    std::cout << (i == pc ? "  >>" : "    ") << std::to_string(i) << ": " << std::visit([](auto& op) { return op.toString(); }, program.opcodes[i]) << "\n";
  }
  std::cout << std::flush;
}

std::string Runtime::debugInstruction(const InstructionTypes& instr) const {
  return std::visit([](auto& op) { return op.toString(); }, instr);
}
};  // namespace quisp::runtime
