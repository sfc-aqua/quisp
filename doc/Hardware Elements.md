
*Note: this file is an early design document, but will be updated in the future.*

# Hardware Elements #

A node or link can be composed of the following:

* [Optical Channel](HE_OptChannel.md)
* [Optical Switch](HE_OptSwitch.md)
* [Optical Bell State Analyzer (OBSA)](HE_OBSA.md)
* [Memory](HE_Memory.md)
* [Entangled Photon Pair Source (EPPS)](HE_EPPS.md)

Other elements that we are _not_ explicitly addressing as separate
items in this simulation:

* Wavelength converter
* Detector (exists, at the moment, only as part of OBSA, but could be
  useful for measurement-only end nodes)
* Single-photon source (we're assuming all photons are created
  entangled, either as a pair of photons from an EPPS, or via emission
  from a quantum memory)
