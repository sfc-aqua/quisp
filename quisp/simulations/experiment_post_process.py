import os
import re
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from experiment_config_generator import get_p_memory_channel_from_coherence_time

######################### CONSTANTS #########################
# Speed of light in optical fiber (m/s)
C_FIBER_M_S = 208189206.944
# Half the distance between Alice and Bob (m)
L_HALF_M_PURIFICATION: int = int(20e3)
L_HALF_M_SWAP = int(10e3)
# Separation time between photons in a train (1 ns)
T_SEP_S = 1e-9


######################### ANALYTICAL MODEL FUNCTIONS #########################


def photon_arrival_probability_from_km_distance(
    distance: int, loss_db_per_km: float = 0.2
) -> float:
    """Return loss probability given distance in km."""
    attenuation_distance = 10 / (np.log(10) * loss_db_per_km)
    return np.exp(-distance / attenuation_distance)


def werner_to_bell_diagonal(fidelity: float) -> np.ndarray:
    """Converts a Werner state fidelity to a Bell diagonal state vector [w, x, y, z]."""
    w = fidelity
    x = (1 - fidelity) / 3.0
    y = (1 - fidelity) / 3.0
    z = (1 - fidelity) / 3.0
    return np.array([w, x, y, z])


def get_decay_rate_param(t_coh: float) -> float:
    """
    Calculates the exponential decay base R such that a single qubit
    starting at 1.0 decays to 1/e at t = t_coh.

    Formula derived from: 1/e = 0.25 + 0.75 * R
    => R = (1/e - 0.25) / 0.75 = (4/e - 1) / 3

    The decay factor at time t will be R^(t / t_coh).
    """
    if t_coh == 0 or t_coh == float("inf"):
        return 1.0

    # This is the "survival fraction" of the excess fidelity at t=t_coh
    base_R = (4.0 / np.e - 1.0) / 3.0
    return base_R


def get_bell_decay_base(t_coh: float) -> float:
    """
    Returns the base R such that the Bell pair fidelity F(t)
    decays to exactly 1/e at t = t_coh.

    F(t) = 0.25 + 0.75 * R^(t/t_coh)
    """
    if t_coh == 0 or t_coh == float("inf"):
        return 1.0

    # Solve 1/e = 0.25 + 0.75 * R
    # R = (1/e - 0.25) / 0.75
    R = (4.0 / np.e - 1.0) / 3.0
    return R


def decay_coefficients(e_vec: np.ndarray, t: float, t_coh: float) -> np.ndarray:
    if t_coh == 0 or t_coh == float("inf"):
        return e_vec

    # Get the rate that satisfies the condition for the full system
    R = get_bell_decay_base(t_coh)

    # Apply exactly that rate (do NOT double t, because R is already tuned for the Bell pair; i.e., 2 qubits decoherence)
    decay_factor = np.power(R, t / t_coh)

    e_decayed = 0.25 + (e_vec - 0.25) * decay_factor
    return e_decayed


def geometric_sum_decay(
    e_init: np.ndarray, t_base: float, t_round: float, t_coh: float, p_geom: float
) -> np.ndarray:
    if t_coh == 0 or t_coh == float("inf"):
        return e_init

    R = get_bell_decay_base(t_coh)

    # Decay per round (no doubling, R is system-level)
    decay_per_round = np.power(R, t_round / t_coh)

    r_factor = (1.0 - p_geom) * decay_per_round
    if r_factor >= 1.0:
        raise ValueError("Series divergence")

    geom_sum = 1.0 / (1.0 - r_factor)

    # First term decay
    decay_first = np.power(R, (t_base + t_round) / t_coh)

    prefactor = p_geom * decay_first * geom_sum
    return 0.25 + (e_init - 0.25) * prefactor


def calculate_p_succ(e1: np.ndarray, e2: np.ndarray) -> float:
    """Calculates purification success probability P_succ."""
    w1, x1, y1, z1 = e1
    w2, x2, y2, z2 = e2
    # P_succ = (w1 + z1)(w2 + z2) + (x1 + y1)(x2 + y2)
    return (w1 + z1) * (w2 + z2) + (x1 + y1) * (x2 + y2)


