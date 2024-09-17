#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

// Binary Search Algorithm
int binary_search(int arr[], int size, int x) {
    int lo = 0, hi = size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == x) return 1;  // Found
        else if (arr[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return 0;  // Not found
}

// Fibonacci Search Algorithm
int fib_search(int arr[], int size, int x) {
    int fib2 = 0;  // (m-2)'th Fibonacci number
    int fib1 = 1;  // (m-1)'th Fibonacci number
    int fib = fib2 + fib1;  // m'th Fibonacci number
    
    while (fib < size) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }
    
    int offset = -1;
    
    while (fib > 1) {
        int i = (offset + fib2) < size ? (offset + fib2) : size - 1;
        
        if (arr[i] < x) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (arr[i] > x) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            return 1;  // Found
        }
    }
    
    if (fib1 && arr[offset + 1] == x) return 1;
    
    return 0;
}

// Generate sorted array
int* generate_sorted_array(int n) {
    int *arr = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i;  // Sorted array from 0 to n-1
    }
    return arr;
}

int main() {
    int min_size = 10000;
    int max_size = 1000000;
    int steps = 200;
    double bin_times[steps], fib_times[steps];
    int sizes[steps];
    
    double step_size = (double)(max_size - min_size) / (steps - 1);
    
    for (int i = 0; i < steps; i++) {
        int n = min_size + (int)(i * step_size);
        sizes[i] = n;
        int *arr = generate_sorted_array(n);
        
        clock_t start, end;
        
        // Binary Search Timing
        start = clock();
        for (int j = 0; j < 1000; j++) {
            binary_search(arr, n, -1);  // Searching for non-existing element
        }
        end = clock();
        bin_times[i] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Fibonacci Search Timing
        start = clock();
        for (int j = 0; j < 1000; j++) {
            fib_search(arr, n, -1);  // Searching for non-existing element
        }
        end = clock();
        fib_times[i] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        free(arr);  // Free the allocated memory
    }
    
    // Write the data to file
    FILE *fp = fopen("search_data.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    fprintf(fp, "size,binary_search_time,fibonacci_search_time\n");
    for (int i = 0; i < steps; i++) {
        fprintf(fp, "%d,%f,%f\n", sizes[i], bin_times[i], fib_times[i]);
    }
    
    fclose(fp);
    
    printf("Data written to search_data.csv. Use Python/Excel to plot.\n");
    
    return 0;
}