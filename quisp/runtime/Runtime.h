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
  int32_t value = 0;
};

// (partner's qnode addr, assigned RuleId) => [half bell pair qubit record]
using QubitResources = std::unordered_multimap<std::pair<QNodeAddr, RuleId>, IQubitRecord*>;

/// @brief QubitId and qubit record map. This is initialized in before each Program execution
using QubitNameMap = std::unordered_map<QubitId, IQubitRecord*>;

/// @brief Memory is a simple dict to store the value during RuleSet execution.
using Memory = std::unordered_map<MemoryKey, MemoryValue>;

/**
 * @brief Runtime class is responsible for executing the given RuleSet and the
 * states' management.
 */
class Runtime {
 public:
  /**
   * @brief ICallBack is an interface for the callback of the Runtime.
   *
   * This class is for dependency injection to decouple the Runtime and
   * RuleEngine. During the RuleSet execution, The Runtime uses this interface
   * to access RuleEngine for qubit operations and classical communications.
   * The actual implementation of this class is in RuleEngine.
   */
  struct ICallBack {
    virtual ~ICallBack() {}

    // Resource Management
    virtual void freeAndResetQubit(IQubitRecord*) = 0;
    virtual bool isQubitLocked(IQubitRecord* const) = 0;
    virtual void lockQubit(IQubitRecord* const, unsigned long rs_id, int rule_id, int action_index) = 0;

    // Quantum Operations
    virtual MeasurementOutcome measureQubitRandomly(IQubitRecord*) = 0;
    virtual MeasurementOutcome measureQubitX(IQubitRecord*) = 0;
    virtual MeasurementOutcome measureQubitZ(IQubitRecord*) = 0;
    virtual void gateX(IQubitRecord*) = 0;
    virtual void gateZ(IQubitRecord*) = 0;
    virtual void gateCNOT(IQubitRecord* control_qubit_rec, IQubitRecord* target_qubit_rec) = 0;
    virtual bool purifyX(IQubitRecord* qubit_rec, IQubitRecord* trash_qubit_rec) = 0;
    virtual bool purifyZ(IQubitRecord* qubit_rec, IQubitRecord* trash_qubit_rec) = 0;

