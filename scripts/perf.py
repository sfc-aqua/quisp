import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import sys


class Perf:
    def __init__(self):
        if len(sys.argv) != 2:
            raise Exception("No input file!\
            Input the file you want to visualize")
        self.file_path = sys.argv[1]
        self.time_stamps = []

    def read_file(self):
        with open(self.file_path) as f:
            self.time_stamps = [i for i in map(str.rstrip, f)]

    def parse_result(self):
        pass

    def duration(self):
        size = len(self.time_stamps)
        i = 0
        self.durations = []
        while i < size-1:
            if self.time_stamps[i] == "s" or self.time_stamps[i] == "f":
                i += 1
            else:
                # print("a", self.time_stamps[i])
                # print("a", self.time_stamps[i+1])
                # FIXME This should not happen
                if self.time_stamps[i+1] == "f":
                    break
                end_time = float(self.time_stamps[i+1])
                start_time = float(self.time_stamps[i])
                self.durations.append(end_time-start_time)
                i += 2
        return self.durations

    def visualize(self):
        self.read_file()
        # durations = self.duration()
        # plt.bar(0, np.average(durations), yerr=np.std(durations))
        # sns.distplot(durations, kde=False, rug=False,
        #              bins=25, axlabel="Bell pair creation time")
        plt.title("Distribution of Bell pair creation time at Node 1")
        times = 0.000009740086*np.array(self.time_stamps, dtype=float)

        # sns.distplot(self.time_stamps, kde=False, rug=False,
        #              bins=100, axlabel="The BSA trial to create one Bell pair")
        sns.distplot(times, kde=False, rug=False,
                     bins=100, axlabel="The creation time of one Bell pair")
        # plt.plot(durations)
        plt.show()


if __name__ == "__main__":
    perf = Perf()
    perf.visualize()
