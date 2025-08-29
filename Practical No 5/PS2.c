#include <stdio.h>
#include <omp.h>
#define N 3

int main() {
    int A[N][N], scalar = 5;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = i + j;

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] *= scalar;

    printf("Matrix after scalar multiplication:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    return 0;
}