    // Messaging
    virtual void sendLinkTomographyResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, int count,
                                          MeasurementOutcome outcome, int max_count, Time start_time) = 0;
    virtual void sendSinglePurificationResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, bool result,
                                              PurType pur_type) = 0;
    virtual void sendDoublePurificationResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, bool result_z, bool result_x,
                                              PurType pur_type) = 0;
    virtual void sendTriplePurificationResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, bool result_z, bool result_x,
                                              bool result_ds, PurType pur_type) = 0;
    virtual void sendQuadruplePurificationResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, bool result_z,
                                                 bool result_x, bool result_ds_z, bool result_ds_x, PurType pur_type) = 0;
    virtual void sendSwappingResults(const unsigned long ruleset_id, const Rule& rule, const QNodeAddr left_partner_addr, int left_op, const QNodeAddr right_partner_addr,
                                     int right_op) = 0;

    // Hack
    virtual void hackSwappingPartners(IQubitRecord* const, IQubitRecord* const) = 0;
    virtual void hackBreakEntanglement(IQubitRecord* qubit) = 0;

    // Debugging
    virtual std::string getNodeInfo() { return ""; };
  };

  Runtime();
  Runtime(const RuleSet& ruleset, ICallBack* callback);
  Runtime(const Runtime&);
  ~Runtime();

  void assignRuleSet(const RuleSet& ruleset);

  /**
   * @brief this method resets the state before each Program execution.
   */
  void cleanup();

  /// @brief execute the assigned RuleSet.
  void exec();

  /// @brief execute the given RuleSet.
  void execRuleSet(const RuleSet& ruleset);

  /// @brief execute the given Program in a Rule
  void execProgram(const Program& program);

  /// @brief execute the one Instruction
  void execInstruction(const InstructionTypes& op);

  /**
   * @brief assign the entangled qubit to the RuleSet. The Runtime assign it to
   * the first rule and the Rule can use the qubit.
   *
   * @param partner_addr the entangled partner QNode address for the qubit.
   * @param qubit_record the entangled qubit's record.
   */
  void assignQubitToRuleSet(QNodeAddr partner_addr, IQubitRecord* qubit_record);

  /**
   * @brief assign the entangled qubit to the rule
   *
   * @param partner_addr the entangled partner QNode address for the qubit.
   * @param rule_id the rule id to assign the qubit
   * @param qubit_record  the entangled qubit's record
   */
  void assignQubitToRule(QNodeAddr partner_addr, RuleId rule_id, IQubitRecord* qubit_record);

  /** @name register operations */
  //@{
  /**
   * @brief Get the Register in @ref registers by RegId
   *
   * @param reg_id
   * @return const Register&
   */
  const Register& getReg(RegId reg_id) const;

  /**
   * @brief Get the Register's value
   *
   * @param reg_id
   * @return int32_t
   */
  int32_t getRegVal(RegId reg_id) const;

  /**
   * @brief Set the given value to the Register
   *
   * @param reg_id the id for the register
   * @param val the value to set the register
   */
  void setRegVal(RegId reg_id, int32_t val);

  /**
   * @brief jump to the instruction that has the given label
   *
   * @param label label to jump.
   */
  void jumpTo(const Label& label);

  /**
   * @brief Set the RuntimeError and will stop the Program execution
   *
   * @param message the error message for debugging
   */
  void setError(const String& message);
  //@}

  /** @name memory operations */
  //@{

  /**
   * @brief store the value into memory.
   *
   * @param key
   * @param val
   */
  void storeVal(MemoryKey key, MemoryValue val);

  /**
   * @brief load the value from memory, and put it into the given register.
   *
   * @param key
   * @param reg_id
   */
  void loadVal(MemoryKey key, RegId reg_id);

  /**
   * @brief load the value from memory.
   *
   * @param key
   * @return MemoryValue
   */
  MemoryValue loadVal(MemoryKey key);
  //@}

  /** @name qubit record operations */
  //@{

  /**
   * @brief check the qubit is locked or not. Purification uses the lock state
   * in a qubit.
   *
   * @return true the qubit is locked by a Rule
   * @return false the qubit is not locked
   */
  bool isQubitLocked(IQubitRecord* const);

  /**
   * @brief Get the qubit record by partner's QNodeAddr
   *
   * This method finds an index-th qubit record entangled with the partner from
   * the @ref qubits member. If the Runtime cannot find the qubit, this returns
   * nullptr.
   * @param index
   * @return IQubitRecord*
   */
  IQubitRecord* getQubitByPartnerAddr(QNodeAddr, int index);

  /**
   * @brief Get the Qubit By QubitId
   *
   * This method finds a qubit record named with the given QubitId in
   * the @ref named_qubits member.
   *
   * @param qubit_id
   * @return IQubitRecord*
   */
  IQubitRecord* getQubitByQubitId(QubitId qubit_id) const;

  /**
   * @brief bind the assigned Qubit to the given qubit id to use it in a Program.
   *
   * @param qubit_record
   * @param qubit_id
   */
  void setQubit(IQubitRecord* qubit_record, QubitId qubit_id);

  /**
   * @brief promote the qubit to the next rule.
   *
   * the next rule id is automatically derived by the Programs in the RuleSet.
   *
   * @param it iterator to specify the qubit
   */
  void promoteQubit(QubitResources::iterator it);

  /**
   * @brief promote the qubit that has new entangled partner.
   *
   * entanglement swapping operations need the promotion of the qubit
   *
   * @param qubit_record the entangled qubit's record already assigned to the RuleSet
   * @param new_partner_addr new entangled partner's QNode address.
   */
  void promoteQubitWithNewPartner(IQubitRecord* qubit_record, QNodeAddr new_partner_addr);
  //@}

  /** @name quantum operations */
  //@{

  /**
   * @brief measure qubit with the given basis and store the result to the memory.
   *
   * @param qubit_id the measurement target qubit's id
   * @param result_key the key to store the measurement result
   * @param basis the measurement result
   */
  void measureQubit(QubitId qubit_id, MemoryKey result_key, Basis basis);

  /// @brief free qubit and release it from the Rule and the RuleSet
  void freeQubit(QubitId);

  /// @brief apply X gate
  void gateX(QubitId);

  /// @brief apply Z gate
  void gateZ(QubitId);

  /// @brief apply CNOT gate
  void gateCNOT(QubitId control_qubit_id, QubitId target_qubit_id);

  /// @brief perform X purification and store the measurement result
  void purifyX(RegId result, QubitId qubit_id, QubitId trash_qubit_id);

  /// @brief perform Z purification and store the measurement result
  void purifyZ(RegId result, QubitId qubit_id, QubitId trash_qubit_id);
  //@}

  /** @name debugging */
  //@{
  void debugRuntimeState();
  void debugSource(const Program& program) const;
  std::string debugInstruction(const InstructionTypes& instr) const;
  //@}

  /** @name related components */
  //@{
  /// @brief The visitor handles all instruction types for Program execution.
  InstructionVisitor visitor;

  /// @brief The callback provides a way to access the RuleEngine.
  ICallBack* callback;
  //@}

  /** @name states */
  //@{
  /// @brief current evaluating rule id
  RuleId rule_id = -1;

  /**
   * @brief program counter for Program execution.
   *
   * The pc points to the current instruction, and after the instruction is
   * executed, the pc will be incremented to point to the next instruction.
   * This value is changed when we want to jump or branch.
   */
  unsigned int pc = 0;

  /**
   * @brief Registers are temporary memory for Program execution.
   *
   * Before each Program execution, Runtime initializes these registers with 0.
   */
  Register registers[5];

  /**
   * @brief This stores the entangled qubits that are assigned to the ruleset.
   *
   * The key is a pair of the entangled partner's QNodeAddr and the assigned
   * RuleId. When Entanglement Swapping changes the entangled partner, we need
   * to erase the record and insert a new key with a new entangled partner.
   */
  QubitResources qubits;

  /**
   * @brief This contains a map for a QubitId and a qubit.
   *
   * The named_qubits must store the qubit in the `qubits` member.
   */
  QubitNameMap named_qubits;

  /**
   * @brief The memory contains a variety of values during the RuleSet execution.
   *
   * Unlike the registers, a Runtime does not initialize the memory in each
   * Program execution. So we can use memory to pass a value between Condition
   * and Action, Rules.
   */
  Memory memory;

  /**
   * @brief The assigned RuleSet for this Runtime instance.
   *
   * One Runtime has only one RuleSet to process and is never re-used for
   * another RuleSet.
   */
  RuleSet ruleset;

  /**
   * @brief The partners store the possible entangled partners' QNodeAddr.
   * The RuleEngine looks at this variable to determine which entangled qubit to
   * assign to which rule set.
   */
  std::set<QNodeAddr> partners;

  /**
   * @brief The label_map is a map of the instruction index and its label to
   * allow to jump or branch.
   *
   * The Runtime changes the value of the pc to the instruction index
   * corresponding to the given label to jump or branch the execution.
   */
  LabelMap const* label_map = nullptr;
  //@}

  /** @name flags */
  //@{
  /**
   * @brief The return_code describes the program's exit status.
   *
   * The Runtime uses the return_code to determine how the Runtime should
   *  execute the RuleSet next. Whether to execute the action, go to the
   * following rule without executing it, or stop the ruleset.
   */
  ReturnCode return_code = ReturnCode::NONE;

  /**
   * @brief if this flag is true, the Runtime stops the Program execution.
   */
  bool should_exit = false;

  /**
   * @brief This flag is enabled when the RuleSet finishes its tasks.
   *
   * If this flag is true, the Runtime stops the Program execution,
   * and then the RuleEngine deletes the RuleSet and the Runtime.
   */
  bool terminated = false;

  /**
   * @brief if the Program faces a problem during execution,
   * the Runtime puts the error to this member variable.
   */
  RuntimeError* error = nullptr;

  /**
   * @brief if the flag is true, show debug information during RuleSet execution.
   *
   * The showing debugging information is a heavy operation. We recommend you
   * enable this with a debugger.
   */
  bool debugging = false;
  //@}
};
}  // namespace quisp::runtime
