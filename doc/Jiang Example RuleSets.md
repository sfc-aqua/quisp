
*Note: this file is an early design document, but will be updated in the future.*

RuleSets for Jiang networks are in some ways similar to [Dur-Briegel ones](Dur-Briegel Example RuleSets).

Key differences:

* Base Bell pairs are only useful once we have *n* of them, where *n* is the code block size. Thus, it makes sense to receive them in groups of that size.
* Swapping is always done only with nearest neighbors.

Thus, RuleSets can be fairly simple.

## *Static-Static* RuleSets for Steane Code with QEC Block Size *n* ##

(n.b.: There are no non-neighbor-node operations in this approach, as
there are with nested entanglement swapping.  The placement of
operations is never really a choice, compared to purify-and-swap
networks.)

Here, we are assuming:

* Bell pair creation success probability is below (probably *waay*
  below) 50%, so we can't do direct ballistic execution; instead, we
  must first build acknowledged Bell pairs, then perform operations on
  top.
* Fidelity is sufficient to run QEC on top, so we aren't purifying
  before QEC.  (The construction of RuleSets should actually allow
  that if they're not good enough, I just haven't included that in
  this example.)

Alice:

1. When holding *n* base Bell pairs with Bob:
    1. Build logical |0> state on *n* ancilla qubits.
    1. Execute logical *H* gate on the ancillae, to make |+> state.
    1. As sender, execute *n* transversal teleported CNOT gates (see
    Eisert et al., PRA 62(5), 52317 (2000)) to Bob's logical |0> state
    built on his ancillae. (n.b.: The order of these has to be defined to
    match the position in the logical block.  Order via age, and match
    to a canonical ordering of the qubits in the error correction code
    block, which we need to right down somewhere.)
1. When holding a logical Bell pair with Charlie, deliver to application.

Result of Rule 1 is a logical Bell pair with Bob. After that, Alice only has to wait on confirmation from Bob that he has done entanglement swapping. Note that, depending on the application of the trailing Pauli reference frame, the logical Bell pair can actually be given to the application after Rule 1 fires, rather than waiting for Rule 2.


Bob:

1. When holding *n* base Bell pairs with Alice:
    1. Build logical |0> state on *n* ancilla qubits.
    1. As receiver, execute *n* transversal teleported CNOT gates (see Eisert et al., PRA 62(5), 52317 (2000)) to Bob's logical |0> state built on his ancillae.
1.  When holding *n* base Bell pairs with Charlie:
    1. Build logical |0> state on *n* ancilla qubits.
    1. Execute logical *H* gate on the ancillae, to make |+> state.
    1. As sender, execute *n* transversal teleported CNOT gates (see Eisert et al., PRA 62(5), 52317 (2000)) to Charlie's logical |0> state built on his ancillae.
1. When holding a logical Bell pair with Alice and a logical Bell pair with Charlie, perform transversal entanglement swapping.

Charlie:

1. When holding *n* base Bell pairs with Bob:
    1. Build logical |0> state on *n* ancilla qubits.
    1. As receiver, execute *n* transversal teleported CNOT gates (see Eisert et al., PRA 62(5), 52317 (2000)) to Bob's logical |+> state built on his ancillae.
1. When holding a logical Bell pair with Alice, deliver to application.

