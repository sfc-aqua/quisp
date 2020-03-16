# Research Questions #

*Note: this file is an early design document, and we are still solving the following questions to make our simulator more sophisticated.
If you are interested in the basis idea behind QUISP (this quantum internet simulation package),please refer to the  [Internet Draft by Van Meter & Matsuo](https://tools.ietf.org/html/draft-van-meter-qirg-quantum-connection-setup-01)
(which, as of this writing, has expired, but will be revived).*

In investigating the design of a complete Quantum Internet, here are some of the questions we care about:

1. What level of [Quantum State Representation](Quantum State Representations) is appropriate for the model carried in software by routers and repeaters?
2. What factors affect the [standalone performance](Standalone Path Performance) of a connection on a heterogeneous path?
3. What factors affect the performance of a connection in [the presence of other traffic](Competition for Resources)?
4. Will we accidentally build a Q.I. in which some pairs of nodes can connect to each other successfully, [but not all](Unconnectable)?
5. Does a quantum Internet demonstrate behavior such as [[Congestion Collapse]]?
6. Does one particular technology make a better [[Backbone]]? If so, why?
7. How stable is the network behavior with respect to [changes](Evolving Network) in technology, deployment (topology and distance), and workload?
8. How do we determine how closely tomography is tracking changes to the physical system, for a real-world link?
9. How do we interleave monitoring (tomography) and user-allocated work on the links and connections?
10. Under what conditions is it beneficial to encode a QNIC memory qubit using QEC, and under what conditions are we better off leaving it as a raw physical qubit?
