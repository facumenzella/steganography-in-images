#include <stdlib.h>
#include <stdio.h>
#include "../includes/math.h"

int
bytePow(int base, int exponent) {
	int ans = 1;
	int i;
	for (i = 0; i < exponent; i++) {
		ans = (ans % MAX_BYTE_VALUE) * base;
	}
	return ans % MAX_BYTE_VALUE;
}

int
intPow(int base, int exponent) {
	int ans = 1;
	int i;
	for (i = 0; i < exponent; i++) {
		ans *= base;
	}
	return ans;
}

int*
divideRowBy(int* row, int row_size, int value) {
	return multiplyRowBy(row, row_size, multiplicativeInverse(value));
}

int
multiplicativeInverse(int number) {
	return bytePow(number, MAX_BYTE_VALUE - 2) % MAX_BYTE_VALUE;
}

int*
addEquations(int* equation_2, int* equation_1, int dimension, sign _sign) {
	int* ans = calloc(dimension, sizeof(int));
	int i;
	for (i = 0; i < dimension; i++) {
		ans[i] = equation_2[i] + (_sign * equation_1[i]);
	}
	return ans;
}

void
printRow(int* row, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d\t", row[i]);
	}
	printf("\n");
}

int*
multiplyRowBy(int* row, int row_size, int value) {
	int i;
	int* multiplied_row = calloc(row_size, sizeof(int));
	for (i = 0; i < row_size; i++) {
		multiplied_row[i] = row[i] * value;
	}
	return multiplied_row;
}

void
identityMatrix(int** matrix, int dimension) {
	int i, j;
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			if (i == j) {
				matrix[i][j] = 1;
			}
		}
	}
}

void
printSquareMatrix(int** matrix, int dimension) {
	int i, j;
	printf("\n");
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void
printByteSquareMatrix(BYTE** matrix, int dimension) {
	int i, j;
	printf("\n");
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

int**
declareEquations(int k) {
	int** equations = calloc(k, sizeof(int*));
	int i;
	for (i = 0; i < k; i++) {
		equations[i] = calloc(k, sizeof(int));
	}
	return equations;
}

BYTE**
declareByteEquations(int k) {
	BYTE** equations = calloc(k, sizeof(BYTE*));
	int i;
	for (i = 0; i < k; i++) {
		equations[i] = calloc(k, sizeof(BYTE));
	}
	return equations;
}

int**
multiplySquareMatrices(int** matrix_1, int** matrix_2, int dimension) {
	int i, j, k;
	k = 0;
	int** ans = declareEquations(dimension);
	for (i = 0; i < dimension; i++) {
		int value_i_j = 0;
		for (j = 0; j < dimension; j++) {
			value_i_j += matrix_1[i][j] * matrix_2[j][i];
		}
		ans[i][k++] = value_i_j;
		if (k % dimension == 0) {
			k = 0;
		}
	}
	return ans;
}

BYTE**
multiplyByteSquareMatrices(BYTE** matrix_1, BYTE** matrix_2, int dimension) {
	int i, j, k;
	k = 0;
	BYTE** ans = declareByteEquations(dimension);
	for (i = 0; i < dimension; i++) {
		int value_i_j = 0;
		for (j = 0; j < dimension; j++) {
			value_i_j += matrix_1[i][j] * matrix_2[j][i];
		}
		ans[i][k++] = value_i_j % MAX_BYTE_VALUE;
		if (k % dimension == 0) {
			k = 0;
		}
	}
	return ans;
}

int**
copySquareMatrix(int** matrix, int dimension) {
	int i, j;
	int** copied_matrix = declareEquations(dimension);
	for (i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			copied_matrix[i][j] = matrix[i][j];
		}
	}
	return copied_matrix;
}

BYTE**
makeModularMatrix(int** matrix, int dimension) {
	int i, j;
	BYTE** ans = declareByteEquations(dimension);
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			int value = matrix[i][j];
			if (value < 0) {
				while (value < 0) {
					value += MAX_BYTE_VALUE;
				}
				ans[i][j] = value;
			} else {
				ans[i][j] = matrix[i][j] % MAX_BYTE_VALUE;
			}
		}
	}
	return ans;
}