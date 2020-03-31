
*Note: this file is an early design document, but might be updated as the version goes up.*

# Quantum Router (Repeater) Software Architecture #

A router has multiple hardware elements, but a single software controller. This page describes the architecture of that software. For more details on the hardware, see the  [Router Architecture](/Router Architecture) page.

![Router software arch.PNG](img/716978964-Router%20software%20arch.PNG)

# Software Modules #

There are five major modules:

1. [Connection Manager](Connection%20Manager.md): One per system.
2. [Rule Engine](Rule%20Engine.md): One per system. The heart of the online operation, creating end-to-end entanglement.
3. [Routing Daemon](Routing%20Daemon.md): One per system.
4. [Hardware Configuration Manager/Monitor](HardwareConfigManager_Methods.md): One per system.
5. [Real-Time Hardware Controllers](Real-Time%20Hardware%20Controller.md): One per independent quantum hardware module. These are our device drivers.

In addition, to complete the simulation, there are [Hardware Element Simulation](Hardware Element Simulation) to simulate the individual hardware modules (and accompanying quantum states), [Workloads](Workloads) and drivers of the entire simulation.

# Internal Inter-Module Interfaces #

Whether internal communications are to be done through pipes or some more direct API is TBD.

1. CM-RE: [RuleSet](RuleSet.md).
1. RE-RTHC: [Physical Gate](Physical%20Gate.md).
1. HM-RTHC: [Physical Gate](Physical%20Gate.md).
1. RD-HM: [Link State](Link%20State.md).
1. CM-RD: [Route Request](Route%20Request).

# External Communications #

For our purposes, we will assume that all external communications are via TCP/IP. Three of the modules may communicate with other routers:

1. The Routing Daemon communicates with neighbors, via e.g. qOSPF or qBGP.  Background communication.  Connections created at boot time only, for our current simulation purposes.

2. The Connection Manager responds to connection requests received from other nodes. Connection setup, so a regular operation but not high bandwidth, relatively low constraints.  Connections from nearest neighbors only.

3. The Rule Engine has to notify partners about changes to the quantum states. Soft real-time, important stuff.  May be either neighbors or other partners, for purify-and-swap networks.

For details, see the respective pages on the software modules.

# Simulation Considerations #

Since this will be implemented on Omnet++:

1. Router Software is an object; each separate router is an instance of that architecture.

2. From node to node, communication is done via Omnet Message.

3. From "process" to process inside a router, communication may be just method invocations for synchronous stuff, but anything that involves representation of time has to be done as an Omnet message.

