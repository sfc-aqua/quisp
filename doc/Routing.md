# Routing for Connections #

*Note: this file is an early design document.  As of this writing,
 routing in the simulation is done using simulation magic.
 Implementing a full routing protocol is one of the fun tasks waiting
 to be done!*

The interior gateway protocol (IGP) will probably be
[qDijkstra](qDijkstra.md), and probably the same recursively for the
exterior gateway protocol (EGP).

Flat (IGP) qDijkstra uses seconds per Bell pair at F=0.98 (or some
other threshold) as the link cost. It's not clear if that's the best
way to do the recursion.

A routing table is the result of this routing process.
