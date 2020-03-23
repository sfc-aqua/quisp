
*Note: this file is an early design document, but might be updated as the version goes up.*

# Simulating a Link: An Example #

This article walks step by step through simulating a single round of
emitting a photon, looking at the data structures required.  This
article assumes actions are already programmed using a
[RuleSet](RuleSet.md), for the simplest link operation of just
creating a Bell pair.

1. Based on schedule determined by required arrival time at BSA,
schedule following actions.
2. Just before firing, initialize qubit
3. Fire photon, schedule BSA event.  Photon must be accompanied by (or
incorporate) info about what stationary qubit it's entangled with.
4. When BSA event occurs:
    1. Calculate probability of clicks occurring, using channel loss
    and BSA parameters, incorporating dark count.
    2. If successful, calculate error probability and type.
    3. Transform individual qubit states into a shared QuantumState,
    including recalculating fidelity/errors and resetting time since
    that calculation was done.
    4. Send ACK/NAK message to both partners, schedule arrival events.
5. When ACK/NAK msg event occurs:
    1. Update local statistics for both link performance and tracking
    the state.
    2. Invoke appropriate RuleEngine routine.  (Global fidelity/state
    will be updated again at the next gate performed at either node.)

The resulting Bell pair may be used either in tomography, or for
application use.  After the link bootstrap phase, the link is placed
in operational mode, during which this choice is determined
cryptographically based on some agreed-upon method.

## Data Structures ##

_Add discussion of how we track states here._

PR: Physical Reality (at least as simulated)

RK: What the Repeater Knows (its tracking of state)

