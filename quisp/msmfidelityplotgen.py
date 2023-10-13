import re
import matplotlib.pyplot as plt

# ファイルからデータを読み込む
with open('msmtestlog.txt', 'r') as file:
    data = file.read()

# 正規表現を使用して行を抽出
pattern = r'EndNode2<-->QuantumChannel{cost=\d+\.\d+;distance=(\d+)km;fidelity=(\d+\.\d+);bellpair_per_sec=\d+\.\d+;}<-->EndNode1;'
matches = re.findall(pattern, data)

# distanceとfidelityの値を抽出
distances = []
fidelities = []
for match in matches:
    distance = int(match[0])
    fidelity = float(match[1])
    distances.append(distance)
    fidelities.append(fidelity)

# distanceごとにfidelityの平均を計算
distance_fidelity_dict = {}
for distance, fidelity in zip(distances, fidelities):
    if distance in distance_fidelity_dict:
        distance_fidelity_dict[distance].append(fidelity)
    else:
        distance_fidelity_dict[distance] = [fidelity]

# 平均を計算
distance_values = []
fidelity_averages = []
for distance, fidelity_list in distance_fidelity_dict.items():
    distance_values.append(distance)
    average_fidelity = sum(fidelity_list) / len(fidelity_list)
    fidelity_averages.append(average_fidelity)

# グラフを描画
plt.figure(figsize=(10, 6))
plt.plot(distance_values, fidelity_averages, marker='o', linestyle='-', label='QuISP')

# 理論値を計算
import numpy as np
x = np.linspace(0, 10, 10000)
x_error = 0.2
y = 0.5 + 0.5 * np.exp(x * np.log((1-x_error)**2))
plt.plot(x,y, marker='', linestyle='-', label='Theory')
plt.legend()
plt.xlabel('Distance (km)')
plt.ylabel('Fidelity')
plt.title(f'Fidelity comparision between QuISP and theory for a MSM link with {x_error} X error rate and 0.2db photon loss')
plt.grid(True)
plt.savefig("msmtestlog.png")
