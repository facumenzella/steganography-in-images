#include <stdlib.h>
#include <stdio.h>
#include "../includes/math.h"
#include "../includes/random.h"

int* createArrayWithSequentialNumbers(int array_size);
BYTE* copyByteArray(BYTE* array, int size);
int* generateShuffledArray(int size);

void
shufflePixels(int image_size, BYTE* image) {
	int i;
	int* image_pixel_indexes = generateShuffledArray(image_size);
	BYTE* copied_image = copyByteArray(image, image_size);
//	printRow(image_pixel_indexes, image_size);
	for (i = 0; i < image_size; i++) {
		image[i] = copied_image[image_pixel_indexes[i]];
	}
}

void
unshufflePixels(int image_size, BYTE* image) {
	int i;
	int* image_pixel_indexes = generateShuffledArray(image_size);
//	printRow(image_pixel_indexes, image_size);
	BYTE* unshuffledimage = calloc(image_size, sizeof(BYTE));
	BYTE* copied_image = copyByteArray(image, image_size);
	for (i = 0; i < image_size; i++) {
		image[image_pixel_indexes[i]] = copied_image[i];
	}
}

int*
generateShuffledArray(int size) {
	int i;
	int pivot;
	int* shuffled_array = createArrayWithSequentialNumbers(size);
	for (i = size - 1; i > 0; i--) {
		long int random = getRandom(i);
		pivot = shuffled_array[random];
		shuffled_array[random] = shuffled_array[i];
		shuffled_array[i] = pivot;
	}
	return shuffled_array;
}

BYTE*
copyByteArray(BYTE* array, int size) {
	int i;
	BYTE* copy = calloc(size, sizeof(BYTE));
	for (i = 0; i < size; i++) {
		copy[i] = array[i];
	}
	return copy;
}

int*
createArrayWithSequentialNumbers(int array_size) {
	int* array = calloc(array_size, sizeof(int));
	int i;
	for(i = 0; i < array_size; i++) {
		array[i] = i;
	}
	return array;
}

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
printMatrix(int** matrix, int rows, int columns) {
	int i, j;
	printf("\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void
printSquareMatrix(int** matrix, int dimension) {
	printMatrix(matrix, dimension, dimension);
}

void
printByteSquareMatrix(BYTE** matrix, int dimension) {
	printByteMatrix(matrix, dimension, dimension);
}

void
setValuesToByteMatrix(BYTE** matrix, int rows, int columns, BYTE value) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			matrix[i][j] = value;
		}
	}
}

void
setValuesToIntMatrix(int** matrix, int rows, int columns, int value) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			matrix[i][j] = value;
		}
	}
}

void
printByteMatrix(BYTE** matrix, int rows, int columns) {
	int i, j;
	printf("\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
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

BYTE**
declareGenericByteMatrix(int rows, int columns) {
	int i;
	BYTE** ans = calloc(rows, sizeof(BYTE*));
	for (int i = 0; i < rows; i++) {
		ans[i] = calloc(columns, sizeof(BYTE));
	}
	return ans;
}

BYTE**
multiplyByteMatrices(BYTE** matrix_1, BYTE** matrix_2, int dim_1_i, int dim_1_j, int dim_2_i, int dim_2_j) {
	int i, j, k, value_i_k;
	BYTE** ans = declareGenericByteMatrix(dim_1_i, dim_2_j);
	for (i = 0; i < dim_1_i; i++) {
		k = 0;
		while(k < dim_2_j) {
			value_i_k = 0;
			for (j = 0; j < dim_1_j; j++) {
				value_i_k += matrix_1[i][j] * matrix_2[j][k];
			}
			ans[i][k] = value_i_k % MAX_BYTE_VALUE;
			k++;
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
	int i, j, value;
	BYTE** ans = declareByteEquations(dimension);
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			value = matrix[i][j];
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

void
makeModularIntMatrix(int** matrix, int dimension) {
	int i, j, value;
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			value = matrix[i][j];
			if (value < 0) {
				while (value < 0) {
					value += MAX_BYTE_VALUE;
				}
				matrix[i][j] = value;
			} else {
				matrix[i][j] = matrix[i][j] % MAX_BYTE_VALUE;
			}
		}
	}
}