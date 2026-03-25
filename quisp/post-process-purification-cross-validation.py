import os

import matplotlib.pyplot as plt
import numpy as np


######################### MODELS #########################

# --- Constants based on the note ---
# Speed of light in optical fiber (m/s)
C_FIBER_M_S = 208189206.944
# Half the distance between Alice and Bob (m)
L_HALF_M = 20e3
# Link-level Bell pair generation probability
P_LINK = 0.07924465965


def werner_to_bell_diagonal(fidelity: float) -> np.ndarray:
    """Converts a Werner state fidelity to a Bell diagonal state vector."""
    w = fidelity
    x = (1 - fidelity) / 3.0
    y = (1 - fidelity) / 3.0
    z = (1 - fidelity) / 3.0
    return np.array([w, x, y, z])


def calculate_p_succ(e1: np.ndarray, e2: np.ndarray) -> float:
    """Calculates the purification success probability."""
    w1, x1, y1, z1 = e1
    w2, x2, y2, z2 = e2
    p_succ = (w1 + z1) * (w2 + z2) + (x1 + y1) * (x2 + y2)
    return p_succ


def calculate_output_state(e1: np.ndarray, e2: np.ndarray, p_succ: float) -> np.ndarray:
    """Calculates the output Bell diagonal state after a successful purification."""
    if p_succ == 0:
        return np.array([0.0, 0.0, 0.0, 0.0])
    w1, x1, y1, z1 = e1
    w2, x2, y2, z2 = e2
    w_out = (w1 * w2 + z1 * z2) / p_succ
    x_out = (x1 * x2 + y1 * y2) / p_succ
    y_out = (x1 * y2 + y1 * x2) / p_succ
    z_out = (w1 * z2 + z1 * w2) / p_succ
    return np.array([w_out, x_out, y_out, z_out])


def calculate_output_fidelity(e_out: np.ndarray) -> float:
    """Calculates the fidelity of the output state."""
    return e_out[0]


def calculate_t_conn(n_conn: int, p_link: float, t_link: float, p_succ: float) -> float:
    """Calculates the total expected time to complete the connection."""
    if p_link <= 0 or p_link >= 2 or p_succ <= 0:
        return np.inf

    e0 = (3 - 2 * p_link) / (p_link * (2 - p_link))
    e_subsequent = 2 + ((1 - p_link) * (3 - 2 * p_link)) / (p_link * (2 - p_link))
    t_conn = t_link * (e0 + ((n_conn - p_succ) / p_succ) * e_subsequent)
    return t_conn


def get_analytical_values(n_conn: int, t_wait_s: float, fin_range: np.ndarray):
    """
    Calculates analytical data and plots it against simulator data with error bars.
    """
    # --- 1. Calculate Analytical Data ---
    t_link = t_wait_s + 2 * (L_HALF_M / C_FIBER_M_S)

    analytical_fidelities = []
    analytical_probabilities = []
    analytical_times = []

    for f_in in fin_range:
        e_initial = werner_to_bell_diagonal(f_in)
        p_succ = calculate_p_succ(e_initial, e_initial)
        e_out = calculate_output_state(e_initial, e_initial, p_succ)
        f_out = calculate_output_fidelity(e_out)
        time_s = calculate_t_conn(n_conn, P_LINK, t_link, p_succ)

        analytical_probabilities.append(p_succ)
        analytical_fidelities.append(f_out)
        analytical_times.append(time_s)

    return analytical_times, analytical_probabilities, analytical_fidelities

# if __name__ == '__main__':
#     N_REQUESTED_PAIRS = 100_000
#     WAIT_TIME_S = 1e-8
#     initial_fidelities = np.linspace(0.6, 1.0, 21)

#     get_analytical_values(N_REQUESTED_PAIRS, WAIT_TIME_S, initial_fidelities)

######################### MODELS #########################




def extract_lines_by_keyword(fn: str, kw: str) -> list[str]:
    found_lines = []
    with open(fn, "r") as f:
        for line in f:
            if kw not in line.strip():
                continue
            found_lines.append(line.strip())
    return found_lines


def extract_lines_below_keyword(fn: str, kw: str) -> list[str]:
    found_lines = []
    get_this_line = False
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
    # this assumes we always have this and extract the first line
    lines = extract_lines_by_keyword(fn, "sim time:")
    completion_times = []
    for line in lines:
        t = float(line.split("sim time: ")[1].split(";")[0].strip())
        completion_times.append(t - 10)
    completion_times = [v for k, v in enumerate(completion_times) if k % 2 == 0]
    return np.mean(completion_times), np.std(completion_times)


