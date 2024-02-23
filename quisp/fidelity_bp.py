import matplotlib.pyplot as plt
import numpy as np

# Read data from the file
data = open("fidelities")
lines = data.readlines()
data.close()

# Create a dictionary to store the results
results = {"MIM": {}, "MSM": {}}
for line in lines:
    line = line.split(",")
    line.pop(-1)
    for link in ["MIM","MSM"]:
        if line[0] == f"{link}_depolarizing":
            results[link][0] = [float(x) for x in line[1:]]
        if line[0] == f"{link}_depolarizing_purification":
            results[link][1] = [float(x) for x in line[1:]]
        if line[0] == f"{link}_depolarizing_purification_two":
            results[link][2] = [float(x) for x in line[1:]]
        if line[0] == f"{link}_depolarizing_purification_three":
            results[link][3] = [float(x) for x in line[1:]]
        if line[0] == f"{link}_depolarizing_purification_four":
            results[link][4] = [float(x) for x in line[1:]]

ymim = []
ymsm = []
emim = []
emsm = []
# Create the plot
for i in range(5):
    ymim.append(np.array(results["MIM"][i]).mean())
    ymsm.append(np.array(results["MSM"][i]).mean())
    emim.append(np.array(results["MIM"][i]).std())
    emsm.append(np.array(results["MSM"][i]).std())


x = ["no purification", "one round", "two rounds", "three rounds","four rounds"]
xaxis = np.arange(len(x))
plt.bar(xaxis-0.2 , ymim, label='MIM',  width=0.4)
plt.bar(xaxis+0.2, ymsm, label='MSM', width=0.4)
plt.errorbar(xaxis-0.2 , ymim, yerr=emim, fmt='.', capsize=3,markersize=10,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
plt.errorbar(xaxis+0.2, ymsm, yerr=emsm, fmt='.', capsize=3,markersize=10,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')

plt.xticks(xaxis, x, fontsize=11)
# Add labels and legend
plt.xlabel('Purification level', fontsize=15)
plt.ylabel('Fidelity', fontsize=15)
# plt.title('Fidelity and purification fidelity for MIM and MSM links')
plt.legend(fontsize=15)

# # Show the plot
plt.savefig("fidelities.pdf", dpi=1000)
