
*Note: this file is an early design document, but might be updated as the version goes up.*

# Quantum Repeater Architecture #

A repeater has exactly two interfaces, and is much like a
[QNIC](QNIC.md) augmented with a [C4](Classical Chassis Control Card (C4).md).

In theory, it is possible to build a repeater using only a single set
of transceiver qubits and an accompanying optical switch, but I think
it's okay to assume that two separate sets of transceivers are used,
without undue loss of generality and flexibility in the simulations.
