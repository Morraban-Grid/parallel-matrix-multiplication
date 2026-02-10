#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500
#define BLOCK_SIZE 32

// Global matrices stored in static memory
double A[N][N];
double B[N][N];
double C[N][N];

/**
 * @brief Initialize matrices for multiplication.
 *
 * - A is initialized as an identity matrix.
 * - B contains row-dependent constant values.
 * - C is initialized to zero.
 */
void init_matrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i == j) ? 1.0 : 0.0;
            B[i][j] = 100.0 + i;
            C[i][j] = 0.0;
        }
    }
}

/**
 * @brief Sequential blocked matrix multiplication.
 *
 * This implementation uses loop tiling (blocking) to improve cache locality.
 * The multiplication is performed in sub-blocks of size BLOCK_SIZE x BLOCK_SIZE.
 */
void multiply_blocked() {
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {

                for (int i = ii; i < ii + BLOCK_SIZE && i < N; i++) {
                    for (int j = jj; j < jj + BLOCK_SIZE && j < N; j++) {

                        double sum = C[i][j];

                        // Compute partial dot product for the current block
                        for (int k = kk; k < kk + BLOCK_SIZE && k < N; k++) {
                            sum += A[i][k] * B[k][j];
                        }

                        C[i][j] = sum;
                    }
                }

            }
        }
    }
}

/**
 * @brief Validate the result of the multiplication.
 *
 * Since A is the identity matrix, the result C should be identical to B.
 */
void validate_result() {
    int correct = 1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (C[i][j] != B[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    }

    if (correct)
        printf("Validation: CORRECT (C = B)\n");
    else
        printf("Validation: ERROR in result\n");
}

/**
 * @brief Program entry point.
 *
 * Measures execution time of the blocked sequential matrix multiplication
 * and performs a basic validation of the result.
 *
 * @return int Program exit status.
 */
int main() {
    clock_t start, end;
    double elapsed_time;

    init_matrices();

    start = clock();
    multiply_blocked();
    end = clock();

    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Execution time (sequential blocked): %.3f seconds\n", elapsed_time);
    printf("C[0][0] = %.2f | B[0][0] = %.2f\n", C[0][0], B[0][0]);

    validate_result();

    return 0;
}
