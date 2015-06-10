#include "../includes/math.h"

BYTE
bytePow(BYTE base, int exponent) {
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
divideRowBy(int* row, int row_size, BYTE value) {
	return multiplyRowBy(row, row_size, multiplicativeInverse(value));
}

BYTE
multiplicativeInverse(BYTE number) {
	return bytePow(number, MAX_BYTE_VALUE - 2) % MAX_BYTE_VALUE;
}

int*
substractEquations(int* equation_2, int* equation_1, int dimension) {
	int* substracted_equation = calloc(dimension, sizeof(int));
	int i;
	for (i = 0; i < dimension; i++) {
		substracted_equation[i] = equation_2[i] - equation_1[i];
	}
	return substracted_equation;
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
multiplyRowBy(int* row, int row_size, BYTE value) {
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

int**
declareEquations(int k) {
	int** equations = calloc(k, sizeof(int*));
	int i;
	for (i = 0; i < k; i++) {
		equations[i] = calloc(k, sizeof(int));
	}
	return equations;
}

int**
multiplySquareByteMatrices(int** matrix_1, int** matrix_2, int dimension) {
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