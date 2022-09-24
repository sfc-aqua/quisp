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

void Runtime::debugRuntimeState() {
  std::cout << "-----debug-runtime-state------"
            << "\npc: " << pc << "\nrule_id: " << rule_id << "\nRegisters:"
            << "\n  Reg0: " << registers[0].value << "\n  Reg1: " << registers[1].value << "\n  Reg2: " << registers[2].value << "\n  Reg3: " << registers[3].value << std::endl;
}
};  // namespace quisp::runtime
