#include "Runtime.h"
#include <cstddef>
#include <stdexcept>
#include <variant>

namespace quisp::runtime {

Runtime::Runtime() : visitor(InstructionVisitor{this}) {}
Runtime::~Runtime() {}

void Runtime::exec(RuleSet ruleset) {
  this->error = nullptr;
  for (auto& rule : ruleset.rules) {
    rule_id = rule.id;
    eval(rule.condition);
    if (error != nullptr) {
      break;
    }
    eval(rule.action);
  }
}

void Runtime::eval(Program& program) {
  collectLabels(program);
  auto& opcodes = program.opcodes;
  auto len = opcodes.size();
  for (pc = 0; pc < len; pc++) {
    if (debugging) {
      debugRuntimeState();
      std::cout << "op: " << std::visit([](auto& op) { return op.toString(); }, opcodes[pc]) << std::endl;
    }
    evalOperation(opcodes[pc]);
  }
}

void Runtime::cleanup() {
  for (auto& reg : registers) {
    reg.value = (unsigned long long)0;
  }
  pc = 0;
  error = nullptr;
}

void Runtime::collectLabels(Program& program) {
  auto& opcodes = program.opcodes;
  auto len = opcodes.size();
  for (pc = 0; pc < len; pc++) {
    auto op = opcodes[pc];
    auto label = std::visit([](auto& o) { return o.label; }, op);
    if (label.size() > 0) {
      label_map.insert({label, pc});
    }
  }
}

void Runtime::evalOperation(InstructionTypes instruction) { std::visit(visitor, instruction); }
void Runtime::assignQubitToRuleSet(QNodeAddr partner_addr, IQubitRecord* qubit_record) { qubits.emplace(std::make_pair(partner_addr, 0), qubit_record); }
const Register& Runtime::getReg(RegId regId) const { return registers[(int)regId]; }
unsigned long long Runtime::getRegVal(RegId regId) const { return registers[(int)regId].value; }
void Runtime::setRegVal(RegId regId, unsigned long long val) { registers[(int)regId].value = val; }
void Runtime::setQubit(IQubitRecord* qubit_ref, QubitId qubit_id) { named_qubits.emplace(qubit_id, qubit_ref); }
IQubitRecord* Runtime::getQubitByPartnerAddr(QNodeAddr partner_addr, int index) {
  auto it = qubits.find({partner_addr, rule_id});
  for (int i = 0; it != qubits.cend(); it++, i++) {
    if (i == index) return it->second;
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
  auto it = label_map.find(label);
  if (it != label_map.end()) {
    // pc will be incremeted before executing the next line
    pc = it->second - 1;
  }
}

void Runtime::setError(const String& message) { error = new RuntimeError(message, pc); }

void Runtime::storeVal(MemoryKey key, MemoryValue val) { memory.insert_or_assign(key, val); }
void Runtime::loadVal(MemoryKey key, RegId reg_id) {
  auto it = memory.find(key);
  if (it == memory.end()) return;
  setRegVal(reg_id, it->second.intValue);
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
    auto outcome = rule_engine->measureQubitRandomly(qubit_ref);
    storeVal(memory_key, MemoryValue{outcome});
    return;
  }
  std::runtime_error("measure qubit with the specified basis is not implemented yet");
}

void Runtime::freeQubit(QubitId qubit_id) {
  auto qubit_ref = getQubitByQubitId(qubit_id);
  if (qubit_ref == nullptr) {
    return;
  }
  rule_engine->freeAndResetQubit(qubit_ref);
}

void Runtime::debugRuntimeState() {
  std::cout << "\n-----debug-runtime-state------"
            << "\npc: " << pc << "\nrule_id: " << rule_id << "\nRegisters:"
            << "\n  Reg0: " << registers[0].value << "\n  Reg1: " << registers[1].value << "\n  Reg2: " << registers[2].value << "\n  Reg3: " << registers[3].value
            << "\n--memory--\n";
  for (auto it : memory) {
    std::cout << it.first << ": " << it.second.intValue << std::endl;
  }
  std::cout << "error: " << (error == nullptr ? "nullptr" : error->message);
  std::cout << "\n--------" << std::endl;
}
};  // namespace quisp::runtime
