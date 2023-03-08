#include "matrix.h"

void matLoad(double **A, matSize size, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (NULL == file) {
        printf("ERROR: could not open file\n");
        exit(1);
    }

    for (size_t i = 0; i < size.rows; i++) {
        for (size_t j = 0; j < size.cols; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                printf("ERROR: could not read file\n");
                exit(1);
            }
        }
    }
    fclose(file);
}

void matPrint(double **A, matSize size) {
    for (size_t i = 0; i < size.rows; i++) {
        for (size_t e = 0; e < size.cols; e++) {
            printf("%lf", A[i][e]);
            e==size.cols-1 ? printf("\n") : printf(", ");
        }
    }
}

void matfprint(double **A, matSize size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (NULL == file) {
        printf("ERROR: could not open file\n");
        exit(1);
    }
    for (size_t i = 0; i < size.rows; i++) {
        for (size_t e = 0; e < size.cols; e++) {
            fprintf(file, "%lf", A[i][e]);
            e==size.cols-1 ? fprintf(file, "\n") : fprintf(file, " ");
        }
    }
    fclose(file);
}

double** matAllocate(matSize size) {
    double **A;

    A=(double **)malloc(size.rows*sizeof(double *));
    for(size_t i=0;i<size.rows;i++) {
        A[i]=(double *)malloc(size.cols*sizeof(double));
    }
    return A;
}

void matUnit(double **A, int size) {
    for(size_t i=0;i<size;i++) {
        for(size_t j=0;j<size;j++) {
            if(i==j) {
                A[i][j]=1;
            } else {
                A[i][j]=0;
            }
        }
    }
}

void matInvert(double **A, double **I, int size) {
    double temp, **hold;
    hold = A;
    for(size_t k=0;k<size;k++) {
        temp=A[k][k];
        for(size_t j=0;j<size;j++) {
            A[k][j]/=temp;
            I[k][j]/=temp;
        }
        for(size_t i=0;i<size;i++) {
            temp=A[i][k];
            for(size_t j=0;j<size;j++) {
                if(i==k)
                    break;
                A[i][j]-=A[k][j]*temp;
                I[i][j]-=I[k][j]*temp;
            }
        }
    }
    A = hold;
}

double** matMul(double **A, double **B, matSize sizeA, matSize sizeB) {
    double **result;
    matSize resultSize;
    resultSize.rows = sizeA.rows;
    resultSize.cols = sizeB.cols;
    result = matAllocate(resultSize);
    for (size_t i = 0; i < sizeA.rows; i++) {
        for (size_t j = 0; j < sizeB.cols; j++) {
            result[i][j] = 0;
            for (size_t k = 0; k < sizeB.rows; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}