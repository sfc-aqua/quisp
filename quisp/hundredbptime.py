import matplotlib.pyplot as plt
import numpy as np

# Read data from the file
data_8mem = open("bellpairtimings_8mem")
data_16mem = open("bellpairtimings_16mem")
data_32mem = open("bellpairtimings_32mem")
lines_8mem = data_8mem.readlines()
lines_16mem = data_16mem.readlines()
lines_32mem = data_32mem.readlines()
data_8mem.close()
data_16mem.close()
data_32mem.close()

# Create a dictionary to store the results
simulations = ["mxm_simple", "mxm_simple_adaptive", "mxm_long", "mxm_long_adaptive", "mim_simple", "mim_long", "msm_simple", "msm_simple_adaptive", "msm_long", "msm_long_adaptive"]

results = {"mxm_simple": {8: {}, 16: {}, 32: {}}, "mxm_simple_adaptive": {8: {}, 16: {}, 32: {}}, "mxm_long": {8: {}, 16: {}, 32: {}}, "mxm_long_adaptive": {8: {}, 16: {}, 32: {}}, "mim_simple": {8: {}, 16: {}, 32: {}}, "mim_long": {8: {}, 16: {}, 32: {}}, "msm_simple": {8: {}, 16: {}, 32: {}}, "msm_simple_adaptive": {}, "msm_long": {8: {}, 16: {}, 32: {}}, "msm_long_adaptive": {8: {}, 16: {}, 32: {}}}

for simulation in simulations: 
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

x = [8, 16, 32]
for simulation in simulations:
    plt.clf()
    xaxis = np.arange(len(x))
    y = [results[simulation][8][0], results[simulation][16][0], results[simulation][32][0]]
    err = [results[simulation][8][1], results[simulation][16][1], results[simulation][32][1]]
    plt.bar(xaxis, y, label='', log=False, width=0.4)
    plt.errorbar(xaxis, y, yerr=err, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
    plt.xticks(xaxis, x)
    plt.xlabel('Memory size (qubits)', fontsize=15)
    plt.ylabel('Time to create 100 Bell pairs (s)', fontsize=15)
    plt.savefig(f"{simulation}.png", dpi=1000)
    plt.savefig(f"{simulation}.pdf", dpi=1000)

