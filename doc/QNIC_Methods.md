
*Note: this file is an early design document, but might be updated as the version goes up.*

# QNIC Controller Methods #

The set of software methods that a QNIC Controller provides to the
RuleEngine:

    Initialize();
    Reset();
    EnumerateResources();
    ExecuteLocalPhysicalCircuit(circuit);
        (consists of:
             1-qubit gates: I,X,Y,Z,H,init,measure
             2-qubit gates: CNOT, SWAP)
    LoopEmitUntilEntangled(list of qubits, callback);
    AbortLoopEmit(list of qubits);

Is that enough?

Each qubit is associated with either the InterQNIC or InterNode half
of the QNIC, so its identifier needs to make that clear.

LoopEmitUntilEntangled() should only be called with a list of qubits
from one half or the other, not both.

For qubits on the InterQNIC side, this function shouldn't be called
until the backplane switch is set up.  Correspondingly,
AbortLoopEmit() should be called before altering the backplane switch
configuration.

## Open Questions ##

1. How much flexibility do we need in circuit execution?  Can the
RuleEngine specify a loop?  (I don't think so.)  Can it specify an
abort condition?  (Hmm, not sure.)
1. How do we return measurement values to the RuleEngine?
