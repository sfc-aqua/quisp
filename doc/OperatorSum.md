# Math: Operator Sum #

One of the things we have to be able to do is apply a set of operators
to a density matrix.  Individual gates, other than measurement, are
unitary operations.  Decoherence processes, on the other hand, are
often non-unitary, at least from the point of view of the qubits we
can see and control.  The right way to represent them is via a set of
operator matrices that collectively are _trace preserving_,
$$\sum_{k}E_k^\dagger E_k = I$$.

(Note that measurement is also non-unitary, but not trace-preserving
due to the additional information you gain.)

## References ##

See the discussion of this in Sec. 8.2.2 in my book, or
(coincidentally) Sec. 8.2.3 and 8.3 of Mike & Ike.
