# God Channel #

*Note: This is an old design document, which we expect to still be useful, but it may or may not correspond well to the current implementation.

When measuring entangled states, the entanglement is destroyed and the superposition collapses, over a distance, instantaneously. The god channel emulates that behavior. It should be part of the physical simulation, choosing the output of the measurement and the resulting states of any remaining entangled qubits, based on the fidelity and the target state (or more completely, on the density matrix).

Complete physical simulation of the quantum Hamiltonian is definitely not required for our purposes; Monte Carlo simulation of whether or not the state is correct is probably good enough.
