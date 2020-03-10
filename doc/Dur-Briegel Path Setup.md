# Setting Up Paths Recursively: the Dur-Briegel Case #

This is the purify-and-swap path setup algorithm, designed for use as
part of the full recursive Quantum Internet.

FindMidpoint() splits the HopStack into two halves, Left and Right,
with the "middle" estimated according to latency.

We know from prior work that purification is essentially a two-round
process: the first round takes a Werner state and makes it into a
binary state with one major error term, then the second round
suppresses that major error term.  Thus, it's not terribly efficient,
but for a first-cut setup algorithm here, we will purify to the
requested E2E fidelity at the link level, then exactly twice at each
level above that.

As with all rule creation algorithms, because this runs in a single
place (the Responder), upgrades to this algorithm can be made simply
and will improve all traffic passing through that node as Responder
(either end node or router).

# Pseudocode for processing a DurBriegelPathSetupRequest message #

Wrapper:

    procedure ProcessDurBriegelPathSetupRequest(Msg)
        RuleSets = BuildDurBriegelRulesets(Msg.ConnSpec,Msg.HopStack)
        ReturnMsg = BuildReturnMsg(RuleSets)
        ReturnMsg.SendMsg()
    endprocedure

Recursive code for creating Rulesets:

    procedure BuildDurBriegelRulesets(ConnSpec,HopStack)
        if (HopStack.Size > one hop) then
            (Left, Right) = FindMidpoint(HopStack)
            LeftRuleset = BuildDurBriegelRulesets(ConnSpec,Left)
            RightRuleset = BuildDurBriegelRulesets(ConnSpec,Right)
            (InitiatorRuleset, ResponderRuleset) = BuildPurifyRules(Left.Bottom,Right.Top,Repeat=2)
            MidpointRuleset = BuildSwapRule(ConnSpec,Left.Stack.Top)
            RuleSetStack.Push(InitiatorRuleset)
            RuleSetStack.Push(LeftRuleset)
            RuleSetStack.Push(MidpointRuleset)
            RuleSetStack.Push(RightRuleset)
            RuleSetStack.Push(ResponderRuleset)
        else // set up purification for single hop
            (LeftRuleSet, RightRuleSet) = BuildPurifyRules(HopStack[0],HopStack[1], Repeat=ToFidelity(ConnSpec.Fidelity))
            RuleSetStack.Push(RightRuleSet)
            RuleSetStack.Push(LeftRuleSet)
        endif
        return RuleSetStack
    endprocedure


# Open Issues #

1. Is latency a reasonable way to estimate the middle?
1. What information is needed for BuildPurifyRules?
1. How do we apply the infidelity of entanglement swapping?


