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
#include "modules/QRSA/QRSA.h"
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {

using IQubitRecord = quisp::modules::qrsa::IQubitRecord;

struct RuntimeError {
  RuntimeError(std::string msg, int pc) : message(msg), pc(pc) {}
  std::string message;
  int pc;
};

struct Register {
  const String name;
  unsigned long long value;
};

struct Flags {
  bool test_result;
};

struct Hash {
  size_t operator()(const std::pair<int, int>& p) const {
    auto seed = std::hash<int>()(p.first);
    // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
    seed ^= std::hash<int>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

// (partner's qnode addr, assigned RuleId) => [half bell pair qubit record]
using QubitResources = std::unordered_multimap<std::pair<QNodeAddr, RuleId>, IQubitRecord*, Hash>;
using QubitNameMap = std::unordered_map<QubitId, IQubitRecord*>;
using LabelMap = std::unordered_map<Label, int>;

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
  void collectLabels(Program& program);
  void debugRuntimeState();

  // operations used by InstructionVisitor
  const Register& getReg(RegId regId) const;
  unsigned long long getRegVal(RegId regId) const;
  void setRegVal(RegId regId, unsigned long long val);
  void setQubit(IQubitRecord*, QubitId);
  IQubitRecord* getQubitByPartnerAddr(QNodeAddr, int);
  IQubitRecord* getQubitByQubitId(QubitId) const;
  void jumpTo(const Label&);
  void setError(const String& message);

  // related components
  InstructionVisitor visitor;
  ICallBack* rule_engine;

  // states
  /// @brief current rule evaluated
  RuleId rule_id = -1;
  /// @brief program counter for execution
  unsigned int pc = 0;
  Register registers[4];
  QubitResources qubits;
  QubitNameMap named_qubits;
  RuntimeError* error = nullptr;
  LabelMap label_map;
};
}  // namespace quisp::runtime
