#include <stdlib.h>
#include "../includes/constants.h"

BYTE* reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k);
BYTE* revealPartialImage(BYTE* partial_image, int partial_image_size);

BYTE*
revealImage(int* n_values, int n_size, int k, BYTE* shadows_pixel) {
	//Repetir hasta consumir todos los bytes de las sombras
		//Agarrar el siguiente byte de cada una de las shadows
		//hacer la interpolacion de lagrange para sacar los coeficientes, voy construyendo  partial_image
	//pasar partial_image por revealPartialImage
	//revertir la permutación

	BYTE* coefficients = lagrangeInterpolation(n_values, n_size, k, shadows_pixel);
	// Acá falta la "despermutación" de todo!!
	return revealPartialImage(coefficients, k);
}


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
	identityMatrix(inverseMatrix);
	int i, j;
	for (j = 0; j < dimension; j++) {
		for (i = 0; i < dimension; i++) {
			if (i != j) {
				if (i != 0) {
					equations[i] = multiplyRowBy(equations[i], dimension, equations[i-1][j]);
					inverseMatrix[i] = multiplyRowBy(inverseMatrix[i], dimension, inverseMatrix[i-1][j]);
					equations[i] = substractEquations(equations[i], multiplyRowBy(equations[i-1], dimension, equations[i]), dimension);
				} else {
					
				}
			}
		}
	}
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
multiplyRowBy(BYTE* row, int row_size, int value) {
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
revealPartialImage(BYTE* partial_image, int partial_image_size) {
	BYTE* result = calloc(partial_image_size, sizeof(BYTE));
	int i, result_index = 0;
	for (i = 0; i < partial_image_size; i++, result_index++) {
		BYTE b = partial_image[i];
		if (b == 250) {
			BYTE following_b = partial_image[++i];
			result[result_index] = b + following_b;
		} else {
			result[result_index] = b;
		}
	}

	return realloc(result, result_index);
}