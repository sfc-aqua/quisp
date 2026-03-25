import os
import numpy as np
import matplotlib.pyplot as plt

######################### CONSTANTS #########################
# Speed of light in optical fiber (m/s)
C_FIBER_M_S = 208189206.944
# Half the distance between Alice and Bob (m)
L_HALF_M = 20e3
# Link-level Bell pair generation probability (constant based on loss)
P_LINK = 0.07924465965
# Separation time between photons in a train (1 ns)
T_SEP_S = 1e-9


######################### ANALYTICAL MODEL FUNCTIONS #########################

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
    if t_coh == 0 or t_coh == float('inf'):
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
    if t_coh == 0 or t_coh == float('inf'):
        return 1.0

    # Solve 1/e = 0.25 + 0.75 * R
    # R = (1/e - 0.25) / 0.75
    R = (4.0 / np.e - 1.0) / 3.0
    return R

def decay_coefficients(e_vec: np.ndarray, t: float, t_coh: float) -> np.ndarray:
    if t_coh == 0 or t_coh == float('inf'): return e_vec

    # Get the rate that satisfies the condition for the full system
    R = get_bell_decay_base(t_coh)

    # Apply exactly that rate (do NOT double t, because R is already tuned for the pair)
    decay_factor = np.power(R, t / t_coh)

    e_decayed = 0.25 + (e_vec - 0.25) * decay_factor
    return e_decayed

def geometric_sum_decay(e_init: np.ndarray, t_base: float, t_round: float, t_coh: float, p_geom: float) -> np.ndarray:
    if t_coh == 0 or t_coh == float('inf'): return e_init

    R = get_bell_decay_base(t_coh)

    # Decay per round (no doubling, R is system-level)
    decay_per_round = np.power(R, t_round / t_coh)

    r_factor = (1.0 - p_geom) * decay_per_round
    if r_factor >= 1.0: raise ValueError("Series divergence")

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
        return np.array([0.25, 0.25, 0.25, 0.25]) # Return mixed state if fail

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
    t_round_1 = t_wait + 2 * (L_HALF_M / C_FIBER_M_S)
    # Round duration for 2 attempts (t_link,2) = t_link,1 + t_sep
    t_round_2 = t_round_1 + T_SEP_S

    # Expected time from S1 to S2
    T1 = t_round_1 / P_LINK

    # Expected time from S0 to S2 (T0)
    numerator = t_round_2 + 2 * (1 - P_LINK) * t_round_1
    denominator = P_LINK * (2 - P_LINK)
    T0 = numerator / denominator

    # Expected time for subsequent attempts
    T_subsequent = t_round_1 + P_LINK * T1 + (1 - P_LINK) * T0

    return t_round_1, T0, T_subsequent


def get_analytical_values_with_decoherence(
    n_conn: int,
    t_wait_s: float,
    fin_range: np.ndarray,
    t_coh: float
):
    """
    Calculates analytical metrics (Time, Prob, Fidelity) considering memory decoherence.
    """
    # 1. Get Timing Constants
    t_round_1, T0, T_subsequent = get_timing_constants(t_wait_s)

    # 2. Define Probabilities for the Average State
    # P_sim: Probability of simultaneous generation from S0
    P_sim = P_LINK / (2.0 - P_LINK)
    P_seq = 1.0 - P_sim

    # P_S1: Probability of entering 'Head Start' (link success during purification delay)
    # We approximate the delay as one round-trip time (t_fresh)
    P_S1_during_delay = 2 * P_LINK * (1.0 - P_LINK)

    # 3. Define Ages
    # Fresh pair age (min time for BSA result)
    t_fresh = 2 * L_HALF_M / C_FIBER_M_S
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
        rho_startup_seq = geometric_sum_decay(rho_init, 2 * t_fresh, 2 * t_round_1, t_coh, P_LINK)

        rho_startup = P_sim * rho_startup_sim + P_seq * rho_startup_seq

        # Part 2: Head Start Scenario (From S1)
        # Age = t_fresh + t_delay + k*t_round
        rho_headstart = geometric_sum_decay(rho_init, 2 * (t_fresh + t_delay), 2 * t_round_1, t_coh, P_LINK)

        # Combine weighted averages
        rho_stale_avg = (1.0 - P_S1_during_delay) * rho_startup + P_S1_during_delay * rho_headstart

        # -- Step B: Purification --
        p_succ = calculate_p_succ(rho_stale_avg, rho_fresh)

        # need to change it here (do the calculation again but with additional waiting time from purification to the actual estimation)
        rho_stale_avg_after_heralded = rho_stale_avg
        rho_fresh_after_heralded = rho_fresh

        t_herald = 2 * L_HALF_M / C_FIBER_M_S
        rho_stale_avg_after_heralded = decay_coefficients(rho_stale_avg, t_herald, t_coh)
        rho_fresh_after_heralded = decay_coefficients(rho_fresh, t_herald, t_coh)
        e_out = calculate_output_state(rho_stale_avg_after_heralded, rho_fresh_after_heralded, p_succ)
        f_out = e_out[0] # Fidelity is the first coefficient (Phi+)

        # -- Step C: Connection Time --
        if p_succ > 0:
            time_s = T0 + ((n_conn - p_succ) / p_succ) * T_subsequent
        else:
            time_s = np.inf

        analytical_probabilities.append(p_succ)
        analytical_fidelities.append(f_out)
        analytical_times.append(time_s)

    return analytical_times, analytical_probabilities, analytical_fidelities


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
    lines = extract_lines_by_keyword(fn, "sim time:")
    completion_times = []
    for line in lines:
        try:
            t = float(line.split("sim time: ")[1].split(";")[0].strip())
            completion_times.append(t - 10)
        except IndexError:
            continue
    completion_times = [v for k, v in enumerate(completion_times) if k % 2 == 0]
    if not completion_times: return 0, 0
    return np.mean(completion_times), np.std(completion_times)


