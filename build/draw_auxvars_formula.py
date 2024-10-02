import numpy as np
import matplotlib.pyplot as plt

# Define n(x)


def n(x):
    return 1000

# Define N(x)


def N(x):
    return n(x) - x + 1


# Define the seq expression


def seq(x):
    return N(x) * (x - 2)


# Define the BDD expression


def bdd(x):
    return N(x) * (2 * x - 3)

# Define the product expression


def product(x):
    return N(x) * 2 * np.sqrt(x)

# Define the duplex expression


def duplex(x):
    return 4 * np.ceil(n(x) / x) * (x - 1)

# Define the SCL expression


def ladder(x):
    return 2 * np.ceil(n(x) / x) * x - 3 * np.ceil(n(x) / x) - 2 * x + 4


# Generate x values
x_values = np.linspace(2, 999, 998)

# Calculate y values using the expressions
seq_values = seq(x_values)
bdd_values = bdd(x_values)
product_values = product(x_values)
duplex_values = duplex(x_values)
ladder_values = ladder(x_values)

plt.figure(figsize=(10, 6))
plt.plot(x_values, seq_values, linestyle='--',
         label="Seq", color='orange', linewidth=2)
plt.plot(x_values, bdd_values, linestyle='-.',
         label="BDD", color='purple', linewidth=2)
plt.plot(x_values, product_values, linestyle=':',
         label="Product", color='red', linewidth=2)
plt.plot(x_values, duplex_values, linestyle='--',
         label="Duplex", color='magenta', linewidth=2)
plt.plot(x_values, ladder_values, linestyle='-',
         label="SCL", color='black', linewidth=2)

plt.xlabel('w')
plt.ylabel('#AuxVars')
plt.axhline(0, color='black', linewidth=0.5, ls='--')
plt.axvline(0, color='black', linewidth=0.5, ls='--')
plt.grid()
plt.legend()
plt.ylim(0, 50000)
plt.show()
