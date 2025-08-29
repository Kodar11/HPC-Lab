#include <stdio.h>
#include <omp.h>

int main() {
    long long N = 1000000000;
    
    // --- Sequential Calculation ---
    double total_sum_seq = 0.0;
    double start_time_seq = omp_get_wtime();
    for (long long i = 1; i <= N; i++) {
        total_sum_seq += (double)i * i;
    }
    double end_time_seq = omp_get_wtime();
    
    printf("--- Sequential Version ---\n");
    printf("N = %lld\n", N);
    printf("Total sum: %.0f\n", total_sum_seq);
    printf("Time taken: %f seconds\n\n", end_time_seq - start_time_seq);

    // --- Parallel Calculation with Reduction ---
    double total_sum_par = 0.0;
    double start_time_par = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:total_sum_par)
    for (long long i = 1; i <= N; i++) {
        total_sum_par += (double)i * i;
    }
    
    double end_time_par = omp_get_wtime();
    
    printf("--- Parallel Version ---\n");
    printf("N = %lld\n", N);
    printf("Total sum: %.0f\n", total_sum_par);
    printf("Time taken: %f seconds\n", end_time_par - start_time_par);
    printf("Speedup: %f\n", (end_time_seq - start_time_seq) / (end_time_par - start_time_par));
    
    return 0;
}
