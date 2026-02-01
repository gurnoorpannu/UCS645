#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000

int main() {
    // Allocate matrices dynamically (on heap, not stack)
    double **A = (double **)malloc(SIZE * sizeof(double *));
    double **B = (double **)malloc(SIZE * sizeof(double *));
    double **C = (double **)malloc(SIZE * sizeof(double *));
    
    for (int i = 0; i < SIZE; i++) {
        A[i] = (double *)malloc(SIZE * sizeof(double));
        B[i] = (double *)malloc(SIZE * sizeof(double));
        C[i] = (double *)malloc(SIZE * sizeof(double));
    }
    
    double start_time, end_time;
    
    // Initialize matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }
    
    printf("Matrix Multiplication - 1000x1000\n");
    printf("=================================\n\n");
    
    // ========== 1D THREADING ==========
    printf("1D Threading (Outer Loop Parallelization):\n");
    printf("-------------------------------------------\n");
    
    for (int threads = 2; threads <= 8; threads++) {
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
        
        #pragma omp parallel for
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                C[i][j] = 0;
                for (int k = 0; k < SIZE; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        
        end_time = omp_get_wtime();
        printf("Threads: %d, Time: %f seconds\n", threads, end_time - start_time);
    }
    
    printf("\n");
    
    // ========== 2D THREADING ==========
    printf("2D Threading (Nested Loop Parallelization with collapse):\n");
    printf("----------------------------------------------------------\n");
    
    for (int threads = 2; threads <= 8; threads++) {
        omp_set_num_threads(threads);
        start_time = omp_get_wtime();
        
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                C[i][j] = 0;
                for (int k = 0; k < SIZE; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        
        end_time = omp_get_wtime();
        printf("Threads: %d, Time: %f seconds\n", threads, end_time - start_time);
    }
    
    // Free allocated memory
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    
    return 0;
}