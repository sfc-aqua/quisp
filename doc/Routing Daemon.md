# Routing Daemon #

*Note: this file is an early design document.  As of this writing,
 routing in the simulation is done using simulation magic.
 Implementing a full routing protocol is one of the fun tasks waiting
 to be done!*

The Routing Daemon is one of the Big Five processes in our [Router
Software Architecture](Router%20Software%20Architecture.md).  It
communicates with neighbors to exchange information about links that
are up or down, and to calculate routes on the network, via e.g. qOSPF
or qBGP.  This operates as a background process.  The RD collects
information from the [Hardware
Monitor](HardwareConfigManager_Methods), and responds to queries for
best path information from the [Connection Manager](Connection
Manager).
