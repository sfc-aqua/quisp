
*Note: this file is an early design document, but might be updated as the version goes up.*

# Repeater #

A Repeater node has exactly two external links, so that it is useful in a line only.  It is essentially a repurposed [QNIC](QNIC), with both halves of the card running the same [Network Type](Network Type). It also contains a simple [C4](C4).

A repeater does not need to run a full [Routing](Routing) protocol, since it has simple decisions on what the next hop is.