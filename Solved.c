#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

// Binary Search Algorithm - Returns index of the found element or -1 if not found
int binary_search(int arr[], int size, int x) {
    int lo = 0, hi = size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == x) return mid;  // Found, return index
        else if (arr[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;  // Not found
}

// Fibonacci Search Algorithm - Returns index of the found element or -1 if not found
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
            return i;  // Found, return index
        }
    }
    
    if (fib1 && arr[offset + 1] == x) return offset + 1;
    
    return -1;  // Not found
}

// Generate sorted array and save to file
void generate_and_save_sorted_array(int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", i);  // Write sorted numbers to file
    }

    fclose(file);
}

// Read sorted array from file
int* read_array_from_file(const char *filename, int size) {
    int *arr = (int*) malloc(size * sizeof(int));
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error reading file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
    return arr;
}

int main() {
    int powers_of_ten[] = {10000, 100000, 1000000, 10000000, 100000000};  // Powers of 10 from 10^4 to 10^8
    int steps = sizeof(powers_of_ten) / sizeof(powers_of_ten[0]);
    double bin_times[steps], fib_times[steps];
    char filenames[steps][20];  // Store filenames dynamically based on input size

    // Generate filenames and create files with sorted arrays
    for (int i = 0; i < steps; i++) {
        sprintf(filenames[i], "file%d.txt", i + 1);
        generate_and_save_sorted_array(powers_of_ten[i], filenames[i]);
    }

    for (int i = 0; i < steps; i++) {
        int n = powers_of_ten[i];
        int *arr = read_array_from_file(filenames[i], n);
        int search_element_best = n / 2;  // Element for the best-case scenario
        int search_element_worst = -1;    // Element for the worst-case scenario

        clock_t start, end;

        // Best Case Binary Search Timing (Searching for an element that exists)
        start = clock();
        int index_bin = -1;
        for (int j = 0; j < 1000; j++) {
            index_bin = binary_search(arr, n, search_element_best);  // Searching for an element in the middle
        }
        end = clock();
        double best_bin_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Best Case Fibonacci Search Timing (Searching for an element that exists)
        start = clock();
        int index_fib = -1;
        for (int j = 0; j < 1000; j++) {
            index_fib = fib_search(arr, n, search_element_best);  // Searching for an element in the middle
        }
        end = clock();
        double best_fib_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Worst Case Binary Search Timing (Searching for non-existing element)
        start = clock();
        for (int j = 0; j < 1000; j++) {
            binary_search(arr, n, search_element_worst);  // Searching for non-existing element
        }
        end = clock();
        bin_times[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Worst Case Fibonacci Search Timing (Searching for non-existing element)
        start = clock();
        for (int j = 0; j < 1000; j++) {
            fib_search(arr, n, search_element_worst);  // Searching for non-existing element
        }
        end = clock();
        fib_times[i] = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Print Best Case Search Times and Indices to Terminal
        printf("Array Size: %d\n", n);
        printf("Best Case Binary Search - Searching for element %d: %f seconds, Index: %d\n", search_element_best, best_bin_time, index_bin);
        printf("Best Case Fibonacci Search - Searching for element %d: %f seconds, Index: %d\n", search_element_best, best_fib_time, index_fib);
        printf("Worst Case Binary Search - Searching for element %d: %f seconds\n", search_element_worst, bin_times[i]);
        printf("Worst Case Fibonacci Search - Searching for element %d: %f seconds\n\n", search_element_worst, fib_times[i]);

        free(arr);  // Free the allocated memory
    }

    // Write the worst-case data to CSV file
    FILE *fp = fopen("search_data.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "size,binary_search_time,fibonacci_search_time\n");
    for (int i = 0; i < steps; i++) {
        fprintf(fp, "%d,%f,%f\n", powers_of_ten[i], bin_times[i], fib_times[i]);
    }

    fclose(fp);

    printf("Worst-case data written to search_data.csv. Files created for sorted arrays.\n");

    return 0;
}