def extract_fidelity(fn: str):
    lines = extract_lines_by_keyword(fn, "Fidelity=")
    fidelities = []
    for line in lines:
        try:
            fid = float(line.split("Fidelity=")[1].split(";")[0])
            fidelities.append(fid)
        except IndexError:
            continue
    fidelities = [v for k, v in enumerate(fidelities) if k % 2 == 0]
    if not fidelities: return 0, 0
    return np.mean(fidelities), np.std(fidelities)


def extract_purification_success(fn: str, target_count: int):
    lines = extract_lines_below_keyword(fn, "BSA Statistics (raw):")
    total_events = []
    for line in lines:
        try:
            bsm_events = (sum(map(int, line.strip().split(" "))) - 4) / 4
            if bsm_events > 0:
                total_events.append(target_count * 1.0 / bsm_events)
        except ValueError:
            continue
    if not total_events: return 0, 0
    return np.mean(total_events), np.std(total_events)


######################### MAIN SCRIPT #########################

# Define paths
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

# --- SELECT SCENARIO ---
# selected_scenario = without_decoherence_long
# selected_scenario = without_decoherence_short
selected_scenario = with_18ms_decoherence_long
# selected_scenario = with_55ms_decoherence_long
# selected_scenario = with_18ms_decoherence_short

# number_of_requested_bellpairs = 500 # short
number_of_requested_bellpairs = 100_000 # long

# --- DETECT COHERENCE TIME ---
scenario_name = selected_scenario[0]
if "no-error" in scenario_name:
    T_COH = np.inf
    scenario_title = "Ideal Memories"
elif "18ms" in scenario_name:
    T_COH = 0.018 # 18ms
    scenario_title = "18ms Coherence"
elif "55ms" in scenario_name:
    T_COH = 0.055 # 55ms
    scenario_title = "55ms Coherence"
else:
    T_COH = np.inf
    scenario_title = "Unknown Coherence"

print(f"Processing Scenario: {scenario_title}")

# number_of_requested_bellpairs = 500 # short
# number_of_requested_bellpairs = 100_000 # long

# --- Extract Simulation Data ---
abs_files = [os.path.join(base_path, rel.lstrip('/')) for rel in selected_scenario]
initial_fidelities = [i / 100 for i in range(60, 101, 2)]

# Note: Using long files for fidelity/prob, but short files for time (as per your comment in original code)
# If you want to use long files for everything, ensure completion_times points to long_completion_times
long_completion_times = [
    extract_completion_time(os.path.join(base_path, fn.lstrip('/'))) for fn in selected_scenario
]
# Use long completion times as default based on your snippet
completion_times_raw = long_completion_times

fidelities_raw = [
    extract_fidelity(os.path.join(base_path, fn.lstrip('/'))) for fn in selected_scenario
]
success_rates_raw = [
    extract_purification_success(os.path.join(base_path, fn.lstrip('/')), number_of_requested_bellpairs)
    for fn in selected_scenario
]

