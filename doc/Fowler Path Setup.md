# Setting Up Paths: the Fowler Case #

*Note: this file is an early design document, and these 2G networks
are not yet handled.  Internetworking (recursive) connections and
networks are not yet handled.*

*(obviously, also, this document was left incomplete)*

This is the surface code communication path setup algorithm, designed
for use as part of the full recursive Quantum Internet.

This procedure should create a set of rules like those in [Fowler
Example RuleSets](Fowler%20Example%20RuleSets.md).

# Pseudocode for processing a FowlerPathSetupRequest message #


Wrapper:

    procedure ProcessFowlerPathSetupRequest(Msg)
        RuleSets = BuildFowlerRulesets(Msg.ConnSpec,Msg.HopStack)
        ReturnMsg = BuildReturnMsg(RuleSets)
        ReturnMsg.SendMsg()
    endprocedure

Recursive code for creating Rulesets:

    procedure BuildFowlerRulesets(ConnSpec,HopStack)
    endprocedure

# Open Issues #

