import matplotlib.pyplot as plt
import pylab
from prettytable import PrettyTable
import numpy as np
import pandas as pd
import openpyxl

tr_y = []
tr_dif = []
tr_ex = []
with open("osn_setka.txt") as f:
    for line in f:
        tr_y.append([float(x) for x in line.split()])

with open("diff.txt") as d:
    for line in d:
        tr_dif.append([float(x) for x in line.split()])

# with open("ExData.txt") as e:
#     for line in e:
#         tr_ex.append([float(x) for x in line.split()])

x = np.array([])
xs = np.array([])
xs2 = np.array([])
y = np.array([])
th = []
z = np.array([])
ex = np.array([])
n_ = tr_y[0][0]
m_ = tr_y[1][0]
n = int(n_)
m = int(m_)
index = []
columns = []
for i in range(8, len(tr_y)):
    z = np.append(z, tr_y[i])
print(len(z))
for i in range(0, len(tr_ex)):
    ex = np.append(ex, tr_ex[i])

for j in range(0, n + 1):
    index.append(j)
    columns.append(j)

h = tr_dif[4][0]
k = tr_dif[7][0]
x_border1 = tr_dif[2][0]
x_border2 = tr_dif[3][0]
y_border1 = tr_dif[5][0]
y_border2 = tr_dif[6][0]
x_ = x_border1
while x_ <= x_border2:
    xs = np.append(xs, round(x_,5))
    x_ += h

#-------------------------------------------если сломалось расскомменте !!!!!!!!! потом исправлю
#xs = np.append(xs, 1.0)

'''x_ = x_border1
while x_ < x_border2:
    if (x_ < 3 * h *n/4 and x_ > h*n/4):
        i += int(h* n//2)
    print('i: ', i)
    xs2 = np.append(xs2, xs1[i])
    x_ += h'''


'''i=0
while i < (n + 1):
    j = 0
    while j < (m + 1):
        if (j == m / 4 and i < 3 * n / 4 and i > n / 4):
            j += n / 2;
        print('i: ', i)
        print('j: ', j) 
        y = np.append(y, y_border1 + j*h)
        j += 1
    i+=1'''


for i in range(n+1):
    j = 0
    while j < (m+1):
        y = np.append(y, round(y_border1 + j * h,5))
        j +=1

for j in range(len(xs)):
    for i in range(n+1):
        x = np.append(x, xs[j])

print('xs: ', xs)

print('x: ', x)
print('y: ', y)
print('z: ', z)

td_data = np.array([])
for i in range(len(z)):
    td_data = np.append(td_data, z[i])
td_data = td_data.reshape(int(m) + 1, int(n) + 1)

columns = len(th)
table = PrettyTable(th)
table.field_names = th
for i in range(n+1):
    table.add_row(td_data[i])
#print(table)
df = pd.DataFrame(td_data)
df.to_excel("Tables.xlsx")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_trisurf(x, y, z)
# fig2 = plt.figure()
# ax2 = fig2.add_subplot(111, projection='3d')
# ax2.plot_trisurf(x, y, ex)
plt.show()

