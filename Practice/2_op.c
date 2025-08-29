#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int N = 1000000;
    int* arr = (int*)malloc(N * sizeof(int));
    int* prefix_sum = (int*)malloc(N * sizeof(int));
    int num_threads;

    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    printf("--- Correct Parallel Prefix Sum ---\n");
    printf("Array size: %d\n", N);

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
    }

    // Allocate an array to hold the sum of each block.
    int* block_sums = (int*)calloc(num_threads, sizeof(int));

    // --- Phase 1: Compute partial sums in parallel ---
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int local_sum = 0;

        #pragma omp for
        for (int i = 0; i < N; i++) {
            local_sum += arr[i];
            prefix_sum[i] = local_sum;
        }

        block_sums[tid] = local_sum;
    }

    // --- Phase 1.5: Sequentially compute the prefix sum of the block sums ---
    for (int i = 1; i < num_threads; i++) {
        block_sums[i] += block_sums[i - 1];
    }

    // --- Phase 2: Adjust each block with the previous block's sum ---
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int offset = (tid > 0) ? block_sums[tid - 1] : 0;
        
        #pragma omp for
        for (int i = 0; i < N; i++) {
            if (tid > 0) {
                prefix_sum[i] += offset;
            }
        }
    }

    double end_time = omp_get_wtime();

    printf("First 10 elements of input array:\n");
    print_array(arr, 10);
    printf("First 10 elements of prefix sum array (CORRECT):\n");
    print_array(prefix_sum, 10);
    
    printf("Time taken (Correct Parallel): %f seconds\n", end_time - start_time);

    free(arr);
    free(prefix_sum);
    free(block_sums);

    return 0;
}
