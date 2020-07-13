import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import sys
import pandas as pd
# from scipy.stats import poisson
from numpy.random import poisson

sns.set(style="white", rc={"axes.facecolor": (0, 0, 0, 0)})


class Perf:
    def __init__(self):
        if len(sys.argv) < 2:
            raise Exception("No input file!\
            Input the file you want to visualize")
        self.file_path = sys.argv[1]
        self.file_paths = [i for i in sys.argv]
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
        plt.title("Distribution of Bell pair creation time at Node 1 (n=2)")
        times = 0.000009740086*np.array(self.time_stamps, dtype=float)

        # sns.distplot(self.time_stamps, kde=False, rug=False,
        #              bins=100, axlabel="The BSA trial to create one Bell pair")
        sns.distplot(times, kde=False, rug=False,
                     bins=100, axlabel="The creation time of one Bell pair")
        # plt.plot(durations)
        plt.show()
    
    def read_files(self):
        ts = []
        for fs in self.file_paths[1:]:
            with open(fs) as f:
                ts.append([i for i in map(str.rstrip, f)])
        return ts

    def visualize_ridge(self):
        ts = self.read_files()
        # to modify the number of data
        g = [("d=%s" % str(i+1)) for i, _ in enumerate(ts)]
        x = []
        gs = []
        bi = []
        for its, pts in enumerate(ts):
            for ets in pts:
                gs.append(g[its])
                x.append(float(ets))
            binom = poisson(lam=its, size=29289)
            for b in binom:
                bi.append(b)
        df = pd.DataFrame({"x": x[:len(bi)], "b": bi, "g": gs[:len(bi)]})
        # df_poisson = pd.DataFrame(dict(x=x, g=data_binom))
        # bi = sns.FacetGrid(,
        #                    aspect=15,
        #                    height=2)
        g = sns.FacetGrid(df,
                          row="g",
                          hue="g",
                          aspect=15,
                          height=2)
        # g.map(sns.distplot, "x", data_binom, ked=False)
        # bi.map(sns.kdeplot)
        g.map(sns.distplot, "b", kde=True)
        g.map(sns.distplot, "x", kde=False)
        # g.map(sns.kdeplot, "x", clip_on=False, color="w", lw=2, bw=.2)
        g.map(plt.axhline, y=0, lw=2, clip_on=True)
        g.map(self.label, "x")

        # Set the subplots to overlap
        g.fig.subplots_adjust(hspace=-.25)
        # Remove axes details that don't play well with overlap
        g.set_titles("")
        g.set(yticks=[])
        g.despine(bottom=True, left=True)
        plt.show()

    def label(self, x, color, label):
        ax = plt.gca()
        ax.text(0, .2, label, fontweight="bold", color=color,
                ha="left", va="center", transform=ax.transAxes)


if __name__ == "__main__":
    perf = Perf()
    # perf.visualize()
    perf.visualize_ridge()