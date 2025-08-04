#include <stdio.h>
#include <omp.h>

int main(void) {
    int num_threads = 4; 

    
    printf("--- Sequential Part ---\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Hello, World from sequential loop.\n");
    }

    
    printf("\n--- Parallel Part ---\n");
    omp_set_num_threads(num_threads); 

    #pragma omp parallel
    {
        
        printf("Hello, World from thread %d.\n", omp_get_thread_num());
    }

    return 0;
}