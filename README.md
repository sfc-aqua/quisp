# QUISP
![travis](https://travis-ci.com/sfc-aqua/quisp.svg?branch=master) <a href="https://aqua-quisp.slack.com/" rel="nofollow"><img src="https://img.shields.io/badge/join-us%20on%20slack-gray.svg?colorB=red&amp;logo=slack&amp;longCache=true" alt="Slack Widget"></a>  
The Quantum Internet Simulation Package (QuISP) is an event-driven
simulation of quantum repeater networks, which will be the foundation
of the coming Quantum Internet.  QuISP's goal is to simulate a full
Quantum Internet consisting of up to 100 networks of up to 100 nodes
each.  Its focus is on protocol design and emergent behavior of
complex, heterogeneous networks at large scale, while keeping the
physical layer as realistic as possible.

QuISP is a product of the Advancing Quantum Architecture (AQUA)
research group headed by Prof. Rodney Van Meter, at Keio University's
Shonan Fujisawa Campus, Fujisawa, Japan.  See 
[http://aqua.sfc.wide.ad.jp](http://aqua.sfc.wide.ad.jp) and the list
of [Authors](Authors.md).

## Research questions

A simulator is one or more of three things: a time machine, an X-ray
machine, or a telescope.  It can be used to look into the future or
the past, look at the internals of an object that are otherwise
inaccessible, or look at objects of a far vaster scale than can be
built in a laboratory.  QuISP is, perhaps, most importantly a
telescope: we are looking at large-scale quantum networks and
ultimately the Quantum Internet, but we do also pause to look at the
micro (local) behavior of protocols, as well.

Research questions we hope to answer:

* Emergent behavior
    - Classical networks exhibit _congestion collapse_;
      are quantum networks subject to the same thing?
    - Will the dynamics of large networks prevent us from making
      end-to-end connections under realistic scenarios, even when a
      naive model suggests it should be possible?
    - Are there other unexpected behaviors in large-scale networks?
* Protocol design
    - Testing of detailed protocol designs to validate correct
      operation.
    - Are there interactions between the classical and quantum
      portions of the network?
* Connection architecture and performance prediction
    - All three proposed network generations exhibit complex behavior
      that makes analytic prediction of performance difficult with
      realistic parameters; simulation, of course, will require the
      best effort we can make at validation, as well.
* Dynamic behavior
    - Are networks stable as conditions change?
    - When a topology change occurs, how do the protocols respond?
    - Network traffic will be dynamic; can our multiplexing and
      resource management protocols adapt so that new connections
      are given service in a reasonable time, and ongoing connections
      continue to receive expected levels?

## Simulation goals

We have a number of long-term goals for development of the simulator:  

* Complex network topologies, including the notion of network
  boundaries and heterogeneity at the physical and logical levels
* support 1G, 2G and 3G quantum networks, utilizing either purify-and-swap (1G)
  or quantum error corrected (QEC) (2G and 3G) protocols for managing
  errors
* Distinct link architectures: memory-to-memory (MM), midpoint
  interference (MIM), and midpoint source (MSM), sneakernet, satellite
* Internetworking protocols for connecting different types of networks
* Various applications running in complex traffic patterns

Because these protocols can result in hundreds of qubits in a single
entangled state, and the entire system may consist of up to a million
qubits, simulation at the physical Hamiltonian level or even just
above that at the unitary (gate, e.g. CNOT) level is infeasible.  We
cannot calculate and store full density matrices for such states.
Instead, like simulators for large-scale error correction, QuISP
operates primarily in the _error basis_, in which we maintain a
description of errors the states have incurred rather than the full
state.  However, unlike most QEC simulators, QuISP supports non-Pauli
errors, in a limited fashion.

QuISP is almost endlessly configurable; for example, it is possible to
set not only different lengths for different links in the network, but
also different gate error rates and memory lifetimes on individual
qubits.  Non-Pauli errors that are at least partially supported in the
current release include qubit loss, relaxation to ground state,
excitation to excited state, and complete mixing.

If you are unfamiliar with the research literature or the terminology
above, see "Learning more", below.

In addition, we aim to make simulations run on QuISP _completely
reproducible_, to the extent humanly possible.  It will be possible
for others to verify work done using QuISP if they have the name of
the QuISP release, version numbers for supporting software, the `.ini`
file, any changed `.ned` files, and the seed for the pseudo-random
number generator.

## Current status

Most of the _infrastructure_ is up and running, though the sets
of actual experiments (interesting simulations) you can do are fairly
limited still.

Working infrastructure:

* All of the basic OMNeT++ functionality, such as events,
  visualization, logging, analysis, etc.
* Complex network topologies, defining per link parameters including
  length, channel error rates, numbers of qubit memories, gate error
  rates, etc.  (You will see the included demonstration networks in
  the documentation linked below.)
* A complete internal model of the software architecture for a
  repeater, including a connection manager, the RuleSet execution
  engine, real-time tracking of quantum states, etc.

Besides the obvious joys of the endless network configurability, here
are the key quantum protocols that are implemented:

* basics of RuleSet creation & distribution
* various *purification protocols*:  Single round
  of X purification, alternating X/Z purification, etc.  Currently
  implemented only over a single hop.  Extending
  these to test your own custom purification protocol is pretty
  straightforward.
* *tomography*: when the simulation boots, it assumes that the software
  at each end of each link knows _nothing_ about the link, so it
  begins by performing tomography on the links.  (This is actually
  problematic, because it turns out to take a long time for tomography
  to converge, which means a lot of boot-up time in the simulation
  before other interesting things start to happen.  We are
  working on a way to pre-calculate this, so that you can choose to
  either include tomography or not.)
* *entanglement swapping*.

Current generic networking-level status:

* fully blocking circuit switching
* random pairwise traffic pattern (flat distribution)

In-progress work:

* entanglement swapping is a relatively new feature, and taking data
  using it is still not fully implemented
* although the connection setup protocol works, the teardown on
  completion of a connection still needs a little love
* the set of demo networks is still being polished

Upcoming features in near-term releases:

* more general resource allocation & multiplexing
* more general mechanism for establishing traffic patterns
* MSM links
* graph states at the link level
* multi-party states at the application level

Mid-term to long-term release features:

* 2G networks, esp. Jiang style
* full quantum internetworking

## Installation requirements

The full installation process is described in
[doc/INSTALL.md](doc/INSTALL.md).  The main software tools you will
need are:

* QUISP requires [OmNET++](https://omnetpp.org/) and
* an external C++ library, [Eigen](http://eigen.tuxfamily.org/), to
  work.
* To contribute to QuISP development, you will also need to be
  familiar with at least the basics of [git](https://git-scm.com/).
* We recommend the use of [Doxygen](http://www.doxygen.nl/) for source
  code comments, but the Doxygen tools are not required unless you
  want to build the source code documentation.

Depending on your local setup and how you intend to use QuISP, you may
also need various tools (a C++ compiler, make, an X Windows server,
Docker, ffmpeg for making videos, etc.), documented in the installation notes.

## Building and running

First see [doc/INSTALL.md](doc/INSTALL.md), then follow the instructions below.

There are two main ways of working with QUISP. You can either use the
Eclipse-like graphical interface of OmNET++, for which you will find
instructions in [doc/USAGE-omnetpp-gui.md](doc/USAGE-omnetpp-gui.md),
or you can use the `Makefile` and GNU make, by looking at instructions
in [doc/USAGE-makefile.md](doc/USAGE-makefile.md). Some operations are
implemented in the Makefile and not explained for the graphical user
interface.

## Moving into useful work

Once you have gotten this far, you should be able to [run some of the
most basic demos](doc/running-demos.md).  Next, you'll want to learn
how to create your own test networks, and how to extend the source
code for your own uses.

When you are ready to start contributing, you can start reading the
code, as [we have done](doc/code-spelunking.md).

You will also want to look at some of the [software design documents](doc/software-design.md).

## Development tools

A few tools (mainly scripts) can be used to make development a bit easier.
Look around in the `bin` folder of this project.

## Is QuISP right for me?

Fundamentally, the point of QuISP is that *networks are much more than
point-to-point connections*.

If you want to know about the behavior of systems and networks, to
study behavior of links that are too complex for simple analytic
equations (esp. those with multiple qubits per link) or to contribute
to the design of network protocols, QuISP is the simulator for you.
If you're trying to adjust detector window timing v. entanglement
fidelity, or figure out what Q factor your cavity needs to be, or
understand dispersion in a fiber, it might not be.

## Learning more

See the [references](doc/References.md).

## Contributing

First, join the [QuISP Slack team](https://aqua-quisp.slack.com).

Please also refer to the [code of conduct](CODE_OF_CONDUCT.md).

## License

QuISP was initially released on April 5, 2020, and is
[licensed](LICENSE) under the [3-Clause BSD License](https://opensource.org/licenses/BSD-3-Clause).

QuISP builds on OMNeT++.  OMNeT++ itself is a [custom
license](https://omnetpp.org/intro/license), open source and free for
academic use, but a license fee required for commercial organizations.
QuISP also requires the linear algebra library Eigen, where license is
MPL2, and so [probably not an
issue](http://eigen.tuxfamily.org/index.php?title=Main_Page#License).
