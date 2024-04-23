import matplotlib.pyplot as plt
import numpy as np

# Read data from the file
data_1mem = open("bellpairtimings_1mem")
data_2mem = open("bellpairtimings_2mem")
data_4mem = open("bellpairtimings_4mem")
data_8mem = open("bellpairtimings_8mem")
data_16mem = open("bellpairtimings_16mem")
data_32mem = open("bellpairtimings_32mem")
lines_1mem = data_1mem.readlines()
lines_2mem = data_2mem.readlines()
lines_4mem = data_4mem.readlines()
lines_8mem = data_8mem.readlines()
lines_16mem = data_16mem.readlines()
lines_32mem = data_32mem.readlines()
data_1mem.close()
data_2mem.close()
data_4mem.close()
data_8mem.close()
data_16mem.close()
data_32mem.close()

# Create a dictionary to store the results
simulations = ["mxm_simple", "mxm_simple_adaptive", "mxm_long", "mxm_long_adaptive", "mim_simple", "mim_long", "msm_simple", "msm_simple_adaptive", "msm_long", "msm_long_adaptive"]

results = {"mxm_simple": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "mxm_simple_adaptive": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "mxm_long": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "mxm_long_adaptive": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "mim_simple": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "mim_long": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "msm_simple": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "msm_simple_adaptive": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "msm_long": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "msm_long_adaptive": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "MIM_long": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "MSM_long": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "MIM_simple": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "MSM_simple": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "MSMa_long": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}, "MSMa_simple": {1: {}, 2: {}, 4: {}, 8: {}, 16: {}, 32: {}}}

# Read data from the file
data = open("bellpairtimings_shortlink")
lines = data.readlines()
data.close()

for line in lines:
    line = line.split(",")
    line.pop(-1)
    for link in ["MIM","MSM"]:
        i = 1
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo"]:
            if line[0] == f"{link}_{memory}":
                arr = np.array([100/(float(x)-10) for x in line[1:]])
                results[f"{link}_simple"][i] = [arr.mean(),arr.std()]
            i *= 2

# Read data from the file
data = open("bellpairtimings_longlink")
lines = data.readlines()
data.close()

for line in lines:
    line = line.split(",")
    line.pop(-1)
    for link in ["MIM","MSM"]:
        i = 1
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo"]:
            if line[0] == f"{link}_{memory}":
                arr = np.array([100/(float(x)-10) for x in line[1:]])
                results[f"{link}_long"][i] = [arr.mean(),arr.std()]
            i *= 2

# Read data from the file
data_short = open("hundredbellpairadaptiveshortmsm")
lines_short = data_short.readlines()
data_short.close()

for line in lines_short:
    line = line.split(",")
    line.pop(-1)
    for link in ["MSM", "MSMa"]:
        i = 1
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo"]:
            if line[0] == f"{link}_{memory}":
                arr = np.array([100/(float(x)-10) for x in line[1:]])
                results[f"{link}_simple"][i] = [arr.mean(),arr.std()]
            i *= 2
# Read data from the file
data_long = open("hundredbellpairadaptivelongmsm")
lines_long = data_long.readlines()
data_long.close()

for line in lines_long:
    line = line.split(",")
    line.pop(-1)
    for link in ["MSM", "MSMa"]:
        i = 1
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo"]:
            if line[0] == f"{link}_{memory}":
                arr = np.array([100/(float(x)-10) for x in line[1:]])
                results[f"{link}_long"][i] = [arr.mean(),arr.std()]
            i *= 2


