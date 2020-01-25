# QUISP

The Quantum Internet Simulation Package (QuISP) is an event-driven
simulation of quantum repeater networks, which will be the ultimate
foundation of the coming Quantum Internet.  QuISP's goal is to
simulate a full Quantum Internet consisting of up to 100 networks of
up to 100 nodes each.  Its focus is on protocol design and emergent
network behavior, while keeping the physical layer as realistic as
possible.

QuISP is a product of the Advancing Quantum Architecture (AQUA)
research group headed by Prof. Rodney Van Meter, at Keio University's
Shonan Fujisawa Campus, Fujisawa, Japan.
[http://aqua.sfc.wide.ad.jp](http://aqua.sfc.wide.ad.jp)

Research questions we hope to answer:

(To be filled in.)

Long-term goals of the simulator:  

* Complex network topologies, including the notion of network
  boundaries and heterogeneity at the physical and logical levels
* support 1G, 2G and 3G quantum networks, utilizing either purify-and-swap (1G)
  or quantum error corrected (QEC) (2G and 3G) protocols for managing
  errors.
* Internetworking protocols for connecting different types of networks
* Various applications running in complex traffic patterns

Because these protocols can result in hundreds of qubits in a single
entangled state, and the entire system may consist of up to a million
qubits, simulation at the physical Hamiltonian level or even just
above that at the unitary level is infeasible.  We cannot calculate
and store full density matrices for such states.  Instead, like
simulators for large-scale error correction, QuISP operates primarily
in the _error basis_, in which we maintain a description of errors the
states have incurred rather than the full state.  However, unlike QEC
simulators, QuISP supports non-Pauli errors, in a limited fashion.

If you are unfamiliar with the research literature, see "Learning
more", below.

## Installation requirements

QUISP requires OmNET++ and external C++ libraries to work. The full installation
process is described in [doc/INSTALL.md](doc/INSTALL.md).

## Building and running

There are two main ways of working with QUISP. You can either use the Eclipse-like
graphical interface of OmNET++, for which you will find instructions in
[doc/USAGE-omnetpp-gui.md](doc/USAGE-omnetpp-gui.md), or you can use the `Makefile` and GNU make,
by looking at instructions in [doc/USAGE-makefile.md](doc/USAGE-makefile.md). Some operations are
implemented in the Makefile and not explained for the graphical user interface.

## Development tools

A few tools (mainly scripts) can be used to make development a bit easier.
Look around in the `bin` folder of this project.

## Learning more

See [doc/References.md](doc/References.md) for more information on the
research underlying QuISP.