def calculate_output_state(e1: np.ndarray, e2: np.ndarray, p_succ: float) -> np.ndarray:
    """Calculates the normalized output Bell diagonal state."""
    if p_succ <= 0:
        return np.array([0.25, 0.25, 0.25, 0.25])  # Return mixed state if fail

    w1, x1, y1, z1 = e1
    w2, x2, y2, z2 = e2

    w_out = (w1 * w2 + z1 * z2) / p_succ
    x_out = (x1 * x2 + y1 * y2) / p_succ
    y_out = (x1 * y2 + y1 * x2) / p_succ
    z_out = (w1 * z2 + z1 * w2) / p_succ

    return np.array([w_out, x_out, y_out, z_out])


def get_timing_constants(t_wait: float):
    """
    Calculates the exact timing constants (T0, T_subsequent).
    """
    # Round duration for 1 attempt (t_link,1)
    t_round_1 = t_wait + 2 * (L_HALF_M_PURIFICATION / C_FIBER_M_S)
    # Round duration for 2 attempts (t_link,2) = t_link,1 + t_sep
    t_round_2 = t_round_1 + T_SEP_S
    # link probability (turns into km first)
    p_link = (
        photon_arrival_probability_from_km_distance(L_HALF_M_PURIFICATION // 1000) ** 2
        * 0.5
    )

    # Expected time from S1 to S2
    T1 = t_round_1 / p_link

    # Expected time from S0 to S2 (T0)
    numerator = t_round_2 + 2 * (1 - p_link) * t_round_1
    denominator = p_link * (2 - p_link)
    T0 = numerator / denominator

    # Expected time for subsequent attempts
    T_subsequent = t_round_1 + p_link * T1 + (1 - p_link) * T0

    return t_round_1, T0, T_subsequent


def get_analytical_values_with_decoherence(
    n_conn: int, t_wait_s: float, fin_range: np.ndarray, t_coh: float
):
    """
    Calculates analytical metrics (Time, Prob, Fidelity) considering memory decoherence.
    """
    # 1. Get Timing Constants
    t_round_1, T0, T_subsequent = get_timing_constants(t_wait_s)
    # link probability (turns into km first)
    p_link = (
        photon_arrival_probability_from_km_distance(L_HALF_M_PURIFICATION // 1000) ** 2
        * 0.5
    )

    # 2. Define Probabilities for the Average State
    # P_sim: Probability of simultaneous generation from S0
    P_sim = p_link / (2.0 - p_link)
    P_seq = 1.0 - P_sim

    # P_S1: Probability of entering 'Head Start' (link success during purification delay)
    # We approximate the delay as one round-trip time (t_fresh)
    P_S1_during_delay = 2 * p_link * (1.0 - p_link)

    # 3. Define Ages
    # Fresh pair age (min time for BSA result)
    t_fresh = 2 * L_HALF_M_PURIFICATION / C_FIBER_M_S
    # Delay for the head start case (assumed to be roughly t_fresh)
    t_delay = t_fresh

    # t_fresh = 2 * t_fresh
    # t_delay = 2 * t_delay

    analytical_times = []
    analytical_probabilities = []
    analytical_fidelities = []

    for f_in in fin_range:
        # -- Step A: Calculate Average Input States --
        rho_init = werner_to_bell_diagonal(f_in)

        # State of the Fresh Pair (Deterministic)
        rho_fresh = decay_coefficients(rho_init, 2 * t_fresh, t_coh)

        # State of the Stale Pair (Probabilistic Average)

        # Part 1: Startup / Reset Scenarios (From S0)
        # 1a. Simultaneous: Age = t_fresh
        rho_startup_sim = rho_fresh
        # 1b. Sequential: Age = t_fresh + k*t_round
        rho_startup_seq = geometric_sum_decay(
            rho_init, 2 * t_fresh, 2 * t_round_1, t_coh, p_link
        )

        rho_startup = P_sim * rho_startup_sim + P_seq * rho_startup_seq

        # Part 2: Head Start Scenario (From S1)
        # Age = t_fresh + t_delay + k*t_round
        rho_headstart = geometric_sum_decay(
            rho_init, 2 * (t_fresh + t_delay), 2 * t_round_1, t_coh, p_link
        )

        # Combine weighted averages
        rho_stale_avg = (
            1.0 - P_S1_during_delay
        ) * rho_startup + P_S1_during_delay * rho_headstart

        # -- Step B: Purification --
        p_succ = calculate_p_succ(rho_stale_avg, rho_fresh)

        # need to change it here (do the calculation again but with additional waiting time from purification to the actual estimation)
        rho_stale_avg_after_heralded = rho_stale_avg
        rho_fresh_after_heralded = rho_fresh

        t_herald = 2 * L_HALF_M_PURIFICATION / C_FIBER_M_S
        rho_stale_avg_after_heralded = decay_coefficients(
            rho_stale_avg, t_herald, t_coh
        )
        rho_fresh_after_heralded = decay_coefficients(rho_fresh, t_herald, t_coh)
        e_out = calculate_output_state(
            rho_stale_avg_after_heralded, rho_fresh_after_heralded, p_succ
        )
        f_out = e_out[0]  # Fidelity is the first coefficient (Phi+)

        # -- Step C: Connection Time --
        if p_succ > 0:
            time_s = T0 + ((n_conn - p_succ) / p_succ) * T_subsequent
        else:
            time_s = np.inf

        analytical_probabilities.append(p_succ)
        analytical_fidelities.append(f_out)
        analytical_times.append(time_s)

    return analytical_times, analytical_probabilities, analytical_fidelities


def get_swap_fidelity(p_cnot: float, p_meas: float) -> float:
    p_no_error = (1 - p_cnot) * (1 - p_meas) ** 2
    p_cnot_err = 3 / 15 * p_cnot * (1 - p_meas) ** 2
    p_single_meas_err = 8 / 15 * p_cnot * (1 - p_meas) * p_meas
    p_two_meas_err = 4 / 15 * p_cnot * p_meas**2
    return p_no_error + p_cnot_err + p_single_meas_err + p_two_meas_err


def get_fidelity_decay_factor_from_decoherence(
    total_time_mu_s: int, coherence_time: int
) -> float:
    """Returns the fidelity factor of total effect from decoherence.
    This is an approximation and a trick utilizing stabilizer by moving the memory error channel to always
    act on idling memories; e.g., photons are always perfect, memories at swapper are perfect by multiplying
    stabilizer element to move the effect of noise to end nodes."""
    # Constant for QuISP's 1/e definition
    kappa = -np.log((4 / np.e - 1) / 3)
    decay_factor = np.exp(-kappa * (total_time_mu_s / coherence_time))

    return 0.25 + 0.75 * decay_factor


def get_analytical_fidelity_for_entanglement_swap_experiment(
    p_cnot: float, p_meas: float, t_coh: int, with_deterministic_link: bool = False
) -> float:
    """Returns expected fidelity for entanglement swap request given:
    - error probability of CNOT
    - error probability of measurement
    - coherence time in microsecond"""
    fidelity_swap = get_swap_fidelity(p_cnot, p_meas)
    fidelity_mem = 1

    # t is time taken (in microsecond) for 1 trip from alice (bob) to repeater (L_0).
    # not to be confused with L (overall distance)
    t = round(2 * L_HALF_M_SWAP / C_FIBER_M_S * 1_000_000)
    p_link = (
        0.5 * photon_arrival_probability_from_km_distance(L_HALF_M_SWAP // 1000) ** 2
    )

    if t_coh != 0:
        fidelity_mem = 0
        t_round = round(10 * T_SEP_S * 1_000_000 + t)
        for i in range(20):
            f_stale = get_fidelity_decay_factor_from_decoherence(
                # first pair minimum time
                2 * t
                # fisrt pair additional wait time
                + 2 * t_round * i
                # second pair minimum time
                + 2 * t
                # e2e pair time after swap
                + 2 * t,
                t_coh,
            )
            fidelity_mem += p_link * (1 - p_link) ** i * f_stale

    f_total = (
        fidelity_mem * fidelity_swap + ((1 - fidelity_mem) * (1 - fidelity_swap)) / 3.0
    )
    return f_total


def get_analytical_completion_time_link_request(
    num_mems: int, num_pairs: int, alice_dist_km: int, bob_dist_km: int
) -> float:
    """Returns expected time to complete the request"""
    L = alice_dist_km + bob_dist_km
    d = max(alice_dist_km, bob_dist_km)
    p_success = (
        photon_arrival_probability_from_km_distance(alice_dist_km)
        * photon_arrival_probability_from_km_distance(bob_dist_km)
        * 0.5
    )
    expected_rounds = np.ceil(num_pairs / (num_mems * p_success))
    T_0 = 1000 * d / C_FIBER_M_S
    T_setup = 1000 * (2 * L + d) / C_FIBER_M_S
    T_round = 2 * T_0 + 10 * T_SEP_S + (num_mems - 1) * T_SEP_S
    return T_setup + expected_rounds * T_round


######################### FILE EXTRACTION HELPERS #########################


def extract_lines_by_keyword(fn: str, kw: str) -> list[str]:
    found_lines = []
    if not os.path.exists(fn):
        return []
    with open(fn, "r") as f:
        for line in f:
            if kw not in line.strip():
                continue
            found_lines.append(line.strip())
    return found_lines


def extract_lines_below_keyword(fn: str, kw: str) -> list[str]:
    found_lines = []
    get_this_line = False
    if not os.path.exists(fn):
        return []
    with open(fn, "r") as f:
        for line in f:
            if get_this_line:
                found_lines.append(line.strip())
                get_this_line = False
                continue
            if kw in line.strip():
                get_this_line = True
    return found_lines


def extract_completion_time(fn: str):
    """Returns mean and std of completion time found in the log file (given fn string)"""
    lines = extract_lines_by_keyword(fn, "sim time:")
    completion_times = []
    for line in lines:
        try:
            t = float(line.split("sim time: ")[1].split(";")[0].strip())
            # We assume that the link start time (first BSA message) is sent at 10.00s.
            completion_times.append(t - 10)
        except IndexError:
            continue
    completion_times = [v for k, v in enumerate(completion_times) if k % 2 == 0]
    if not completion_times:
        return 0, 0
    return np.mean(completion_times), np.std(completion_times)


def extract_fidelity(fn: str):
    """Returns mean and std of fidelities found in the log file (given fn string)"""
    lines = extract_lines_by_keyword(fn, "Fidelity=")
    fidelities = []
    for line in lines:
        try:
            fid = float(line.split("Fidelity=")[1].split(";")[0])
            fidelities.append(fid)
        except IndexError:
            continue
    fidelities = [v for k, v in enumerate(fidelities) if k % 2 == 0]
    if not fidelities:
        return 0, 0
    return np.mean(fidelities), np.std(fidelities)


def extract_purification_success(fn: str, target_count: int, num_memories: int = 2):
    """Returns the purification success probability calculated by the raw BSA statistics.
    The number of memories is required because the final memories will be entangled but unused
    for precise accounting."""
    lines = extract_lines_below_keyword(fn, "BSA Statistics (raw):")
    total_events = []
    for line in lines:
        try:
            bsm_events = (sum(map(int, line.strip().split(" "))) - (2 * num_memories)) / 4
            if bsm_events > 0:
                total_events.append(target_count * 1.0 / bsm_events)
        except ValueError:
            continue
    if not total_events:
        return 0, 0
    return np.mean(total_events), np.std(total_events)


######################### LOG EXTRACTION TO CSV #########################
experiment_0_file_pattern = re.compile(
    r"swapping_validation_cnot_(\d+)_meas_(\d+)_with_(\d+|inf)_coherence_time_for_(\d+)_pairs"
)
experiment_1_file_pattern = re.compile(
    r"cross_validation_mim_link_imbalanced_10km_10km_(\d+)_memories_for_(\d+)"
)
experiment_2_file_pattern = re.compile(
    r"cross_validation_mim_link_imbalanced_(\d+)km_(\d+)km_1_memories_for_(\d+)"
)
experiment_3_file_pattern = re.compile(
    r"swapping_validation_cnot_(\d+)_meas_(\d+)_with_(\d+|inf)_coherence_time_for_(\d+)_pairs"
)
experiment_4_file_pattern = re.compile(
    r"purification_validation_with_(\d+|inf)_coherence_for_(\d+)_pairs_with_link_fidelity_(\d+|unit)"
)

base_path = os.path.dirname(__file__)
base_path = str(Path(base_path).parents[0])
base_path = f"{base_path}/cross-validation"

# extract logs of exp 1
exp_1_base_path = f"{base_path}/exp1"
exp_1_data = []

for fn in os.listdir(exp_1_base_path):
    match = experiment_1_file_pattern.match(fn)
    if match is None:
        continue
    num_mems, num_pairs = map(int, match.groups())
    mu, sigma = extract_completion_time(os.path.join(exp_1_base_path, fn.lstrip("/")))
    exp_1_data.append(
        {
            "num_mem": num_mems,
            "num_bellpairs": num_pairs,
            "completion_time_mean": mu,
            "completion_time_std": sigma,
            "completion_time_analytical": get_analytical_completion_time_link_request(
                num_mems, num_pairs, 10, 10
            ),
        }
    )
df_exp1 = pd.DataFrame(exp_1_data)
df_exp1.sort_values("num_mem").to_csv(
    f"{os.path.dirname(__file__)}/exp1.csv", index=False
)

# extract logs of exp 2
exp_2_base_path = f"{base_path}/exp2"
exp_2_data = []

for fn in os.listdir(exp_2_base_path):
    match = experiment_2_file_pattern.match(fn)
    if match is None:
        continue
        # raise RuntimeError("cannot find files for exp 1 to extract.")
    alice_dist, bob_dist, num_pairs = map(int, match.groups())
    mu, sigma = extract_completion_time(os.path.join(exp_2_base_path, fn.lstrip("/")))
    exp_2_data.append(
        {
            "alice_dist": alice_dist,
            "bob_dist": bob_dist,
            "num_bellpairs": num_pairs,
            "completion_time_mean": mu,
            "completion_time_std": sigma,
            "completion_time_analytical": get_analytical_completion_time_link_request(
                1, num_pairs, alice_dist, bob_dist
            ),
        }
    )
df_exp2 = pd.DataFrame(exp_2_data)
df_exp2.sort_values("alice_dist").to_csv(
    f"{os.path.dirname(__file__)}/exp2.csv", index=False
)


# extract logs of exp 3
exp_3_base_path = f"{base_path}/exp3"
exp_3_data = []

for fn in os.listdir(exp_3_base_path):
    match = experiment_3_file_pattern.match(fn)
    if match is None:
        continue
        # raise RuntimeError("cannot find files for exp 1 to extract.")
    p_cnot, p_meas, coh_time, num_pairs = match.groups()
    # correcting the data from file name
    coh_time = int(coh_time) if coh_time != "inf" else 0
    p_cnot = float(f"0.{p_cnot}")
    p_meas = float(f"0.{p_meas}")
    num_pairs = int(num_pairs)

    mu, sigma = extract_fidelity(os.path.join(exp_3_base_path, fn.lstrip("/")))
    exp_3_data.append(
        {
            "num_bellpairs": num_pairs,
            "cnot_err_prob": p_cnot,
            "meas_err_prob": p_meas,
            "coherence_time": coh_time,
            "fidelity_mean": mu,
            "fidelity_std": sigma,
            "fidelity_analytical": get_analytical_fidelity_for_entanglement_swap_experiment(
                p_cnot, p_meas, coh_time
            ),
        }
    )
df_exp3 = pd.DataFrame(exp_3_data)
df_exp3.sort_values(["num_bellpairs", "coherence_time", "cnot_err_prob", "meas_err_prob"]).to_csv(
    f"{os.path.dirname(__file__)}/exp3.csv", index=False
)

# extract logs of exp 0 (validation of error model)
exp_0_base_path = f"{base_path}/validation"
exp_0_data = []

for fn in os.listdir(exp_0_base_path):
    match = experiment_0_file_pattern.match(fn)
    if match is None:
        continue
        # raise RuntimeError("cannot find files for exp 1 to extract.")
    p_cnot, p_meas, coh_time, num_pairs = match.groups()
    # correcting the data from file name
    coh_time = int(coh_time) if coh_time != "inf" else 0
    p_cnot = float(f"0.{p_cnot}")
    p_meas = float(f"0.{p_meas}")
    num_pairs = int(num_pairs)

    mu, sigma = extract_fidelity(os.path.join(exp_0_base_path, fn.lstrip("/")))
    exp_0_data.append(
        {
            "num_bellpairs": num_pairs,
            "cnot_err_prob": p_cnot,
            "meas_err_prob": p_meas,
            "coherence_time": coh_time,
            "fidelity_mean": mu,
            "fidelity_std": sigma,
            "fidelity_analytical": get_analytical_fidelity_for_entanglement_swap_experiment(
                p_cnot, p_meas, coh_time
            ),
        }
    )
df_exp0 = pd.DataFrame(exp_0_data)
df_exp0.sort_values(
    ["num_bellpairs", "coherence_time", "cnot_err_prob", "meas_err_prob"]
).to_csv(f"{os.path.dirname(__file__)}/exp0.csv", index=False)


# extract logs of exp 4
exp_4_base_path = f"{base_path}/exp4"
exp_4_data = []

for fn in os.listdir(exp_4_base_path):
    match = experiment_4_file_pattern.match(fn)
    if match is None:
        continue
        # raise RuntimeError("cannot find files for exp 1 to extract.")
    coh_time, num_pairs, link_fidelity = match.groups()
    # correcting the data from file name
    coh_time = int(coh_time) if coh_time != "inf" else 0
    num_pairs = int(num_pairs)
    if link_fidelity != "unit":
        link_fidelity = float(f"0.{link_fidelity}")
    else:
        link_fidelity = 1.0

    f_mu, f_sigma = extract_fidelity(os.path.join(exp_4_base_path, fn.lstrip("/")))
    t_mu, t_sigma = extract_completion_time(
        os.path.join(exp_4_base_path, fn.lstrip("/"))
    )
    p_succ_mu, p_succ_sigma = extract_purification_success(
        os.path.join(exp_4_base_path, fn.lstrip("/")), num_pairs
    )

    t_ana, p_succ_ana, f_ana = get_analytical_values_with_decoherence(
        num_pairs, 1e-8, np.array([link_fidelity]), coh_time / 1_000_000
    )
    exp_4_data.append(
        {
            "num_bellpairs": num_pairs,
            "coherence_time": coh_time,
            "link_fidelity": link_fidelity,
            "fidelity_mean": f_mu,
            "fidelity_std": f_sigma,
            "completion_time_mean": t_mu,
            "completion_time_std": t_sigma,
            "purification_success_prob_mean": p_succ_mu,
            "purification_success_prob_std": p_succ_sigma,
            "fidelity_analytical": f_ana[0],
            "completion_time_analytical": t_ana[0],
            "purification_success_prob_analytical": p_succ_ana[0],
        }
    )
df_exp4 = pd.DataFrame(exp_4_data)
df_exp4.sort_values(["coherence_time", "num_bellpairs", "link_fidelity"]).to_csv(
    f"{os.path.dirname(__file__)}/exp4.csv", index=False
)
