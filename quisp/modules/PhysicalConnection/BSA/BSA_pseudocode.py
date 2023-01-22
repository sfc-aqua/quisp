record_left = []
record_right = []
state = 'idle'
indistinguish_time_period = 'some number'
dark_count_threshold = 'some number'
efficiency_threshold = 'some number'
bsm_success_prob = 'some number'

from random import random as rand

# photon has {from_left, from_right, arrive_time, is_lost, first, last}

# this pseudocode is during the accepting state
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

def discardPhoton(photon):
    pass

def processRecords():
    results_list = []
    for left_photon, right_photon in zip(record_left, record_right):
        if abs(left_photon.arrive_time - right_photon.arrive_time) <= indistinguish_time_period:
            results_list.append(process_indistinguish_photons(left_photon, right_photon))
        else:
            results_list.append('fail')


def process_indistinguish_photons(p, q):
    if not p.is_lost and not q.is_lost:
        # perform bell measurement
        if (rand() < bsm_success_prob and rand() < efficiency_threshold):
            # force bsm to |Phi+> (pick half)
            return 'success'
        # measure both in random basis
        return 'fail' # check physical implementation details
    elif (not p.is_lost and q.is_lost) or (p.is_lost and not q.is_lost):
        # WLOG p arrive but q lost
        # measure both in random basis
        if p.is_lost: p, q = q, p
        if (rand() < dark_count_threshold):
            return 'success'
        return 'fail'
    else:
        # measure both in random basis
        if (rand() < dark_count_threshold and rand() < dark_count_threshold):
            return 'success'
        return 'fail'


"""
Questions:
- is it fine to model lost as random basis measurement to the photons? (is this the right way to do it for RGS? counterfactual measurement?)
- how to model dead time? Should we just assume that the photons are well separated?
- should we also model the coupling lost? Maybe add collection efficiency-
"""
