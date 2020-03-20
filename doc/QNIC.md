
*Note: this file is an early design document, but might be updated as the version goes up.*

# QNIC: Hardware and Software #

Specifying a QNIC consists of both hardware and software.

A QNIC consists of a set of transceiver qubits facing the external
(MAN) link, known as the InterNode subsystem, an optional Buffer
memory not connected to any optical channels (currently called the
Connector, though I now think that's not a great name), and a set of
transceiver qubits facing the optical interconnect between QNICs,
known as the InterQNIC.

The buffer in the middle is the key.  It is technically optional, but
important for performance and critical for ensuring that qubits are
not tampered with by external hackers, as in the blinding attacks by
the Makarov group.

## Software Behavior ##

    ErrorManagementMethod
        LinkCodeFamily: { Jiang, Fowler, Purify, OneEPP, None }
        LinkCode: { Steane, Surface, None } (others possible)
        CodeSpecificParameters: e.g. CodeDistance

## Hardware Elements ##

    CData: ClassicalRegister
        NumBits
    InterQNIC: HalfCardHardware
        NumPhyQubits
        XmitterRate (governed by qubit reinit)
    ConnectorHardware
        BufferSize
    InterNode: HalfCardHardware
        NumPhyQubits
        XmitterRate (governed by qubit reinit)
    BellStateAnalyzer (optional)
        Duration
        LossProb
        ErrorProb
    Channel
        Distance (gives us loss and latency)
        SystemLoss (any additional loss)

(It's not clear that the ClassicalRegister needs to be modeled in this
simulation.)

## Other ##

See [QNIC_Methods](QNIC_Methods) for the methods provided to the
RuleEngine.
