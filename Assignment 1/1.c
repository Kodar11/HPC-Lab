#include <stdio.h>
#include <omp.h>

int main(void)
{
    #pragma omp parallel
    printf("Hello, world.\n"); 
    return 0;
}

// command - gcc -fopenmp 1.c -o hello -> .\hello.exe