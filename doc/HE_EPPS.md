
*Note: this file is an early design document, but will be updated in the future.*


# Hardware Element: Entangled Photon Pair Source (EPPS) #

Parameters:

    TrialRate
    EmissionProbability
    OutputState

OutputState should be a density matrix, I believe.

## Background & References ##

The simplest(?) way to make entangled photon pairs is probably
spontaneous parametric down conversion (SPDC), which happens with a
nonlinear crystal.  Depending on whether you use Type 1 or Type 2, you
get either two photons with the same polarization or two with
orthogonal polarizations.

Type 1, giving the same polarization, I think, is only useful to treat
SPDC as a heralded single-photon source.

Type 2, with the photons picked up from the points where they overlap,
gives you the state $$(|H\rangle|V\rangle +
|V\rangle|H\rangle)/\sqrt{2}$$, which is a useful Bell state.
Question: given that the process is stochastic, how do you turn this
into a reliable source of pairs?

See:

1. Gerry & Knight for a reasonable explanation.
1. [Cody's
paper](http://iopscience.iop.org/article/10.1088/1367-2630/18/8/083015/meta)
for how to make a link out of it.

## Making a Link Out of It ##

See Cody's paper for what he calls Midpoint Source.
