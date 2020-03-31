# Rule Sets

A set of rules for operating a repeater to support a connection.

*Note: This document contains some important, early thoughts on the
design of RuleSets.  However, this description does not exactly
correspond to the current implementation.  At the time of this
writing, the best documentation is [Takaaki's master's
thesis](https://arxiv.org/abs/1908.10758) and the shorter
_Phys. Rev. A_ [paper](https://arxiv.org/abs/1904.08605) on the
topic.*

*In particular, the notion of "dynamic function placement" has not yet
appeared in any of our work, and is probably not well explained here,
anyway.*

RuleSets are created by the [Connection Manager](Connection%20Manager.md) and given to the [Rule Engine](Rule%20Engine.md).  See the [Router Software Modules](Router-Software-Modules-no-HW-Executive.jpg).

## Strategies for Building Consistent RuleSets ##

* *Function placement*: dynamic or static
* *Action decision*: state- (decoherence-)sensitive dynamic, or static

This gives us four possible combinations: static-static, static-dynamic, dynamic-static (which I don't think makes any sense), and dynamic-dynamic. We will begin with static-static, even though the banded purification (IEEE Trans. on Networking) was static-dynamic.

## Scheduling Purification ##

Several purification scheduling algorithms have been proposed. Some of these may be implemented either in static or dynamic fashion.

* Entanglement pumping: either
* Symmetric tree: static only
* Greedy: either
* Banded: dynamic only

# Dynamic Rules #

Each individual dynamic rule may be something like:

* If holding a pair with Alice with F > 0.98, and a pair with
  Charlie of F > 0.98, then swap.
* If holding two pairs with Alice and both F < 0.98, then do
  purification with the older one as control.
* If holding a pair with Alice and F < 0.60, then discard.

Each Rule has a condition and an action. The action may include local quantum operations and measurements, and emission of one or more (classical) messages to partners.

A RuleSet is customized for each node and connection. Repeaters (or routers) execute those rules blindly, without further coordination with other nodes beyond what is encapsulated in meeting the condition. Thus, it is up to the creator of the original set of RuleSets to ensure that they are consistent and will not result in deadlock or misoperation such as "leapfrog" or the bad dogleg, caused by race conditions in the firing of the rules.


# Principles of Consistent Dynamic RuleSets #

Adequate coordination can be achieved by adhering to a few key
principles:

* Alice and Bob (or all participants, for larger states) must
  agree on the state created (both the target pure state and the noise
  terms);
* Alice and Bob must agree on the original creation time of the
  quantum state;
* Alice and Bob must share an understanding of the time evolution
  of the density matrix (or at least fidelity), *with enough
    accuracy to guarantee consistent decisions*; and
* Alice and Bob must run higher-level algorithms *at the same
    point in the sequence of operations* and *on the same list of
    states*.

# Example RuleSets #

* [Dur-Briegel Example RuleSets](Dur-Briegel_Example_RuleSets.md)
* [Jiang Example RuleSets](Jiang%20Example%20RuleSets.md)
* [Fowler Example RuleSets](Fowler%20Example%20RuleSets.md)

# Specification #

The format of these messages is, at the moment, completely unspecified. Only contents and semantics are discussed here.

## Rule ##

As noted above, each Rule has a condition and an action. The action
SHALL include local quantum operations or measurements, and emission
of one or more (classical) messages to partners.  Note that this is a
key factor in helping to decide what rules should appear in the
protocol, as opposed to actions that are internal to a node: a Rule
MUST send one or more classical messages when complete.

### Condition Clause ###

A condition clause:

1. Specifies number of subclauses (generally one for purification or QEC, two for swapping).
1. Specifies number of Bell pairs needed, the partners, their condition.
1. Can refer to Bell pairs:
    1. By creation order: BellPairs.ByAge[0] is oldest, etc.
    1. By fidelity: BellPairs.ByFidelity[0] is highest fidelity, etc.
1. Can access the following information about a Bell pair:
    1. Address/identifier of local qubit
    1. Address/identifier of remote qubit
    1. Fidelity

A condition clause also needs to be able to specify reception of a message, and processing of its contents.

Example:

    NumSubClauses: 2
    SubClause1:
        Partner: 10.0.1.2
        MinFidelity: 0.5	// corresponds to "any entangled state"
    SubClause2:
        Partner: 10.0.1.2
        MinFidelity: 0.5	// corresponds to "any entangled state"

### Types of Condition Subclauses ###

A subclause consists of two parts: an identifier that can be
translated into a local qubit (whether locally only, or part of a
distributed state, and named in a message), and a condition which the
qubit meets.

### Events ###

1. BecameEntangled
1. ReceivedMessage

### Action Clause ###

The Action Clause specifies a *sequence* of actions to be taken. Note that there are no additional branches or conditionals here; if they are needed, they are achieved by adding more Rules. This means that no loops are possible, but I don't think we need a fully Turing-complete RuleSet.

Example:

    CNOT(BellPairs.ByAge[0],BellPairs.ByAge[1])
    A = MEAS(BellPairs.ByAge[1])
    SendMsg(10.0.1.2,BellPairs.ByAge[1].ID,A)
    QueueAction(BellPairs.ByAge[1],WaitForMessage(10.0.1.2))

*Note: Now I'm not sure what the intent of that QueueAction was when I
 wrote it.*



# Open Questions #

1. How do we represent the recalculation of the state in our rule sets?
1. How do we represent waiting for a specific message?
1. To what extent do we want Rules to correspond to events, rather
than states or conditions?
