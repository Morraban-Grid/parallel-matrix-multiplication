#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500
#define BLOCK_SIZE 32

double A[N][N];
double B[N][N];
double C[N][N];

/*
 * Inicialización de matrices:
 * A -> matriz identidad
 * B -> valores constantes dependientes de la fila
 * C -> matriz resultado inicializada en cero
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

/*
 * Multiplicación secuencial de matrices
 * utilizando bloqueo para mejorar la localidad de caché
 */
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

/*
 * Validación básica del resultado:
 * Dado que A es identidad, el resultado C debe ser igual a B
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
        printf("Validacion: CORRECTA (C = B)\n");
    else
        printf("Validacion: ERROR en el resultado\n");
}

int main() {
    clock_t start, end;
    double elapsed_time;

    init_matrices();

    start = clock();
    multiply_blocked();
    end = clock();

    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion (secuencial base): %.3f segundos\n", elapsed_time);
    printf("C[0][0] = %.2f | B[0][0] = %.2f\n", C[0][0], B[0][0]);

    validate_result();

    return 0;
}
