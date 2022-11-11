#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define N 4096
#define BLOCK 1

float A[N][N];
float B[N][N];
float C[N][N];

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


float time_diff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec-start->tv_sec) + 1e-6*(end->tv_usec-start->tv_usec);
}

void mat_mul(float A[N][N], float B[N][N]) {
    // for(int bi = 0; bi < N; bi+=BLOCK){
    //     for(int bj = 0; bj < N; bj += BLOCK) {
    for(int i = 0; i < N; i++) {
        for(int k = 0; k < N; k++) {
            for(int j = 0;j < N; j++) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    //     }
    // }
}

void generate_metrices() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = (double) random() / (double) RAND_MAX; // Generate number between 0,1
            B[i][j] = (double) random() / (double) RAND_MAX;
            C[i][j] = 0;
        }
    }
}


int main() {
    generate_metrices();
    struct timeval start, end;
    gettimeofday(&start, NULL);
    mat_mul(A, B);
    gettimeofday(&end, NULL);
    float time_spent = time_diff(&start, &end);
    double GFLOPS =  2.0 * N  * N * N * 1e-9;
    printf("Took %0.6f seconds to multuply A and B\n", time_spent);
    printf("Number of GFLOP/S with matmul in C: %f\n", GFLOPS/time_spent);
    return 0;
}