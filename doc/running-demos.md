# Running Basic QuISP Demos

## Included Demos

QuISP is delivered with a lot of working network files, most
configurations from Takaaki Matsuo's master's thesis.  You will want
to start instead from a set of basic demos:

- two nodes: a single link
- three link demo:  (MM, MIM, MSM) 
- straight line: three or four hops of one type of link (n.b.: not very useful until we have entanglement swapping!) (might have to make this one?)
- big demo: many nodes in a complex config (based on real ISP) `./quisp/networks/check_list/Tomography_networks.ispMap_1239_node_23_48_hetero_distance

## Opening a Simulation

(If you arrived here from [Build on Windows](Build_on_windows.md),
some of this will look redundant; if not, we encoourage you to skim
that document regardless of your platform.)

You should see a screen almost like this in the OMNeT++ IDE.

![ide-opening-tutorial.png](ide-opening-tutorial.png)

In the upper left panel, each of the subdirectories is probably
closed.  Click on `networks` and scroll down until you find
`quisp_tutorial.ini`.  Click on it, and your screen should look much
like the one above.

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
![MM_demo](img/demo_1.png)
According to [one old
message](https://groups.google.com/forum/#!topic/omnetpp/5p1ufXvpDwA)
on the OmNET++ mailing list from a decade ago, the "packet" (photon or
classical message) colors derive from the message kind, an internal
field related to the message definition.  Modulo 8, the colors you see
are:

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

## Finding and interpreting the results

**kaaki, help fill this in!!!***

## Important file types you will encounter

As you are leaping through the sources, you will encounter many file
types.  A few of the most important ones are listed here.

### `_dm` file

A density matrix file -- this is generated as an output of the
simulator.  It is an ASCII text file.  This is the only file type that
is _completely_ unique to QuISP; the rest come from or extend standard
OmNET++ files.

This file is described in Appendix A.2.2 of Takaaki Matsuo's master's
thesis.

### `.ini` file

See especially the default file `omnetpp.ini`.  This is the main file
that drives your simulation scenarios.  Works in conjunction with one
`.ned` file(s).

`.ini` files can be created by hand, or edited using the OmNET++
built-in editor.  The files are described in Ch. 3 of the OmNET++ User
Guide, available [here](https://omnetpp.org/documentation/).

For the examples here, find and open `quisp_tutorial.ini`.  This simple
example contains five `Config` statements, each of which specifies a
`network`.  There are no other parameters in this simple tutorial, but
for a complex experiment, this file will be very long and will
specify values for many of the parameters in Appendix A.2.1 of
Matsuo's master's thesis.

### `.ned` file

Describes a network topology and hardware configuration.  Each `.ned`
file contains one or more `network` blocks, listing all of the nodes
and links.

`.ned` files can be created by hand, or edited using the OmNET++
built-in editor.  The files are described in Ch. 2 of the OmNET++ User
Guide, available [here](https://omnetpp.org/documentation/).

Find the file `topology_linear_network.ned`.  It should contain four
of the five demo networks listed above.  Inside a network block, you
will find nodes of type `repeater`, `HoM`, etc.  The definitions of
_those_ network types are automatically found from _other_ .ned
files; in this case, files named `qnic.ned`, `qrsa.ned`,
`QNode.ned`, and `channels.ned`.  Those define, among other things,
default values for parameters that you may override in the .ini file,
e.g. the default X gate error rate is set to zero in `qnic.ned`:

```
        double Xgate_error_rate = default(0);
```

This nested referencing of `.ned` files from first the `.ini` file and
then from other `.ned` files, with the automatic searching of
directories for corresponding network and module names and overriding
of the parameters, complicates sharing and archiving of experimental
parameter sets, but allows for referencing that makes for sharing of
parameters and for much less verbose individual files.

### `.msg` file

Describes the format and contents of the messages exchanged.  At the
moment, you will find one for classical messages
(`classical_messages.msg`) and one for quantum messages
(`PhotonicQubit.msg`).

### `.cc` and `.h` files

You know what these are.  There is a modest number of C++ files that
are specific to QuISP.

### Next steps

When you are ready to start contributing, you can start reading the
code, as [we have done](code-spelunking.md).
