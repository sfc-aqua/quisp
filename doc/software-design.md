# Software Design for QuISP

As we saw while [code spelunking](code-spelunking.md), the source code
is also [documented using doxygen](html/index.html).  You may wish to
attempt to match items from these design documents to some of the
code.

n.b.: Most of these design documents were created in a couple of
extended bursts of group work, actually quite some time ago.  After
that design work, implementation proceeded with most of the core
elements of the design intact, but we all know that a design never
survives the first attempt to implement it unaltered.  If you find
places where these docs differ from reality, we encourage you to
submit pull requests to make one conform to the other -- which way, we
will leave to your judgment.

Also, these designs document a dream: the initial releases are _far_
from completing all of this!  Especially, as of this writing, only
first-generation (1G) repeaters are implemented _at all_.  2G and 3G
are Future Work.

# Welcome to the QUISP project.

Our goals are

1. to determine if it is *possible* to build a
quantum Internet (defined as a global network of networks utilizing
very distinct technical approaches);
1. to assess the *robustness* of such an internetwork in the face of evolving
technology, deployment, and workload;
1. to establish some key *design decisions* that will help us build a robust, long-lived network; and
1. finally, to feed back what we have learned to the
experimental community to guide future development.

The simulator also serves as a platform for future development of
increasingly real-world source code, and for simulations of evolving
technologies and approaches.  We hope to make the simulator available
as a service via the web, and possibly to open source the simulator.

# Orientation #

- [Research Questions](Research Questions)
- [Terminology](Terminology)
- [Quantum State Representations](Quantum State Representations)
- [The story for a first SIGCOMM paper](The Story)

# Decisions #

- [Major Design Decisions](Major%20Design%20Decisions)
- [Major Functionality Descriptions](Major%20Functionality%20Descriptions)

# Nodes and Links #

- [Router Architecture](Router Architecture) (with links to hardware modules)
- [Router Software Architecture](Router Software Architecture) (with links to software modules)
- [Repeater](Repeater)
- [End Node](End Node)
- [BSA Node](BSA Node) (Bell State Analyzer)
- [EPPS](EPPS) (Entangled Photon Pair Source)
- [Channel](Channel)

# Networks, Protocols and Operations #

- [Path Setup](Path Setup)
- [Rule Sets](RuleSet)
- [Routing](Routing)
- [Resource Allocation](Resource Allocation)
- [Distributed Tomography and State Monitoring](Distributed Tomography and State Monitoring)

# Simulation #

- [SimulatorSourceStructure](SimulatorSourceStructure)
- [InitialRequirements](InitialRequirements)
- [Datasets](Datasets) we intend to collect to write papers with (reach topology and workload discussions through here)
- [Link Simulation Example](SimLink)
- [Simlating Errors](SimErrors)

# Other #

- [References](References)
- [[Open Issues Bucket]]