def extract_fidelity(fn: str):
    # this assumes we always have this and extract the first line
    lines = extract_lines_by_keyword(fn, "Fidelity=")
    fidelities = []
    for line in lines:
        fid = float(line.split("Fidelity=")[1].split(";")[0])
        fidelities.append(fid)
    fidelities = [v for k, v in enumerate(fidelities) if k % 2 == 0]
    return np.mean(fidelities), np.std(fidelities)


def extract_purification_success(fn: str, target_count: int):
    # this assumes we always have this and extract the first line
    lines = extract_lines_below_keyword(fn, "BSA Statistics (raw):")
    # there are additional 4 for the last two unused Bell pairs
    total_events = []
    for line in lines:
        bsm_events = (sum(map(int, line.strip().split(" "))) - 4) / 4
        total_events.append(target_count * 1.0 / bsm_events)

    return np.mean(total_events), np.std(total_events)


#### main process
# base_path = "/workspaces/quisp/quisp/cross-validation/{no-error|18ms|55ms}/{short|long}"
base_path = os.path.dirname(__file__)
without_decoherence_long = [
    f"/cross-validation/no-error/long/purification-fidelity-no-error-initial-fidelity-{i}"
    for i in range(60, 101, 2)
]
without_decoherence_short = [
    f"/cross-validation/no-error/short/purification-fidelity-no-error-initial-fidelity-{i}"
    for i in range(60, 101, 2)
]
short_time_files = [
    f"/cross-validation/short-1000-purification-fidelity-no-error-initial-fidelity-{i}"
    for i in range(60, 101, 2)
]
with_18ms_decoherence_short = [
    f"/cross-validation/18ms/short/purification-fidelity-with-18ms-initial-fidelity-{i}"
    for i in range(60, 101, 2)
]
with_18ms_decoherence_long = [
    f"/cross-validation/18ms/long/purification-fidelity-with-18ms-initial-fidelity-{i}"
    for i in range(60, 101, 2)
]
with_55ms_decoherence_short = [
    f"/cross-validation/55ms/short/purification-fidelity-with-55ms-initial-fidelity-{i}"
    for i in range(60, 101, 2)
]
with_55ms_decoherence_long = [
    f"/cross-validation/55ms/long/purification-fidelity-with-55ms-initial-fidelity-{i}"
    for i in range(60, 101, 2)
]

# =========================================
# =========================================

# selected_scenario = without_decoherence_short
# selected_scenario = without_decoherence_long
# selected_scenario = with_18ms_decoherence_short
# selected_scenario = with_18ms_decoherence_long
# selected_scenario = with_55ms_decoherence_short
selected_scenario = with_55ms_decoherence_long

number_of_requested_bellpairs = 500 # short
# number_of_requested_bellpairs = 100_000 # long time for fidelity

# =========================================
# =========================================

#
abs_files = [os.path.join(base_path, rel) for rel in selected_scenario]
# print(base_path)
# print(abs_files)

initial_fidelities = [i / 100 for i in range(60, 101, 2)]

long_completion_times = [
    extract_completion_time(f"{base_path}{fn}") for fn in selected_scenario
]
short_completion_times = [
    extract_completion_time(f"{base_path}{fn}") for fn in short_time_files
]
fidelities = [
    extract_fidelity(f"{base_path}{fn}") for fn in selected_scenario
]
success_rates = [
    extract_purification_success(f"{base_path}{fn}", number_of_requested_bellpairs)
    for fn in selected_scenario
]

# completion_times = short_completion_times
completion_times = long_completion_times

completion_times, completion_times_err = map(list, zip(*completion_times))
fidelities, fidelities_err = map(list, zip(*fidelities))
success_rates, success_rates_err = map(list, zip(*success_rates))




# print(completion_times)
# print(fidelities)
# print(success_rates)

# print(completion_times_err)
# print(fidelities_err)
# print(success_rates_err)

N_REQUESTED_PAIRS = number_of_requested_bellpairs
WAIT_TIME_S = 1e-8
initial_fidelities = np.linspace(0.6, 1.0, 21)

ana_completion_times, ana_success_rates, ana_fidelities = get_analytical_values(N_REQUESTED_PAIRS, WAIT_TIME_S, initial_fidelities)

