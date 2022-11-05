#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define N 16

float A[N][N];
float B[N][N];
float C[N][N];
float EXPECTED_C[N][N];

void mat_mul(float A[N][N], float B[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k]*B[k][j];
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
            if (abs(C[i][j] - EXPECTED_C[i][j] > 1e-4)){
                printf("Matrix Multiplier FAILED at index: (%zu, %zu)", i,j);
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
    mat_mul(A, B);
    printf("SUCCESS");
    return 0;
}