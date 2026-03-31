#!/usr/bin/python3

import os
from pathlib import Path

import numpy as np


def get_channel_error_from_link_werner_noise(fidelity, dist_in_km) -> float:
    """
    Given the expected initial link-level (from node to BSA; not from node to node) fidelity and distance of the fiber,
    return the px, py, pz (per km) for the transition matrix to be used for QuantumChannel.ned assuming isotropic noise (Werner state).
    """
    left: float = 0.0
    right: float = 0.3
    l: float = (
        0.04500741397  # this is the fixed loss probability per kilometer (coming from ~0.2 dB/km)
    )
    iter_count = 0
    while left < right:
        p = (left + right) / 2
        iter_count += 1
        if iter_count > 100:
            print("exceed max iteration in getting channel error from link werner noise")
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
    return p


def get_channel_fidelity_from_symmetric_link_fidelity(f):
    """Returns the fidelity for photon-memory Bell pairs at the BSA from the fidelity
    of the link (memory-memory).
    A -- BSA -- C: given f A--C
    returns A--BSA and BSA--C fidelity; assuming symmetric BSA and Werner state.
    """
    left: float = 0.0
    right: float = 1
    iter_count = 0
    while left < right:
        p = (left + right) / 2
        iter_count += 1
        if iter_count > 100:
            print("exceed max iteration")
            raise RuntimeError("Could not find fidelity")
        fn = p**2 + 3 * ((1 - p) / 3) ** 2
        if fn > f:
            right = p
        else:
            left = p
        if round(fn, 10) == round(f, 10):
            break
    return p


def get_p_memory_channel_from_coherence_time(decoherence_time_mu_s: int) -> float:
    """Returns the X, Y, Z error probability of the memory channel;
    p = px = py = pz, meaning probability of no error is 1 - 3p."""
    # Although QuISP allows for relaxation/excitation noise, we do not include it here.
    left: float = 0.0
    right: float = 0.3
    iter_count = 0
    while left < right:
        p = (left + right) / 2
        iter_count += 1
        if iter_count > 100:
            print(f"exceed max iteration in getting channel error for decoherence: given {decoherence_time_mu_s}")
            print(f"we got p (memory) = {p}")
            print(f"    expected (fidelity has decohere): {1/np.e}")
            print(f"    obtained after T time has passed: {Qt[0, 0]}")
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
    # print(f"we got p (memory) = {p}")
    # print(f"    expected (fidelity has decohere): {1/np.e}")
    # print(f"    obtained after T time has passed: {Qt[0, 0]}")
    return p


def generate_imbalanced_mim_config(
    alice_dist: int, bob_dist: int, num_memory: int, num_bellpairs: int
):
    """Returns array of config strings for Exp 1 and 2."""
    config_name = f"[Config cross_validation_mim_link_imbalanced_{alice_dist}km_{bob_dist}km_{num_memory}_memories_for_{num_bellpairs}]"
    network_name = f"network = networks.cross_validation_mim_link_imbalanced_{alice_dist}_{bob_dist}"
    main_params = [
        f"**.buffers = {num_memory}",
        f"**.app.number_of_bellpair = {num_bellpairs}",
        f"**.qrsa.hm.num_measure = {num_bellpairs}",
    ]
    other_params = [
        "repeat = 200",
        "seed-set =  ${repetition}",
        "**.photon_detection_per_second = 1000000000 # 1GHz",
        "**.qrsa.hm.link_tomography = false",
        "**.qrsa.hm.initial_purification = 0",
        '**.qrsa.hm.purification_type = ""',
        "*.alice.is_initiator = true",
    ]
    return [config_name, network_name, *main_params, *other_params]


