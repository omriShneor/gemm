#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#define N 1024
#define BLOCK 64

float A[N][N];
float B[N][N];
float C[N][N];
float EXPECTED_C[N][N];



void mat_mul(float A[N][N], float B[N][N]){
    for(int bi = 0; bi < N; bi+=BLOCK){
        for(int bj = 0; bj < N; bj += BLOCK) {
            for(int i = bi; i < bi+BLOCK; i++) {
                for(int k = 0; k < BLOCK; k++) {
                    for(int j = bj;j < bj+BLOCK; j++) {
                        C[i][j] += A[i][k]*B[k][j];
                    }
                }
            }
        }
    }
}

void load_matrix(float A[N][N], const char* filename) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
        return;

    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            fscanf(fp, "%f", A[i] + j); 
        }
    }
    return;
}

void compare_matmul(float C[N][N], float EXPECTED_C[N][N]) {
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            if (abs(C[i][j] - EXPECTED_C[i][j] > 1e-3)){
                printf("Matrix Multiplier FAILED at index: (%zu, %zu)\n", i,j);
                return;
            }
        }
    }
    return;
}


int main() {
    load_matrix(A, "A.dat");
    load_matrix(B, "B.dat");
    load_matrix(EXPECTED_C, "C.dat");
    clock_t begin = clock();
    mat_mul(A, B);
    clock_t end = clock();
    double GFLOP =  2.0 * N  * N * N * 1e-9;
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC; // The result is in seconds
    compare_matmul(C, EXPECTED_C);
    printf("Took %f seconds to multuply A and B\n", time_spent);
    printf("Number of GFLOP/S with matmul in C: %f\n", GFLOP/time_spent);
    return 0;
}