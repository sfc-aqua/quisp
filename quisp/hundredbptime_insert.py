import matplotlib.pyplot as plt
import numpy as np

# Create a dictionary to store the results
simple_simulations = ["simple", "simple_adaptive"]
long_simulations = ["long", "long_adaptive"]
locations = ["homogeneous", "zero", "one", "two", "three", "four"]


def genplot(memory):
    print(f"Memory: {memory}")
    data = open("bellpairtimings_" + str(memory) + "mem_insert_mim")
    plt.clf()
    lines = data.readlines()
    data.close()
    result_simple = {"simple": {"homogeneous": {}, "zero": {}, "one": {}, "two": {}, "three": {}, "four": {} }, "simple_adaptive": {"homogeneous": {}, "zero": {}, "one": {}, "two": {}, "three": {}, "four": {} }}
    dist = 0
    for simulation in simple_simulations:
        for location in locations:
            for line in lines:
                line = line.split(",")
                line.pop(-1)
                if line[0] == f"msm_ten_nodes_mim_{location}_{simulation}":
                    print(line[0])
                    tmp = [100/(float(x)-10) for x in line[1:]]
                    # For some cases (especially when the link is asymmetric) the time to generate 100 BP are different between the two nodes. We use the longer time, since that is when we can confirm to have a bell pair among the link.
                    # Initialize variables to store principal components and current maximum
                    tmp_step1 = []
                    max_value = tmp[0]
                    # Iterate through the array to find principal components
                    for value in tmp[1:]:
                        if value > max_value:
                            max_value = value
                        else:
                            tmp_step1.append(max_value)
                            max_value = value
                    # Add the last maximum value as the principal component
                    tmp_step1.append(max_value)
                    result_simple[simulation][location] = [np.array(tmp_step1).mean(), np.array(tmp_step1).std()]
        xaxis = np.arange(len(locations))
        y = [result_simple[simulation]["homogeneous"][0], result_simple[simulation]["zero"][0], result_simple[simulation]["one"][0], result_simple[simulation]["two"][0], result_simple[simulation]["three"][0], result_simple[simulation]["four"][0]]
        err = [result_simple[simulation]["homogeneous"][1], result_simple[simulation]["zero"][1], result_simple[simulation]["one"][1], result_simple[simulation]["two"][1], result_simple[simulation]["three"][1], result_simple[simulation]["four"][1]]
        simulation = simulation.replace("_simple_", " ")
        simulation = simulation.replace("_simple", " ")
        print(y)
        plt.bar(xaxis-0.2+dist, y, label=f'{simulation}', log=False, width=0.4)
        plt.errorbar(xaxis-0.2+dist, y, yerr=err, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
        dist += 0.4
    plt.legend()
    plt.xticks(xaxis, locations)
    plt.xlabel('Replaced link', fontsize=15)
    plt.ylabel('Bell pair generation rate (BP/s)', fontsize=15)
    plt.savefig(f"1kmdist_inserted_{memory}mem.png", dpi=1000)
    plt.savefig(f"1kmdist_inserted_{memory}mem.pdf", dpi=1000)
    plt.clf()
    result_long = {"long": {"homogeneous": {}, "zero": {}, "one": {}, "two": {}, "three": {}, "four": {} }, "long_adaptive": {"homogeneous": {}, "zero": {}, "one": {}, "two": {}, "three": {}, "four": {} }}
    dist = 0
    for simulation in long_simulations:
        for location in locations:
            for line in lines:
                line = line.split(",")
                line.pop(-1)
                if line[0] == f"msm_ten_nodes_mim_{location}_{simulation}":
                    print(line[0])
                    tmp = [100/(float(x)-10) for x in line[1:]]
                    # For some cases (especially when the link is asymmetric) the time to generate 100 BP are different between the two nodes. We use the longer time, since that is when we can confirm to have a bell pair among the link.
                    
                    # Initialize variables to store principal components and current maximum
                    tmp_step1 = []
                    max_value = tmp[0]
                    # Iterate through the array to find principal components
                    for value in tmp[1:]:
                        if value > max_value:
                            max_value = value
                        else:
                            tmp_step1.append(max_value)
                            max_value = value
                    # Add the last maximum value as the principal component
                    tmp_step1.append(max_value)
                    result_long[simulation][location] = [np.array(tmp_step1).mean(), np.array(tmp_step1).std()]
        xaxis = np.arange(len(locations))
        y = [result_long[simulation]["homogeneous"][0], result_long[simulation]["zero"][0], result_long[simulation]["one"][0], result_long[simulation]["two"][0], result_long[simulation]["three"][0], result_long[simulation]["four"][0]]
        err = [result_long[simulation]["homogeneous"][1], result_long[simulation]["zero"][1], result_long[simulation]["one"][1], result_long[simulation]["two"][1], result_long[simulation]["three"][1], result_long[simulation]["four"][1]]
        simulation = simulation.replace("_long_", " ")
        simulation = simulation.replace("_long", " ")
        plt.bar(xaxis-0.2+dist, y, label=f'{simulation}', log=False, width=0.4)
        plt.errorbar(xaxis-0.2+dist, y, yerr=err, fmt='.', capsize=3,markersize=6,ecolor='black',elinewidth=0.5,markeredgecolor = 'black', color='w')
        dist += 0.4
    plt.legend()
    plt.xticks(xaxis, locations)
    plt.xlabel('Replaced link', fontsize=15)
    plt.ylabel('Bell pair generation rate (BP/s)', fontsize=15)
    plt.savefig(f"20kmdist_inserted_{memory}mem.png", dpi=1000)
    plt.savefig(f"20kmdist_inserted_{memory}mem.pdf", dpi=1000)
for (memory) in ["4", "32"]:
    genplot(memory)