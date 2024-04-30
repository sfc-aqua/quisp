import matplotlib.pyplot as plt
import numpy as np

# Read data from the file
data = open("hundredbellpairadaptiveshortmsm")
lines = data.readlines()
data.close()

# Create a dictionary to store the results
results = {"MIM": {},"MSM": {}, "MSMa": {}}
for line in lines:
    line = line.split(",")
    line.pop(-1)
    for link in ["MSM","MSMa"]:
        i = 0
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo", "sixtyfour", "onetwentyeight"]:
            if line[0] == f"{link}_{memory}":
                results[link][i] = [100/(float(x)-10) for x in line[1:]]
            i += 1

data= open("hundredbellpairshort")
lines = data.readlines()
data.close()

for line in lines:
    line = line.split(",")
    line.pop(-1)
    i = 0
    for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo", "sixtyfour", "onetwentyeight"]:
        if line[0] == f"MIM_{memory}":
            results["MIM"][i] = [100/(float(x)-10) for x in line[1:]]
        i += 1
x = [pow(2,i-1) for i in range(1,9)]
ymim = []
ymsm = []
ymsma = []
emim = []
emsm = []
emsma = []
# Create the plot
for i in range(8):
    ymim.append(np.array(results["MIM"][i]).mean())
    emim.append(np.array(results["MIM"][i]).std())
    ymsm.append(np.array(results["MSM"][i]).mean())
    emsm.append(np.array(results["MSM"][i]).std())
    ymsma.append(np.array(results["MSMa"][i]).mean())
    emsma.append(np.array(results["MSMa"][i]).std())

xaxis = np.arange(len(x))
plt.bar(xaxis-0.3, ymsm, label='MSM', log=True, width=0.3)
plt.bar(xaxis, ymsma, label='adaptive MSM', log=True, width=0.3)
plt.bar(xaxis+0.3, ymim, label='MIM', log=True, width=0.3)
plt.errorbar(xaxis-0.3, ymsm, yerr=emsm, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
plt.errorbar(xaxis, ymsma, yerr=emsma, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
plt.errorbar(xaxis+0.3, ymim, yerr=emim, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')

plt.xticks(xaxis, x)
# Add labels and legend
plt.xlabel('Memory size (qubits)', fontsize=15)
plt.ylabel('Bell pair generation rate (BP/s)', fontsize=15)
# plt.title('Time to create 100 Bell pairs for MIM and MSM links, 20km distance')
plt.legend(fontsize=15)

# # Show the plot
plt.savefig("hundredbellpair_log_short_adaptive_msm_comparision.pdf", dpi=1000)
plt.savefig("hundredbellpair_log_short_adaptive_msm_comparision.png", dpi=1000)

plt.clf()

# Read data from the file
data = open("hundredbellpairadaptivelongmsm")
lines = data.readlines()
data.close()

# Create a dictionary to store the results
results = {"MIM": {},"MSM": {}, "MSMa": {}}
for line in lines:
    line = line.split(",")
    line.pop(-1)
    for link in ["MSM","MSMa"]:
        i = 0
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo", "sixtyfour", "onetwentyeight"]:
            if line[0] == f"{link}_{memory}":
                results[link][i] = [100/(float(x)-10) for x in line[1:]]
            i += 1

data= open("hundredbellpairlong")
lines = data.readlines()
data.close()

for line in lines:
    line = line.split(",")
    line.pop(-1)
    i = 0
    for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo", "sixtyfour", "onetwentyeight"]:
        if line[0] == f"MIM_{memory}":
            results["MIM"][i] = [100/(float(x)-10) for x in line[1:]]
        i += 1
x = [pow(2,i-1) for i in range(1,9)]
ymim = []
ymsm = []
ymsma = []
emim = []
emsm = []
emsma = []
# Create the plot
for i in range(8):
    ymim.append(np.array(results["MIM"][i]).mean())
    emim.append(np.array(results["MIM"][i]).std())
    ymsm.append(np.array(results["MSM"][i]).mean())
    emsm.append(np.array(results["MSM"][i]).std())
    ymsma.append(np.array(results["MSMa"][i]).mean())
    emsma.append(np.array(results["MSMa"][i]).std())

xaxis = np.arange(len(x))
plt.clf()
plt.bar(xaxis-0.3, ymsm, label='MSM', log=True, width=0.3)
plt.bar(xaxis, ymsma, label='adaptive MSM', log=True, width=0.3)
plt.bar(xaxis+0.3, ymim, label='MIM', log=True, width=0.3)
plt.errorbar(xaxis-0.3, ymsm, yerr=emsm, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
plt.errorbar(xaxis, ymsma, yerr=emsma, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
plt.errorbar(xaxis+0.3, ymim, yerr=emim, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')

plt.xticks(xaxis, x)
# Add labels and legend
plt.xlabel('Memory size (qubits)', fontsize=15)
plt.ylabel('Bell pair generation rate (BP/s)', fontsize=15)
# plt.title('Time to create 100 Bell pairs for MIM and MSM links, 20km distance')
plt.legend(fontsize=15)

# # Show the plot
plt.savefig("hundredbellpair_log_long_adaptive_msm_comparision.pdf", dpi=1000)
plt.savefig("hundredbellpair_log_long_adaptive_msm_comparision.png", dpi=1000)
