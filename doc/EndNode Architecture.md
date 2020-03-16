# Quantum End Node Architecture #

*Note: This is an old design document, which we expect to still be useful, but it may or may not correspond well to the current implementation.

An end node has exactly one interface.  It has some similarities to a
[QNIC](QNIC.md) augmented with a [C4](Classical%20Chassis%20Control%20Card%20(C4).md), except that it has only
one block of transceiver qubits.

Parameters:

    TransceiverQubits
    BufferQubits

## Measurement-Only End Node ##

The second model of end node, which we aren't yet addressing but
probably should, is the measurement-only device.  For this, we would
need a model of a detector, which currently exists only as part of a
BSA.
