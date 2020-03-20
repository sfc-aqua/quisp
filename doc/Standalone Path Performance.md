
*Note: this file is an early design document, but might be updated as the version goes up.*

# Research question #

Factors that might affect performance of a standalone path (either a chain that exists by itself, or a network with only a single active connection):

1. Number of AS boundaries crossed?
2. Does number of types of ASes crossed have an effect -- is two types better than three?
3. Does total E2E latency have more of an effect than we would
  naturally expect, either due to artificially introduced waits as a
  result of poor protocol design, or memory decay?

# Experiments to be run #

Datasets we need to answer this question:

* [[Baseline Dataset]]
* [[Isolated Dataset]]
