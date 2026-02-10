#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define MAX 500
#define BLOCK_SIZE 16

/**
 * @brief CUDA kernel for square matrix multiplication C = A × B.
 *
 * Each thread computes a single element of matrix C.
 * The kernel uses a naive O(n³) algorithm without shared memory
 * optimizations. Intended as a baseline CUDA implementation.
 *
 * @param A Pointer to matrix A in device memory.
 * @param B Pointer to matrix B in device memory.
 * @param C Pointer to result matrix C in device memory.
 * @param n Matrix dimension (n x n).
 */
__global__ void matmul(const int *A, const int *B, int *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        int sum = 0;

        // Compute dot product of row from A and column from B
        for (int k = 0; k < n; k++) {
            sum += A[row * n + k] * B[k * n + col];
        }

        // Store computed value in result matrix
        C[row * n + col] = sum;
    }
}

/**
 * @brief Entry point of the CUDA matrix multiplication program.
 *
 * Allocates host and device memory, initializes input matrices,
 * launches the CUDA kernel, measures execution time using CUDA events,
 * and validates the result.
 *
 * @return int Program exit status.
 */
int main() {
    size_t bytes = MAX * MAX * sizeof(int);

    // Allocate host memory
    int *h_A = (int*)malloc(bytes);
    int *h_B = (int*)malloc(bytes);
    int *h_C = (int*)malloc(bytes);

    // Initialize matrices:
    // A as identity matrix, B with constant row-based values
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            h_A[i * MAX + j] = (i == j) ? 1 : 0;
            h_B[i * MAX + j] = 100 + i;
        }
    }

    // Allocate device memory
    int *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, bytes);
    cudaMalloc((void**)&d_B, bytes);
    cudaMalloc((void**)&d_C, bytes);

    // Copy input data from host to device
    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    // Configure CUDA execution gri
    dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
    dim3 blocks(
        (MAX + BLOCK_SIZE - 1) / BLOCK_SIZE,
        (MAX + BLOCK_SIZE - 1) / BLOCK_SIZE
    );

    // Create CUDA events for timing
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Launch kernel and measure execution time
    cudaEventRecord(start);
    matmul<<<blocks, threads>>>(d_A, d_B, d_C, MAX);
    cudaEventRecord(stop);

    // Copy result back to host
    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);
    cudaEventSynchronize(stop);

    float time_ms = 0.0f;
    cudaEventElapsedTime(&time_ms, start, stop);

    // Print execution time and simple validation
    printf("CUDA execution time: %.3f ms\n", time_ms);
    printf("Validation: C[0][0] = %d\n", h_C[0]);

    // Free device and host memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