# output as a CSV format
print(f'initial fidelity (input), completion time (mean), completion time (stdev), fidelities (mean), fidelities (stdev), success rate (mean), success rate (stdev)')
for i in range(len(completion_times)):
    print(f'{initial_fidelities[i]}, {completion_times[i]}, {completion_times_err[i]}, {fidelities[i]}, {fidelities_err[i]}, {success_rates[i]}, {success_rates_err[i]}')


# --- 2. Create the Plot ---

# Create a figure and the first (primary) y-axis
fig, ax1 = plt.subplots(figsize=(12, 7))

# --- Plot 1: Completion Times (Left Y-axis) ---
color1 = 'tab:red'
ax1.set_xlabel('Initial Fidelity', fontsize=14)
ax1.set_ylabel('Completion Time (s)', color=color1, fontsize=14)
p1, = ax1.plot(initial_fidelities, ana_completion_times, color=color1, linestyle='-', label='Analityical Completion Time')
p1 = ax1.errorbar(initial_fidelities, completion_times, yerr=completion_times_err, color=color1, fmt='o', capsize=6, label='QuISP Completion Time')
# p1 = ax1.errorbar(initial_fidelities, completion_times, yerr=completion_times_err, color=color1, fmt='o', capsize=4, label='Simulator Success Prob.')
ax1.tick_params(axis='y', labelcolor=color1)
ax1.grid(True, linestyle='--', alpha=0.6)

# --- Plot 2: Fidelities (Right Y-axis 1) ---
# Create the second y-axis, sharing the x-axis with ax1
ax2 = ax1.twinx()
color2 = 'tab:blue'
ax2.set_ylabel('Final Fidelity', color=color2, fontsize=14)
p2, = ax2.plot(initial_fidelities, ana_fidelities, color=color2, linestyle='--', label='Analytical Fidelity')
# p2, = ax2.errorbar(initial_fidelities, fidelities, yerr=fidelities_err, color=color2, marker='s', linestyle='none', label='Final Fidelity')
p2 = ax2.errorbar(initial_fidelities, fidelities, yerr=fidelities_err, color=color2, fmt='s', capsize=6, label='QuISP e2e Fidelity')
ax2.tick_params(axis='y', labelcolor=color2)

# --- Add Reference Fidelity Line ---
# This plots a y=x line on the same axes as the final fidelity for easy comparison.
# p_ref, = ax2.plot(initial_fidelities, initial_fidelities, color='black', linestyle='--', alpha=0.7, label='Reference Fidelity (y=x)')
p_ref, = ax2.plot(initial_fidelities, initial_fidelities, color='black', linestyle='--', alpha=0.7, label='Reference Fidelity (y=x)')


# --- Plot 3: Success Rates (Right Y-axis 2) ---
# Create the third y-axis
ax3 = ax1.twinx()
color3 = 'tab:green'

# Offset the third y-axis's spine to prevent it from overlapping with the second one
ax3.spines['right'].set_position(('outward', 60))

ax3.set_ylabel('Success Rate', color=color3, fontsize=14)
p3, = ax3.plot(initial_fidelities, ana_success_rates, color=color3, linestyle=':', label='Analytical Success Rate')
# p3 = ax3.errorbar(initial_fidelities, success_rates, yerr=success_rates_err, color=color3, marker='^', linestyle='none', label='Success Rate')
p3 = ax3.errorbar(initial_fidelities, success_rates, yerr=success_rates_err, color=color3, fmt='^', capsize=6, label='QuISP Pur Success Rate')
# p3_sim = ax3.errorbar(initial_fidelities, sim_probabilities, yerr=sim_probabilities_err, color=color3,
                            # fmt='^', capsize=4, label='Simulator Success Prob.')
ax3.tick_params(axis='y', labelcolor=color3)


# --- 3. Final Touches ---
y_lim_range = (0.58, 1.04)
ax2.set_ylim(y_lim_range)
ax3.set_ylim(y_lim_range)

# Add a title
plt.title('Performance Metrics vs. Initial Fidelity for purification experiments (55ms)', fontsize=16)

# Create a combined legend for all plots, including the new reference line
fig.legend(handles=[p1, p2, p3, p_ref], loc='upper center', bbox_to_anchor=(0.5, 0.95), ncol=4, frameon=False)

# Ensure the layout is tight and clean
fig.tight_layout()

plt.savefig('purification_55ms_performance_plot.png', dpi=300, bbox_inches='tight')

# Display the plot
plt.show()






# import numpy as np
# import matplotlib.pyplot as plt

