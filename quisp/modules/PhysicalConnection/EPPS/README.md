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

## Protocol Description

The EPPS controller sends EPPSTimingNotification to neighboring QNodes. Each QNode starts emitting photons at the specified time and time interval. Simultaneously, the EntangledPhotonPairSource continuously sends entangled photons to each QNode.

After performing a Bell state measurement, the result is sent back to the rule engine. Each emission iteration from the EPPS is counted locally at the QNode. If the result is a failure, it immediately releases the qubit used for that photon emission. Then, the QNode sends these results to its partner QNode. When a QNode receives a result from its partner, it compares the qubits with the same photon iteration count, and the following operations are performed:

Local BSM: fail | Partner BSM: success/fail
- No action is taken.

Local BSM: success | Partner BSM: fail
- Free the qubit that succeeded in the BSM.

Local BSM: success | Partner BSM: success
- Based on the results, correct the qubits.
- Save the information of the Bell pair in the bellpairstore.

Once the required number of qubits, as specified by the ruleset, are created, each QNode stops emitting photons and sends StopEPPSEmission to the EPPSController. When the EPPSController receives this message, the continuous emission from the EntangledPhotonPairSource also terminates.
