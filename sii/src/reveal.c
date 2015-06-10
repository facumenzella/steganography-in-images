#include <stdio.h>
#include "../includes/reveal.h"

BYTE* lagrangeInterpolation(int* n_values, int n_size, int k, BYTE* shadows_pixel);
void initializeEquations(int** equations, int* n_values, int n_size, int k);
int** pixelCoefficients(int** equations, int dimension);
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
	int** equations = declareEquations(k);
	initializeEquations(equations, n_values, n_size, k);

	return partial_image_section_pixels;
}

void
initializeEquations(int** equations, int* n_values, int n_size, int k) {
	int i, j;
	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			equations[i][j] = intPow(n_values[i], k - j - 1);
		}
	}
}

int**
pixelCoefficients(int** equations, int dimension) { //AKA: Matrix inversion
	int** inverseMatrix = declareEquations(dimension);
	identityMatrix(inverseMatrix, dimension);
	printSquareMatrix(equations, dimension);
	int i, j, k;
	for (j = 0; j < dimension; j++) {
		for (i = dimension - 1; i >= 0; i--) {
			if (i != j && equations[i][j] != 0) {
				if (i != 0) {
					int* new_equation_i = multiplyRowBy(equations[i], dimension, equations[i-1][j]);
					int* new_inverse_i = multiplyRowBy(inverseMatrix[i], dimension, equations[i-1][j]);
					inverseMatrix[i] = substractEquations(new_inverse_i, multiplyRowBy(inverseMatrix[i-1], dimension, equations[i][j]), dimension);
					equations[i] = substractEquations(new_equation_i, multiplyRowBy(equations[i-1], dimension, equations[i][j]), dimension);
				} else {
					int* new_equations_i = multiplyRowBy(equations[i], dimension, equations[j][j]);
					int* new_inverse_i = multiplyRowBy(inverseMatrix[i], dimension, equations[j][j]);
					inverseMatrix[i] = substractEquations(new_inverse_i, multiplyRowBy(inverseMatrix[j], dimension, equations[i][j]), dimension);
					equations[i] = substractEquations(new_equations_i, multiplyRowBy(equations[j], dimension, equations[i][j]), dimension);
				}
			}
			printf("-------------------------\n");
			printSquareMatrix(equations, dimension);
			printSquareMatrix(inverseMatrix, dimension);
		}
	}
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			if (i == j) {
				inverseMatrix[i] = divideRowBy(inverseMatrix[i], dimension, equations[i][i]);
				equations[i] = divideRowBy(equations[i], dimension, equations[i][i]);
			}
			inverseMatrix[i][j] = ((BYTE) inverseMatrix[i][j]) % MAX_BYTE_VALUE;
			equations[i][j] = ((BYTE) equations[i][j]) % MAX_BYTE_VALUE;
		}
	}
	printSquareMatrix(equations, dimension);
	printSquareMatrix(inverseMatrix, dimension);
	return inverseMatrix;
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

int
main(void) {
	int** matrix = calloc(3, sizeof(int*));
	int i;
	for (i = 0; i < 3; i++) {
		matrix[i] = calloc(3, sizeof(int));
	}
	int** inverse = calloc(3, sizeof(int*));
	for (i = 0; i < 3; i++) {
		inverse[i] = calloc(3, sizeof(int));
	}
	matrix[0][0] = 1;
	matrix[0][1] = 3;
	matrix[0][2] = 3;
	matrix[1][0] = 1;
	matrix[1][1] = 4;
	matrix[1][2] = 3;
	matrix[2][0] = 1;
	matrix[2][1] = 3;
	matrix[2][2] = 4;
	inverse[0][0] = 7;
	inverse[0][1] = -3;
	inverse[0][2] = -3;
	inverse[1][0] = -1;
	inverse[1][1] = 1;
	inverse[1][2] = 0;
	inverse[2][0] = -1;
	inverse[2][1] = 0;
	inverse[2][2] = 1;
	// int** ans = pixelCoefficients(matrix, 3);
	printSquareMatrix(multiplySquareByteMatrices(inverse, matrix, 3), 3);
}