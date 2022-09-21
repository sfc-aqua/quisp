#pragma once
#include <modules/QRSA/QRSA.h>
#include <cstddef>
#include <iostream>
#include <tuple>
#include <variant>
#include <vector>

#include "InstructionVisitor.h"
#include "RuleSet.h"
#include "macro_utils.h"
#include "opcode.h"

namespace quisp::runtime {

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

class Runtime {
 public:
  class ICallBack {
    virtual ~ICallBack() {}

    void freeAndResetQubit(quisp::modules::qrsa::IQubitRecord*);
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

  void exec(RuleSet ruleset);
  void eval(Program& program);
  void evalOperation(InstructionTypes op);
  const Register& getReg(RegId regId) const;
  unsigned long long getRegVal(RegId regId) const;
  void setRegVal(RegId regId, unsigned long long val);

  unsigned int pc = 0;
  Register registers[4];
  RuntimeError* error;
  InstructionVisitor visitor;
  ICallBack* rule_engine;
};
}  // namespace quisp::runtime
