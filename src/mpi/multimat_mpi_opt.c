#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX 500

/**
 * @brief MPI-based distributed square matrix multiplication.
 *
 * This program performs matrix multiplication C = A × B using
 * data distribution across multiple MPI processes.
 *
 * Strategy:
 * - Matrix B is broadcast to all processes.
 * - Matrix A is divided by rows and scattered among processes.
 * - Each process computes its portion of the result matrix.
 * - Partial results are gathered back to the root process.
 *
 * Matrices are initialized such that:
 * - A is an identity matrix.
 * - B contains row-dependent constant values.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Program exit status.
 */
int main(int argc, char *argv[]) {
    int rank, size;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_proc = MAX / size;

    int *A = NULL;
    int *B = (int*)malloc(MAX * MAX * sizeof(int));
    int *C = NULL;

    // Local buffers for each process
    int *A_local = (int*)malloc(rows_per_proc * MAX * sizeof(int));
    int *C_local = (int*)malloc(rows_per_proc * MAX * sizeof(int));

    // Root process initializes matrices
    if (rank == 0) {
        A = (int*)malloc(MAX * MAX * sizeof(int));
        C = (int*)malloc(MAX * MAX * sizeof(int));

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                A[i * MAX + j] = (i == j) ? 1 : 0;
                B[i * MAX + j] = 100 + i;
            }
        }
    }

    // Broadcast matrix B to all processes
    MPI_Bcast(B, MAX * MAX, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter rows of matrix A among processes
    MPI_Scatter(A, rows_per_proc * MAX, MPI_INT,
                A_local, rows_per_proc * MAX, MPI_INT,
                0, MPI_COMM_WORLD);

    // Local matrix multiplication
    for (int i = 0; i < rows_per_proc; i++) {
        for (int j = 0; j < MAX; j++) {
            int sum = 0;

            // Compute dot product for assigned rows
            for (int k = 0; k < MAX; k++) {
                sum += A_local[i * MAX + k] * B[k * MAX + j];
            }

            C_local[i * MAX + j] = sum;
        }
    }

    // Gather partial results into final matrix C at root
    MPI_Gather(C_local, rows_per_proc * MAX, MPI_INT,
               C, rows_per_proc * MAX, MPI_INT,
               0, MPI_COMM_WORLD);

    // Root validates result
    if (rank == 0) {
        printf("Validation: C[0][0] = %d\n", C[0]);
        free(A);
        free(C);
    }

    // Free allocated memory
    free(B);
    free(A_local);
    free(C_local);

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
