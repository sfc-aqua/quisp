#include <stdexcept>
#include <variant>

#include "Runtime.h"
#include "runtime/InstructionVisitor.h"
#include "runtime/Value.h"
#include "runtime/types.h"

namespace quisp::runtime {

Runtime::Runtime(const Runtime& rt) : Runtime() {
  rule_id = rt.rule_id;
  debugging = rt.debugging;
  ruleset = rt.ruleset;
  partners = rt.partners;
  callback = rt.callback;
}

Runtime::Runtime() : visitor(InstructionVisitor{this}) {}
Runtime::Runtime(const RuleSet& ruleset, ICallBack* cb) : visitor(InstructionVisitor{this}), callback(cb) { assignRuleSet(ruleset); }
Runtime::~Runtime() {}

void Runtime::exec(const RuleSet& ruleset) {
  cleanup();
  debugging = ruleset.debugging;
  if (debugging) {
    std::cout << "Run RuleSet: " << ruleset.name << "\n";
  }
  for (auto& rule : ruleset.rules) {
    rule_id = rule.id;
    debugging = rule.debugging || ruleset.debugging;
    if (debugging) {
      std::cout << "Run Rule: " << rule.name << "\n";
      debugRuntimeState();
    }
    eval(rule.condition);
    if (return_code == ReturnCode::COND_FAILED) {
      continue;
    }
    eval(rule.action);
  }
}

void Runtime::eval(const Program& program) {
  label_map = &program.label_map;
  auto& opcodes = program.opcodes;
  auto len = opcodes.size();

  cleanup();
  for (pc = 0; pc < len; pc++) {
    if (should_exit) return;
    if (program.debugging || debugging) {
      debugSource(program);
      debugRuntimeState();
    }
    evalOperation(opcodes[pc]);
  }

  if (program.debugging || debugging) {
    debugRuntimeState();
  }
  if (error != nullptr && !error->caught) {
    throw std::runtime_error("uncaught error");
  }
}

void Runtime::cleanup() {
  for (auto& reg : registers) {
    reg.value = (unsigned long long)0;
  }
  pc = 0;
  error = nullptr;
  named_qubits.clear();
  should_exit = false;
}

void Runtime::evalOperation(const InstructionTypes& instruction) { std::visit(visitor, instruction); }

void Runtime::assignRuleSet(const RuleSet& _ruleset) {
  ruleset = _ruleset;
  ruleset.finalize();
  partners = ruleset.partners;
}

void Runtime::assignQubitToRuleSet(QNodeAddr partner_addr, IQubitRecord* qubit_record) {
  auto it = ruleset.partner_initial_rule_table.find(partner_addr);
  assert(it != ruleset.partner_initial_rule_table.end());
  qubits.emplace(std::make_pair(partner_addr, it->second), qubit_record);
}

void Runtime::promoteQubit(QubitResources::iterator iter) {
  auto [partner_addr, current_rule_id] = iter->first;
  auto it = ruleset.next_rule_table.find({partner_addr, current_rule_id});
  assert(it != ruleset.next_rule_table.end());
  auto next_rule_id = it->second;
  auto& qubit = iter->second;
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
const Register& Runtime::getReg(RegId regId) const { return registers[(int)regId]; }
unsigned long long Runtime::getRegVal(RegId regId) const { return registers[(int)regId].value; }
void Runtime::setRegVal(RegId regId, unsigned long long val) { registers[(int)regId].value = val; }
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

void Runtime::setError(const String& message) { error = new RuntimeError(message, pc); }

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

void Runtime::gateCNOT(QubitId control_qubit_id, QubitId target_qubit_id) {
  auto control_qubit = getQubitByQubitId(control_qubit_id);
  auto target_qubit = getQubitByQubitId(target_qubit_id);
  if (control_qubit == nullptr) return;
  if (target_qubit == nullptr) return;
  callback->gateCNOT(control_qubit, target_qubit);
}

void Runtime::purifyX(QubitId qubit_id, QubitId trash_qubit_id) {
  auto qubit = getQubitByQubitId(qubit_id);
  auto trash_qubit = getQubitByQubitId(trash_qubit_id);
  if (qubit == nullptr) return;
  if (trash_qubit == nullptr) return;
  callback->purifyX(qubit, trash_qubit);
}

void Runtime::purifyZ(QubitId qubit_id, QubitId trash_qubit_id) {
  auto qubit = getQubitByQubitId(qubit_id);
  auto trash_qubit = getQubitByQubitId(trash_qubit_id);
  if (qubit == nullptr) return;
  if (trash_qubit == nullptr) return;
  callback->purifyZ(qubit, trash_qubit);
}

bool Runtime::isQubitLocked(IQubitRecord* const qubit) { return callback->isQubitLocked(qubit); }
void Runtime::debugRuntimeState() {
  std::cout << "\n---------runtime-state---------"
            << "\npc: " << pc << ", rule_id: " << rule_id << ", error: " << (error == nullptr ? "no error" : error->message);
  std::cout << "\nReg0: " << registers[0].value << ", Reg1: " << registers[1].value << ", Reg2: " << registers[2].value << ", Reg3: " << registers[3].value
            << "\n----------memory------------\n";
  for (auto it : memory) {
    std::cout << "  " << it.first << ": " << it.second << "\n";
  }
  std::cout << "\n----------qubits---------\n";
  for (auto& [key, qubit] : qubits) {
    //// (partner's qnode addr, assigned RuleId) => [half bell pair qubit record]
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
