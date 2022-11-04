#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 1024

double** load_mat(char* file_name) {
    /*Allocate N rows*/
    double** mat= malloc(N*sizeof(double*));
    
    // For each row allocate N columns
    for(int i=0;i<N;++i)
        mat[i]=malloc(N*sizeof(double));


    FILE *file;
    file=fopen(file_name, "r");

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            if (!fscanf(file, "%lf", &mat[i][j])) 
                break;
        }
    }
    fclose(file);
    return mat;
}

double** matmul(double** A, double** B) {
    /*Allocate N rows*/
    double** mat= malloc(N*sizeof(double*));
    
    // For each row allocate N columns
    for(int i=0;i<N;++i)
        mat[i]=malloc(N*sizeof(double));


    // Compute Matmul
    for(int i = 0; i < N; ++i) {
        for(int j=0; j < N; ++j){
            mat[i][j] = 0;
            for(int k = 0; k < N; ++k){
                mat[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return mat;
}

void compare_matmul(double** mat1, double** mat2) {
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (fabs(mat1[i][j] - mat2[i][j]) > 1e-3) {
                printf("MISMATCH AT i: %d, j %d, mat1: %lf, mat2: %lf \n", i, j , mat1[i][j], mat2[i][j]);
            }
        }
    }
    printf("MATCH!\n");
}

void free_mat(double** mat) {
    for(int i = 0; i < N; ++i) {
        free(mat[i]);
    }
    free(mat);
}

int main(int argc, char** argv) {
    double** A = load_mat("A.txt");
    double** B = load_mat("B.txt");
    double** C = load_mat("C.txt");

    clock_t t1 = clock();
    double** res = matmul(A, B);
    clock_t t2 = clock();
    double s = (double)(t2 - t1) / CLOCKS_PER_SEC;
    double GFLOPS = (N * N * 2.0 * N)*1e-9;
    printf("GFLOP/S: %lf, %lf ms\n", GFLOPS/s, s*1e3);
    compare_matmul(res, C);
    free(A);
    free(B);
    free(C);
}