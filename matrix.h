#ifndef matrix
#define matrix
#include <stdio.h>
#include <stdlib.h>

// Type that is used to store the dimensions of a matrix in a vec2
typedef struct vec2 {
    int rows;
    int cols;
}matSize;

// Reads a matrix from a specified file
void matLoad(double **A, matSize size, const char* filename);

// Prints a matrix
void matPrint(double **A, matSize size);

// Prints a matrix to a file
void matfprint(double **A, matSize size, const char* filename);

// Allocate memory that a matrix will occupie
double** matAllocate(matSize size);

// Initialize a given square matrix A into a unit matrix
void matUnit(double **A, int size);

// Invert a square matrix using Gauss Jordan algorithm
void matInvert(double **A, double **I, int size);

// Multiples two matrices A and B
double** matMul(double **A, double **B, matSize sizeA, matSize sizeB);

#endif