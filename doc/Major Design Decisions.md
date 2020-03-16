# Major Design Decisions for the Quantum Internet

*Note: this file is an early design document.  As of this writing,
 routing in the simulation is done using simulation magic.
 Implementing a full routing protocol is one of the fun tasks waiting
 to be done!*

Ultimately, we are creating only a single model of a Quantum Internet.

- **Service model**: the network provides Bell pairs with independent timing at each end, potentially with a trailing Pauli reference frame. Requests should specify a desired fidelity. We are not yet doing real time operation, but a rate would be necessary if so.
- **Multiplexing** and **resource management**: statistical multiplexing without resource reservation.  (*currently: fully blocking circuit switching in implementation*)
- **Routing**: qDijkstra shortest path first for the IGP for Dur-Briegel. IGP for Fowler and Jiang still TBD, but probably also a variant of SPF. EGP still TBD. (*current simulation status: depends on OMNeT++ internal magic, no true routing protocol*)
- **Role assignment** in path setup: Static placement of entanglement swapping points and thresholds.
- The key idea in ** path setup** is that a path is collected on a forward pass, then rules are created at the end point, and rules are popped off a stack by individual nodes on the return pass.
