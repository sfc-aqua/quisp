#!/usr/bin/python3

import os

import numpy as np


def get_channel_error_from_link_werner_noise(fidelity, dist_in_km) -> float:
    """
    Given the expected initial link-level noise model and distance of the fiber,
    return the px, py, pz (per km) for the transition matrix to be used for QuantumChannel.ned.
    """
    left: float = 0.0
    right: float = 0.3
    l: float = 0.04500741397 # this is the fixed loss probability per kilometer (coming from ~0.2 dB/km)
    iter_count = 0
    while left < right:
        p = (left + right) / 2
        iter_count += 1
        if iter_count > 100:
            print("exceed max iteration")
            break
        Q = np.matrix(
            [
                [1 - 3 * p - l, p, p, p, l],
                [p, 1 - 3 * p - l, p, p, l],
                [p, p, 1 - 3 * p - l, p, l],
                [p, p, p, 1 - 3 * p - l, l],
                [0, 0, 0, 0, 1],
            ]
        )
        Qt = Q**dist_in_km
        calculated_f = Qt[0, 0] / (Qt[0, 0] + Qt[0, 1] + Qt[0, 2] + Qt[0, 3])
        if calculated_f > fidelity:
            left = p
        else:
            right = p
        if round(calculated_f, 10) == round(fidelity, 10):
            break
    print(f"we got p (fiber error)= {p}")
    print(f"    expected fidelity (input): {fidelity}")
    print(f"    obtained from calculation: {calculated_f}")
    print(f" {Qt}")
    return p


def get_fidelity_from_target_bsm_swap(f):
    left: float = 0.0
    right: float = 1
    iter_count = 0
    while left < right:
        p = (left + right) / 2
        iter_count += 1
        if iter_count > 100:
            print("exceed max iteration")
            break
        fn = p**2 + 3 * ((1 - p) / 3) ** 2
        if fn > f:
            right = p
        else:
            left = p
        if round(fn, 10) == round(f, 10):
            break
    print(f"we got p = {p}")
    print(f"    expected: {f}")
    print(f"    obtained: {fn}")
    return p


def bds_werner_swap(fa, fb):
    f = fa * fb + 3 * (1 - fa) * (1 - fb)
    return f


def get_p_from_decoherence_time(decoherence_time_mu_s: int) -> float:
    # Although QuISP allows for relaxation/excitation noise, we do not include it here.
    left: float = 0.0
    right: float = 0.3
    iter_count = 0
    while left < right:
        p = (left + right) / 2
        iter_count += 1
        if iter_count > 100:
            print("exceed max iteration")
            break
        Q = np.matrix(
            [
                [1 - 3 * p, p, p, p],
                [p, 1 - 3 * p, p, p],
                [p, p, 1 - 3 * p, p],
                [p, p, p, 1 - 3 * p],
            ]
        )
        Qt = Q**decoherence_time_mu_s
        if Qt[0, 0] > 1 / np.e:
            left = p
        else:
            right = p
        if round(Qt[0, 0], 10) == round(1 / np.e, 10):
            break
    print(f"we got p (memory) = {p}")
    print(f"    expected (fidelity has decohere): {1/np.e}")
    print(f"    obtained after T time has passed: {Qt[0, 0]}")
    return p


def get_error_param_balanced_mim_werner(
    link_fidelity, half_distance, coherence_time_mu_s
):
    p_mem_per_mu_s = get_p_from_decoherence_time(coherence_time_mu_s)
    mem_transition_mat = q = np.matrix(
        [
            [1 - 3 * p_mem_per_mu_s, p_mem_per_mu_s, p_mem_per_mu_s, p_mem_per_mu_s],
            [p_mem_per_mu_s, 1 - 3 * p_mem_per_mu_s, p_mem_per_mu_s, p_mem_per_mu_s],
            [p_mem_per_mu_s, p_mem_per_mu_s, 1 - 3 * p_mem_per_mu_s, p_mem_per_mu_s],
            [p_mem_per_mu_s, p_mem_per_mu_s, p_mem_per_mu_s, 1 - 3 * p_mem_per_mu_s],
        ]
    )
    total_q = mem_transition_mat**half_distance
    gen_time = half_distance * 2 / 208189.206944 * 1_000_000  # to mu s

    left: float = 0.0
    right: float = 0.3
    iter_count = 0
    while left < right:
        p = (left + right) / 2
        iter_count += 1
        if iter_count > 100:
            print("exceed max iteration")
            break
        # channel transition matrix
        Q = np.matrix(
            [
                [1 - 3 * p, p, p, p],
                [p, 1 - 3 * p, p, p],
                [p, p, 1 - 3 * p, p],
                [p, p, p, 1 - 3 * p],
            ]
        )
        Qt = Q**half_distance
        f = Qt[0, 0]
        f = bds_werner_swap(f, f)

        if Qt[0, 0] > 1 / np.e:
            left = p
        else:
            right = p
        if round(Qt[0, 0], 10) == round(1 / np.e, 10):
            break
    print(f"we got p = {p}")
    print(f"    expected: {1/np.e}")
    print(f"    obtained: {Qt[0, 0]}")
    return p


