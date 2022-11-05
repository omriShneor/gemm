#include <stdlib.h>
#include <stdio.h>
#define N 16

float A[N][N];
float B[N][N];
float C[N][N];

void mat_mul(float A[N][N], float B[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k]*B[k][j];
            }
            printf("%f ", C[i][j]);
        } 
    }
}






int main() {
    mat_mul(A, B);
    return 0;
}