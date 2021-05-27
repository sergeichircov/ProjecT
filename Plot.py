import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from tqdm import tqdm

text = pd.read_table('output.txt', sep=' ')# считывается файл с названием output.txt и разделителем по столбцам - пробелом

u = text['temperature']# берётся столбец с заголовком temperature
text# просто выводит содержимое файла

a = 0 #начало по координате
b = 0.1# конец по координате
c = 0# начало по времени
d = 10# конец по времени

N = 100# число точек по координате
M = 100000# число точек по времени

z = np.linspace(a, b, N)# создаёт разбиение отрезка по координате
t = np.linspace(c, d, M)
T, Z = np.meshgrid(t, z)# создаёт двумерные массивы для времени и координаты графика

U = np.empty((N, M))# пустой двумерный массив, куда положим температуру

for i in tqdm(range(N)):
  for j in range(M):
    U[i][j] = u[N*j + i]

# строим график
fig = plt.figure(figsize=(10,7))# (10,7) - размер окна для вывода графиков
ax = fig.add_subplot(111, projection='3d')# создаёт само поле графика с осями, 111 - значит, что оно единственное в этом окне
ax.plot_surface(T, Z, U, cmap='inferno') #собственно, строим, inferno - стиль графика, он же цвет
ax.set_xlabel('время (с)')
ax.set_ylabel('координата (м)')
ax.set_zlabel('температура (°С)')
plt.show() 