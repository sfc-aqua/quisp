# Rule Engine #

*Note: This document contains some important, early thoughts on the
design of RuleSets.  However, this description does not exactly
correspond to the current implementation.*

## Key decisions ##

1. The only two software entities with interfaces to the RE are the [Connection Manager](Connection%20Manager.md) and the [Real-Time Hardware Controllers](Real-Time Hardware Controller).
1. Operation is entirely event-driven. Those events can be either notification from a Real-Time Hardware Controller or a message from another node.
1. Actions by the RE can be either request an operation of one or more RTHCs, or to send a message to another node.
1. The RE accepts [RuleSets](RuleSet) from the Connection Manager.

## Software Structure ##

![Rule Engine block diagram](img/Rule%20Engine.png)

There are five important data structures.  One really important one not yet shown in the figure:

1. The Rule Table itself. *How should this be indexed, searched for
a match and updated?*

Two shown in the figure:

1. QubitStateTable lists the states of every qubit in the node: QNIC and qubit address form the qubit identifier, then some description of the state itself (TBD), and a local timestamp for the last update.
1. EventQueue holds all of the relevant events, whether they are messages from other nodes, or asynchronous (but hopefully expected) events from an RTHC.

And two more not shown, both used by the Communicator:

1. SocketTable holds the set of open sockets, each connected to a partner node somewhere.
1. MessageQueue holds messages from the Crankshaft to be sent out to partners.

There are two threads:

1. Crankshaft, which just loops (see pseudocode below), consuming events and making other things happen.
1. Communicator, which is in charge of the sockets and parses incoming messages into Events.

## Pseudocode for Crankshaft ##

Very simple loop for processing incoming messages.  The hard part is
figuring out the semantics of the individual components.

    while (1) {
        msg = EventQueue.ReceiveEvent()
        Rule = MatchToRule()
        // assert that only one rule was/could have been returned
        assert(Rule.Size == 1)
        // this will do gates and measurements, MUST send 
        // at least one message.  May establish callbacks?
        Rule.ActionClause.Execute()
        // Is update of qubit state a side effect of Execute, or
        // separate?  Note (figure) that measurement results
        // come straight into the Execute() clause, rather than
        // being pushed back into the EventQueue.
    }

None of these actions are allowed to block; this loop is assumed to
run continuously and *fast*.  (See below for an estimate of required performance.)

*n.b.:* For the purposes of this simulation, we will assume that
 circuits are synchronous/essentially instantaneous.  In the real
 world, here we would have to queue messages to the various QNICs to
 get circuits executed, and allow messages to come back.  Whether they
 would be stuck into the same queue as the higher-level events is an
 issue we don't have to deal with right here.

## Pseudocode for Communicator ##

The Communicator needs to handle more than one socket.  Handling the
opening of those sockets is a bit tricky.  This needs the accept()
call.

    while (1) {
        // check for new socket
        // check if we need to create a new socket
        // loop through existing sockets, reading
        // need to be able to handle incomplete messages here,
        // buffer them for later completion before inserting into
        // EventQueue?
        msg = SomethingReadFromSocketAndParsed()
        EventQueue.InsertEvent(msg)
        // Events may also be from RTHCs.
    }

## Events and the EventQueue ##

This is the means of communicating between the Communicator and the
Crankshaft.

Types of events:

1. RTHC (dependent on hardware capabilities):
    2. EntanglementSuccess
    2. other types of operation completion?
1. Message from partner nodes (n.b.: dependent on RuleSet):
    2. *This is not the right level of abstraction yet; should match circuit.*
    2. SwapNotification
    2. PurificationResult
1. Meta:
    2. Connection establishment
    2. Connection teardown

## Communications ##
![Paths on phys topology.PNG](img/Paths%20on%20phys%20topology.png)

Scalability of communications to/from the RE is a serious concern.  Worst
case is purify-and-swap networks, in which a router *or* repeater may
have to communicate with up to N log N other nodes in near-real time,
for N connections passing through it.  (This alone is a good argument
for the error corrected forms of network, which allow the router to
communicate only with nearest neighbors, although in our
connection-oriented architecture, a router still uses O(N) resources
for maintaining connection state.)

