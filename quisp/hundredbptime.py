import matplotlib.pyplot as plt
import numpy as np

# Read data from the file
data_4mem = open("bellpairtimings_4mem")
data_8mem = open("bellpairtimings_8mem")
data_16mem = open("bellpairtimings_16mem")
data_32mem = open("bellpairtimings_32mem")
lines_4mem = data_4mem.readlines()
lines_8mem = data_8mem.readlines()
lines_16mem = data_16mem.readlines()
lines_32mem = data_32mem.readlines()
data_4mem.close()
data_8mem.close()
data_16mem.close()
data_32mem.close()

# Create a dictionary to store the results
simulations = ["mxm_simple", "mxm_simple_adaptive", "mxm_long", "mxm_long_adaptive", "mim_simple", "mim_long", "msm_simple", "msm_simple_adaptive", "msm_long", "msm_long_adaptive"]

results = {"mxm_simple": {4: {}, 8: {}, 16: {}, 32: {}}, "mxm_simple_adaptive": {4: {},8: {}, 16: {}, 32: {}}, "mxm_long": {4: {},8: {}, 16: {}, 32: {}}, "mxm_long_adaptive": {4: {},8: {}, 16: {}, 32: {}}, "mim_simple": {4: {},8: {}, 16: {}, 32: {}}, "mim_long": {4: {},8: {}, 16: {}, 32: {}}, "msm_simple": {4: {},8: {}, 16: {}, 32: {}}, "msm_simple_adaptive": {4: {},8: {}, 16: {}, 32: {}}, "msm_long": {4: {},8: {}, 16: {}, 32: {}}, "msm_long_adaptive": {4: {},8: {}, 16: {}, 32: {}}}

for simulation in simulations:
    for line in lines_4mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][4] = [(float(x)-10) for x in line[1:]]
            results[simulation][4] = [results[simulation][4][i] for i in range(len(results[simulation][4])) if i % 2 != 0]
            results[simulation][4] = [np.array(results[simulation][4]).mean(), np.array(results[simulation][4]).std()]
    for line in lines_8mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][8] = [(float(x)-10) for x in line[1:]]
            results[simulation][8] = [results[simulation][8][i] for i in range(len(results[simulation][8])) if i % 2 != 0]
            results[simulation][8] = [np.array(results[simulation][8]).mean(), np.array(results[simulation][8]).std()]
    for line in lines_16mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][16] = [(float(x)-10) for x in line[1:]]
            results[simulation][16] = [results[simulation][16][i] for i in range(len(results[simulation][16])) if i % 2 != 0]
            results[simulation][16] = [np.array(results[simulation][16]).mean(), np.array(results[simulation][16]).std()]
    for line in lines_32mem:
        line = line.split(",")
        line.pop(-1)
        if line[0] == f"{simulation}":
            results[simulation][32] = [(float(x)-10) for x in line[1:]]
            results[simulation][32] = [results[simulation][32][i] for i in range(len(results[simulation][32])) if i % 2 != 0]
            results[simulation][32] = [np.array(results[simulation][32]).mean(), np.array(results[simulation][32]).std()]

x = [4, 8, 16, 32]
simulation_simple = ["mxm_simple", "mxm_simple_adaptive", "mim_simple", "msm_simple", "msm_simple_adaptive"]
simulation_long = ["mxm_long", "mxm_long_adaptive", "mim_long", "msm_long", "msm_long_adaptive"]
dist = 0
plt.clf()
dist = 0
for simulation in simulation_long:
    xaxis = np.arange(len(x))
    y = [results[simulation][4][0], results[simulation][8][0], results[simulation][16][0], results[simulation][32][0]]
    err = [results[simulation][4][1], results[simulation][8][1], results[simulation][16][1], results[simulation][32][1]]
    simulation = simulation.replace("_long_", " ")
    simulation = simulation.replace("_long", " ")
    plt.bar(xaxis-0.2+dist, y, label=f'{simulation}', log=True, width=0.1)
    plt.errorbar(xaxis-0.2+dist, y, yerr=err, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
    dist += 0.1
plt.legend()
plt.xticks(xaxis, x)
plt.xlabel('Memory size (qubits)', fontsize=15)
plt.ylabel('Time to create 100 Bell pairs (s)', fontsize=15)
plt.savefig("20kmdist.png", dpi=1000)
plt.savefig("20kmdist.pdf", dpi=1000)

plt.clf()
dist = 0
for simulation in simulation_simple:
    xaxis = np.arange(len(x))
    y = [results[simulation][4][0], results[simulation][8][0], results[simulation][16][0], results[simulation][32][0]]
    err = [results[simulation][4][1], results[simulation][8][1], results[simulation][16][1], results[simulation][32][1]]
    simulation = simulation.replace("_simple_", " ")
    simulation = simulation.replace("_simple", " ")
    plt.bar(xaxis-0.2+dist, y, label=f'{simulation}', log=True, width=0.1)
    plt.errorbar(xaxis-0.2+dist, y, yerr=err, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
    dist += 0.1
plt.legend()
plt.xticks(xaxis, x)
plt.xlabel('Memory size (qubits)', fontsize=15)
plt.ylabel('Time to create 100 Bell pairs (s)', fontsize=15)
plt.savefig("1kmdist.png", dpi=1000)
plt.savefig("1kmdist.pdf", dpi=1000)