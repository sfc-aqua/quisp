#include "Runtime.h"
#include <cstddef>
#include <variant>

namespace quisp::runtime {

Runtime::Runtime() : visitor(InstructionVisitor{this}) {}
Runtime::~Runtime() {}

void Runtime::exec(RuleSet ruleset) {
  this->error = nullptr;
  for (auto& rule : ruleset.rules) {
    eval(rule.condition);
    if (error != nullptr) {
      break;
    }
    eval(rule.action);
  }
}

void Runtime::eval(Program& program) {
  pc = 0;
  auto len = program.opcodes.size();
  for (auto& op : program.opcodes) {
    evalOperation(op);
    pc++;
  }
}

void Runtime::cleanup() {
  for (auto& reg : registers) {
    reg.value = (unsigned long long)0;
  }
  pc = 0;
  error = nullptr;
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

};  // namespace quisp::runtime
