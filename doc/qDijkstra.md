
*Note: this file is an early design document, but might be updated as the version goes up.*

# qDijkstra: SPF for purify-and-swap networks #

qDijkstra for the IGP, and probably the same recursively/EGP.

Flat (IGP) qDijkstra uses seconds per Bell pair as the link cost, for an arbitrarily defined fidelity.  We will use F=0.98. It's not clear if that's the best way to do the recursion.

A *routing table* is the result of this routing process. If you looking for the detail of this routing process, please refer to this [paper](https://arxiv.org/pdf/1206.5655.pdf).
