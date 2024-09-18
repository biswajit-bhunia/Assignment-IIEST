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

-------------

import numpy as np
import matplotlib.pyplot as plt

# Read data from CSV
data = np.genfromtxt('search_data.csv', delimiter=',', skip_header=1)
sizes = data[:, 0]
bin_times = data[:, 1]

# Plotting the Binary Search times with connected lines
plt.plot(sizes, bin_times, 'o-', label='Binary Search Time', color='red')

# Calculating the constant 'c'
c = bin_times[0] / np.log2(sizes[0])  # Constant 'c' from the first data point
print(c)
# Generate a larger set of x-values for smoother curve
new_sizes = np.linspace(sizes.min(), sizes.max(), 100)  # Generate 100 points

# Calculate theoretical curve for the new sizes
new_log_curve = c * np.log2(new_sizes)

# Plot the theoretical curve with interpolation
plt.plot(new_sizes, new_log_curve, 'b-', label='c * log2(n)')

# Add labels and legend
plt.xlabel('Array Size')
plt.ylabel('Execution Time (seconds)')
plt.legend()
plt.title('Binary Search Performance')

plt.show()
------------------
import numpy as np
import matplotlib.pyplot as plt

# Read data from CSV
data = np.genfromtxt('search_data.csv', delimiter=',', skip_header=1)
sizes = data[:, 0]          # Array sizes
bin_times = data[:, 1]      # Binary Search times
fib_times = data[:, 2]      # Fibonacci Search times

# Create a line plot for Binary Search and Fibonacci Search times
plt.plot(sizes, bin_times, '-o', label='Binary Search Time', color='red')  # Red line with circles
plt.plot(sizes, fib_times, '-o', label='Fibonacci Search Time', color='green')  # Green line with circles

# Add titles and labels
plt.xlabel('Array Size (n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Binary Search vs Fibonacci Search')

# Add a legend
plt.legend()

# Show grid for better readability
plt.grid(True)

# Display the plot
plt.show()
