#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 2

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

double** naive_matmul(double** A, double** B) {
    /*Allocate N rows*/
    double** mat= malloc(N*sizeof(double*));
    
    // For each row allocate N columns
    for(int i=0;i<N;++i)
        mat[i]=malloc(N*sizeof(double));

    // for(int i = 0; i < N; ++i) {
    //     for(int j = 0; j < N; ++j) {
    //         for(int k = 0; k < N; ++k) {
    //             mat[i][j] += A[i][k] * B[k][j];
    //         }
    //     }
    // }
    return mat;
}


void compare_matmul(double** mat1, double** mat2) {
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (fabs(mat1[i][j] - mat2[i][j]) > 1e-4) {
                printf("MISMATCH AT i: %d, j %d, mat1: %lf, mat2: %lf \n", i, j , mat1[i][j], mat2[i][j]);
            }
        }
    }
    printf("MATCH!\n");
}

int main(int argc, char** argv) {
    double** A = load_mat("A.txt");
    double** B = load_mat("B.txt");
    double** C = load_mat("B.txt");
    double** res = naive_matmul(A, B);
    compare_matmul(res, A);
}