#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 500
#define NUM_THREADS 4

// Global matrices allocated in static memory
int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

/**
 * @brief Structure to pass row range information to each thread.
 */
typedef struct {
    int start_row;  /**< Starting row (inclusive) for this thread */
    int end_row;    /**< Ending row (exclusive) for this thread */
} thread_data_t;

/**
 * @brief Thread function that performs partial matrix multiplication.
 *
 * Each thread computes a subset of rows of the result matrix C.
 *
 * @param arg Pointer to thread_data_t containing row boundaries.
 * @return void* Thread exit status.
 */
void* matmul_thread(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < MAX; j++) {
            int sum = 0;

            // Compute dot product of row i from A and column j from B
            for (int k = 0; k < MAX; k++) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }

    pthread_exit(NULL);
}

/**
 * @brief Main function that coordinates pthread-based matrix multiplication.
 *
 * The workload is divided by rows among multiple threads.
 * Each thread computes a disjoint portion of the result matrix.
 *
 * Matrices are initialized such that:
 * - A is an identity matrix.
 * - B contains row-dependent constant values.
 *
 * @return int Program exit status.
 */
int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];

    // Initialize matrices: identity for A, constant rows for B
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = (i == j) ? 1 : 0;
            B[i][j] = 100 + i;
        }
    }

    int rows_per_thread = MAX / NUM_THREADS;

    // Create threads and assign row ranges
    for (int t = 0; t < NUM_THREADS; t++) {
        thread_data[t].start_row = t * rows_per_thread;
        thread_data[t].end_row =
            (t == NUM_THREADS - 1) ? MAX : (t + 1) * rows_per_thread;

        pthread_create(&threads[t], NULL, matmul_thread, &thread_data[t]);
    }

    // Wait for all threads to finish
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Basic validation of the result
    printf("Validation: C[0][0] = %d\n", C[0][0]);

    return 0;
}
