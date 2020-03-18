
*Note: this file is an early design document, but will be updated in the future.*

# Contents of a path setup return message #

This is the "flat" version, without recursion.

* ConnectionSpec
    * InitiatorAddr address (format unspecified)
    * ResponderAddr address (format unspecified)
    * (any other identifying information? port #, etc.?)
    * TargetFidelity
* RuleSetStack
    * ordered list of [RuleSets](RuleSet.md)

Here, "Initiator" and "Responder" correspond to the original request and are opposite to the direction of propagation of this message; the ultimate quantum communication will be adirectional.

Each node (including the Responder, where the message originates) pops off its RuleSet and installs it. The RuleSetStack should only be empty when this message reaches the Initiator.

Notice that no connection lifetime is specified here; connections are assumed to live until torn down, so we also need a teardown mechanism (either timeout-driven or explicit).