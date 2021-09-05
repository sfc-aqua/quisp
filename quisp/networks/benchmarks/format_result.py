# formatting output result
import pickle
import sys


def format_result(file_path):
    f = open(file_path)
    data = f.read()
    f.close()
    lines = data.split(' ')
    result = {"ev/sec": {i: [] for i in range(10)}}
    file_name = lines[0].replace("\n", "")
    trial = -1
    for ln in lines:
        if ln[:6] == "ev/sec":
            if float(ln[7:]) == 0:
                trial += 1
            else:
                result["ev/sec"][trial].append(float(ln[7:]))
    with open("./output/" + file_name + ".pkl", "wb") as tf:
        pickle.dump(result, tf)


if __name__ == "__main__":
    file = sys.argv[1]
    format_result(file)
