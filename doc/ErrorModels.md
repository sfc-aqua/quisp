# Math: Error Models #

*Note: This file contains some important background thoughts on how to
handle non-Pauli errors.  This grew to become our "error basis"
representation.  However, this description does not exactly correspond
to the current implementation.  At the time of this writing, the best
documentation is Sec. 5.3 of [Takaaki's master's
thesis](https://arxiv.org/abs/1908.10758).*

We have two main ways of representing errors: tracking Pauli frame
errors introduced using Monte Carlo methods, or using a more
physically grounded model with density matrices and operator sums.

These are, of course, tied into the choice of [quantum state
representation](Quantum State Representations.md).

## Pauli Frame Errors and Monte Carlo Simulations ##

For simulation of large-scale entangled states, full density matrix
representation is impossible.  Instead, the simplest, most common
approach is the Monte Carlo approach, using randomly introduced X, Y,
or Z errors.  This is the approach Shota took in his surface code
sims, which was then used in [Satoh & Kaori's network coding
paper](https://arxiv.org/abs/1508.02141) and [Takaaki's network coding
paper](https://arxiv.org/abs/1710.04827).

The disadvantage is that it can't easily represent asymmetric
(non-unitary) error processes or multi-qubit error processes.

### Building a Channel ###

All we need for this is three parameters, normalized to some time
constant:

```
    XFlipProbability
    YFlipProbability
    ZFlipProbability
```

## The Physical/Mathematical Models ##

More physically motivated error models may be important under some
circumstances.

These depend on the [Operator Sum](OperatorSum.md) representation.

### Bit Flip Channel ###

This is a simple, symmetric Shannon channel (through time rather than
space) with some probability $$p$$ of the bit being flipped 1 to 0 or
0 to 1.

### Phase Flip Channel, or Phase Damping ###

This is the equivalent to the bit flip channel, but for the phase
instead.  This is known as _phase damping_.

In phase damping, we have $$|+\rangle\rightarrow |-\rangle$$ and vice
versa.  The time constant here is $$T_2$$.  See Eqs. 8.12-8.14 in Rod
Van Meter's book, _Quantum Networking_.

### Energy Relaxation ###

An asymmetric channel in which $$|1\rangle\rightarrow |0\rangle$$ is
more likely to happen than $$|0\rangle\rightarrow |1\rangle$$.

This is tied to $$T_1$$, the energy relaxation time.  See
Eqs. 8.6-8.10 in Van Meter's book for the representation known as
generalized amplitude damping.

The other parameter we need for a relatively complete picture of
energy relaxation is the Boltzmann polarization, the fraction of
qubits that would be in the $$|0\rangle$$ state when the system has
completely relaxed as best possible given the current temperature and
the difference in energy level between the two states.

We can build a bit flip channel here by setting the Boltzmann
polarization to 0.5 and setting $$T_1$$ appropriately.  _(Need to
confirm this; am I sure that the off-diagonal elements are treated
appropriately?)_

### Systemic and Correlated Errors ###

It is also possible that errors such as mis-calibration of timing
signals results in groups of qubits all decohering together, or in
error processes not being memoryless.  E.g., if our timing signal is
off by 1kHz, after 0.5 msec, the qubit is *guaranteed* to have a bit
flip error, but weirdly, after 1 msec that error *vanishes* and the
state is once again correct, as the timing signals come back into
phase with each other.

In practice, these kinds of errors are handled at a level _below_ our
simulation here, through techniques such as _spin echo_ or _composite
pulses_ (Vandersypen and Chuang, _RMP_).  After their application, we
are left with the kinds of errors we discuss in more detail here.

### Building a Channel ###

We can initialize an error channel as if it is a combination of all of
the above types, by specifying just three parameters when calling a
single, unified initializer.

```
    BoltzmannPolarization (0.0 to 1.0, but usually 0.5 to 1.0)
    EnergyRelaxationT1
    PhaseDampingT2
```

_(Do we need a null value for input sometimes?)_

## Local Versus Distributed Errors ##

Decoherence processes are local, even for distributed states.  Can we
keep management of errors entirely local?

I think the answer is _yes_, *except* for an important exception:
measurement and its effect on the state.  In particular, dark counts
at a BSA convince the system that actually unentangled qubits are
entangled.

