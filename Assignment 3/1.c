#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int compare_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int N = 100000; 
    int *vec_a, *vec_b;
    double start_time, end_time;

    vec_a = (int *)malloc(N * sizeof(int));
    vec_b = (int *)malloc(N * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vec_a[i] = rand() % 1000;
        vec_b[i] = rand() % 1000;
    }

    printf("Calculating minimum scalar product with N = %d\n", N);

    start_time = omp_get_wtime();
    qsort(vec_a, N, sizeof(int), compare_asc);
    end_time = omp_get_wtime();
    printf("Time for sorting vector A (ascending): %f seconds\n", end_time - start_time);

    start_time = omp_get_wtime();
    qsort(vec_b, N, sizeof(int), compare_desc);
    end_time = omp_get_wtime();
    printf("Time for sorting vector B (descending): %f seconds\n", end_time - start_time);

    long long min_scalar_product = 0;

    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:min_scalar_product)
    for (int i = 0; i < N; i++) {
        min_scalar_product += (long long)vec_a[i] * vec_b[i];
    }
    end_time = omp_get_wtime();

    printf("Time for parallel dot product: %f seconds\n", end_time - start_time);
    printf("Minimum scalar product = %lld\n", min_scalar_product);

    free(vec_a);
    free(vec_b);

    return 0;
}
