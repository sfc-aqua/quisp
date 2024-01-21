import matplotlib.pyplot as plt
import numpy as np

# Read data from the file
data = open("thousandbellpair")
lines = data.readlines()
data.close()

# Create a dictionary to store the results
results = {"MIM": {}, "MSM": {}}
for line in lines:
    line = line.split(",")
    line.pop(-1)
    for link in ["MIM","MSM"]:
        i = 0
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo", "sixtyfour", "onetwentyeight"]:
            if line[0] == f"{link}_{memory}":
                results[link][i] = [float(x)-10 for x in line[1:]]
            i += 1

x = [pow(2,i-1) for i in range(1,9)]
ymim = []
ymsm = []
emim = []
emsm = []
# Create the plot
for i in range(8):
    ymim.append(np.array(results["MIM"][i]).mean())
    ymsm.append(np.array(results["MSM"][i]).mean())
    emim.append(np.array(results["MIM"][i]).std())
    emsm.append(np.array(results["MIM"][i]).std())

xaxis = np.arange(len(x))
plt.bar(xaxis, ymim, label='MIM',  width=0.4)
plt.bar(xaxis+0.4, ymsm, label='MSM', width=0.4)
plt.errorbar(xaxis, ymim, yerr=emim, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
plt.errorbar(xaxis+0.4, ymsm, yerr=emsm, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')

plt.xticks(xaxis, x)
# Add labels and legend
plt.xlabel('Memory size (qubits)')
plt.ylabel('Time to create 100 Bell pairs (s)')
plt.title('Time to create 100 Bell pairs for MIM and MSM links')
plt.legend()

# # Show the plot
plt.savefig("thousandbellpair.png", dpi=1000)
