#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500
#define BLOCK_SIZE 32

double A[N][N];
double B[N][N];
double C[N][N];

/* Inicializa matrices */
void init_matrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i == j) ? 1.0 : 0.0;   // Matriz identidad
            B[i][j] = 100.0 + i;
            C[i][j] = 0.0;
        }
    }
}

/* Multiplicación de matrices con bloqueo */
void multiply_blocked() {
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {

                for (int i = ii; i < ii + BLOCK_SIZE && i < N; i++) {
                    for (int j = jj; j < jj + BLOCK_SIZE && j < N; j++) {

                        double sum = C[i][j];
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

int main() {
    clock_t start, end;
    double elapsed_time;

    init_matrices();

    start = clock();
    multiply_blocked();
    end = clock();

    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion (secuencial optimizado): %.3f segundos\n", elapsed_time);

    /* Verificación simple */
    printf("C[0][0] = %.2f\n", C[0][0]);

    return 0;
}
