# Network #

*Note: this file is an early design document, so some of the terminology has likely changed.*

* A *network* is a set of connected nodes that all use the same error management technology, connected via links.

# Node #

A *node*:

  * attaches to one or more quantum channels
  * has a single, unified classical controller

A node may be one of three types:

  * (E) *End node*: Has exactly one interface.
  * (R) *Repeater*: built from exactly one line card, with exactly two interfaces, internally homogeneous device, internal operations all done via local gates; may incorporate H-O-M device, or may not.
  * (X) *Router*: two or more line cards, connected via optical backplane; heterogeneous Bell pairs may be created between line cards.

Note that the following are *not* nodes:

  * (S) *Standalone entangled photon pair source (EPPS)*.
  * (B) *Standalone Bell State Analyzer (BSA)*.

Those two devices, when they exist, are incorporated into the model of
a *link*.  They can stand alone, or be incorporated into a router QNIC or
a repeater.

# Link #

A *link* is a point-to-point system for creating entanglement.

A *link* may include the H-O-M entangler or EPPS.

# Module #

Nodes and links are built from *modules*:

* Dur-Briegel QNIC
* Fowler QNIC
* Jiang QNIC
* Bell State Analyzer (e.g., a Hong-Ou-Mandel dip detection setup)
* Entangled photon pair source (EPPS)
* Switch (Crossbar)
* Wavelength conversion (not modeled here)
* Channel
* Couplers (passive sources of loss)

Modules are built from *components*.

# Component #

Hardware components. TBD.
