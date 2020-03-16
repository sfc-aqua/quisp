
*Note: this file is an early design document, but will be updated in the future.*

# Hardware Element: Optical Bell State Analyzer (OBSA) #

Rather than model beam splitters and photon detectors explicitly, we
will treat them as a unit here, and call it the BSA or OBSA.

For this simulation, without loss of generality, we are assuming that
inter-node entanglement is always generated using an OBSA.

* As a [standalone BSA node](BSA Node.md), appears in an [MIM
  Link](MIM_Link.md).
* As a component of a node, appears once in [MM Link](MM_Link.md) and
  twice in [MSM Link](MSM_Link.md).


## Simulation Parameters ##

Parameters:

    DetectionProbability
    ErrorProbability
    CycleTime

ErrorProbability is the probability that the photon is correctly
received, but that the measurement result differs from the actual
effect on the quantum state.  It should be calculated by incorporating
the measurement window and the dark count for a complete error
picture, so it is setting-dependent, but I don't think we need to
model that at this level.

CycleTime is how long it takes us to reset the detector for its next
use, including the measurement window itself.  The maximum number of
detection attempts/second is therefore 1/CycleTime.