Actually, that's the naive form of the argument.  Fortunately, our
recursive structure reduces that number.  In our simulation of 100
networks of 100 nodes, each, the worst case should be 200 open TCP
sockets: one for each other node in the current network, and one for
each other network.

Therefore:

1. In order to limit the number of TCP sockets a router must keep
open, messages related to multiple quantum connections should be
multiplexed across a single TCP socket.  This doesn't change the O()
complexity of the maximum number of nodes a router has to communicate
with, but should give a significant reduction, and will prevent the
silliness of having a thousand open TCP sockets with each immediate
neighbor.
1. A socket to another node should be opened, as necessary, when the
CM informs the RE that a new connection is being created.  If a socket
to the corresponding node is already open, there is no need for a new
one, but a table of quantum paths using that particular TCP socket may
need to be updated.
1. The Communicator will therefore have to maintain a UserCount for
each socket; the socket should be closed when it reaches zero.

## Indexing RuleSets ##

An incoming message is easily mapped to a particular RuleSet by its
connection identifier (form TBD).

## Performance Requirements (Real World and Simulation) ##

The RTHCs need to operate on hard real time, nanosecond time scales.
The RE, however, is generating and processing messages from neighbors,
operating at a much slower time scale.

We established above that for our simulation purposes here, each node
will be multiplexing a thousand connections across 100 TCP sockets.
Given that each connection may be a fairly large number of low-level
rules, there might be ten thousand rules that need to be searched.
(See above on indexing.)

The real driving factor in the number of actions that an RE needs to
take is the number of successful Bell pair creations per second; each
results in at most a few operations.  (See below about "rule
recursion" firing.)  Keep in mind that this includes backplane Bell
pair creations.  For the moment, let's assume, for router hardware:

1. Link performance ranges 10-10,000 Bell pairs/second (mean of
1,000/second on a node)
1. Backplane performance range 100-100,000 Bell pairs/second (mean of
10,000/sec. on a node)
1. Average node degree of 4.

That should be an average of 14,000 Bell pairs/second in a router.  A
repeater would be an average of 2,000.  (Remember the REs operate
independently at each end of a link, so a Bell pair is effectively
processed twice.)

For the software:

1. 1,000 simultaneous connections multiplexed over 100 TCP sockets.
1. 100 rules/connection.
1. Average of 50 rules must be examined to match condition clause.
1. Average of 10 operations in the Action clause.
1. One message generated in each Action clause.
1. For moment, assume that this holds for both routers and repeaters.

This would be 700,000 rule checks/second, 140,000 operations/second, and
14,000 messages/second in a router.  100,000 rule checks/sec., 20,000
operations/sec., and 2,000 messages/sec. in a repeater.

Topology (shouldn't this be documented elsewhere?):

1. 10,000 total nodes
1. 1,000 routers as above
1. 9,000 repeaters

Total computational load across the entire network:

1. 700Kx1000 + 100Kx9000 = 1.6B rule checks/second
1. 140Kx1000 + 20Kx9000 = 320M operations/second
1. 14Kx1000 + 2Kx9000 = 32M messages/second

So to simulate an entire hour's operation:

1. 1.6Bx3600 = 5.76 trillion rule checks!
1. 320Mx3600 = 1.152 trillion operations (gates)
1. 32Mx3600 = 115B messages

To do that in one day in a single-threaded sim takes:

1. 70M rule checks/sec.
1. 15M operations (gates)/sec., and
1. 1.3M messages/sec.


## Open Questions ##

1. Does the RE need to know about the concept of a Connection?
1. How should the Rule Table be indexed, searched and updated?
1. Biggest open question is related to Rule Sets -- how do we correctly identify a particular qubit?
1. How do we implement concurrency?
1. Does a RuleSet have a specified lifetime? If not, the only information flow from RE to CM would be on some status query from the CM.
1. Can we get away without callbacks, or do we have to have them?
1. Is update of qubit state a side effect of Execute, or separate?
1. How fast does the RE need to be in the real world, and for our sims?
1. "Rule recursion": Does completion of one rule directly result in
firing of another?  Possibly, I'm not sure yet.
1. Can we *always* quickly map an event to a connection?  If so, this
dramatically simplifies the performance demands on rule indexing.
