# Runtime

# RuleSet Execution with Runtime
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
            RT->>RE: finsih RuleSet execution
            RE->>RT: delete the RuleSet and the Runtime
        end
</div>
<script src="https://unpkg.com/mermaid/dist/mermaid.min.js"></script>
<script>mermaid.initialize({startOnLoad:true});</script>
@endhtmlonly

# Storage Scopes
The Runtime has two types of storage scopes. One is Program-scope, where the Runtime initializes the storage before every Program execution. Only the Program can read/write the storage.
Another is RuleSet-scope, where all Rule can read/write their value and the Runtime initializes it only once.

# Storage types
The Runtime has four types of storage, Register, Memory, Flags, and Qubits.

## Register
The Register is Program-scope storage that can store one number. You can use these Registers to perform simple arithmetic or check the number of measurements the RuleSet has done or qubits you can use in The Program.

## Memory
The Memory is RuleSet-scope storage that can store any value with the MemoryKey. Unlike ordinary computer memory, the Memory is a simple key-value store for simplicity and safety. The RuleSet uses this Memory to keep the RuleSet-wise values like the total measurement count. You should load the value to the Register to use the Memory values.

## Flags (pc, should_exit, terminated, error, and return_code)
The Flag is Program-scope storage that can store a value for control flow. The Program cannot access these values directly.

## Qubits
The Qubits is RuleSet-scope storage that can store the qubits entangled with other QNode. The RuleEngine assigns the qubits to some Runtime when it detects the entangled qubits. Then the Runtime can use the assigned qubits as their resources to executing the RuleSet.
