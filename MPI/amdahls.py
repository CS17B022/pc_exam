import matplotlib.pyplot as plt

parallel = 0.9
serial = 0.1

x = []
y = []
p = 1
for np in range(1,10):
    x.append(p)
    sp = 1 / ((1 - parallel) + parallel / p)
    y.append(sp)
    print(p)
    p = p * 256

plt.plot(x, y)
plt.ylabel('speedup')
plt.xlabel('processors')
plt.show()