def generate_swapping_config(
    num_bell_pairs: int,
    cnot_error_prob: float,
    measurement_error_prob: float,
    with_decoherence: bool,
    coherence_time_in_mu_s: int,
    with_coherence_time_in_sequence_duration: bool,
):
    # round error probability to 6 decimal places
    cnot_error_prob = round(cnot_error_prob, 6)
    measurement_error_prob = round(measurement_error_prob, 6)
    if with_coherence_time_in_sequence_duration:
        sequence_factor = -np.log((4 / np.e - 1) / 3)
        coherence_time_in_mu_s /= sequence_factor
        coherence_time_in_mu_s = round(coherence_time_in_mu_s)

    # delete leading 0. and change it into string
    cnot_error_prob_str = str(cnot_error_prob)[2:]
    measurement_error_prob_str = str(measurement_error_prob)[2:]
    coherence_time_str = "inf"
    if len(cnot_error_prob_str) == 0:
        cnot_error_prob_str = "0"
    if len(measurement_error_prob_str) == 0:
        measurement_error_prob_str = "0"
    if with_decoherence:
        coherence_time_str = str(coherence_time_in_mu_s).split(".")[0]
    p_decoherence = (
        get_p_memory_channel_from_coherence_time(coherence_time_in_mu_s) if with_decoherence else 0
    )

    config_name = f"[Config swapping_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_with_{coherence_time_str}_coherence_time_for_{num_bell_pairs}_pairs]"
    network_name = "network = networks.cross_validation_swapping"
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
        "repeat = 30",
        "seed-set =  ${repetition}",
        "**.photon_detection_per_second = 1000000000 # 1GHz",
        "**.qrsa.hm.link_tomography = false",
        "**.qrsa.hm.initial_purification = 0",
        '**.qrsa.hm.purification_type = ""',
        "*.alice.is_initiator = true",
        #
        "**.buffers = 1",
        f"**.app.number_of_bellpair = {num_bell_pairs}",
        "**.qrsa.hm.num_measure = 10",
    ]
    return [config_name, network_name, *error_params, *other_params]


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
    with_decoherence: bool,
    coherence_time_in_mu_s: int,
    with_coherence_time_in_sequence_duration: bool,
    initial_link_fidelity: float,
):
    """This function generates simulation config for experiment 4 in the paper with no memory decoherence."""
    if with_coherence_time_in_sequence_duration:
        sequence_factor = -np.log((4 / np.e - 1) / 3)
        coherence_time_in_mu_s /= sequence_factor
        coherence_time_in_mu_s = round(coherence_time_in_mu_s)

    channel_error_single_prob = get_channel_error_from_link_werner_noise(
        get_channel_fidelity_from_symmetric_link_fidelity(initial_link_fidelity), 20
    )
    if initial_link_fidelity == 1:
        channel_error_single_prob = 0

    initial_fidelity = round(initial_link_fidelity, 6)
    initial_f_str = str(initial_fidelity)[2:] if initial_fidelity != 1 else 'unit'

    coherence_time_str = "inf"
    if with_decoherence:
        coherence_time_str = str(coherence_time_in_mu_s).split(".")[0]
    p_decoherence = (
        get_p_memory_channel_from_coherence_time(coherence_time_in_mu_s) if with_decoherence else 0
    )

    config_name = f"[Config purification_validation_with_{coherence_time_str}_coherence_for_{num_bellpairs}_pairs_with_link_fidelity_{initial_f_str}]"

    network_name = "network = networks.cross_validation_purification"
    error_params = [
        f"**.memory_x_error_rate = {p_decoherence}",
        f"**.memory_y_error_rate = {p_decoherence}",
        f"**.memory_z_error_rate = {p_decoherence}",
        #
        f"**.channel_x_error_rate = {channel_error_single_prob}",
        f"**.channel_z_error_rate = {channel_error_single_prob}",
        f"**.channel_y_error_rate = {channel_error_single_prob}",
    ]
    other_params = [
        "repeat = 30",
        "seed-set =  ${repetition}",
        "**.photon_detection_per_second = 1000000000 # 1GHz",
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
    config_names = []
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
            cur_conf_name = config[0][8:-1]
            if cur_conf_name in config_names:
                continue
            config_names.append(cur_conf_name)
            the_file.write("\n".join(config))
            the_file.write("\n\n\n")
    return config_names

def write_run_commands_to_bash_script(filename: str, ini_file: str, configs: list[str], result_dest: str):
    dirname = os.path.dirname(__file__)
    dirname = str(Path(dirname).parents[0])
    filename = os.path.join(dirname, filename)

    pre_commands = [f"mkdir -p {result_dest}\n", "pids=()\n\n"]
    run_commands = []
    for i, config in enumerate(configs):
        run_commands.append(f"""
echo "Running {config}"
./quisp -n "./networks:./channels:./modules:./simulations" \\
    -i ./images ./simulations/{ini_file} -u Cmdenv \\
    -c "{config}" --cmdenv-status-frequency=10s > "{result_dest}/{config.replace('-', '_')}" &
pids+=($!)
        """)
        if i % 16 == 15:
            run_commands.append("""
echo "waiting for experiments"
for pid in ${pids[*]};
do
    echo "waiting on pid = $pid"
    wait $pid
done
pids=()
""")
    post_commands = [
        """
echo "waiting for experiments"
for pid in ${pids[*]};
do
    echo "waiting on pid = $pid"
    wait $pid
done
pids=()
    """
    ]
    with open(filename, 'w') as the_file:
        for cmd in pre_commands:
            the_file.write(cmd)
        for cmd in run_commands:
            the_file.write(cmd)
        for cmd in post_commands:
            the_file.write(cmd)


memory_coherence_time_params = [0, 18 * 1000, 55 * 1000]  # in milliseconds
link_fidelities = list(np.linspace(0.6, 1, 21))

fixed_cnot_err = 0.05
fixed_meas_err = 0.1
fixed_cnot_err_adjusted = fixed_cnot_err / 16 * 15


# experiment 1: varying memories
config_exp_1_mim_varying_memories = [
    generate_imbalanced_mim_config(10, 10, num_mem, 1000)
    for num_mem in [1, 2, 4, 8, 16, 32]
]

# experiment 2: varying BSA placement
config_exp_2_varying_bsa_dist = [
    generate_imbalanced_mim_config(20 - bob_dist, bob_dist, 1, 1000)
    for bob_dist in range(11)
]

# model validation 0.1 model validation: varying CNOT error; fixed meas error at 0.1
config_model_validation_varying_cnot_err = [
    generate_swapping_config(10_000, p_cnot, fixed_meas_err, False, 0, False)
    for p_cnot in list(np.linspace(0, 1, 41))
]
# model validation 0.2: varying measurement error; fixed cnot error at 0.05
config_model_validation_varying_meas_err = [
    generate_swapping_config(10_000, fixed_cnot_err, p_meas, False, 0, False)
    for p_meas in list(np.linspace(0, 1, 41))
]
# model validation 0.3: varying coherence time; fixed cnot error at 0.05 and meas error at 0.1
#                       coherence times are in the range 1000 mu_s to 100_000 mu_s
config_model_validation_varying_coherence = [
    generate_swapping_config(10_000, fixed_cnot_err, fixed_meas_err, True, coh_time, False)
    for coh_time in list(np.round(1000 * np.logspace(0, 2, 40, endpoint=True)).astype(int))
]

## Below are experiments where we need to adjust CNOT error probability and coherence time to
##     SeQUeNCe's error description

# experiment 3.1: varying coherence time and varying cnot error; no other errors.
config_exp_3_varying_cnot_varying_coherence_adjusted = [
    generate_swapping_config(100_000, p_cnot, 0, coh_time != 0, coh_time, True)
    for coh_time in memory_coherence_time_params
    for p_cnot in list(15 / 16 * np.linspace(0, 1, 41))
]
# experiment 3.2: varying coherence time and varying meas error; no other errors.
config_exp_3_varying_meas_varying_coherence_adjusted = [
    generate_swapping_config(100_000, 0, p_meas, coh_time != 0, coh_time, True)
    for coh_time in memory_coherence_time_params
    for p_meas in list(np.linspace(0, 1, 41))
]

# experiment 4: varying link fidelity with inf coherence time; only with adjusted coherence time with SeQUeNCe
config_exp_4_varying_link_fidelities_adjusted = [
    generate_purification_experiment_config(100_000, coh_time != 0, coh_time, True, f_link)
    for coh_time in memory_coherence_time_params
    for f_link in link_fidelities
]

confignames = write_config(
    "cross_validation_config_experiment_1.ini",
    [
        *config_exp_1_mim_varying_memories,
    ],
)
write_run_commands_to_bash_script("cross-validation-sim-exp-1.sh", "cross_validation_config_experiment_1.ini", confignames, "cross-validation/exp1")

confignames = write_config(
    "cross_validation_config_experiment_2.ini",
    [
        *config_exp_2_varying_bsa_dist,
    ],
)
write_run_commands_to_bash_script("cross-validation-sim-exp-2.sh", "cross_validation_config_experiment_2.ini", confignames, "cross-validation/exp2")

confignames = write_config(
    "cross_validation_config_experiment_0_model_validation.ini",
    [
        *config_model_validation_varying_cnot_err,
        *config_model_validation_varying_meas_err,
        *config_model_validation_varying_coherence,
    ],
)
write_run_commands_to_bash_script("cross-validation-sim-exp-0-model-validation.sh", "cross_validation_config_experiment_0_model_validation.ini", confignames, "cross-validation/validation")

confignames = write_config(
    "cross_validation_config_experiment_3.ini",
    [
        *config_exp_3_varying_cnot_varying_coherence_adjusted,
        *config_exp_3_varying_meas_varying_coherence_adjusted,
    ],
)
write_run_commands_to_bash_script("cross-validation-sim-exp-3.sh", "cross_validation_config_experiment_3.ini", confignames, "cross-validation/exp3")

confignames = write_config(
    "cross_validation_config_experiment_4.ini",
    [
        *config_exp_4_varying_link_fidelities_adjusted
    ],
)
write_run_commands_to_bash_script("cross-validation-sim-exp-4.sh", "cross_validation_config_experiment_4.ini", confignames, "cross-validation/exp4")
