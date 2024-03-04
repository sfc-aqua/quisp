import matplotlib.pyplot as plt
import numpy as np

# Read data from the file
data = open("hundredbellpairadaptiveshortmsm")
lines = data.readlines()
data.close()

# Create a dictionary to store the results
results = {"MSM": {}, "MSMa": {}}
for line in lines:
    line = line.split(",")
    line.pop(-1)
    for link in ["MSM","MSMa"]:
        i = 0
        for memory in ["one","two", "four", "eight", "sixteen", "thirtytwo", "sixtyfour", "onetwentyeight"]:
            if line[0] == f"{link}_{memory}":
                results[link][i] = [(float(x)-10) for x in line[1:]]
            i += 1

x = [pow(2,i-1) for i in range(1,9)]
ymsm = []
ymsma = []
emsm = []
emsma = []
# Create the plot
for i in range(8):
    ymsm.append(np.array(results["MSM"][i]).mean())
    emsm.append(np.array(results["MSM"][i]).std())
    ymsma.append(np.array(results["MSMa"][i]).mean())
    emsma.append(np.array(results["MSMa"][i]).std())

xaxis = np.arange(len(x))
plt.bar(xaxis-0.2, ymsm, label='MSM', log=True, width=0.4)
plt.bar(xaxis+0.2, ymsma, label='Adaptive MSM', log=True, width=0.4)
plt.errorbar(xaxis-0.2, ymsm, yerr=emsm, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
plt.errorbar(xaxis+0.2, ymsma, yerr=emsma, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')

plt.xticks(xaxis, x)
# Add labels and legend
plt.xlabel('Memory size (qubits)', fontsize=15)
plt.ylabel('Time to create 100 Bell pairs (s)', fontsize=15)
# plt.title('Time to create 100 Bell pairs for MIM and MSM links, 20km distance')
plt.legend(fontsize=15)

# # Show the plot
plt.savefig("hundredbellpair_log_short_adaptive_msm_comparision.pdf", dpi=1000)
