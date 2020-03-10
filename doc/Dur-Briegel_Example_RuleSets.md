# Dur-Briegel RuleSet Creation

*Note: this file is an early design document, and the concept names
(e.g. "SubClause", as well as the notions of static and dynamic Rules)
have evolved somewhat.  Internetworking (recursive) connections and
networks are not yet handled.  The Flat Path setup should also
correspond fairly closely to the [Internet Draft by Van Meter &
Matsuo](https://tools.ietf.org/html/draft-van-meter-qirg-quantum-connection-setup-01)
(which, as of this writing, has expired, but will be revived).*

This document describes RuleSets for a single swapping operation.  For
building a multi-hop path, see [Setting Up Multi-hop Paths: the
Dur-Briegel Case](Dur-Briegel%20Path%20Setup.md).

*At the moment, you are on your own to extend this to more than two
hops.*

## *Static-Static:* Example Simple, Static Purify-and-Swap Ruleset ##

This basic set of RuleSets for a three-hop chain gives the key ideas for a set of RuleSets that *do not* adapt their behavior based on current estimated fidelity, and don't model memory decoherence, and don't allow varying choices of entanglement swapping (irrelevant anyway since it's only two hops):

Alice:

1. If holding two base pairs with Bob, then do
  purification with the older one as control.
1. If holding two unpurified pairs with Charlie, then do
  purification with the older one as control.

Bob:

1. If holding a once-purified pair with Alice, and a once-purified pair with
  Charlie, then swap.
1. If holding two base pairs with Alice, then do
  purification with the older one as control.
1. If holding two base pairs with Charlie, then do
  purification with the older one as control.

Charlie:

1. If holding two base pairs with Bob, then do
  purification with the older one as control.
1. If holding two unpurified pairs with Alice, then do
  purification with the older one as control.

This is the simplest kind of RuleSetSet, since it doesn't take any real calculation, and doesn't take into account any time. Implementing it is very straightforward. It is, however, certainly less than optimal, since it never discards any old pairs, and probably purifies things that don't need to be purified.

Implementing pure tree-based purification scheduling is straightforward. Implementing pure entanglement pumping is straightforward. But implementing banded purification or anything that makes decisions based on fidelity doesn't work here.

    // Rule 1, basic first-half-purification at Alice (10.0.1.1)
    ConditionClause:
        NumSubClauses: 2
        SubClause1: EntangledQubitFidelityClause
            Partner: 10.0.1.2
            MinFidelity: 0.5	// corresponds to "any entangled state"
        SubClause2: EntangledQubitFidelityClause
            Partner: 10.0.1.2
            MinFidelity: 0.5	// corresponds to "any entangled state"
    ActionClause:
        CNOT(BellPairs.ByAge[0],BellPairs.ByAge[1])
        A = MEAS(BellPairs.ByAge[1])
        SendMsg(10.0.1.2,BellPairs.ByAge[1].ID,A)
        QueueAction(BellPairs.ByAge[1],WaitForMessage(10.0.1.2))

    // Rule 2, basic second-half-purification at Alice (10.0.1.1)
    ConditionClause:
        NumSubClauses: 1
        SubClause1: RcvMsgClause
            Partner: 10.0.1.2
            RcvMsg()
    ActionClause:
        CNOT(BellPairs.ByAge[0],BellPairs.ByAge[1])
        A = MEAS(BellPairs.ByAge[1])
        SendMsg(10.0.1.2,BellPairs.ByAge[1].ID,A)
        QueueAction(BellPairs.ByAge[1],WaitForMessage(10.0.1.2))

## *Static-Dynamic:* Example Simple, Dynamic Purify-and-Swap Ruleset ##

This basic set of RuleSets for a three-hop chain gives the key ideas for a set of RuleSets that *do* adapt their behavior based on current estimated fidelity, but *don't* model memory decoherence, and don't allow varying choices of entanglement swapping (irrelevant anyway since it's only two hops):

Alice:

1. If holding two pairs with Bob and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Bob and F < 0.70, then discard.
1. If holding two pairs with Charlie and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Charlie and F < 0.70, then discard.

Bob:

1. If holding a pair with Alice with F > 0.98, and a pair with
  Charlie with F > 0.98, then swap.
1. If holding two pairs with Alice and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Alice and F < 0.70, then discard.
1. If holding two pairs with Charlie and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Charlie and F < 0.70, then discard.

Charlie:

1. If holding two pairs with Bob and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Bob and F < 0.70, then discard.
1. If holding two pairs with Alice and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Alice and F < 0.70, then discard.

However, this set of sets is not realistic, because it does not include rules for recalculating fidelity based on memory decoherence. I think it is race condition-free at the moment.

## *Static-Dynamic:* Bob as a Router ##

If Bob is a router, rather than a repeater, he has internal latency and fidelity, and uses an internal Bell pair to complete his swapping transaction. Replace his rules above with the rules:

Bob:

1. (null condition), build AliceFacingNIC-to-CharlieFacingNIC Bell pair with fidelity F > 0.98.
1. If holding a pair with Alice with F > 0.98, and a pair with
  Charlie with F > 0.98, and an internal pair with fidelity F > 0.98, then swap using the internal pair.
1. If holding two pairs with Alice and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Alice and F < 0.70, then discard.
1. If holding two pairs with Charlie and both F < 0.98, then do
  purification with the older one as control.
1. If holding a pair with Charlie and F < 0.70, then discard.

## *Static-Dynamic:* Full Dynamic, Decoherence-Aware, Race Condition-Free RuleSetSet ##

Hoo, boy, writing this up will be fun...

## Open Issues ##

1. It has been suggested that it might be better to use a callback
specified in the SendMsg, rather than a separate line in the Action
clause.

