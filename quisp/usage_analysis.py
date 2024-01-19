import pandas as pd
from matplotlib import pyplot as plt
from analysis_utils import (
    calc_durations,
    plot_timeline,
)

logs = []
logs.append(pd.read_json("networks/results/Testing_MSM_onetwoeight_memory-0.jsonl", orient="records", lines=True))


index = 128
for log in logs:
    durations = calc_durations(log)
    fig, ax = plt.subplots(figsize=(35, 22))
    plt.xlim([10.0, 10.001])
    plot_timeline(ax, durations, "qubit_busy")
    plot_timeline(ax, durations, "qubit_allocation")
    plot_timeline(ax, durations, "bp_lifetime")
    for e in durations["bp_annotations"]:
        text, x, y = e
        ax.annotate(text, xy=(x, y))
    ax.legend(loc=(0.1, 0.1))
    plt.savefig(f"usage_analysis_{index}_memory_sorted.png")
    index *= 2
