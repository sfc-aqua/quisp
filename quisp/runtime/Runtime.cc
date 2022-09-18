#include "Runtime.h"

namespace quisp::runtime {

Runtime::Runtime() : error(nullptr) {}
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
  for (auto& op : program.opcodes) {
    evalOperation(op);
  }
}

void Runtime::evalOperation(OperationType op) { std::visit(OperationVisitor{}, op); }

void OperationVisitor::operator()(Operation0 op) {
  auto [optype] = op;
  switch (optype) {
    case OpType::DEBUG:
      std::cout << "debug" << std::endl;
      break;
    case OpType::NONE:
    default:
      break;
  }
}
void OperationVisitor::operator()(Operation1 op) {}
};  // namespace quisp::runtime
