#ifndef matriC
#define matriC
#include <stdio.h>
#include <stdlib.h>

// Type that is used to store a matrix
typedef struct matrix {
    double ** mat;
    int rows;
    int cols;
} matrix;

// Creates a matrix
matrix matCreate(int rows, int cols);

// Reads a matrix from a specified file
void matLoad(matrix A, const char* filename);

// Prints a matrix
void matPrint(matrix A);

// Prints a matrix to a file
void matfprint(matrix A, const char* filename);

// Allocate memory that a matrix will occupie
double** matAllocate(int rows, int cols);

// Frees dynamically allocated matrix
matrix matFree(matrix A);

// Initialize a given square matrix A into a unit matrix
void matUnit(matrix A);

// Invert a square matrix using Gauss Jordan algorithm
void matInvert(matrix A, matrix I);

// Multiples two matrices A and B
matrix matMul(matrix A, matrix B);

#endif
