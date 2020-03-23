
*Note: this file is an early design document, but will be updated in the future.*

# Making Entanglement #

(This article is a bridge between [Link Architecture](Link%20Architecture.md) and the hardware modules and concepts.)

## TU Delft NV Link ##

See

1. [Bernien et al.](https://www.nature.com/nature/journal/v497/n7447/abs/nature12016.html), three meter entanglement
2. [Hensen et al.](https://www.nature.com/articles/srep30289), 1.3 km entanglement, second experiment

1.3km (actually 1.7km of fiber, but distance is only 1.3km) entanglement is achieved by observing one "early" and one "late" photon after the midpoint beam splitter.

Output state is the singlet, <img src="https://latex.codecogs.com/gif.latex?%28%7C0%5Crangle%7C1%5Crangle%20-%7C1%5Crangle%7C0%5Crangle%29/%5Csqrt%7B2%7D" />

Hensen paper says they use an event-ready Bell setup.

The 1.3km success rate was <img src="https://latex.codecogs.com/gif.latex?6.4%5Ctimes%2010%5E%7B-9%7D" />, giving only a little more than one success per hour (geez).  Keep in mind that this is with one transceiver qubit.  They did extensive characterization of the setup and tuned appropriately, including having the angles in the BSA slightly off from expected values, in part because correlations are asymmetric; they get better correlation in <img src="https://latex.codecogs.com/gif.latex?ZZ" /> than <img src="https://latex.codecogs.com/gif.latex?XX" />.

Their bootstrap/characterization procedure includes a straight H-O-M test,
which doesn't entangle but allows them to assess timing and photon indistinguishability.  
They report a contrast of <img src="https://latex.codecogs.com/gif.latex?0.90%5Cpm0.06" />. They estimate fidelity of the <img src="https://latex.codecogs.com/gif.latex?%7C%5CPsi%5E-%5Crangle" /> state to be <img src="https://latex.codecogs.com/gif.latex?0.92%5Cpm%200.03" />.

Their fiber loss is 8dB/km, primarily (entirely?) just due to being at the wrong wavelength.

The early/late separation is 300nsec.  Does that limit the burst rep rate to less than 3MHz?  I wonder how much this can be shrunk.

In their setup, they run the two fibers to input ports of a beam splitter, then have two detectors on the output ports.  Their protocol succeeds only when you get an early click on one detector and a late click on the other, so it would be capped at 50% success rate if the beam splitter is 50/50.

I don't understand why it can't be done with one detector, unless it's limited by the cycle time of the detector.  Is simply merging the optical streams too difficult?  Does which-path info still appear somewhere?  Is indistinguishability hurt in some way?  Without two ports and two detectors, running a true H-O-M test is difficult, so calibration and confirmation of indistinguishability is tough.

I'm not exactly certain how the induce early/late emission from an NV center in something approximating a <img src="https://latex.codecogs.com/gif.latex?%7C&plus;%5Crangle" /> state.

Lots of details on their setup in the supplementary material to Hensen, including their online calibration sequence:

1. Every 250 attempts (3.75msec; attempt rep rate is every <img src="https://latex.codecogs.com/gif.latex?15%20%5Cmu%20%5Ctext%7Bsec%7D" />), they double-check their NV center to see that they have an electron and that it's on-resonance with their excitation lasers.
2. A feedback loop is used to stabilize the NV excitation and emission wavelength to keep it with the excitation lasers.
3. Every 10 seconds, they check classical control of subsystems: AWG (arbitrary waveform generator), wavemeters, laser stabilization.
4. Every 5 minutes, they run a scan with the spin-pumping laser to reset the optimal operation point.
5. Every 45 minutes (one run), spatial position of objective lenses is adjusted (must be an automatic system), and the laser powers are recalibrated.
6. Once a day, they check and recalibrate a bunch of stuff.

(Needs more detail here on the input states, photonic states, what happens at the beam splitters and detectors.)

## Nemoto NV Architecture ##

[Kae's NV diamond architecture](https://journals.aps.org/prx/abstract/10.1103/PhysRevX.4.031022) uses a scheme with a single photon that is "split" in two and reflects off of two cavities, where it picks up a phase that depends on the state of the NV electronic qubit, then recombined at a beam splitter to erase "which path" information.  See Fig. 1 in the main paper for the main concept.  The paper claims this is similar to the original DLCZ setup.

For the arrangement of components, see Fig. 5 in the supplementary material.  The photon is split, with one arm going around the cavity and the other reflecting off of it, then the two arms are temporally multiplexed into a fiber and the converse operation is done at the other end.

This is set up to be an <img src="https://latex.codecogs.com/gif.latex?M%5Crightarrow%20M" /> architecture for a SAN, so it converts fairly easily to a LAN.

Success probability is low:<img src="https://latex.codecogs.com/gif.latex?p%20%3D%20%5Ceta%5E2%20P_R/8"/> , where <img src="https://latex.codecogs.com/gif.latex?%5Ceta" /> is collection efficiency and <img src="https://latex.codecogs.com/gif.latex?P_R" /> depends on details of the cavity design.  They recognize that this is low probability, but claim high
fidelity, <img src="https://latex.codecogs.com/gif.latex?F%20%3E%200.99" />, on success.

Output state is the singlet, <img src="https://latex.codecogs.com/gif.latex?%28%7C0%5Crangle%7C1%5Crangle%20-%20%7C1%5Crangle%7C0%5Crangle%29/%5Csqrt%7B2%7D" />.

Questions/concerns:

1. I'm a little unclear on what kind of switching is required at the receiving end, and how fast it has to be.
2. I don't understand the success probability well enough to know why it's divided by 8.  I guess only one of the four possible state combinations "works", and there's only a 50% chance of the detector clicking?  Not sure why both arms can't be detected after the last BS, one for even parity and one for odd parity.  Need to grok this a little more.
3. What's their cycle time?

(Needs more detail here on the input states, photonic states, what
happens at the beam splitters and detectors.)

## Monroe Ion Trap ##

In Hucul et al., _Nature Physics_, they describe ion trap to ion trap entanglement using photons.  The atoms emit state-dependent polarized photons; either <img src="https://latex.codecogs.com/gif.latex?%7C%5Csigma%5E&plus;%5Crangle" /> or <img src="https://latex.codecogs.com/gif.latex?%7C%5Csigma%5E-%5Crangle" />.  These circularly polarized states are converted to H and V using a quarter-wave plate before insertion into the fiber.

Their BSA uses a 50/50 BS and two PBS (polarizing beam splitters). They use four PMTs (photomultiplier tubes) as detectors, and can detect two of the four Bell states:  <img src="https://latex.codecogs.com/gif.latex?%7CHV%5Crangle%5Cpm%20%7CVH%5Crangle" />, depending on which pair of detectors clicks.  (Detecting <img src="https://latex.codecogs.com/gif.latex?%7CHH%5Crangle%5Cpm%20%7CVV%5Crangle" /> without collapsing the state would be quite a trick to add to the bag.)

(Needs more detail here on the input states, photonic states, what happens at the beam splitters and detectors.)