# Running Basic QuISP Demos

## Included Demos

QuISP is delivered with a lot of working network files, most
configurations from Takaaki Matsuo's master's thesis.  You will want
to start instead from a set of basic demos:

- two nodes: a single link
- three link demo:  (MM, MIM, MSM) 
- straight line: three or four hops of one type of link (n.b.: not very useful until we have entanglement swapping!) (might have to make this one?)
- big demo: many nodes in a complex config (based on real ISP) `./quisp/networks/check_list/Tomography_networks.ispMap_1239_node_23_48_hetero_distance

## What the Heck am I Looking At?

If you are running a simulation properly, you will see two or more
nodes, which may be any of several different node types distinguished
by different icons, connected via links (simple black lines).
Messages exchanged are always "packets" in OmNET++.  ("Messages" are
also internal, software object-to-object things.)  We represent
individual photons, classical physical signals (e.g., synchronization
pulses), and larger, digital classical messages all via different
types of packets.  You will see these flowing between nodes, along
with labels that tell you what they are.

According to [one old
message](https://groups.google.com/forum/#!topic/omnetpp/5p1ufXvpDwA)
on the OmNET++ mailing list from a decade ago, the "packet" (photon or
classical message) colors derive from the message kind, an internal
field related to the message definition.  Modulo 8, the colors you see
are:

![MM_demo](img/demo_1.png)

```
0 = RED
1 = GREEN
2 = BLUE
3 = WHITE
4 = YELLOW
5 = CYAN
6 = MAGENTA
7 = BLACK
```

As of this writing, the colors (message kinds) assigned are as
follows:

```
RED	Just a photon in a burst. Not the beginning, nor the end.
GREEN	(not used?)
BLUE	(not used?)
WHITE	First or last photon in a burst (STATIONARY_PULSE_BOUND)
YELLOW	SPDC (symmetric parametric down conversion) control (sync
pulses, basically; classical physical signal)
CYAN	BSA (Bell state analysis) results (classical message)
MAGENTA	Link tomography results (memory measurement results?)
(classical message)
BLACK	Purification results (classical message)
```

(These color assignments seem to be artifacts of the coding; grep for
`setKind()` in the source code.)

## Important file types you will encounter

As you are leaping through the sources, you will encounter many file
types.  A few of the most important ones are listed here.

### `_dm` file

A density matrix file -- this is generated as an output of the
simulator.  It is an ASCII text file.  This is the only file type that
is _completely_ unique to QuISP; the rest come from or extend standard
OmNET++ files.

### `.ini` file

Especially `omnetpp.ini`.  This is the main file that drives your
simulation scenarios.  Works in conjunction with one (or more?) .ned
file(s).

### `.ned` file

Describes a network topology and hardware configuration.  Referenced
from the .ini file?
