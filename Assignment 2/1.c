#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int N = 10000; 
    int scalar = 5;
    int *A = (int*)malloc(N * sizeof(int));


    for (int i = 0; i < N; i++) {
        A[i] = i;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        A[i] = A[i] + scalar;
    }

    for (int i = 0; i < 10; i++) {
        printf("A[%d] = %d\n", i, A[i]);
    }

    free(A);
    return 0;
}