# ######################### CONSTANTS #########################
# # Speed of light in optical fiber (m/s)
# C_FIBER_M_S = 208189206.944
# # Half the distance between Alice and Bob (m)
# L_HALF_M = 20e3
# # Link-level Bell pair generation probability (constant based on loss)
# P_LINK = 0.07924465965
# # Separation time between photons in a train (1 ns)
# T_SEP_S = 1e-9


# ######################### HELPER FUNCTIONS #########################

# def werner_to_bell_diagonal(fidelity: float) -> np.ndarray:
#     """Converts a Werner state fidelity to a Bell diagonal state vector [w, x, y, z]."""
#     w = fidelity
#     x = (1 - fidelity) / 3.0
#     y = (1 - fidelity) / 3.0
#     z = (1 - fidelity) / 3.0
#     return np.array([w, x, y, z])


# def decay_coefficients(e_vec: np.ndarray, t: float, t_coh: float) -> np.ndarray:
#     """
#     Applies depolarizing noise to Bell diagonal coefficients.
#     Decay formula: c(t) = 1/4 + (c(0) - 1/4) * exp(-t / t_coh)
#     """
#     # Handle infinite coherence time (no decoherence)
#     if t_coh == 0 or t_coh == float('inf'):
#         return e_vec

#     decay_factor = np.exp(-t / t_coh)
#     # The maximally mixed state has coefficients [0.25, 0.25, 0.25, 0.25]
#     e_decayed = 0.25 + (e_vec - 0.25) * decay_factor
#     return e_decayed


# def geometric_sum_decay(e_init: np.ndarray, t_base: float, t_round: float, t_coh: float, p_geom: float) -> np.ndarray:
#     """
#     Calculates the expected state coefficients for a waiting time k that follows
#     a Geometric distribution: P(k) = p * (1-p)^(k-1) for k >= 1.

#     Expected State = Sum_{k=1 to inf} P(k) * State(t_base + k * t_round)
#     """
#     if t_coh == 0 or t_coh == float('inf'):
#         return e_init

#     # The sum forms a geometric series.
#     # Common ratio r = (1 - p) * exp(-t_round / t_coh)
#     r_factor = (1 - p_geom) * np.exp(-t_round / t_coh)

#     if r_factor >= 1.0:
#         raise ValueError("Geometric series does not converge. Check p_link and t_coh parameters.")

#     # Geometric sum S = 1 / (1 - r)
#     geom_series_sum = 1.0 / (1.0 - r_factor)

#     # The first term (k=1) has decay factor: exp(-(t_base + t_round)/t_coh)
#     decay_first_term = np.exp(-(t_base + t_round) / t_coh)

#     # Combined prefactor for the decay component
#     prefactor = p_geom * decay_first_term * geom_series_sum

#     # E[c_j] = 1/4 + (c_j(0) - 1/4) * prefactor
#     e_avg = 0.25 + (e_init - 0.25) * prefactor
#     return e_avg


# ######################### CORE ANALYTICAL FUNCTIONS #########################

# def calculate_p_succ(e1: np.ndarray, e2: np.ndarray) -> float:
#     """Calculates purification success probability P_succ."""
#     w1, x1, y1, z1 = e1
#     w2, x2, y2, z2 = e2
#     # P_succ = (w1 + z1)(w2 + z2) + (x1 + y1)(x2 + y2)
#     return (w1 + z1) * (w2 + z2) + (x1 + y1) * (x2 + y2)


# def calculate_output_state(e1: np.ndarray, e2: np.ndarray, p_succ: float) -> np.ndarray:
#     """Calculates the normalized output Bell diagonal state."""
#     if p_succ <= 0:
#         return np.array([0.25, 0.25, 0.25, 0.25]) # Return mixed state if fail

#     w1, x1, y1, z1 = e1
#     w2, x2, y2, z2 = e2

#     w_out = (w1 * w2 + z1 * z2) / p_succ
#     x_out = (x1 * x2 + y1 * y2) / p_succ
#     y_out = (x1 * y2 + y1 * x2) / p_succ
#     z_out = (w1 * z2 + z1 * w2) / p_succ

#     return np.array([w_out, x_out, y_out, z_out])


# def get_timing_constants(t_wait: float):
#     """
#     Calculates the exact timing constants (T0, T_subsequent) derived in the note.
#     """
#     # Round duration for 1 attempt (t_link,1)
#     t_round_1 = t_wait + 2 * (L_HALF_M / C_FIBER_M_S)
#     # Round duration for 2 attempts (t_link,2) = t_link,1 + t_sep
#     t_round_2 = t_round_1 + T_SEP_S

