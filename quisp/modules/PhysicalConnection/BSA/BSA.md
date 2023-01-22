# Bell State Analyzer

In QuISP, we assume that there is an implicit mechanism for repeaters and end nodes to signal BSA node about the beginning and the end of the photon trains (e.g., strong light pulse before and after each train).

The BSA can be internal, inside a QNode, or external as a stand-alone node.

The BellStateAnalyzer module is the one processing the photons.

The BSA works like a state machine. It has 3 states,


BSA has 4 states: Idle, accepting, accepting_left, accepting_right (Q: should we stop after one leg is done?)
Pseudocode for BSA:

