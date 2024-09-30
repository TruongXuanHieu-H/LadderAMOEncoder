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
filename4 = 'reduced_report.txt'
filename5 = 'naive_report.txt'
filename6 = 'seq_report.txt'

# Read data
x1, y1 = read_data(filename1, 5)
x2, y2 = read_data(filename2, 5)
x3, y3 = read_data(filename3, 5)
x4, y4 = read_data(filename4, 5)
x5, y5 = read_data(filename5, 5)
x6, y6 = read_data(filename6, 5)


# Plot the data
plt.figure(figsize=(10, 50))
plt.plot(x4, y4, linestyle=':', color='blue', label="Reduced")
# plt.plot(x6, y6, linestyle='--', color='orange', label="Seq")
# plt.plot(x5, y5, linestyle='-', color='green', label="Naive")
# plt.plot(x3, y3, linestyle=':', color='red', label="Product")
plt.plot(x2, y2, linestyle='--', color='magenta', label="Duplex")
plt.plot(x1, y1, linestyle='-', color='black', label="Ladder", linewidth=2)
plt.legend()
plt.xlabel('w')
plt.ylabel('Time (ns)')
plt.grid(True)
plt.show()
