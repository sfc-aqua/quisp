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

Also, we ignore incoming photons for cases where there are no free memory. Therefore, when QNodeA does not have free memory and the QNodeB has free memory, QNodeB does not receive the BSM result from QNodeA, and for cases where the BSM at QNodeB succeeds, it cannot release the memory qubit forever. To counter this corner case, we set a timeout for each memory qubit, described in the pseudocode as `handle_link_timeout`.

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
       - Waiting time should be longer than the travel time to the partner
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
            1. Apply Pauli Z Gate to `qubit`\*
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

\* This operation is due to as follows.

We prepare the following entangled state at the beginning of the protocol.

- QNodeA releases entangled photon from memory in following state: $|\text{QNodeA}_{memory}, \text{QNodeA}_{photon}\rangle = \frac{1}{\sqrt{2}}(|00\rangle + |11\rangle)$.

- EPPS releases entangled photons in following state: $|\text{EPP}_{A}, \text{EPP}_{B}\rangle = \frac{1}{\sqrt{2}}(|00\rangle + |11\rangle)$.

- QNodeB releases entangled photon from memory in following state: $|\text{QNodeB}_{memory}, \text{QNodeB}_{photon}\rangle = \frac{1}{\sqrt{2}}(|00\rangle + |11\rangle)$.

After emission, we perform bsm between $|\text{QNodeA}_{photon}\rangle$  $|\text{EPP}_{A}\rangle$, and $|\text{QNodeB}_{photon}\rangle$  $|\text{EPP}_{B}\rangle$.

The quantum circuit for this operation is as follows. (the measurements are performed in computation basis. This quantum circuit is conceptional, so in an optical BSM, cases when EPA and EPB both measure state $|0\rangle$, result in a failure.)

```
     ┌───┐          ┌───┐
QAM: ┤ H ├──■────■──┤ H ├───────────────────
     └───┘┌─┴─┐  │  └───┘┌─┐
QAP: ─────┤ X ├──┼───────┤M├────────────────
     ┌───┐└───┘┌─┴─┐ ┌─┐ └╥┘┌───┐
EPA: ┤ H ├──■──┤ X ├─┤M├──╫─┤ X ├───────────
     └───┘┌─┴─┐└───┘ └╥┘  ║ └─┬─┘     ┌─┐
EPB: ─────┤ X ├───────╫───╫───┼───────┤M├────
     ┌───┐└───┘       ║   ║   │  ┌───┐└╥┘┌─┐
QBP: ┤ H ├──■─────────╫───╫───■──┤ H ├─╫─┤M├
     └───┘┌─┴─┐       ║   ║      └───┘ ║ └╥┘
QBM: ─────┤ X ├───────╫───╫────────────╫──╫─
          └───┘       ║   ║            ║  ║
reg: ═════════════════╩═══╩════════════╩══╩═

QAM: QNodeA_memory, QAP: QNodeA_photon, EPA: EPP_A, EPB: EPP_B, QBP: QNodeB_photon, QBM: QNodeB_memory
```
With simple calculation we can see that the state after this operation is $|\text{QNodeA}_{memory}, \text{QNodeB}_{memory}\rangle = \frac{1}{\sqrt{2}}(|00\rangle + (-1)^{\psi^{A}+\psi^{B}}|11\rangle)$, where $\psi^{A/B}$ is the result of the BSM at QNodeA/B, with values $\psi^{A/B} = 0$ for obtaining $|\psi_{+}\rangle$ and $\psi^{A/B} = 1$ for $|\psi_{-}\rangle$.

Therefore, we need to apply a Pauli Z gate to either memory qubit if $\psi^{A}$ is not the same value as $\psi^{B}$.
