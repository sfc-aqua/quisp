#pragma once
#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

#include "InstructionVisitor.h"
#include "RuleSet.h"
#include "macro_utils.h"

#include "Value.h"
#include "opcode.h"
#include "types.h"

namespace quisp::runtime {

struct RuntimeError {
  RuntimeError(std::string msg, int pc) : message(msg), pc(pc) {}
  std::string message;
  int pc;
  bool caught = false;
};

struct Register {
  const String name;
  unsigned long long value = 0;
};

struct QubitResourceHash {
  size_t operator()(const std::pair<QNodeAddr, int>& p) const {
    auto seed = std::hash<int>()(p.first.val);
    // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
    seed ^= std::hash<int>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

// (partner's qnode addr, assigned RuleId) => [half bell pair qubit record]
using QubitResources = std::unordered_multimap<std::pair<QNodeAddr, RuleId>, IQubitRecord*, QubitResourceHash>;

using QubitNameMap = std::unordered_map<QubitId, IQubitRecord*>;
using LabelMap = std::unordered_map<Label, int>;

using Memory = std::unordered_map<MemoryKey, MemoryValue>;

class Runtime {
 public:
  struct ICallBack {
    virtual ~ICallBack() {}

    // // Resource Preparations
    // void validate() {}

    // // Quantum Operations
    // void gate() {}
    virtual MeasurementOutcome measureQubitRandomly(IQubitRecord*) = 0;
    virtual void gateX(IQubitRecord*) = 0;
    virtual void gateZ(IQubitRecord*) = 0;

    // // Messaging
    virtual void sendLinkTomographyResult(QNodeAddr partner_addr, int count, MeasurementOutcome outcome, bool is_finished) = 0;

    // // Post processing
    virtual void freeAndResetQubit(IQubitRecord*) = 0;
    // void update() {}
  };

  Runtime();
  Runtime(const Runtime&);
  Runtime(const RuleSet& ruleset, ICallBack* callback);
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
  void storeVal(MemoryKey, MemoryValue);
  void loadVal(MemoryKey, RegId);
  MemoryValue loadVal(MemoryKey);
  void measureQubit(QubitId, MemoryKey, Basis);
  void freeQubit(QubitId);
  void gateX(QubitId);
  void gateZ(QubitId);

  // related components
  InstructionVisitor visitor;
  ICallBack* callback;

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
  Memory memory;
  bool debugging = false;
  bool should_exit = false;
  RuleSet ruleset;
  std::set<QNodeAddr> partners;
};
}  // namespace quisp::runtime
