#include <stdio.h>
#include <omp.h>
#define N 8

int main() {
    int arr[N], prefix[N];

    for (int i = 0; i < N; i++) arr[i] = i + 1;

    prefix[0] = arr[0];
    for (int i = 1; i < N; i++)  // Sequential due to dependency
        prefix[i] = prefix[i - 1] + arr[i];

    printf("Prefix Sum Array:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", prefix[i]);
    printf("\n");

    return 0;
}
