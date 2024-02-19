import pandas as pd
from matplotlib import pyplot as plt
from analysis_utils import (
    calc_durations,
    plot_timeline,
)

logs = []
logs.append(pd.read_json("simulations/results/Testing_MSM_one_memory-0.jsonl", orient="records", lines=True))
logs.append(pd.read_json("simulations/results/Testing_MSM_two_memory-0.jsonl", orient="records", lines=True))
logs.append(pd.read_json("simulations/results/Testing_MSM_four_memory-0.jsonl", orient="records", lines=True))
logs.append(pd.read_json("simulations/results/Testing_MSM_eight_memory-0.jsonl", orient="records", lines=True))
logs.append(pd.read_json("simulations/results/Testing_MSM_sixteen_memory-0.jsonl", orient="records", lines=True))
logs.append(pd.read_json("simulations/results/Testing_MSM_thirtytwo_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MSM_sixtyfour_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MSM_onetwentyeight_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_one_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_two_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_four_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_eight_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_sixteen_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_thirtytwo_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_sixtyfour_memory-0.jsonl", orient="records", lines=True))
# logs.append(pd.read_json("simulations/results/Testing_MIM_onetwentyeight_memory-0.jsonl", orient="records", lines=True))


index = 1
link = "MSM"
for log in logs:
    print("getting durations")
    durations = calc_durations(log)
    fig, ax = plt.subplots(figsize=(35, 22))
    plt.xlim([10.0, 10.005])
    print("plotting")
    plot_timeline(ax, durations, "qubit_busy")
    plot_timeline(ax, durations, "qubit_allocation")
    plot_timeline(ax, durations, "bp_lifetime")
    for e in durations["bp_annotations"]:
        text, x, y = e
        ax.annotate(text, xy=(x, y))
    ax.legend(loc=(0.1, 0.1))
    plt.savefig(f"{link}_usage_analysis_{index}_memory.png")
    index *= 2
