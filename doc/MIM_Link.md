# MIM Link #

*Note: This is an old design document, which we expect to still be useful, but it may or may not correspond well to the current implementation.

## Timing ##

The timing of transmission on the two link halves must be dictated by
the midpoint [BSA Node](BSA%20Node.md) (Bnode).

The Bnode must determine the latency to each of the two endpoints to
high precision (sub-nanosecond), and instruct the two endpoints
accordingly in order to arrange for photons to arrive within a timing
window sufficiently precise to allow them to interfere on a beam
splitter.  (The required precision might be e.g. a 1.5nsec timing
window, as in _which paper?  Schuck et al., PRL 96, I believe._)

The Bnode orders a burst of transmissions; if each endpoint has 100
transceiver qubits, and can emit at 1nsec intervals, for example, that
would be a 100nsec burst.  If the distance from the Bnode to the
endpoint is 10km, at 5nsec/m = 5usec/km = 50usec/10km one way =
100usec round trip in fiber, such a burst happens only once every
100usec.

Interesting inefficiencies develop when there is an imbalance, with
one endpoint having more transceiver qubits than the other.  If one
has 10 transceiver qubits and the other has 100, then 90 qubits at the
larger end are simply wasted in this architecture.

