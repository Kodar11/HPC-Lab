#include <stdio.h>
#include <omp.h>
#define N 3

int main() {
    int A[N][N], V[N], R[N] = {0};

    for (int i = 0; i < N; i++) {
        V[i] = i + 1;
        for (int j = 0; j < N; j++)
            A[i][j] = i + j;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            R[i] += A[i][j] * V[j];

    printf("Result Vector:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", R[i]);
    printf("\n");
    return 0;
}
