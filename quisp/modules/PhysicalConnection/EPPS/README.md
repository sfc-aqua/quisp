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

We will show a pseudocode for the protocol below.


**Global variables:**

- `photon_index`: Variable to specify the entangled photon pair. We perform post-processing among memory qubits that share the same value of this variable.

- `success_list`: List to store the information of memory qubits that succeeded local BSM. Contains the qubit information and the correction information.

**Pseudocodes**:

### Function to emit photons from qnodes in msm links

**Input:**
- Interval of emission specified by the EPPSTimingNotification: `interval`
---
**function** `emit_photons_msm(interval)`
1. `photon_index` \gets `photon_index` + 1
1. **If** There exist free memory qubits **then**
    1. Pick a free memory qubit and emit a photon from it
1. Call `emit_photons_msm(interval)` after interval
---
### Function to handle the click result

**Input:**
- BSM success result: `success`
- BSM correction operation: `correction`
- Memory qubit which emitted photon for this BSM: `qubit`
---
**function** `handle_click_result(success, correction, qubit)`
1. **If** `success` **then**
    1. Append `qubit` and `correction` to `success_list`
    1. Call `handle_link_timeout(qubit)` after $1.1 \times$ `travel_time`
       - *Comment:* Waiting time should be longer than the travel time to the partner
1. **Else**
    1. Free `qubit`
1. Send `success, correction, photon_index`

---
### Function to handle the link generation result

**Input:**
- Partner BSM success result: `success`
- Partner BSM correction operation: `correction`
- Photon index the partner performed BSM with: `photon_index`
---
**function** `handle_msm_result(success, correction, photon_index)`
1. **If** found `photon_index` in `success_list` **then**
    1. Set `correction_local` $\gets$ `success_list[photon_index].correction`
    1. Set `qubit \gets success_list[photon_index].qubit
    1. **If** `success` **then**
        1. Set `qubit.handled` $\gets$ True
        1. **If** (`correction = correction_{local}` and `Addr_partner < Addr_self`) **then**
            1. Apply Pauli Z Gate to `qubit`
            1. Save bell pair information
    1. **Else**
        1. Free `qubit`
---

### Function to handle the timeout

**Input:**
- Memory qubit: `qubit`
---
**function** `handle_link_timeout(qubit)`
1. **If** (`qubit.handled` = False) **then**
    1. Free `qubit`
1. Set `qubit.handled` $\gets$ False
---
