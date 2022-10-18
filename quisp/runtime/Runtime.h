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

// (partner's qnode addr, assigned RuleId) => [half bell pair qubit record]
using QubitResources = std::unordered_multimap<std::pair<QNodeAddr, RuleId>, IQubitRecord*>;

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
    virtual void gateCNOT(IQubitRecord* control_qubit_rec, IQubitRecord* target_qubit_rec) = 0;
    virtual bool purifyX(IQubitRecord* qubit_rec, IQubitRecord* trash_qubit_rec) = 0;
    virtual bool purifyZ(IQubitRecord* qubit_rec, IQubitRecord* trash_qubit_rec) = 0;
    // // Messaging
    virtual void sendLinkTomographyResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, int count,
                                          MeasurementOutcome outcome, bool is_finished) = 0;
    virtual void sendPurificationResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, bool result) = 0;

    // // Post processing
    virtual void freeAndResetQubit(IQubitRecord*) = 0;
    // void update() {}

    virtual bool isQubitLocked(IQubitRecord* const) = 0;
    virtual void lockQubit(IQubitRecord* const, unsigned long rs_id, int rule_id, int action_index) = 0;
  };

  Runtime();
  Runtime(const Runtime&);
  Runtime(const RuleSet& ruleset, ICallBack* callback);
  ~Runtime();
  void assignRuleSet(const RuleSet& ruleset);
  void cleanup();
  void exec(const RuleSet& ruleset);
  void eval(const Program& program);
  void evalOperation(InstructionTypes op);
  void assignQubitToRuleSet(QNodeAddr partner_addr, IQubitRecord* qubit_record);
  void assignQubitToRule(QNodeAddr partner_addr, RuleId rule_id, IQubitRecord* qubit_record);
  void collectLabels(const Program& program);
  void debugRuntimeState();
  void promoteQubit(QubitResources::iterator);

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
  void gateCNOT(QubitId, QubitId);
  void purifyX(QubitId, QubitId);
  void purifyZ(QubitId, QubitId);
  bool isQubitLocked(IQubitRecord* const);

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
  ReturnCode return_code = ReturnCode::NONE;
};
}  // namespace quisp::runtime
