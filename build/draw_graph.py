import matplotlib.pyplot as plt

# Function to read data from the file


def read_data(filename, step):
    x = []
    y = []
    with open(filename, 'r') as file:
        for line in file:
            # Split the line into two parts
            parts = line.split(': ')
            if len(parts) == 2:
                # Extract the number and time
                number = int(parts[0])
                time = int(parts[1].replace(' ns', '').strip())
                if number % step == 0:
                    x.append(number)
                    y.append(time)
    return x, y


# File name
filename1 = 'ladder_report.txt'
filename2 = 'duplex_report.txt'
filename3 = 'product_report.txt'

# Read data
x1, y1 = read_data(filename1, 5)
x2, y2 = read_data(filename2, 5)
x3, y3 = read_data(filename3, 5)

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(x3, y3, linestyle='-', color='red', label="Product")
plt.plot(x2, y2, linestyle='-', color='magenta', label="Duplex")
plt.plot(x1, y1, linestyle='-', color='black', label="Ladder", linewidth=2)
plt.legend()
plt.xlabel('w')
plt.ylabel('Time (ns)')
plt.grid(True)
plt.show()
