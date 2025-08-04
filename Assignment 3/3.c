#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200

void vector_addition(int *a, int *b, int scalar, int n) {
    for (int i = 0; i < n; i++) {
        b[i] = a[i] + scalar;
    }
}

int main() {
    int a[SIZE], b[SIZE];
    int scalar = 5;
    double start_time, end_time, sequential_time, parallel_time;

    for (int i = 0; i < SIZE; i++) {
        a[i] = i;
    }

    printf("--- Static Schedule Demonstration ---\n");
    printf("Vector size: %d, Scalar: %d\n", SIZE, scalar);

    start_time = omp_get_wtime();
    vector_addition(a, b, scalar, SIZE);
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Sequential time: %f seconds\n", sequential_time);

    int static_chunk_sizes[] = {1, 10, 50, 100};
    for (int i = 0; i < sizeof(static_chunk_sizes) / sizeof(int); i++) {
        int chunk_size = static_chunk_sizes[i];
        
        start_time = omp_get_wtime();
        #pragma omp parallel for schedule(static, chunk_size)
        for (int j = 0; j < SIZE; j++) {
            b[j] = a[j] + scalar;
        }
        end_time = omp_get_wtime();
        parallel_time = end_time - start_time;
        printf("Static schedule with chunk size %d: %f seconds, Speedup: %f\n", chunk_size, parallel_time, sequential_time / parallel_time);
    }
    printf("\n");

    printf("--- Dynamic Schedule Demonstration ---\n");
    int dynamic_chunk_sizes[] = {1, 10, 50};
    for (int i = 0; i < sizeof(dynamic_chunk_sizes) / sizeof(int); i++) {
        int chunk_size = dynamic_chunk_sizes[i];

        start_time = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int j = 0; j < SIZE; j++) {
            b[j] = a[j] + scalar;
        }
        end_time = omp_get_wtime();
        parallel_time = end_time - start_time;
        printf("Dynamic schedule with chunk size %d: %f seconds, Speedup: %f\n", chunk_size, parallel_time, sequential_time / parallel_time);
    }
    printf("\n");

    printf("--- Nowait Clause Demonstration ---\n");
    double time_with_barrier_start = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = 0; i < SIZE / 2; i++) {
                b[i] = a[i] + scalar;
            }
        }
        #pragma omp section
        {
            #pragma omp parallel for
            for (int i = SIZE / 2; i < SIZE; i++) {
                b[i] = a[i] + scalar;
            }
        }
    }
    double time_with_barrier_end = omp_get_wtime();
    printf("Time with implicit barrier: %f seconds\n", time_with_barrier_end - time_with_barrier_start);

    double time_without_barrier_start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE / 2; i++) {
            b[i] = a[i] + scalar;
        }

        #pragma omp for nowait
        for (int i = SIZE / 2; i < SIZE; i++) {
            b[i] = a[i] + scalar;
        }
    }
    double time_without_barrier_end = omp_get_wtime();
    printf("Time without implicit barrier (using nowait): %f seconds\n", time_without_barrier_end - time_without_barrier_start);

    return 0;
}
