# Satellite Communication with QuISP

## Quick Start

To run a simulation with a satellite link, choose one of the SAT configurations in the `simulations_test.ini` file. To design your own, use Sat nodes both at the ground and at the space end of the link, specifying `is_satellite=true` in the parameters of the satellite node. You should provide two .csv files: one with `time (s),distance (m)` pairs and one with `time (s), atmospheric attenuation` pairs. The atmospheric attenuation quantity is _not_ expected to be in dB: it corresponds to what is defined in the _Methods_ section of [this paper](https://www.nature.com/articles/s42005-022-01123-7) as `10^(A_{atm,x}(t)/10)`.

## Code Breakdown

Enabling satellite communication with QuISP relies on three fundamental elements: the `PointingSystem`, the `GatedQueue` and the `Free Space Channel`.

### The Gated Queue

The purpose of `GatedQueue` is to buffer classical messages when the receiving node is not visible and therefore cannot receive messages.
This module works as an extension of the already present `Queue` module: whereas the original module was just in charge of queueing the packets that are incoming and outgoing from a given node, the `GatedQueue` adds a layer of control logic to the outgoing section. Whenever an outgoing message is ready to be sent, the `GatedQueue` runs a visibility check by generating a `VisibilityCheckRequest` packet and sending it to the `PointingSystem`. If the outcome of the visibility check is favorable (i.e. `NextCheckTime = 0`), the packet is sent normally. If not, another visibility check is run at `t + NextCheckTime`.

### The Pointing System

This module is in charge of simulating the acquisition, pointing and tracking between the satellite and the ground nodes. In practice, this node receives a `VisibilityCheckRequest` (VCR) packet and replies with a `VisibilityCheckOutcome` (VCO) packet, which contains the `NextCheckTime` variable, i.e. the time interval to wait for the satellite to be visible again. If the satellite is already visible, `NextCheckTime` is 0.

### The Free Space Channel

`ClassicalChannel_FS` and `QuantumChannel_FS` are two new channel objects that model the variable attenuation and delay that comes with free-space communication with a moving node. By parsing CSV files that specify the length and atmospheric attenuation of the satellite link, these channels recalculate link parameters as part of the `processMessage` method. Nodes should have a `PointingSystem` that checks whether there is visibility before communicating: if a message is sent through a free-space channel when the receiving node is not visible, it is discarded by the channel. 

## Modifications to existing components

Most of QuISP's internals worked seamlessly over the transition to satellite communication. However, a couple lines of code required tweaking:

- The (active) BSA and EPPS controllers calculate the time at which photon emission should happen and share it with their passive partners. Every time entanglement needs to be established, the active node schedules emission at `now + LinkDelay` and instructs the passive node to attempt latching qubits in memory at `now + 2LinkDelay`, to account for the latency of the link and emit synchronously. In the original code, the (fiber) link delay can be calculated once and cached. However, a satellite link must account for the varying delay of a free-space link. Due to hardware constraints, it is unfeasible to recalculate the photon emission delay for every single photon, so the time interval between photon is left constant. What is changed is the emission time of the first photon of each train: every time an active node needs to start entanglement generation, it reads the orbit data in order to calculate what the link delay is now (`CurrentLinkDelay`) and what it will be after the photon request arrives at the receiving node (`PredictedLinkDelay`). Then, it schedules local emission for `now + CurrentLinkDelay` and instructs the passive node to emit at `now + CurrentLinkDelay + PredictedLinkDelay`. This way, the first photon of every emission train lines up perfectly. Although the rest of the train slowly drifts out of sync, it is not enough to disrupt entanglement generation even at low indistinguishability window values. A note should be made on EPPS links: since they work with continuous emission by making each photon the first and last of its respective train and using the inter-train delay as interval between photons, it is not possible to apply this modification directly. The (hacky) solution that was implemented was to schedule a periodic recalculation of the photon emission time. The time interval at which resynchronization is performed is a tunable parameter.

- The `RuleEngine` code was tweaked to reject a TimingNotification (BSA and EPPS) if it has a `first_photon_emit_time` that precedes the current `simTime()`. This of course never happens in the fiber case, but it covers the edge case of when the TimingNotification is generated with the satellite out of sight and sent when visibility is established again. Without this failsafe measure, Omnet++ produces an error when the `TimingNotification` is received and photon emission cannot be scheduled for a past time.

### Acknowledgements

Thank you very much to Valentina Marulanda Acosta and Matteo Schiavon for providing the example data included in the `satellite_csvs` directory.