"""
Experimental settings for single round of purification at link level.
- link length: 40km
- no. of memories per node: 2
- generated link-level Bell pairs are Werner states
- sweep initial Bell pair fidelity from 0.6 to 0.9 in steps of 0.05
- one round of standard X-error purification (I would assume noiseless CNOT gates and no measurement errors, at least for now)
- output: fidelity of purified Bell pair following a successful purification, total time to obtain 500 purified Bell pairs
- memory decoherence: 18ms, 55ms (Table 1 in QuNAP paper)
"""


def generate_purification_experiment_config(
    num_bellpairs: int,
    cnot_error_prob: float,
    measurement_error_prob: float,
    with_depolarizing: bool,
    coherence_time_in_mu_s: int,
):
    """This function generates simulation config for experiment 4 in the paper with no memory decoherence."""
    # [Config mim_purification_20_20]
    # network = networks.cross_validation_mim_purification_20_20
    # **.qrsa.hm.link_tomography = true
    # **.qrsa.hm.initial_purification = 0
    # **.qrsa.hm.purification_type = ""
    # **.buffers = 1

    # round error probability to 3 decimal places
    cnot_error_prob = round(cnot_error_prob, 3)
    measurement_error_prob = round(measurement_error_prob, 3)

    # delete leading 0. and change it into string for config naming
    cnot_error_prob_str = str(cnot_error_prob)[2:]
    measurement_error_prob_str = str(measurement_error_prob)[2:]

    if len(cnot_error_prob_str) == 0:
        cnot_error_prob_str = "0"
    if len(measurement_error_prob_str) == 0:
        measurement_error_prob_str = "0"

    if with_depolarizing:
        if num_bellpairs != 100_000:
            config_name = f"[Config short_{num_bellpairs}_purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_with_decoherence_{coherence_time_in_mu_s}_ms]"
        else:
            config_name = f"[Config purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_with_decoherence_{coherence_time_in_mu_s}_ms]"
        # get close value up to 10th decimal place
        p_decoherence = get_p_from_decoherence_time(coherence_time_in_mu_s)
    else:
        if num_bellpairs != 100_000:
            config_name = f"[Config short_{num_bellpairs}_purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_without_decoherence]"
        else:
            config_name = f"[Config purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_without_decoherence]"
        p_decoherence = 0
    network_name = "network = networks.cross_validation_purification"
    error_params = [
        f"**.cnot_gate_error_rate = {cnot_error_prob}",
        #
        f"*.Repeater.**.x_measurement_error_rate = {measurement_error_prob}",
        f"*.Repeater.**.y_measurement_error_rate = {measurement_error_prob}",
        f"*.Repeater.**.z_measurement_error_rate = {measurement_error_prob}",
        #
        f"**.memory_x_error_rate = {p_decoherence}",
        f"**.memory_y_error_rate = {p_decoherence}",
        f"**.memory_z_error_rate = {p_decoherence}",
    ]
    other_params = [
        "repeat = 25",
        "sim-time-limit = 1000s",
        "**.qrsa.hm.link_tomography = false",
        "**.qrsa.hm.initial_purification = 0",
        '**.qrsa.hm.purification_type = ""',
        "*.alice.is_initiator = true",
        "**.buffers = 2",
        f"**.app.number_of_bellpair = {num_bellpairs}",
        f"**.qrsa.hm.num_measure = {num_bellpairs}",
    ]
    return [config_name, network_name, *error_params, *other_params]


