#pragma once
#include <cassert>
#include <cstddef>
#include <deque>
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
struct Register {
  int32_t value = 0;
};

/// @brief (partner's qnode addr, assigned RuleId) => [local half of the bell pair qubit record]
using QubitResources = std::multimap<std::pair<QNodeAddr, RuleId>, IQubitRecord*>;

/// @brief (partner's qnode addr, assigned RuleId, sequence number) => [local half of the stationary bell pair qubit record]
using QubitResourcesWithSequenceNumbers = std::map<std::tuple<QNodeAddr, RuleId, SequenceNumber>, IQubitRecord*>;
using SequenceNumberTracker = std::map<IQubitRecord*, std::tuple<QNodeAddr, RuleId, SequenceNumber>>;

/// @brief ResourceId needs to be increment each time a qubit of certain properties (same <QNodeAddr>) is added to the Rule.
using SequenceNumberCounter = std::map<std::pair<QNodeAddr, RuleId>, SequenceNumber>;

/// @brief Store messages for each rule for decision making mainly used for WaitRules (e.g., purification, Pauli Frame correction).
using MessageResources = std::map<RuleId, std::deque<MessageRecord>>;

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
    virtual int getActionIndex(IQubitRecord* const) = 0;

    // Quantum Operations
    virtual MeasurementOutcome measureQubitRandomly(IQubitRecord*) = 0;
    virtual MeasurementOutcome measureQubitX(IQubitRecord*) = 0;
    virtual MeasurementOutcome measureQubitZ(IQubitRecord*) = 0;
    virtual MeasurementOutcome measureQubitY(IQubitRecord*) = 0;
    virtual void gateX(IQubitRecord*) = 0;
    virtual void gateZ(IQubitRecord*) = 0;
    virtual void gateY(IQubitRecord*) = 0;
    virtual void gateCNOT(IQubitRecord* control_qubit_rec, IQubitRecord* target_qubit_rec) = 0;
    virtual int purifyX(IQubitRecord* qubit_rec, IQubitRecord* trash_qubit_rec) = 0;
    virtual int purifyZ(IQubitRecord* qubit_rec, IQubitRecord* trash_qubit_rec) = 0;
    virtual int purifyY(IQubitRecord* qubit_rec, IQubitRecord* trash_qubit_rec) = 0;
    virtual void updateQubitPartner(IQubitRecord* qubit_rec, QNodeAddr partner_addr) = 0;

    // Messaging
    virtual void sendLinkTomographyResult(const unsigned long ruleset_id, const Rule& rule, const int action_index, const QNodeAddr partner_addr, int count,
                                          MeasurementOutcome outcome, int max_count, Time start_time) = 0;
    // TODO: change to this
    // virtual void sendTomographyResult(const QNodeAddr partner_addr, const int shared_rule_tag, const int sequence_number, const int measurement_result, const basis) = 0;
    virtual void sendPurificationResult(const unsigned long ruleset_id, const QNodeAddr partner_addr, const int shared_rule_tag, const int sequence_number,
                                        const int measurement_result, PurType protocol) = 0;
    virtual void sendSwappingResult(const unsigned long ruleset_id, const QNodeAddr partner_addr, const QNodeAddr new_partner_addr, const int shared_rule_tag,
                                    const int sequence_number, const int frame_correction) = 0;
    // Debugging
    virtual std::string getNodeInfo() { return ""; };
  };

  Runtime();
  Runtime(const RuleSet& ruleset, ICallBack* callback);
  Runtime(const Runtime&);
  Runtime& operator=(Runtime&& runtime);
  ~Runtime();

  void assignRuleSet(const RuleSet& ruleset);

  /**
   * @brief this method resets the state before each Program execution.
   */
  void cleanup();

  /// @brief public method to execute the assigned RuleSet.
  void exec();

  /// @brief execute the given Program in a Rule
  void execProgram(const Program& program);

  /// @brief execute the one Instruction
  void execInstruction(const InstructionTypes& op);

  /**
   * @brief assign the message to the rule
   *
   * @param partner_addr the entangled partner QNode address for the qubit.
   * @param rule_id the rule id to assign the qubit
   * @param msg the content of the message (e.g., purification [measurement_result, sequence_number, pur_type], swapping [frame_correction, sequence_number])
   */
  void assignMessageToRuleSet(int shared_rule_tag, MessageRecord& msg_content);

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

  /// @brief find the qubit iterator that match with this rule_id and sequence_number
  QubitResources::iterator findQubit(IQubitRecord*);

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
   * @brief Get the qubit record by sequence number
   *
   * This method finds a qubit record with the associated sequence number.
   * If the Runtime cannot find the qubit, this returns nullptr.
   * Reminder, sequence number is the order in which the qubit is assisgned to the Program.
   * @param partner_address
   * @param rule_id
   * @param sequence_number
   * @return IQubitRecord*
   */
  IQubitRecord* getQubitBySequenceNumber(QNodeAddr, RuleId, SequenceNumber);

  /**
   * @brief Get the qubit record by partner's QNodeAddr
   *
   * This method finds an index-th qubit record entangled with the partner from
   * the @ref qubits member. If the Runtime cannot find the qubit, this returns
   * nullptr. The qubit must be assigned to the current rule_id.
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
   * @param qubit_record the entangled qubit's record already assigned to the RuleSet
   */
  void promoteQubit(IQubitRecord* qubit_record);

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
  /**
   * @brief measure qubit with given basis and put result into register
   *
   * @param qubit_id qubit to measure
   * @param result_reg register to put result into
   * @param basis measurement basis
   */
  void measureQubit(QubitId qubit_id, RegId result_reg, Basis basis);

  /// @brief free qubit and release it from the Rule and the RuleSet
  void freeQubit(QubitId);

  /// @brief apply X gate
  void gateX(QubitId);

  /// @brief apply Z gate
  void gateZ(QubitId);

  /// @brief apply Z gate
  void gateY(QubitId);

  /// @brief apply CNOT gate
  void gateCNOT(QubitId control_qubit_id, QubitId target_qubit_id);

  /// @brief perform X purification and store the measurement result
  void purifyX(RegId result, QubitId qubit_id, QubitId trash_qubit_id);

  /// @brief perform Z purification and store the measurement result
  void purifyZ(RegId result, QubitId qubit_id, QubitId trash_qubit_id);

  /// @brief perform Y purification and store the measurement result
  void purifyY(RegId result, QubitId qubit_id, QubitId trash_qubit_id);
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
  /// @brief currently evaluating rule id
  RuleId rule_id = -1;

  /// @brief currently evaluating send/receive tag of this rule id (if it is defined)
  int send_tag = -1;
  int receive_tag = -1;

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

  MessageResources messages;

  QubitResourcesWithSequenceNumbers sequence_number_to_qubit;
  SequenceNumberTracker qubit_to_sequence_number;
  /**
   * @brief This stores the latest sequence no. of resource assigned to the Stage/Rule.
   */
  SequenceNumberCounter resource_counter;

  /**
   * @brief [shared_rule_tag] => [rule_id]
   */
  std::unordered_map<int, RuleId> shared_tag_to_rule_id;
  std::unordered_map<RuleId, int> rule_id_to_shared_tag;

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
   * @brief The GET_QUBIT instruction sets this flag. if it's true, the GET_QUBIT
   * instruction successfully found the qubit. if not, the instruction cannot
   * find qubit.
   */
  bool qubit_found = false;

  /**
   * @brief The GET_MESSAGE instruction sets this flag. if it's true, the GET_MESSAGE
   * instruction successfully found the corresponding message. if not, the instruction cannot
   * find a message meant for this Program.
   */
  bool message_found = false;

  /**
   * @brief if the flag is true, show debug information during RuleSet execution.
   *
   * The showing debugging information is a heavy operation. We recommend you
   * enable this with a debugger.
   */
  bool debugging = true;
  //@}
};
}  // namespace quisp::runtime
