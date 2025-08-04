#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    long long num_steps = 1000000000;
    double step;
    double sum = 0.0;
    
    step = 1.0 / (double)num_steps;

    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    
    double pi = step * sum;
    printf("Pi approximation: %.15f\n", pi);

    return 0;
}