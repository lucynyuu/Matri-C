#include "matriC.h"

matrix matCreate(int rows, int cols) {
    matrix A;
    A.rows = rows;
    A.cols = cols;
    A.mat = matAllocate(rows, cols);
    return A;
}

void matLoad(matrix A, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (NULL == file) {
        printf("ERROR: could not open file\n");
        exit(1);
    }

    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < A.cols; j++) {
            if (fscanf(file, "%lf", &A.mat[i][j]) != 1) {
                printf("ERROR: could not read file\n");
                exit(1);
            }
        }
    }
    fclose(file);
}

void matPrint(matrix A) {
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t e = 0; e < A.cols; e++) {
            printf("%lf", A.mat[i][e]);
            e==A.cols-1 ? printf("\n") : printf(", ");
        }
    }
}

void matfprint(matrix A, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (NULL == file) {
        printf("ERROR: could not open file\n");
        exit(1);
    }
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t e = 0; e < A.cols; e++) {
            fprintf(file, "%lf", A.mat[i][e]);
            e==A.cols-1 ? fprintf(file, "\n") : fprintf(file, " ");
        }
    }
    fclose(file);
}

double** matAllocate(int rows, int cols) {
    double **A;
    A=(double **)malloc(rows*sizeof(double *));
    for(size_t i=0;i<rows;i++)
        A[i]=(double *)malloc(cols*sizeof(double));
    return A;
}

void matReallocate(matrix A, int rows, int cols) {
    free(A.mat);
    A.mat=(double **)malloc(rows*sizeof(double *));
    for(size_t i=0;i<rows;i++)
        A.mat[i]=(double *)malloc(cols*sizeof(double));
    A.rows = rows;
    A.cols = cols;
}

matrix matFree(matrix A) {
    free(A.mat);
}

void matUnit(matrix A) {
    for(size_t i=0;i<A.rows;i++) {
        for(size_t j=0;j<A.rows;j++) {
            if(i==j)
                A.mat[i][j]=1;
            else
                A.mat[i][j]=0;
        }
    }
}

void matInvert(matrix A, matrix I) {
    double temp, **hold;
    hold = A.mat;
    for(size_t k=0;k<A.rows;k++) {
        temp=A.mat[k][k];
        for(size_t j=0;j<A.rows;j++) {
            A.mat[k][j]/=temp;
            I.mat[k][j]/=temp;
        }
        for(size_t i=0;i<A.rows;i++) {
            temp=A.mat[i][k];
            for(size_t j=0;j<A.rows;j++) {
                if(i==k)
                    break;
                A.mat[i][j]-=A.mat[k][j]*temp;
                I.mat[i][j]-=I.mat[k][j]*temp;
            }
        }
    }
    A.mat = hold;
}

matrix matMul(matrix A, matrix B) {
    matrix result = matCreate(A.rows, B.cols);
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < B.cols; j++) {
            result.mat[i][j] = 0;
            for (size_t k = 0; k < B.rows; k++) {
                result.mat[i][j] += A.mat[i][k] * B.mat[k][j];
            }
        }
    }
    return result;
}

void matZero(matrix A) {
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t e = 0; e < A.cols; e++) {
            A.mat[i][e] = 0;
        }
    }
}

matrix matSub(matrix A, matrix B) {
    matrix result = matCreate(A.rows, B.cols);
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t e = 0; e < A.cols; e++) {
            result.mat[i][e] = A.mat[i][e] - B.mat[i][e];
        }
    }
    return result;
}

matrix matAdd(matrix A, matrix B) {
    matrix result = matCreate(A.rows, B.cols);
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t e = 0; e < A.cols; e++) {
            result.mat[i][e] = A.mat[i][e] + B.mat[i][e];
        }
    }
    return result;
}

matrix matScale(matrix A, int k) {
    matrix result = matCreate(A.rows, B.cols);
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t e = 0; e < A.cols; e++) {
            result.mat[i][e] = A.mat[i][e] * k;
        }
    }
    return result;
}