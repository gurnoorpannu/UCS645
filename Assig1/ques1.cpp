#include <stdio.h>
#include <omp.h>

#define N 65536
int main() {
    double X[N], Y[N];
    double a = 2.5;
    double start_time, end_time;
    
    for (int i = 0; i < N; i++) {
        X[i] = i * 1.0;
        Y[i] = i * 0.5;
    }
    
    printf("DAXPY: X[i] = a*X[i] + Y[i]\n");
    printf("Vector size: %d\n\n", N);
    
    // Test different thread counts
    for (int threads = 2; threads <= 8; threads++) {
        for (int i = 0; i < N; i++) {
            X[i] = i * 1.0;
        }
        
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
        
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            X[i] = a * X[i] + Y[i];
        }
        
        end_time = omp_get_wtime();
        
        printf("Threads: %d, Time: %f seconds\n", threads, end_time - start_time);
    }
    
    return 0;
}