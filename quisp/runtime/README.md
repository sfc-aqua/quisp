# Runtime

The Runtime is an environment for executing RuleSet.
This Runtime abstraction allows us to analyze the behavior of RuleSet execution
for further research about RuleSet-based quantum networks. The Runtime is a
simple register-based machine with a simple key-value memory store. It's
responsible for executing RuleSet written in intermediate representations(IR)
and managing its states like assigned qubits entangled with a partner,
temporary values (Registers and Memory), and flags. The current Runtime design
focuses on 1). easy to implement and debug, 2). flexible in tweaking the
instructions.
See also @ref quisp::runtime

## Intermediate Representations (IR)
The IR is similar to the Intel syntax so that we can write down the instruction:
"load the value of the _KEY_ from the memory to the register _REG0_" into
"LOAD REG0 KEY". Be careful about the order of the destination (_REG0_) and the
source (_KEY_). The IR is like a simple assembly language with labels. Action
and Condition in a Rule are written in the IR to describe how it works. We can
write a control flow with jump or branch instructions. So there is no if-else
statement nor for-loop syntax in the language due to simplicity for
implementation and debugging. Here is an pseudo code to perform the random
measure action and its C++ representations.

```plaintext
  // load the "count" key from memory to the register
  LOAD count "count"

  // find a n-th qubit entangled with partner_addr and set as q0.
  // if qubit is not found, set qubit_found flag false.
  GET_QUBIT q0 partner_addr qubit_resource_index

  // if qubit_found flag is set true, go to QUBIT_FOUND label
  BRANCH_IF_QUBIT_FOUND QUBIT_FOUND

  // raise unrecoverable error and stop execution
  RET ReturnCode::ERROR

QUBIT_FOUND: // this is a label

  // measure the qubit q0 and store the result to the "outcome" key
  MEASURE_RANDOM "outcome" q0

  // increment the count register
  INC count

  // store the count register val to the "count" key in the memory
  STORE "count" count

  // free the qubit q0 from the RuleSet and remove the name q0 from the qubit.
  FREE_QUBIT q0

  // send the link tomography (measurement) result to partner_addr.
  SEND_LINK_TOMOGRAPHY_RESULT partner_addr count "outcome" max_count
```

The C++ representation format is
`INSTR_{instruction name}_{argument1 type}_{argument2 type}_`.
These are aliases of the @ref Instruction template class so that you can
instantiate by the C++ initializers list with curly braces like
`INSTR_ADD_RegId_RegId_int_{{REG0, REG1, 7}}`.

```cpp
  // prepare a qubit id to handle a qubit.
  QubitId q0{0};
  // name the register 0 as count
  auto count = RegId::REG0;
  int max_count = 1000;
  QNodeAddr partner_addr{3};
  auto qubit_resource_index = 0;
  simtime_t start_time = simTime();
  Label qubit_found_label{"qubit_found"};
  MemoryKey count_key{"count"};
  MemoryKey outcome_key{"outcome"};
  return Program{
      "Tomography",
      {
          // clang-format off
INSTR_LOAD_RegId_MemoryKey_{{count, count_key}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, qubit_resource_index}},
INSTR_BRANCH_IF_QUBIT_FOUND_Label_{qubit_found_label},
INSTR_RET_ReturnCode_{{ReturnCode::ERROR}},
INSTR_MEASURE_RANDOM_MemoryKey_QubitId_{{outcome_key, q0}, qubit_found_label},
INSTR_INC_RegId_{count},
INSTR_STORE_MemoryKey_RegId_{{count_key, count}},
INSTR_FREE_QUBIT_QubitId_{q0},
INSTR_SEND_LINK_TOMOGRAPHY_RESULT_QNodeAddr_RegId_MemoryKey_int_Time_{{partner_addr, count, outcome_key, max_count, start_time }}
          // clang-format on
      },
  };
```

## RuleSet Execution with Runtime
@htmlonly
<div class="mermaid">
   sequenceDiagram
        participant RE as RuleEngine
        participant RT as Runtime
        participant IV as InstructionVisitor
        participant CB as ICallBack

        RE->>RT: create Runtime and assign RuleSet
        RT->>IV: initialize
        RT->> CB: initialize
        RT->>RT: analyze the given RuleSet
        RE->>RT: assign qubit
        RE->>+RT: execute RuleSet
        loop Each Program Instruction execution
            RT->>+IV: execute Instruction
            IV->>IV: handle Instruction
            IV->>RT: call Runtime methods
            RT->>CB: call the Callback
            CB->>RE: quantum operation or classical communication
        end
        alt RuleSet not terminated
            RT->>-RE: finish RuleSet execution
        else RuleSet terminated
            RT->>RE: finish RuleSet execution
            RE->>RT: delete the RuleSet and the Runtime
        end
</div>
<script src="https://unpkg.com/mermaid/dist/mermaid.min.js"></script>
<script>mermaid.initialize({startOnLoad:true});</script>
@endhtmlonly

## Storage Scopes
The Runtime has two types of storage scopes.
One is Program-scope, where the Runtime initializes the storage before every
Program execution. Only the Program can read/write the storage. Another is
RuleSet-scope, where all Rule can read/write their value and the Runtime
initializes it only once.

## Storage types
The Runtime has four types of storage, Register, Memory, Flags, and Qubits.

### Register
The Register is Program-scope storage that can store one number. You can use
these Registers to perform simple arithmetic or check the number of
measurements the RuleSet has done or qubits you can use in The Program.

### Memory
The Memory is RuleSet-scope storage that can store any value with the
MemoryKey. Unlike ordinary computer memory, the Memory is a simple key-value
store for simplicity and safety. The RuleSet uses this Memory to keep the
RuleSet-wise values like the total measurement count. You should load the value
to the Register to use the Memory values.

### Flags (pc, should_exit, terminated, error, and return_code)
The Flag is Program-scope storage that can store a value for control flow.
The Program cannot access these values directly.

### Qubits
The Qubits is RuleSet-scope storage that can store the qubits entangled with
other QNode. The RuleEngine assigns the qubits to some Runtime when it detects
the entangled qubits. Then the Runtime can use the assigned qubits as their
resources to executing the RuleSet.
