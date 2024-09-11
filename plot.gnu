# Set the output format and file
set terminal pngcairo size 800,600 enhanced font 'Arial,10'
set output 'search_times.png'

# Title and Labels
set title "Binary Search vs Fibonacci Search"
set xlabel "Array Size"
set ylabel "Execution Time (seconds)"

# Set key (legend) position
set key outside

# Plot styles
set style line 1 lc rgb 'red' pt 7 ps 1.5 lt 1 lw 2  # Red points for binary search
set style line 2 lc rgb 'green' pt 7 ps 1.5 lt 1 lw 2  # Green points for Fibonacci search
set style line 3 lc rgb 'blue' lt 1 lw 2  # Blue line for log curve

# Load data from CSV file
set datafile separator ","

# Read data from the CSV file
plot 'search_data.csv' using 1:2 with points ls 1 title 'Binary Search Time', \
     'search_data.csv' using 1:3 with points ls 2 title 'Fibonacci Search Time', \
     'search_data.csv' using 1:(($2/log($1)/log(2))*log($1)/log(2)) with lines ls 3 title 'c * log2(n)'




# gnuplot plot.gnu