for simulation in simulations:
    for line in lines_1mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][1] = [100/(float(x)-10) for x in line[1:]]
            results[simulation][1] = [results[simulation][1][i] for i in range(len(results[simulation][1])) if i % 2 != 0]
            results[simulation][1] = [np.array(results[simulation][1]).mean(), np.array(results[simulation][1]).std()]
    for line in lines_2mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][2] = [100/(float(x)-10) for x in line[1:]]
            results[simulation][2] = [results[simulation][2][i] for i in range(len(results[simulation][2])) if i % 2 != 0]
            results[simulation][2] = [np.array(results[simulation][2]).mean(), np.array(results[simulation][2]).std()]
    for line in lines_4mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][4] = [100/(float(x)-10) for x in line[1:]]
            results[simulation][4] = [results[simulation][4][i] for i in range(len(results[simulation][4])) if i % 2 != 0]
            results[simulation][4] = [np.array(results[simulation][4]).mean(), np.array(results[simulation][4]).std()]
    for line in lines_8mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][8] = [100/(float(x)-10) for x in line[1:]]
            results[simulation][8] = [results[simulation][8][i] for i in range(len(results[simulation][8])) if i % 2 != 0]
            results[simulation][8] = [np.array(results[simulation][8]).mean(), np.array(results[simulation][8]).std()]
    for line in lines_16mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][16] = [100/(float(x)-10) for x in line[1:]]
            results[simulation][16] = [results[simulation][16][i] for i in range(len(results[simulation][16])) if i % 2 != 0]
            results[simulation][16] = [np.array(results[simulation][16]).mean(), np.array(results[simulation][16]).std()]
    for line in lines_32mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][32] = [100/(float(x)-10) for x in line[1:]]
            results[simulation][32] = [results[simulation][32][i] for i in range(len(results[simulation][32])) if i % 2 != 0]
            results[simulation][32] = [np.array(results[simulation][32]).mean(), np.array(results[simulation][32]).std()]

x = [1, 2, 4, 8, 16, 32]
simulation_simple = ["mxm_simple", "MIM_simple", "MSM_simple"]
simulation_long = ["mxm_long", "MIM_long", "MSM_long"]
dist = 0
plt.clf()
dist = 0
for simulation in simulation_long:
    xaxis = np.arange(len(x))
    y = [results[simulation][1][0], results[simulation][2][0], results[simulation][4][0], results[simulation][8][0], results[simulation][16][0], results[simulation][32][0]]
    err = [results[simulation][1][1], results[simulation][2][1], results[simulation][4][1], results[simulation][8][1], results[simulation][16][1], results[simulation][32][1]]
    simulation = simulation.replace("_long_", " ")
    simulation = simulation.replace("_long", " ")
    if simulation == "mxm ":
        simulation = "MSM and MIM"
    if simulation == "mim ":
        simulation = "MIM-only"
    if simulation == "msm ":
        simulation = "MSM-only"
    if simulation == "mxm adaptive":
        simulation = "MSM-adaptive and MIM"
    if simulation == "msm adaptive":
        simulation = "MSM-adaptive-only"
    if simulation == "MSMa ":
        simulation = "MSM-adaptive"
    plt.bar(xaxis-0.3+dist, y, label=f'{simulation}', log=True, width=0.3)
    plt.errorbar(xaxis-0.3+dist, y, yerr=err, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
    dist += 0.3
plt.legend()
plt.xticks(xaxis, x)
plt.xlabel('Memory size (qubits)', fontsize=15)
plt.ylabel('Bell pair generation rate (BP/s)', fontsize=15)
plt.savefig("20kmdist_comparetolink.png", dpi=1000)
plt.savefig("20kmdist_comparetolink.pdf", dpi=1000)

plt.clf()
dist = 0
for simulation in simulation_simple:
    xaxis = np.arange(len(x))
    y = [results[simulation][1][0], results[simulation][2][0], results[simulation][4][0], results[simulation][8][0], results[simulation][16][0], results[simulation][32][0]]
    err = [results[simulation][1][1], results[simulation][2][1], results[simulation][4][1], results[simulation][8][1], results[simulation][16][1], results[simulation][32][1]]
    simulation = simulation.replace("_simple_", " ")
    simulation = simulation.replace("_simple", " ")
    if simulation == "mxm ":
        simulation = "MSM and MIM"
    if simulation == "mim ":
        simulation = "MIM-only"
    if simulation == "msm ":
        simulation = "MSM-only"
    if simulation == "mxm adaptive":
        simulation = "MSM-adaptive and MIM"
    if simulation == "msm adaptive":
        simulation = "MSM-adaptive-only"
    if simulation == "MSMa ":
        simulation = "MSM-adaptive"
    plt.bar(xaxis-0.3+dist, y, label=f'{simulation}', log=True, width=0.3)
    plt.errorbar(xaxis-0.3+dist, y, yerr=err, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
    dist += 0.3
plt.legend()
plt.xticks(xaxis, x)
plt.xlabel('Memory size (qubits)', fontsize=15)
plt.ylabel('Bell pair generation rate (BP/s)', fontsize=15)
plt.savefig("1kmdist_comparetolink.png", dpi=1000)
plt.savefig("1kmdist_comparetolink.pdf", dpi=1000)