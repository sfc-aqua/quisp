# RuleSets for Fowler 2G Networks

*Note: this file is an early design document, and these 2G networks
are not yet handled.  Internetworking (recursive) connections and
networks are not yet handled.*

RuleSets for Fowler networks require somewhat different operation than
Jiang or Dur-Briegel.

Key differences:

* Base Bell pairs are only useful once we have $2*d*(*d*-1)$ of them, where $d$
  is the surface code distance. Thus, it makes sense to receive them in
  groups of that size.
* There is no swapping operation, only surface code stabilizer
  measurement.

## *Static-Static* RuleSets for Surface Code Distance=*d* ##

(n.b.: Since there are no non-neighbor operations in this approach,
the placement of operations is never really a choice, compared to
purify-and-swap networks.)

Here, we are assuming:

* Bell pair creation success probability is below (probably *waay*
  below) 50%, so we can't do direct ballistic execution; instead, we
  must first build acknowledged Bell pairs, then perform operations on
  top.
* Fidelity is sufficient to run QEC on top, so we aren't purifying
  before QEC.  (The construction of RuleSets should actually allow
  that if they're not good enough, I just haven't included that in
  this example.)

In this example, Alice and Charlie both wait until they have all
$2*d*(*d*-1)$ Bell pairs they need to complete an end-to-end logical
Bell pair before they bother initializing their local qubits and doing
anything else.  An alternative approach is to do this incrementally,
in sets of *d* Bell pairs, stepping through the time steps.  That
approach would use less memory, and the demands on memory lifetime are
probably comparable, but I chose the simpler approach here for
pedagogical purposes.

**Important decision/question**: At the moment, this RuleSet is a
  little vague about where and how the surface code error matching
  algorithm (Blossom V or equivalent) is actually run.  The RuleSet
  currently treats this as data that propagates left to right along
  the path, and assumes that the correction is done in a distributed
  fashion, but that's really not a good model here.  Needs to be
  corrected.  (This is actually an interesting problem I hadn't
  thought much about.)

Alice:

1. When holding *d*(2*d*-1) base Bell pairs with Bob:
    1. Build logical |0> state on *d*-by-*d* surface code lattice on
    ancillae qubits.
    1. Execute logical *H* gate on the ancillae, to make |+> state.
    1. Repeat *d* times:
        1. As sender, execute 2*d*-1 local CNOT gates between state
        qubits and Bell pairs.
        1. Measure Bell pairs, send results to Bob.
1. When holding a logical Bell pair with Charlie, deliver to application.

Bob:

1. When holding *d*(2*d*-1) base Bell pairs with Alice and
    *d*(2*d*-1) base Bell pairs with Charlie:
    1. Build logical |0> state on 1-by-*d* surface code lattice on
    ancillae qubits.
    1. Repeat *d* times:
        1. As sender, execute 2*d*-1 local CNOT gates between state
        qubits and Alice Bell pairs.
        1. Measure Bell pairs, combine with results from Alice to form
	complete stabilizer measurements.  Correct as necessary.
    1. Repeat *d* times:
        1. As sender, execute 2*d*-1 local CNOT gates between state
        qubits and Charlie Bell pairs.
        1. Measure Bell pairs, send results to Charlie.

Charlie:

1. When holding *d*(2*d*-1) base Bell pairs with Bob:
    1. Build logical |0> state on *d*-by-*d* surface code lattice on
    ancillae qubits.
    1. Repeat *d* times:
        1. As sender, execute 2*d*-1 local CNOT gates between state
        qubits and Bell pairs.
        1. Measure Bell pairs, combine with results from Bob to form
    complete stabilizer measurements.  Correct as necessary.
1. When holding a logical Bell pair with Charlie, deliver to application.

