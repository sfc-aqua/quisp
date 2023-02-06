# Bell State Analyzer

In QuISP, we assume that there is an implicit mechanism for repeaters and end nodes to signal the BSA module about the beginning and the end of the photon trains (e.g., strong light pulse before and after each train).
We achieve this in QuISP using the `STATIONARY_PULSE_XXX` flag where `<XXX>` can be `BEGIN`, `END`, or `BOUND`.
The flag is one of the parameters of the photonic qubit we send to the BSA.

The BSA component in QuISP comprises two modules, the BellStateAnalyzer and the BSAController.
BellStateAnalyzer is the physical module where it only concerns itself with measuring the photons coming from the two ports.
BSAController on the other hand, handles the messaging and signalling of neighbour QNode(s), sending measurement results and telling them when the first photon should arrive.

The BSA can be inside a QNIC (referred to as QNIC_R or QNIC receiver) which lives inside a QNode, or inside a stand-alone node (BSANode).
Its functionality stays the same whether it lives inside a QNIC or a BSANode.
The only difference between internal (inside QNode) and external (inside BSANode) is the initialization phase inside the BSAController.
The module hierarchy traversal to find the incoming channel and which nodes this BSAController should talk to is different.

## How BellStateAnalyzer Module works

The BellStateAnalyzer manage its behaviour using a state machine. It has 4 states namely; `idle`, `accepting`, `accepting_left`, and `accepting_right`.
Currently, it caches all the photons coming in from both sides until the last photons from both sides arrive.
Then it compiles the results in batches and signals the BSAController which then sends it to QNodes.

In QuISP, we assume that the BSA can distinguish between $\ket{\Psi^+}$ and $\ket{\Psi^-}$ state while it cannot distinguish between $\ket{\Phi^+}$ and $\ket{\Phi^-}$.
This leads to a success probability of only 50% even if all the lossy parameters are set to be ideal (no loss, no error, no false positive click).

Pseudocode for BSA:

The parameters
```python
record_left = []
record_right = []
state = 'idle' | 'accepting_left' | 'accepting_right' | 'accepting'
indistinguish_time_period = 'positive number in (ns)'
dark_count_threshold = 'number in range [0, 1]'
efficiency_threshold = 'number in range [0, 1]'
# photon has {from_left, from_right, arrive_time, is_lost, first, last}
```

State management part
```python
def processArrivalPhotons(photon):
    if (state == 'accepting right' and photon.from_left) \
        or (state == 'accepting left' and photon.from_right) \
        or (state == 'idle' and not photon.first):
        discardPhoton(photon)
        return

    if state == 'idle':
        state = 'accepting'

    if photon.from_left:
        record_left.append(photon)
    else:
        record_right.append(photon)

    if photon.last and state == 'accepting':
        if photon.from_left:
            state = 'accepting right'
        else:
            state = 'accepting left'
    elif photon.last:
        state = 'idle'
        processRecords()
```

Processing of the cache results
```python
def processRecords():
    results_list = []
    for left_photon, right_photon in zip(record_left, record_right):
        if abs(left_photon.arrive_time - right_photon.arrive_time) <= indistinguish_time_period:
            results_list.append(process_indistinguish_photons(left_photon, right_photon))
        else:
            results_list.append('fail')
```

If both the photons should arrive within the indistinguishability time window
```python
def process_indistinguish_photons(p, q):
    if not p.is_lost and not q.is_lost:
        # perform bell measurement (need 2 rolls because of 2 detectors)
        if (rand() < efficiency_threshold and rand() < efficiency_threshold):
            if (rand() > 0.5): # we get Phi+/- states cannot distinguish
                return 'fail'
            return 'success', 'Psi+' | 'Psi-' # select randomly 50:50
    elif (not p.is_lost and q.is_lost) or (p.is_lost and not q.is_lost):
        # WLOG p arrive but q lost
        if p.is_lost: p, q = q, p
        if (rand() < dark_count_threshold):
            if (rand() > 0.5): # we thought we get Phi+/- so we declare fail
                return 'fail'
            return 'success', 'Psi+' | 'Psi-' # select randomly 50:50
    else:
        if (rand() < dark_count_threshold and rand() < dark_count_threshold):
            if (rand() > 0.5): # we thought we get Phi+/- so we declare fail
                return 'fail'
            return 'success', 'Psi+' | 'Psi-' # select randomly 50:50
    # measure both in Z basis to simulate loss event
    return 'fail'
```