#     # Expected time from S1 to S2
#     T1 = t_round_1 / P_LINK

#     # Expected time from S0 to S2 (T0)
#     # T0 = (t_link,2 + 2(1-p)t_link,1) / (p(2-p))
#     numerator = t_round_2 + 2 * (1 - P_LINK) * t_round_1
#     denominator = P_LINK * (2 - P_LINK)
#     T0 = numerator / denominator

#     # Expected time for subsequent attempts
#     # T_sub = t_link,1 + p*T1 + (1-p)*T0
#     T_subsequent = t_round_1 + P_LINK * T1 + (1 - P_LINK) * T0

#     return t_round_1, T0, T_subsequent


# ######################### MAIN DATA GENERATOR #########################

# def get_analytical_values_with_decoherence(
#     n_conn: int,
#     t_wait_s: float,
#     fin_range: np.ndarray,
#     t_coh: float
# ):
#     """
#     Calculates analytical metrics (Time, Prob, Fidelity) considering memory decoherence.

#     Args:
#         n_conn: Number of connections requested.
#         t_wait_s: Hardware wait time (s).
#         fin_range: Array of initial input fidelities to simulate.
#         t_coh: Memory coherence time (s). Use 0 or inf for ideal memories.

#     Returns:
#         tuple: (analytical_times, analytical_probabilities, analytical_fidelities)
#     """
#     # 1. Get Timing Constants
#     t_round_1, T0, T_subsequent = get_timing_constants(t_wait_s)

#     # 2. Define Probabilities for the Average State
#     # P_sim: Probability of simultaneous generation from S0
#     P_sim = P_LINK / (2.0 - P_LINK)
#     P_seq = 1.0 - P_sim

#     # P_S1: Probability of entering 'Head Start' (link success during purification delay)
#     # We approximate the delay as one round-trip time (t_fresh)
#     P_S1_during_delay = 2 * P_LINK * (1.0 - P_LINK)

#     # 3. Define Ages
#     # Fresh pair age (min time for BSA result)
#     t_fresh = 2 * L_HALF_M / C_FIBER_M_S
#     # Delay for the head start case (assumed to be roughly t_fresh)
#     t_delay = t_fresh

#     analytical_times = []
#     analytical_probabilities = []
#     analytical_fidelities = []

#     for f_in in fin_range:
#         # -- Step A: Calculate Average Input States --
#         rho_init = werner_to_bell_diagonal(f_in)

#         # State of the Fresh Pair (Deterministic)
#         rho_fresh = decay_coefficients(rho_init, t_fresh, t_coh)

#         # State of the Stale Pair (Probabilistic Average)

#         # Part 1: Startup / Reset Scenarios (From S0)
#         # 1a. Simultaneous: Age = t_fresh
#         rho_startup_sim = rho_fresh
#         # 1b. Sequential: Age = t_fresh + k*t_round
#         rho_startup_seq = geometric_sum_decay(rho_init, t_fresh, t_round_1, t_coh, P_LINK)

#         rho_startup = P_sim * rho_startup_sim + P_seq * rho_startup_seq

#         # Part 2: Head Start Scenario (From S1)
#         # Age = t_fresh + t_delay + k*t_round
#         rho_headstart = geometric_sum_decay(rho_init, t_fresh + t_delay, t_round_1, t_coh, P_LINK)

#         # Combine weighted averages
#         rho_stale_avg = (1.0 - P_S1_during_delay) * rho_startup + P_S1_during_delay * rho_headstart

#         # -- Step B: Purification --
#         p_succ = calculate_p_succ(rho_stale_avg, rho_fresh)
#         e_out = calculate_output_state(rho_stale_avg, rho_fresh, p_succ)
#         f_out = e_out[0] # Fidelity is the first coefficient (Phi+)

#         # -- Step C: Connection Time --
#         if p_succ > 0:
#             # t_conn = T0 + ((N - p_succ)/p_succ) * T_subsequent
#             time_s = T0 + ((n_conn - p_succ) / p_succ) * T_subsequent
#         else:
#             time_s = np.inf

#         analytical_probabilities.append(p_succ)
#         analytical_fidelities.append(f_out)
#         analytical_times.append(time_s)

#     return analytical_times, analytical_probabilities, analytical_fidelities
