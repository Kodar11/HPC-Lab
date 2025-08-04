#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void initialize_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = i + j;
        }
    }
}

void free_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int thread_counts[] = {1, 2, 4, 8};
    double start_time, end_time, sequential_time;

    for (int s = 0; s < sizeof(sizes) / sizeof(int); s++) {
        int N = sizes[s];
        printf("----------------------------------\n");
        printf("Matrix size: %d x %d\n", N, N);

        int **A = (int **)malloc(N * sizeof(int *));
        int **B = (int **)malloc(N * sizeof(int *));
        int **C = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            A[i] = (int *)malloc(N * sizeof(int));
            B[i] = (int *)malloc(N * sizeof(int));
            C[i] = (int *)malloc(N * sizeof(int));
        }

        initialize_matrix(A, N);
        initialize_matrix(B, N);

        omp_set_num_threads(1);
        start_time = omp_get_wtime();
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        end_time = omp_get_wtime();
        sequential_time = end_time - start_time;
        printf("Sequential time (1 thread): %f seconds\n", sequential_time);

        for (int t = 0; t < sizeof(thread_counts) / sizeof(int); t++) {
            int num_threads = thread_counts[t];
            if (num_threads == 1) continue; 

            omp_set_num_threads(num_threads);
            start_time = omp_get_wtime();
            #pragma omp parallel for collapse(2)
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    C[i][j] = A[i][j] + B[i][j];
                }
            }
            end_time = omp_get_wtime();
            double parallel_time = end_time - start_time;
            double speedup = sequential_time / parallel_time;
            printf("Time with %d threads: %f seconds, Speedup: %f\n", num_threads, parallel_time, speedup);
        }

        free_matrix(A, N);
        free_matrix(B, N);
        free_matrix(C, N);
    }

    return 0;
}
