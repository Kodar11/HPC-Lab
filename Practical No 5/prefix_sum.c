// prefix_sum.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 20;
    double *a = malloc(n * sizeof(double));
    double *s = malloc(n * sizeof(double));
    for (int i=0;i<n;i++) a[i] = 1.0; 

    int T;
    #pragma omp parallel
    { if (omp_get_thread_num() == 0) T = omp_get_num_threads(); }

    double *block_sum = malloc(T * sizeof(double));

    double t0 = omp_get_wtime();
    
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int start = (long)tid * n / T;
        int end = (long)(tid + 1) * n / T;
        double local = 0.0;
        for (int i = start; i < end; ++i) {
            local += a[i];
            s[i] = local; 
        }
        block_sum[tid] = local;
    }

    
    double acc = 0.0;
    for (int t = 0; t < T; ++t) {
        double tmp = block_sum[t];
        block_sum[t] = acc;  
        acc += tmp;
    }

 
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int start = (long)tid * n / T;
        int end = (long)(tid + 1) * n / T;
        double offset = block_sum[tid];
        if (offset != 0.0) {
            for (int i = start; i < end; ++i) s[i] += offset;
        }
    }

    double t1 = omp_get_wtime();
    printf("Time: %f sec\n", t1 - t0);
    // for(int i = 0; i < n; i++){
    //      printf("%f\n", s[i]);
    // }
    // printf("\n");
    printf("s[0]=%f s[n-1]=%f\n", s[0], s[n-1]);

    free(a); free(s); free(block_sum);
    return 0;
}

