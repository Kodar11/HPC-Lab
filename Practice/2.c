#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_array(int* arr,int size){
    for(int i = 0; i < size; i++){
        printf(" %d ",arr[i]);
    }
    printf("\n");
}

int main(){
    int N = 1000000;

    int* arr = (int*)malloc(N*sizeof(int));
    int* prefix_sum = (int*)malloc(N*sizeof(int));

    for(int i = 0; i < N; i++){
        arr[i] = i + 1 ;
    }
    printf("--- Sequential Prefix Sum ---\n");
    printf("Array size: %d\n", N);

    double start_time = omp_get_wtime();

    prefix_sum[0] = arr[0];

    for(int i = 1;i < N; i++){
        prefix_sum[i] = arr[i] + prefix_sum[i-1];
    }

    double end_time = omp_get_wtime();
    printf("First 10 elements of input array:\n");
    print_array(arr, 10);
    printf("First 10 elements of prefix sum array:\n");
    print_array(prefix_sum, 10);

    printf("Time taken (Sequential): %f seconds\n", end_time - start_time);

    free(arr);
    free(prefix_sum);

    return 0;
}