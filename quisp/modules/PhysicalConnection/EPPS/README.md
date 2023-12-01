# EPPS Modules and the MSM Protocol

The EPPS component in QuISP consists of two modules: the EntangledPhotonPairSource and the EPPSController. The EntangledPhotonPairSource is a physical module responsible for emitting entangled photon pairs from its two ports. On the other hand, the EPPSController handles the messaging and signaling of neighboring QNodes, sending emission partner information, and indicating when the first photon should arrive.
## EntangledPhotonPairSource Module

The EntangledPhotonPairSource simply emits entangled photon pairs when called by the EPPSController.
## EPPSController Module

The EPPSController manages the messaging and signaling of neighbor QNodes in the MSM protocol. It is also responsible for sending emission partner information to the neighboring QNodes and specifying when the first photon should arrive.
## Usage

To use the MSM protocol, you need to configure several parameters in the NED file. Below, a simple example with comparision to the MIM protocol is provided.

```ned
// MIM
    submodules:
        EndNode1: QNode
        EndNode2: QNode
        BSA: BSANode
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> BSA.port++;
        BSA.port++      <--> ClassicalChannel {  distance = 0.5km; } <--> EndNode2.port++;
        EndNode1.quantum_port++ <--> QuantumChannel {  distance = 0.5km; } <--> BSA.quantum_port++;
        BSA.quantum_port++      <--> QuantumChannel {  distance = 0.5km; } <--> EndNode2.quantum_port++;

// MSM
    submodules:
        EndNode1: QNode
        EndNode2: QNode
        EPPS: EPPSNode
    connections:
        EndNode1.port++ <--> ClassicalChannel {  distance = 0.5km; } <--> EPPS.port++;
        EPPS.port++      <--> ClassicalChannel {  distance = 0.5km; } <--> EndNode2.port++;
        EndNode1.quantum_port_receiver_passive++ <--> QuantumChannel {  distance = 0.5km; } <--> EPPS.quantum_port++;
        EPPS.quantum_port++      <--> QuantumChannel {  distance = 0.5km; } <--> EndNode2.quantum_port_receiver_passive++;
```
The description is similar to MIM. We just have to replace BSANode with EPPSNode and the QNode's quantum_port with quantum_port_receiver_passive.

## MSM protocol details which take part in EPPS modules

The EPPS controller sends EPPSTimingNotification to the neighboring QNodes. Then, the EntangledPhotonPairSource sends entangled photons to each QNode, at the time and with the interval specified by EPPSTimingNotification.Once the required number of qubits, as specified by the ruleset, are created, each QNode stops emitting photons and sends StopEPPSEmission to the EPPSController. When the EPPSController receives this message, the continuous emission from the EntangledPhotonPairSource also terminates.
