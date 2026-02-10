#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 500

// Global matrices allocated in static memory
int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

/**
 * @brief OpenMP-based parallel square matrix multiplication.
 *
 * This program computes C = A × B using OpenMP to parallelize
 * the nested loops. The collapse(2) clause allows parallelization
 * across both row and column dimensions.
 *
 * Matrices are initialized such that:
 * - A is an identity matrix.
 * - B contains row-dependent constant values.
 *
 * Execution time is measured using omp_get_wtime().
 *
 * @return int Program exit status.
 */
int main() {

    // Initialize matrices: identity for A, constant rows for B, zero for C
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = (i == j) ? 1 : 0;
            B[i][j] = 100 + i;
            C[i][j] = 0;
        }
    }

    // Start timing
    double start = omp_get_wtime();

    // Parallel matrix multiplication using OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            int sum = 0;

            // Compute dot product of row i from A and column j from B
            for (int k = 0; k < MAX; k++) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }

    // End timing
    double end = omp_get_wtime();

    // Print execution time and validation
    printf("OpenMP execution time: %f seconds\n", end - start);
    printf("Validation: C[0][0] = %d\n", C[0][0]);

    return 0;
}
