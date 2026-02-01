#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 100000

int main() {
    double step = 1.0 / (double)NUM_STEPS;
    double pi, sum;
    double start_time, end_time;
    
    printf("Pi Calculation using Integration\n");
    printf("Number of steps: %d\n\n", NUM_STEPS);
    
    // Test different thread counts
    for (int threads = 2; threads <= 8; threads++) {
        sum = 0.0;
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
        
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < NUM_STEPS; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        
        pi = step * sum;
        end_time = omp_get_wtime();
        
        printf("Threads: %d, Pi: %.10f, Time: %f seconds\n", 
               threads, pi, end_time - start_time);
    }
    
    return 0;
}