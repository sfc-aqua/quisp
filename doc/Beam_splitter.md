
*Note: this file is an early design document, but might be updated as the version goes up.*

# Beam splitter #

This article is primarily for reference, since we don't plan to make
beam splitters separate entities in the simulator.

## Photon Number States ##

When you see  <img src="https://latex.codecogs.com/gif.latex?$$|0\rangle$$" title="$$|0\rangle$$" />, <img src="https://latex.codecogs.com/gif.latex?$$|1\rangle$$" title="$$|1\rangle$$" />, <img src="https://latex.codecogs.com/gif.latex?$$|2\rangle$$" title="$$|2\rangle$$" />, etc. in a paper on quantum optics, be aware that it likely represents a photon number state, also called Fock state, I believe.  The 0, 1, 2 represents the number of photons in a particular place and time (called a _spatial mode_).

For photon number (or spatial mode) qubits, photon statistics at beam splitters are complicated.

See:

1. Weihs and Zeilinger lecture notes from Caltech QIP course
2. Sec. 6.2 & 6.3 of Gerry & Knight
3. Campos et al., PRA 40(3), 1371, 1989, esp. Eqs. 24, 42-48

## Polarization States ##

When you see <img src="https://latex.codecogs.com/gif.latex?$$|H\rangle$$" title="$$|H\rangle$$" /> and <img src="https://latex.codecogs.com/gif.latex?$$|V\rangle$$" title="$$|V\rangle$$" /> states, they refer to the polarization of a photon.  It's important to realize, though, that they represent the polarization of photon in a particular place and at
a fixed time.  Weihs and Zeilinger refer to it as spin representing an _additional_ degree of freedom, and are very explicit about writing out the behavior of the BS in four bases: H and V at each of the two input ports.  This allows the unitary to be written properly, with the after state being a four-basis representation at the two output ports.

Based on Eqs. 1.21 & 1.21 of W&Z, in the basis

<img src="https://latex.codecogs.com/gif.latex?$$\left(\begin{matrix}&space;a_H&space;\\&space;b_H&space;\\&space;a_V&space;\\&space;b_V&space;\end{matrix}\right)$$" title="$$\left(\begin{matrix} a_H \\ b_H \\ a_V \\ b_V \end{matrix}\right)$$" />

the unitary is

<img src="https://latex.codecogs.com/gif.latex?$$\left(\begin{matrix}&space;t_H&space;&&space;ir_H&space;&&space;0&space;&&space;0&space;\\&space;ir_H&space;&&space;t_H&space;&&space;0&space;&&space;0&space;\\&space;0&space;&&space;0&space;&&space;t_V&space;&&space;ir_V&space;\\&space;0&space;&&space;0&space;&&space;ir_V&space;&&space;t_V&space;\end{matrix}\right)$$" title="$$\left(\begin{matrix} t_H & ir_H & 0 & 0 \\ ir_H & t_H & 0 & 0 \\ 0 & 0 & t_V & ir_V \\ 0 & 0 & ir_V & t_V \end{matrix}\right)$$" />

where <img src="https://latex.codecogs.com/gif.latex?$$t$$" title="$$t$$" /> is the transmission amplitude and <img src="https://latex.codecogs.com/gif.latex?$$r$$" title="$$r$$" />  is the reflection amplitude.

n.b.: I'm not positive that the sign of the terms is actually right; there should be a relative phase shift of <img src="https://latex.codecogs.com/gif.latex?$$\pi$$" title="$$\pi$$" /> for one term, or <img src="https://latex.codecogs.com/gif.latex?$$\pm\pi/2$$" title="$$\pm\pi/2$$" /> for both.  Is that what this actually does?  Satoh and I think that this produces <img src="https://latex.codecogs.com/gif.latex?$$\pi/2$$" title="$$\pi/2$$" /> difference in the states.  We don't quite understand yet.  (Wikipedia says that even for the quantum mechanical one, the phase difference between reflected and transmitted beams should be <img src="https://latex.codecogs.com/gif.latex?$$\pi$$" title="$$\pi$$" />.)

## Reconciling with Classical Beam Splitters and Interferometry ##

It's worth investing some words in this topic of the phase shift (and
perhaps amplitude) and how we represent that mathematically.

Gerry & Knight answers some questions about what happens to the phase of a state at a beam splitter; it's dependent on the dielectric constant.  According to Wikipedia, for a classical beam splitter, it depends on whether you are going from high index of refraction to low index of refraction, or vice versa; see this link(https://en.wikipedia.org/wiki/Beam_splitter#Phase_shift).