# Unzip data
completion_times, completion_times_err = map(list, zip(*completion_times_raw))
fidelities, fidelities_err = map(list, zip(*fidelities_raw))
success_rates, success_rates_err = map(list, zip(*success_rates_raw))

print('=========================')
for sr in success_rates_err:
    print(sr)
print('=========================')


# --- Calculate Analytical Data ---
N_REQUESTED_PAIRS = number_of_requested_bellpairs
WAIT_TIME_S = 1e-8
initial_fidelities_arr = np.linspace(0.6, 1.0, 21)

ana_completion_times, ana_success_rates, ana_fidelities = get_analytical_values_with_decoherence(
    N_REQUESTED_PAIRS,
    WAIT_TIME_S,
    initial_fidelities_arr,
    T_COH
)

for i in range(len(ana_completion_times)):
    print(f'{ana_completion_times[i]}, {ana_fidelities[i]}, {ana_success_rates[i]}')

# --- Console Output ---
print(f'Initial Fid | Time (Sim) +/- Err | Fid (Sim) +/- Err | Succ (Sim) +/- Err')
for i in range(len(completion_times)):
    print(f'{initial_fidelities[i]:.2f} | {completion_times[i]:.4f} +/- {completion_times_err[i]:.4f} | {fidelities[i]:.4f} +/- {fidelities_err[i]:.4f} | {success_rates[i]:.4f} +/- {success_rates_err[i]:.4f}')


# --- Plotting ---
fig, ax1 = plt.subplots(figsize=(12, 7))

# Plot 1: Completion Times (Left Y-axis)
color1 = 'tab:red'
ax1.set_xlabel('Initial Fidelity', fontsize=14)
ax1.set_ylabel('Completion Time (s)', color=color1, fontsize=14)
p1_ana, = ax1.plot(initial_fidelities_arr, ana_completion_times, color=color1, linestyle='-', label='Analytical Time')
p1_sim = ax1.errorbar(initial_fidelities, completion_times, yerr=completion_times_err, color=color1, fmt='o', capsize=6, label='QuISP Time')
ax1.tick_params(axis='y', labelcolor=color1)
ax1.grid(True, linestyle='--', alpha=0.6)

# Plot 2: Fidelities (Right Y-axis 1)
ax2 = ax1.twinx()
color2 = 'tab:blue'
ax2.set_ylabel('Final Fidelity', color=color2, fontsize=14)
p2_ana, = ax2.plot(initial_fidelities_arr, ana_fidelities, color=color2, linestyle='--', label='Analytical Fidelity')
p2_sim = ax2.errorbar(initial_fidelities, fidelities, yerr=fidelities_err, color=color2, fmt='s', capsize=6, label='QuISP Fidelity')
ax2.tick_params(axis='y', labelcolor=color2)

# Plot 3: Reference Fidelity Line (y=x)
p_ref, = ax2.plot(initial_fidelities_arr, initial_fidelities_arr, color='black', linestyle=':', alpha=0.6, label='Ref Fidelity (y=x)')

# Plot 4: Success Rates (Right Y-axis 2)
ax3 = ax1.twinx()
color3 = 'tab:green'
# Offset the third y-axis to not overlap
ax3.spines['right'].set_position(('outward', 60))
ax3.set_ylabel('Success Rate', color=color3, fontsize=14)
p3_ana, = ax3.plot(initial_fidelities_arr, ana_success_rates, color=color3, linestyle='-.', label='Analytical Success Rate')
p3_sim = ax3.errorbar(initial_fidelities, success_rates, yerr=success_rates_err, color=color3, fmt='^', capsize=6, label='QuISP Success Rate')
ax3.tick_params(axis='y', labelcolor=color3)

# Plot Limits & Title
# Set reasonable limits for visualization (adjust as needed based on data)
y_lim_range = (0.5, 1.05)
ax2.set_ylim(y_lim_range)
ax3.set_ylim(y_lim_range)

plt.title(f'Performance Metrics vs. Initial Fidelity ({scenario_title})', fontsize=16)

# Combined Legend
handles = [p1_ana, p1_sim, p2_ana, p2_sim, p_ref, p3_ana, p3_sim]
fig.legend(handles=handles, loc='upper center', bbox_to_anchor=(0.5, 0.95), ncol=4, frameon=False)

fig.tight_layout()

# Save
filename = f'purification_{scenario_title.replace(" ", "_").lower()}_performance.png'
plt.savefig(filename, dpi=300, bbox_inches='tight')
print(f"Plot saved to {filename}")

plt.show()
