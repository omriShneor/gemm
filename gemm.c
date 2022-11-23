#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define N 4096
#define BLOCK 1

float A[N][N];
float B[N][N];
float C[N][N];



float time_diff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec-start->tv_sec) + 1e-6*(end->tv_usec-start->tv_usec);
}

void mat_mul(float A[N][N], float B[N][N]) {
    // for(int bi = 0; bi < N; bi+=BLOCK){
    //     for(int bj = 0; bj < N; bj += BLOCK) {
    for(int i = 0; i < N; i++) {
    for(int j = 0;j < N; j++) {
    for(int k = 0; k < N; k++) {
    
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