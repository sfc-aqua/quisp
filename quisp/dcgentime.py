# A python file to read the data from the file and plot the data

import matplotlib.pyplot as plt
import numpy as np

# read data from the file
data = open("bellpairtimings")
lines = data.readlines()
data.close()

# create a dict to store the results
results = {}

for line in lines:
    line = line.split(",")
    line.pop(-1)
    results[line[0]] = line[1:]
    ## get the average and std of the results
    results[line[0]] = [1000/(float(i)-10) for i in results[line[0]]]
    results[line[0]] = [np.mean(results[line[0]]), np.std(results[line[0]])]

# key is in format of "${arch}_${length}_${adaptive}_${mem}"
# plot the data for 10m and 100m cases, for three legends MIM, MSM, and MSM adaptive (ignore the MIM adaptive), where the x label is the memory size and the y label is the rate calculated in results[key] = [rate.mean, rate.std]


# Plot the data
memory_sizes = [1,2,4,8,16,32,64,128,256,512]
mim_10m = {'mean': [], 'std': []}
msm_10m = {'mean': [], 'std': []}
msm_adaptive_10m = {'mean': [], 'std': []}
mim_100m = {'mean': [], 'std': []}
msm_100m = {'mean': [], 'std': []}
msm_adaptive_100m = {'mean': [], 'std': []}

for key, value in results.items():
    arch, length, adaptive, mem = key.split("_")
    if(mem=="one"):
        mem = 1
    elif(mem=="two"):
        mem = 2
    elif(mem=="four"):
        mem = 4
    elif(mem=="eight"):
        mem = 8
    elif(mem=="sixteen"):
        mem = 16
    elif(mem=="thirtytwo"):
        mem = 32
    elif(mem=="sixtyfour"):
        mem = 64
    elif(mem=="onehundredtwentyeight"):
        mem = 128
    elif(mem=="twohundredfiftysix"):
        mem = 256
    elif(mem=="fivehundredtwelve"):
        mem = 512

    if length =="ten":
        if adaptive == "na":
            if arch == "mim":
                mim_10m['mean'].append(value[0])
                mim_10m['std'].append(value[1])
            elif arch == "msm":
                msm_10m['mean'].append(value[0])
                msm_10m['std'].append(value[1])
        elif adaptive == "a" and arch == "msm":
            msm_adaptive_10m['mean'].append(value[0])
            msm_adaptive_10m['std'].append(value[1])
    elif length == "hun":
        if adaptive == "na":
            if arch == "mim":
                mim_100m['mean'].append(value[0])
                mim_100m['std'].append(value[1])
            elif arch == "msm":
                msm_100m['mean'].append(value[0])
                msm_100m['std'].append(value[1])
        elif adaptive == "a" and arch == "msm":
            msm_adaptive_100m['mean'].append(value[0])
            msm_adaptive_100m['std'].append(value[1])


# Function to plot bar graphs
def plot_bars(memory_sizes, data, title, length):
    x = np.arange(len(memory_sizes))  # the label locations
    width = 0.25  # the width of the bars

    fig, ax = plt.subplots()
    rects1 = ax.bar(x - width, data[0]['mean'], width, label='MIM', yerr=data[0]['std'], capsize=5)
    rects2 = ax.bar(x, data[1]['mean'], width, label='MSM', yerr=data[1]['std'], capsize=5)
    rects3 = ax.bar(x + width, data[2]['mean'], width, label='MSM Adaptive', yerr=data[2]['std'], capsize=5)

    # Add some text for labels, title, and custom x-axis tick labels, etc.
    ax.set_xlabel('Memory Size')
    ax.set_ylabel('Rate (mean ± std)')
    ax.set_title(title)
    ax.set_xticks(x)
    ax.set_xticklabels(memory_sizes)
    ax.legend()

    fig.tight_layout()
    plt.savefig(f"bellpairtimings_{length}m.png", dpi=1000)
    plt.savefig(f"bellpairtimings_{length}m.pdf", dpi=1000)



# Plotting 10m cases
plot_bars(memory_sizes, [mim_10m, msm_10m, msm_adaptive_10m], 'Rates for 10m Case', 10)

# Plotting 100m cases
plot_bars(memory_sizes, [mim_100m, msm_100m, msm_adaptive_100m], 'Rates for 100m Case', 100)
