import numpy as np
import matplotlib.pyplot as plt

# Read data from CSV
data = np.genfromtxt('search_data.csv', delimiter=',', skip_header=1)
sizes = data[:, 0]
bin_times = data[:, 1]
fib_times = data[:, 2]

# Plotting the search times
plt.plot(sizes, bin_times, 'or', label='Binary Search Time')
plt.plot(sizes, fib_times, 'og', label='Fibonacci Search Time')

# Plotting the theoretical log2(n) curve
c = bin_times[0] / np.log2(sizes[0])  # Constant 'c' from the first data point
log_curve = c * np.log2(sizes)
plt.plot(sizes, log_curve, '-b', label='c * log2(n)')

# Add labels and legend
plt.xlabel('Array Size')
plt.ylabel('Execution Time (seconds)')
plt.legend()
plt.title('Binary Search vs Fibonacci Search')

plt.show()