# Distributed Tomography and State Monitoring #

*Note: This is an old design document, which we expect to still be useful, but it may or may not correspond well to the current implementation.

Full tomography (or just "tomography") is essentially exhaustive
testing of an ensemble of states prepared the same way, to test either
the state itself ("state tomography") or the accuracy of the gate or
preparation process ("process tomography").  See Kwiat for basic
tutorial on full tomography, recent papers by Robin Blum-Kohout for
valuable shortcuts.

We need to do this in a distributed fashion, which is a process that
no one seems to really fully understand yet. See rdv's upcoming paper,
"Distributed Management of Density Matrices," for some thoughts on how
to do this.

See the [God Channel](God%20Channel.md) for a discussion of the
relationship between simulation of the underlying physical system and
our network-level understanding of the state.

Note that the selection of states to be used for tomography must be
coordinated with the partner node, and that the sequence of base
Bell pairs used for tomography must be cryptographically securely
selected.  Coordinating this with the RuleEngine is necessary in the
real world, but probably not used in these simulations.

*Add a diagram here, such as a figure from my upcoming paper.*

# Link-Level Monitoring #

Link-level monitoring is the responsibility of the
[HardwareConfigManager_Methods](HardwareConfigManager_Methods.md).
It will be carried out on an ongoing basis to determine parameters of
the link, fed to the [Routing Daemon](Routing%20Daemon.md).

*This will be dummied out in our current round of simulations, instead
 specified in a config file.*

# Multi-Hop Monitoring #

We ultimately need some monitoring done over multiple hops, especially
end-to-end.  It's not clear to me yet how to incorporate this into
[Rule Sets](RuleSet.md), or whether it should even be some out-of-band
monitoring, performed only at the end points by the application.  My
belief is that it should be done at the network level, probably border
router to border router, but figuring out how to manage that is
tricky.

# Open Issues #

1. See above, how to implement multi-hop monitoring.

