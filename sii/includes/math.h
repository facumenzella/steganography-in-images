#ifndef __MATH_H__
#define __MATH_H__

#include "constants.h"
#include "random.h"

BYTE bytePow(BYTE base, int exponent);
int intPow(int base, int exponent);
int* divideRowBy(int* row, int row_size, int value);
int multiplicativeInverse(int number);
int* substractEquations(int* equation_2, int* equation_1, int dimension);
void printRow(int* row, int size);
int* multiplyRowBy(int* row, int row_size, int value);
void identityMatrix(int** matrix, int dimension);
void printSquareMatrix(int** matrix, int dimension);
void printByteSquareMatrix(BYTE** matrix, int dimension);
int** declareEquations(int k);
BYTE** declareByteEquations(int k);
int** multiplySquareMatrices(int** matrix_1, int** matrix_2, int dimension);
BYTE** multiplyByteSquareMatrices(BYTE** matrix_1, BYTE** matrix_2, int dimension);
int** copySquareMatrix(int** matrix, int dimension);
BYTE** makeModularMatrix(int** matrix, int dimension);

#endif