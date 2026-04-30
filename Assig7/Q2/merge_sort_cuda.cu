%%writefile merge_sort_basic.cu
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N 1000

__global__ void mergeKernel(int *arr, int *temp, int width, int n) {

    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int start = tid * 2 * width;

    if (start >= n) return;

    int mid = min(start + width, n);
    int end = min(start + 2 * width, n);

    int i = start, j = mid, k = start;

    while (i < mid && j < end) {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i < mid) temp[k++] = arr[i++];
    while (j < end) temp[k++] = arr[j++];
}

int main() {

    int h_arr[N];

    for (int i = 0; i < N; i++)
        h_arr[i] = rand() % 1000;

    int *d_arr, *d_temp;

    cudaMalloc(&d_arr, N * sizeof(int));
    cudaMalloc(&d_temp, N * sizeof(int));

    cudaMemcpy(d_arr, h_arr, N * sizeof(int), cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    int blockSize = 256;

    for (int width = 1; width < N; width *= 2) {
        int numThreads = (N + (2 * width - 1)) / (2 * width);
        int gridSize = (numThreads + blockSize - 1) / blockSize;

        mergeKernel<<<gridSize, blockSize>>>(d_arr, d_temp, width, N);

        int *tmp = d_arr;
        d_arr = d_temp;
        d_temp = tmp;
    }

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float gpu_time;
    cudaEventElapsedTime(&gpu_time, start, stop);

    printf("CUDA Merge Sort Time = %f ms\n", gpu_time);

    cudaFree(d_arr);
    cudaFree(d_temp);

    return 0;
}
