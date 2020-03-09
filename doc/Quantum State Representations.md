# Quantum State Representations #

# Choice of Basis #

We talk about quantum states in terms of the *basis vectors*.  The
most common ones:

* The *computational*, basis, also known as the *Z* basis for a single
  qubit.  This is |000>, |001>, |010>, |011>, etc.
* The +/-, or *X*, basis (again, for a single qubit).
* The [*Bell* basis](https://www.quantiki.org/wiki/bell-basis), useful for exactly two qubits.  Extremely useful
  for repeaters.

# Representations #

* *State Vector*: good only for pure states (those without errors).
  Up to $$2^n$$ complex numbers for an $$n$$-qubit state.  [Dirac's ket
  notation](https://en.wikipedia.org/wiki/Bra%E2%80%93ket_notation)
  (|000>, etc.) is essentially a sparse representation of the complete
  state vector.
* [*Density Matrix*](https://en.wikipedia.org/wiki/Density_matrix):
  good for mixed as well as pure states. Requires
  $$2^{2n}$$ complex numbers.  Sparse representations also possible;
  can be written as a sum of the outer products of pure states.
  Pioneered by von Neumann.
* *Stabilizer*: Certain states can be written in terms of their
  "stabilizers", or operations that don't affect the state.
  Super-efficient memory consumption.
* *Pauli frame*: In the Pauli frame representation, we don't actually
  track the state itself, just a Monte Carlo-driven representation of
  the errors in the state, on a per-qubit basis.  Requires only $2n$
  bits to track $I,X,Z,Y$ errors.  Some quantum error correction (QEC)
  simulators operate in the Pauli frame basis.
* *error basis*: This is *our chosen basis* for QuISP.  It is a
  generalization of the Pauli frame basis.  More documentation is in
  progress, but not yet ready.  At the time of this writing, the best
  documentation is Sec. 5.3 of [Takaaki's master's
  thesis](https://arxiv.org/abs/1908.10758).

## References ##

Stabilizers are important, and were first defined in [Gottesman's
Ph.D. thesis](https://arxiv.org/abs/quant-ph/9705052), but that's kind
of heavy going and the notation has simplified somewhat in daily
practice since then.

* See [IBM's recent blog
  posting](https://www.ibm.com/blogs/research/2017/10/quantum-computing-barrier/)
  and the [accompanying arXiv paper](https://arxiv.org/abs/1710.05867)
  for discussions on the upper limits of representing quantum states
  in classical computers.
