
*Note: this file is an early design document, but might be updated as the version goes up.*

Role assignment is done at the destination, in a two-phase algorithm. Information about the path is collected in the outbound phase, then the destination node performs the role assignment to create RuleSets. These RuleSets are then installed on the return phase of the operation.

This may be done either in flat form, or recursive.

* [[FlatPathSetup Processing]]
