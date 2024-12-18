# Quick docs to troubleshoot teardown
## The ReservationRegister
To implement the teardown sequence, I started from the `ConnectionManager` (CM) and how it handles qnic reservations: before, reserved qnics' addresses were kept in a set and if an address was in that set the qnic was reserved.
To track which RuleSet reserved which qnic, I introduced a `ReservationRegister` (RR) object which is essentially two maps: one with RuleSetID as key and set of qnic addresses as values, and the other with qnic address as key and RuleSetID as value. This allows the CM to create and delete reservations by qnic address and by ruleset id, and it also offers the possibility to change the ruleset id of an existing reservation, which will be useful in the connection setup phase. I wrote unit tests for the RR and it seems to work correctly.

## The ConnectionSetupRequestID
Adding a Reservation Register means that in order to reserve a qnic we need to know which Ruleset is reserving it. However, qnic reservation is made during the connection setup phase, when the ruleset id is not yet known. To solve this issue, the ConnectionSetupRequestID (CSRqID) field was added to ConnectionSetupRequest(CSRq) messages. This ID is generated and added to CSRq messages when they are first enqueued at the Initiator's `ConnectionManager`. As the CSRq is relayed through repeaters, reservations are made in the ReservationRegister with the CSRqID as a provisional ID.

The CSRqID field was added to ConnectionSetupResponse (CSRp) messages as well: when generating the CSRp, the Responder includes both the RuleSetID as normal and the CSRqID. This way, nodes receiving the Response can update the reservations to the correct RuleSet ID. The reservation process is now complete.

## The ConnectionTeardown messages
The ConnectionTeardown (CTD) messages are generated and cached by the Responder in the connection response phase, at the same time when the CSRp is generated.
When the RuleSet is terminated, the Responder sends ConnectionTeardown (CTD) messages to all the nodes in the path.

Pre-generating and caching the CTD has two advantages:
we are sure that only the Responder has CTD messages to send (this is probably a weakness for future multiparty implementations) and
we generate the CTD at a point where we are aware of all relevant information (Ruleset ID, partners' addresses).
The messages will be sent once the Ruleset is terminated.

## Actually Terminating Connections
Inside the RuleEngine, the `execAllRulesets()` call was modified: originally it looped `exec()` for all the existing Runtimes, while now it also collects the RulesetIDs from the terminated Runtimes.
These are the IDs of the connections that need to be torn down. These IDs are relayed to the CM through an InternalTerminatedRulesetIdsNotifier message, which now knows some rulesets are terminated and the connections needs to be torn down.
IF any CTD messages are available in cache for the terminated rulesets (i.e. this node was the responder for the connection in object), they are sent out. Otherwise, the node does nothing.

## Reception and Handling of the ConnectionTeardown messages

When a CM receives a CTD message, it does three things:
### Request Termination of Swapping RuleSets
The rulesets that repeaters use for entanglement swapping do not have an explicit termination condition. Therefore, there needs to exist an external termination mechanism for them:
the CM sends a RequestRulesetTermination (RRT) with the ID that's being torn down to the RuleEngine, who checks if the relevant Ruleset is already terminated.
If not, the `terminated` flag of the relevant Runtime is set to true so that execution of entanglement swapping stops.
### Order the RuleEngine to deallocate the resources
A ReleaseResources message containing the qnic addresses to release and the corresponding Ruleset ID is sent to the RuleEngine.
Upon reception of this message, the RuleEngine is to free up resources allocated to the Ruleset in question (more detail later).
### Remove the Reservation
The reservation is finally removed from the Reservation Register: a new connection can be accepted now.

## Deallocation of Resources
Throughout the simulation, whenever a new entangled pair is generated, it is allocated to a RuleSet. Such allocation must be reverted at teardown time.
Interaction with entangled pairs at the RuleEngine level is done through the `BellPairStore` object, by requesting the range of local qubits that are entangled with a given partner.
For the RuleEngine to have this information, a `partners_register` map was introduced. The keys are RuleSetIDs and the values are vectors of addresses of all the potential partners involved in the RuleSet (Swappers and endnodes).
This map is populated by the acceptRuleset methods and depopulated when deallocating resource.

When the ReleaseResources message arrives, the following pseudocode is run:
```
partners = ReleaseResourcesMessage.RuleSetID;
for qnic_addr in ReleaseResourcesMessage:
    stopPhotonEmission();
    freeFailedEntanglementAttempts();
    for partner in partners:
        for pair in bell_pair_store.getPairs(partner):
            if (pair.isAllocated) pair.setAllocated(false);
```

# The Problem
When running the MM simulation test, all seems to work properly. Running the simulation and inspecting the memories from the simulation view shows that all of them are freed after old connections are torn down and before new ones are negotiated.
The simulation ends after roughly 4M events, which is consistent with expectations.

However, with the Swapping tests (especially the 3 node one), there seems to be a problem I cannot pin down.
After every connection is torn down, there seem to be some qubits in the QNICs that remain busy and are never freed. This can be observed by running the simulation until e.g. t = 13s and inspecting the StationaryQubits inside the qnics: a couple of them will have last emission time around 10s, which shouldn't be the case since there was a CSRq at 12s. (In the MM case, at this point every qubit has last emission time > 12s).
I even tried hardcoding the number of QNIC slots, looping through them and deallocating (or even reinitializing) everything but it still doesn't work.
After a couple connections, the stuck qubits are too many, the RuleSet never reaches termination and the simulation ends.
What I observe at the end is that the qnics in the link are P--FE--E (E = empty, P = partially filled, F = full).
