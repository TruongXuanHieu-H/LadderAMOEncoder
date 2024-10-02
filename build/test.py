import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

# Sample data
x = np.linspace(0, 10, 100)
y = 50000 * np.sin(x)

plt.plot(x, y)

# Define the ticks and the corresponding labels
ticks = [10000, 20000, 30000, 40000, 50000]
tick_labels = [1, 2, 3, 4, 5]

# Set the y-ticks and labels
plt.yticks(ticks, tick_labels)

# Add the exponent above the ticks
for tick in ticks:
    plt.text(y=1, x=0, s='e+04', va='bottom',
             ha='center', transform=plt.gca().transAxes)

plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Plot with Exponent Above Tick Values')
plt.grid()

plt.show()
