#pragma once
#include <cstddef>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

#include "InstructionVisitor.h"
#include "RuleSet.h"
#include "macro_utils.h"
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {

struct IQubitRecord;

class RuntimeError {
 public:
  std::string message;
};

struct Register {
  const String name;
  unsigned long long value;
};

struct Flags {
  bool test_result;
};

// (partner's qnode addr, assigned RuleId) => [half bell pair qubit record]
using QubitResources = std::unordered_multimap<std::pair<QNodeAddr, RuleId>, IQubitRecord*>;
using QubitNameMap = std::unordered_map<QubitId, IQubitRecord*>;

class Runtime {
 public:
  class ICallBack {
    virtual ~ICallBack() {}

    void freeAndResetQubit(IQubitRecord*);
    // // Resource Preparations
    // void validate() {}

    // // Quantum Operations
    // void gate() {}
    // void measure() {}

    // // Messaging
    // void send() {}

    // // Post processing
    // void freeQubit() {}
    // void setNameToResource() {}
    // void update() {}
  };

  Runtime();
  ~Runtime();
  void assignRuleSet(const RuleSet& ruleset);
  void cleanup();
  void exec(RuleSet ruleset);
  void eval(Program& program);
  void evalOperation(InstructionTypes op);
  void assignQubitToRuleSet(QNodeAddr partner_addr, IQubitRecord* qubit_record);

  // operations used by InstructionVisitor
  const Register& getReg(RegId regId) const;
  unsigned long long getRegVal(RegId regId) const;
  void setRegVal(RegId regId, unsigned long long val);
  void setQubit(IQubitRecord*, QubitId);
  IQubitRecord* getQubitByPartnerAddr(QNodeAddr, int);

  // related components
  InstructionVisitor visitor;
  ICallBack* rule_engine;

  // states
  /// @brief current rule evaluated
  RuleId rule_id;
  /// @brief program counter for execution
  unsigned int pc = 0;
  Register registers[4];
  QubitResources qubits;
  QubitNameMap named_qubits;
  RuntimeError* error = nullptr;
};
}  // namespace quisp::runtime
