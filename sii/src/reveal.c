#include <stdlib.h>
#include "../includes/constants.h"

BYTE* lagrangeInterpolation(int* n_values, int n_size, int k, BYTE* shadows_pixel);
BYTE** declareEquations(int k);
BYTE** initializeEquations(BYTE** equations, int n, int k);
BYTE** pixelCoefficients(BYTE** equations, int dimension);
BYTE* divideRowBy(BYTE* row, int row_size, BYTE value);
BYTE multiplicativeInverse(BYTE number);
BYTE* substractEquations(BYTE* equation_2, BYTE* equation_1, int dimension);
BYTE* multiplyRowBy(BYTE* row, int row_size, BYTE value);
void identityMatrix(BYTE** matrix, int dimension);
BYTE* reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k);

BYTE*
lagrangeInterpolation(int* n_values, int n_size, int k, BYTE* shadows_pixel) {
	BYTE* partial_image_section_pixels = calloc(k, sizeof(BYTE));
	BYTE** equations = declareEquations(k);
	initializeEquations(equations, n_size, k);

	return partial_image_section_pixels;
}

BYTE**
declareEquations(int k) {
	BYTE** equations = calloc(k, sizeof(BYTE*));
	int i;
	for (i = 0; i < k; i++) {
		equations[i] = calloc(k, sizeof(BYTE));
	}
	return equations;
}

BYTE**
initializeEquations(BYTE** equations, int n, int k) {
	int i, j;
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			
		}
	}
}

BYTE**
pixelCoefficients(BYTE** equations, int dimension) { //AKA: Matrix inversion
	BYTE** inverseMatrix = declareEquations(dimension);
	identityMatrix(inverseMatrix, dimension);
	int i, j;
	for (j = 0; j < dimension; j++) {
		for (i = 0; i < dimension; i++) {
			if (i != j) {
				if (i != 0) {
					equations[i] = multiplyRowBy(equations[i], dimension, equations[i-1][j]);
					inverseMatrix[i] = multiplyRowBy(inverseMatrix[i], dimension, inverseMatrix[i-1][j]);
					equations[i] = substractEquations(equations[i], multiplyRowBy(equations[i-1], dimension, equations[i][j]), dimension);
				} else {
					if (j != 0) {
						equations[i] = multiplyRowBy(equations[i], dimension, equations[i+1][j]);
						inverseMatrix[i] = multiplyRowBy(inverseMatrix[i], dimension, inverseMatrix[i+1][j]);
						equations[i] = substractEquations(equations[i], multiplyRowBy(equations[i+1], dimension, equations[i][j]), dimension);
					}
				}
			}
		}
	}
	i = 0;
	for (i = 0; i < dimension; i++) {
		inverseMatrix[i] = divideRowBy(inverseMatrix[i], dimension, inverseMatrix[i][i]);
	}
	return inverseMatrix;
}

BYTE*
divideRowBy(BYTE* row, int row_size, BYTE value) {
	multiplyRowBy(row, row_size, multiplicativeInverse(value));
}

// bytePow() está en distribution.c. Quizás haya que extraer el código a una librería más general.
BYTE
multiplicativeInverse(BYTE number) {
	return bytePow(number, MAX_BYTE_VALUE - number) % MAX_BYTE_VALUE;
}

BYTE*
substractEquations(BYTE* equation_2, BYTE* equation_1, int dimension) {
	BYTE* substracted_equation = calloc(dimension, sizeof(BYTE));
	int i;
	for (i = 0; i < dimension; i++) {
		substracted_equation[i] = equation_2[i] - equation_1[i];
	}
	return substracted_equation;
}

BYTE*
multiplyRowBy(BYTE* row, int row_size, BYTE value) {
	int i;
	BYTE* multiplied_row = calloc(row_size, sizeof(BYTE));
	for (i = 0; i < row_size; i++) {
		multiplied_row[i] = row[i] * value;
	}
	return multiplied_row;
}

void
identityMatrix(BYTE** matrix, int dimension) {
	int i, j;
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			if (i == j) {
				matrix[i][j] = 1;
			}
		}
	}
}

BYTE*
reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k) {
	BYTE* image = calloc(partial_image_size, sizeof(BYTE)); //La imagen tendrá un 
	int i, j = 0;																					//tamaño k por el tamaño
	while(i < partial_image_size) {												// de la sombra, por 2,
		if (partial_image[i] < 250) {												//en el caso de que cada
			image[j++] = partial_image[i++];									// pixel sea >= a 250.
		} else {
			image[j++] = partial_image[i] + partial_image[i+1];
			i+=2;
		}
	}
	image = realloc(image, j);	//Comprimo la imagen borrando el espacio sobrante
	return image;								//allocado inicialmente como partial_image_size.
}