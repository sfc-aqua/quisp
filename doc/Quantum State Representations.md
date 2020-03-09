# Quantum State Representations #

# Choice of Basis #

We talk about quantum states in terms of the *basis vectors*.  The
most common ones:

* The *computational*, basis, also known as the *Z* basis for a single
  qubit.  This is |000>, |001>, etc.
* The +/-, or *X*, basis (again for a single qubit).
* The *Bell* basis, useful for exactly two qubits.  Extremely useful
  for repeaters.  We will primarily work in the Bell basis.

# Representations #

* *State Vector*: good only for pure states.  Up to $$2^n$$ complex
  numbers for an $$n$$-qubit state.  Dirac's ket notation doesn't
  require representation of zero amplitudes.
* *Density Matrix*: good for mixed as well as pure states. $$2^{2n}$$ complex
  numbers.  Sparse representations also possible; can be written as a
  sum of the outer products of pure states.  Pioneered by von Neumann.
* *Stabilizer*: Certain states can be written in terms of their
  "stabilizers", or operations that don't affect the state.
  Super-efficient memory consumption.
* *Pauli frame*: In the Pauli frame representation, we don't actually
  track the state itself, just a Monte Carlo-driven representation of
  the errors in the state, on a per-qubit basis.  2n bits to track
  I,X,Z,Y errors.

## References ##

* See [IBM's recent blog
  posting](https://www.ibm.com/blogs/research/2017/10/quantum-computing-barrier/)
  and the [accompanying arXiv paper](https://arxiv.org/abs/1710.05867)
  for discussions on the upper limits of representing quantum states
  in classical computers.
