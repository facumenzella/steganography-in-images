#ifndef __MATH_H__
#define __MATH_H__

#include "constants.h"
#include "random.h"

typedef int sign;
#define POSITIVE 1
#define NEGATIVE -1
#define UP -1
#define DOWN 1

int bytePow(int base, int exponent);
int intPow(int base, int exponent);
int* divideRowBy(int* row, int row_size, int value);
int multiplicativeInverse(int number);
int* addEquations(int* equation_2, int* equation_1, int dimension, sign _sign);
void printRow(int* row, int size);
int* multiplyRowBy(int* row, int row_size, int value);
void identityMatrix(int** matrix, int dimension);
void printSquareMatrix(int** matrix, int dimension);
void printByteSquareMatrix(BYTE** matrix, int dimension);
void printByteMatrix(BYTE** matrix, int rows, int columns);
int** declareEquations(int k);
BYTE** declareGenericByteMatrix(int rows, int columns);
BYTE** declareByteEquations(int k);
BYTE** multiplyByteMatrices(BYTE** matrix_1, BYTE** matrix_2, int dim_1_i, int dim_1_j, int dim_2_i, int dim_2_j);
int** multiplySquareMatrices(int** matrix_1, int** matrix_2, int dimension);
BYTE** multiplyByteSquareMatrices(BYTE** matrix_1, BYTE** matrix_2, int dimension);
int** copySquareMatrix(int** matrix, int dimension);
BYTE** makeModularMatrix(int** matrix, int dimension);
void setValuesToIntMatrix(int** matrix, int rows, int columns, int value);
void setValuesToByteMatrix(BYTE** matrix, int rows, int columns, BYTE value);
void permutePixels(int n, BYTE* image);

#endif