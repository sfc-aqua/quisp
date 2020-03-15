
*Note: this file is an early design document, but will be updated in the future.*

# Hardware Element: Physical Optical Channel #

An optical channel (whether optical fiber, free space, satellite,
etc.) has the following characteristics:

    Length (in km)
    LossPerKM (in dB)
    SystemLoss (in dB)
    SpeedOfLight (in km/sec)
    ErrorOperatorSum (an arbitrary-length list of single-qubit density operators)

From these characteristics, we can compute the total loss and latency
for the channel, which should probably be cached alongside those other
values.

Note that a channel is unidirectional; that is specified only in the
network topology.

## Types of Fiber ##

(Discuss single mode, step-index multimode, graded-index multimode.
[Optical communication at
RPI](https://www.ecse.rpi.edu/~schubert/Light-Emitting-Diodes-dot-org/chap22/chap22.htm)
has good figures on fibers.  Multimode is easy to fab and couple, but
has high modal dispersion, whereas single-mode has low modal
dispersion but is hard to couple.  I'm not sure what difference there
is in loss.)

Modes in fibers are described [here](https://www.rp-photonics.com/passive_fiber_optics2.html).

Hucul-Monroe and Hensen-Hanson both use single-mode fiber, which I
suspect is necessary.  Hensen-Hanson use fiber beam splitters and
fiber-based polarizers.

## Losses in Fiber ##

[Optical communication at
RPI](https://www.ecse.rpi.edu/~schubert/Light-Emitting-Diodes-dot-org/chap22/chap22.htm)
has good figures on fibers, including [this
figure](https://www.ecse.rpi.edu/~schubert/Light-Emitting-Diodes-dot-org/chap22/F22-02%20Attenuation%20in%20SiO2.jpg)
which shows that loss in silica fiber rises really rapidly with
wavelengths shorter than 1.2$$\mu$$m; this is a theoretical limit due
to Rayleigh scattering.  I'm not sure what parameters that depends on:
core diameter? probably not, since this mentions "silica" but not
single v. multimode; index of refraction?  Shows the theoretical limit as
being about 6.5dB at 600nm and about 2.5 or 3 at 800nm, so it's a big
difference.

Some discussion of Rayleigh
scattering[here](https://www.rp-photonics.com/rayleigh_scattering.html).
It's scattering due to scattering centers that are much smaller than
the wavelength, and depends on $$\lambda^{-4}$$, but I don't
understand what drives the constant factor that must exist.

There's a high loss peak around 1400nm due to the presence of
OH$$^-$$.  This peak seems to be going away with more modern fibers.

There are considered to be three or four "windows" in which loss is
considered acceptable; see, for example, [this
figure](http://www.olson-technology.com/mr_fiber/images/fiber-history-04-big.gif)
from
[here](http://www.olson-technology.com/mr_fiber/fiber-history.htm).
They are around 850nm (around 2dB/km for "modern" fiber, above 3 for
1980s fiber); 1310 (0.5dB/km); and the lowest-loss window around
1550nm (0.2dB/km).  The fourth window, around 1625, will be higher
than 1550, but maybe not too bad.  (This source is a 2003 book, so
already quite a bit out of date, but I think the rate of improvement
has slowed quite a bit.)