def generate_purification_experiment_config_with_initial_fidelity(
    num_bellpairs: int,
    cnot_error_prob: float,
    measurement_error_prob: float,
    initial_fidelity: float,
    with_depolarizing: bool,
    coherence_time_in_mu_s: int,
):
    """This function generates simulation config for experiment 4 in the paper with no memory decoherence."""
    # [Config mim_purification_20_20]
    # network = networks.cross_validation_mim_purification_20_20
    # **.qrsa.hm.link_tomography = true
    # **.qrsa.hm.initial_purification = 0
    # **.qrsa.hm.purification_type = ""
    # **.buffers = 1

    # TODO: make this changeable
    channel_error_single_prob = get_channel_error_from_link_werner_noise(
        get_fidelity_from_target_bsm_swap(initial_fidelity), 20
    )

    # round error probability to 3 decimal places
    cnot_error_prob = round(cnot_error_prob, 3)
    measurement_error_prob = round(measurement_error_prob, 3)

    # delete leading 0. and change it into string for config naming
    cnot_error_prob_str = str(cnot_error_prob)[2:]
    measurement_error_prob_str = str(measurement_error_prob)[2:]
    initial_fid_str = str(int(100 * round(initial_fidelity, 2)))

    if len(cnot_error_prob_str) == 0:
        cnot_error_prob_str = "0"
    if len(measurement_error_prob_str) == 0:
        measurement_error_prob_str = "0"

    if with_depolarizing:
        if num_bellpairs != 100_000:
            config_name = f"[Config short_{num_bellpairs}_purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_with_decoherence_{coherence_time_in_mu_s}_ms_initial_fidelity_{initial_fid_str}]"
        else:
            config_name = f"[Config purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_with_decoherence_{coherence_time_in_mu_s}_ms_initial_fidelity_{initial_fid_str}]"
        # get close value up to 10th decimal place
        p_decoherence = get_p_from_decoherence_time(coherence_time_in_mu_s)
    else:
        if num_bellpairs != 100_000:
            config_name = f"[Config short_{num_bellpairs}_purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_without_decoherence_initial_fidelity_{initial_fid_str}]"
        else:
            config_name = f"[Config purification_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_without_decoherence_initial_fidelity_{initial_fid_str}]"
        p_decoherence = 0
    network_name = "network = networks.cross_validation_purification"
    error_params = [
        f"**.cnot_gate_error_rate = {cnot_error_prob}",
        #
        f"*.Repeater.**.x_measurement_error_rate = {measurement_error_prob}",
        f"*.Repeater.**.y_measurement_error_rate = {measurement_error_prob}",
        f"*.Repeater.**.z_measurement_error_rate = {measurement_error_prob}",
        #
        f"**.memory_x_error_rate = {p_decoherence}",
        f"**.memory_y_error_rate = {p_decoherence}",
        f"**.memory_z_error_rate = {p_decoherence}",
        #
        f"**.channel_x_error_rate = {channel_error_single_prob}",
        f"**.channel_z_error_rate = {channel_error_single_prob}",
        f"**.channel_y_error_rate = {channel_error_single_prob}",
    ]
    other_params = [
        "repeat = 25",
        "sim-time-limit = 1000s",
        "**.qrsa.hm.link_tomography = false",
        "**.qrsa.hm.initial_purification = 0",
        '**.qrsa.hm.purification_type = ""',
        "*.alice.is_initiator = true",
        "**.buffers = 2",
        f"**.app.number_of_bellpair = {num_bellpairs}",
        f"**.qrsa.hm.num_measure = {num_bellpairs}",
    ]
    return [config_name, network_name, *error_params, *other_params]


def write_config(filename: str, configs: list[list[str]]):
    # config relative path inside simulation folder
    dirname = os.path.dirname(__file__)
    general_ini_file = os.path.join(dirname, "general_config.ini")
    filename = os.path.join(dirname, filename)

    with open(filename, "w") as the_file:
        with open(general_ini_file) as f:
            for line in f:
                the_file.write(line)
        the_file.write("\n\n\n")
        for config in configs:
            the_file.write("\n".join(config))
            the_file.write("\n\n\n")


memory_coherence_time_params = [18 * 1000, 55 * 1000]  # in milliseconds
link_fidelities = list(np.linspace(0.6, 1, 21))

config_no_error = generate_purification_experiment_config(100_000, 0, 0, False, 0)
config_no_error_short_time = generate_purification_experiment_config(
    500, 0, 0, False, 0
)
# config_only_depolarizing_error = [generate_purification_experiment_config(100_000, 0, 0, True, dp) for dp in memory_coherence_time_params]
config_purification_initial_fidelity_no_error = [
    generate_purification_experiment_config_with_initial_fidelity(
        100_000, 0, 0, fid, False, 0
    )
    for fid in link_fidelities
]
config_purification_initial_fidelity_no_error_short_time = [
    generate_purification_experiment_config_with_initial_fidelity(
        500, 0, 0, fid, False, 0
    )
    for fid in link_fidelities
]

config_purification_initial_fidelity_18ms = [
    generate_purification_experiment_config_with_initial_fidelity(
        100_000, 0, 0, fid, True, 18_000
    )
    for fid in link_fidelities
]
config_purification_initial_fidelity_55ms = [
    generate_purification_experiment_config_with_initial_fidelity(
        100_000, 0, 0, fid, True, 55_000
    )
    for fid in link_fidelities
]

config_purification_initial_fidelity_18ms_short = [
    generate_purification_experiment_config_with_initial_fidelity(
        500, 0, 0, fid, True, 18_000
    )
    for fid in link_fidelities
]
config_purification_initial_fidelity_55ms_short = [
    generate_purification_experiment_config_with_initial_fidelity(
        500, 0, 0, fid, True, 55_000
    )
    for fid in link_fidelities
]

write_config(
    "cross_validation_config_generated.ini",
    [
        config_no_error,
        config_no_error_short_time,
        # *config_only_depolarizing_error,
        *config_purification_initial_fidelity_no_error,
        *config_purification_initial_fidelity_no_error_short_time,
        # *purification_config_no_operation_error,
        *config_purification_initial_fidelity_18ms,
        *config_purification_initial_fidelity_55ms,
        # short time version
        *config_purification_initial_fidelity_18ms_short,
        *config_purification_initial_fidelity_55ms_short,
        # *purification_config_gate_error,
        # *purification_config_gate_error_with_depo,
        # *purification_config_meas_error,
        # *purification_config_meas_error_with_depo,
    ],
)
