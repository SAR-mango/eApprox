import numpy as np
import matplotlib.pyplot as plt

data = np.empty((0, 6))

with open("points.txt", 'r') as file:
    for line in file:
        row = line.split()
        data = np.append(data, [[float(row[0]), float(row[1]), float(row[2]), float(row[3]), float(row[4]), float(row[5])]], axis = 0)
        # x, y, e^x, y - e^x, y^(1/x), y^(1/x) - e

plt.title("e^x and e Approximation")
plt.xlabel("x")
plt.ylabel("y")
plt.scatter(data[:, 0], data[:, 1], color = "blue", label = "e^x Approximation") # scatter plot of e^x approximation
plt.plot(data[:, 0], data[:, 2], color = "orange", label = "e^x") # solid line plot of e^x
plt.scatter(data[:, 0], data[:, 3], color = "red", label = "e^x Approximation Error") # scatter plot of error of e^x approximation
plt.scatter(data[:, 0], data[:, 4], color = "purple", label = "e Approximation") # scatter plot of e approximation
plt.scatter(data[:, 0], data[:, 5], color = "green", label = "e Approximation Error") # scatter plot of error of e approximation
plt.legend()
plt.show()
