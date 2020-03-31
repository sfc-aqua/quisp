
*Note: this file is an early design document, but will be updated in the future.*

# Network-Independent Operational Behavior #

All repeaters, regardless of network type, share a few physical and operational characteristics.

During runtime operation, Jiang and Fowler repeaters deal only with their immediate neighbors, though note that they may of course be supporting multiple concurrent connections which may even be using different codes (on Jiang) or code distances (on Fowler). Dur-Briegel repeaters may be required to communicate with arbitrary nodes, depending on the swapping behavior. (Note that in recursive operation, repeaters in the "interior" of the network never directly communicate with those outside, this is handled instead by the border routers.)

All repeaters have the following in physical characteristics in common:

1. They have two interfaces, which by convention we call "left" and right".

All repeaters have the following in operational characteristics in common:

1. The links to the left and right are in *constant* operation, building new link-level base Bell pairs.
1. Bell pairs have a CreationTime
1. A live [[RuleSetTable]] dictates the disposition of Bell pairs.

For flat operation:

1. They receive and process [[FlatPathSetupRequest (Outbound) Message Contents]].
1. They receive [RuleSet](RuleSets) from end nodes as part of the [[FlatPathSetupReturn Message Contents]], and install those RuleSets in their table of current connections.

Contents of both of those depend on the network type.

For recursive operation: (TBD)

# Network-Specific Operation #

* [Dur-Briegel Repeater Operation](Dur-Briegel Repeater Operation)
* [Fowler Repeater Operation](Fowler Repeater Operation)
* [Jiang Repeater Operation](Jiang Repeater Operation)
