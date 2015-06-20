#include <stdlib.h>
#include <stdio.h>
#include "../includes/reveal.h"

BYTE*
revealImage(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size, int seed) {
	int i, j, l, partial_image_index;
	BYTE** shadows_i_pixels = declareGenericByteMatrix(n_size, 1);
	BYTE* partial_image = calloc(k * shadow_size, sizeof(BYTE));
	long partial_image_size;
	BYTE** inverseMatrix;
	BYTE** coefficients;
	int** equations = declareEquations(k);
	partial_image_index = 0;
	initializeEquations(equations, n_values, n_size, k);
	inverseMatrix = makeModularMatrix(gaussJordanEliminationMethod(equations, n_size), n_size);
	for (j = 0; j < shadow_size; j++) {
		for (i = 0; i < n_size; i++) {
			shadows_i_pixels[i][0] = shadows_pixels[i][j];
		}
		coefficients = multiplyByteMatrices(inverseMatrix, shadows_i_pixels, n_size, n_size, n_size, 1); // Se supone que a esta altura, n = k par que quede la matriz cuadrada.
		for (l = 0; l < k; l++) {
			partial_image[partial_image_index + l] = coefficients[l][0];
		}
		partial_image_index += l;
		setValuesToByteMatrix(shadows_i_pixels, n_size, 0, 0);
	}
	// randomize(5);
 	// int permuted_image_size;
 	// Si está prendido el flag de revelar la imagen sin pérdida, entonces
 	// llamamos a la función de abajo!!!
 	// BYTE* image = revealPartialImageWithoutLoss(partial_image, partial_image_index);
 	//permutePixels(partial_image_index, partial_image);
 	// TENEMOS QUE DEVOLVER EL TAMAÑO DE LA NUEVA IMAGEN??? O ESO SE ENCUENTRA EN LAS SOMBRAS???
 	return partial_image;
 }

void
initializeEquations(int** equations, int* n_values, int n_size, int k) {
	int i, j;
	for (i = 0; i < n_size; i++) {
		for (j = 0; j < k; j++) {
			equations[i][j] = intPow(n_values[i], j);
		}
	}
}

int**
gaussJordanEliminationMethod(int** equations, int dimension) { //AKA: Matrix inversion
	int** inverseMatrix = declareEquations(dimension);
	int** copied_equations = copySquareMatrix(equations, dimension);
	identityMatrix(inverseMatrix, dimension);
	int i;
	for (i = 0; i < dimension; i++) {
		eliminateValuesAtColumn(copied_equations, inverseMatrix, dimension, i);
	}
	return inverseMatrix;
}

void
eliminateValuesAtColumn(int** equations, int** inverse, int dimension, int pivot) {
	if (equations[pivot][pivot] != 1){
		inverse[pivot] = divideRowBy(inverse[pivot], dimension, equations[pivot][pivot]);
		equations[pivot] = divideRowBy(equations[pivot], dimension, equations[pivot][pivot]);
	}
	eliminateValues(equations, inverse, dimension, pivot, UP);
	eliminateValues(equations, inverse, dimension, pivot, DOWN);
}

void
eliminateValues(int** equations, int** inverse, int dimension, int pivot, int direction) {
	int i = pivot + direction;
	while(i >= 0 && i < dimension) {
		if (equations[i][pivot] != 0) {
			inverse[i] = addEquations(inverse[i], multiplyRowBy(inverse[pivot], dimension, equations[i][pivot]), dimension, NEGATIVE);
			equations[i] = addEquations(equations[i], multiplyRowBy(equations[pivot], dimension, equations[i][pivot]), dimension, NEGATIVE);
		}
		makeModularIntMatrix(equations, dimension);
		makeModularIntMatrix(inverse, dimension);
		i += direction;
	}
}

BYTE*
revealPartialImageWithoutLoss(BYTE* partial_image, int partial_image_size, int* permuted_image_size) {
	BYTE* result = calloc(partial_image_size*2, sizeof(BYTE));
	int i, result_index = 0;
	for (i = 0; i < partial_image_size; i++, result_index++) {
		BYTE b = partial_image[i];
		if (b == MAX_BYTE_VALUE - 1) {
			BYTE following_b = partial_image[++i];
			result[result_index] = b + following_b;
		} else {
			result[result_index] = b;
		}
	}
	*permuted_image_size = result_index;
	return realloc(result, result_index);
}

// int
// main(void) {
// 	// http://www.wolframalpha.com/widgets/view.jsp?id=2de311966212471dec23077dd840840d
// 	// http://www.gregthatcher.com/Mathematics/GaussJordan.aspx
// 	BYTE** matrix = calloc(3, sizeof(BYTE*));
// 	int i;
// 	for (i = 0; i < 3; i++) {
// 		matrix[i] = calloc(3, sizeof(BYTE));
// 	}
// 	BYTE** results = calloc(3, sizeof(BYTE*));
// 	for (i = 0; i < 3; i++) {
// 		results[i] = calloc(1, sizeof(BYTE));
// 	}
// 	matrix[0][0] = 2;
// 	matrix[0][1] = 249;
// 	matrix[0][2] = 1;
// 	matrix[1][0] = 208;
// 	matrix[1][1] = 128;
// 	matrix[1][2] = 166;
// 	matrix[2][0] = 42;
// 	matrix[2][1] = 125;
// 	matrix[2][2] = 84;
// 	results[0][0] = 135;
// 	results[1][0] = 243;
// 	results[2][0] = 46;
// 	// printSquareMatrix(matrix, 3);
// 	// int** ans = gaussJordanEliminationMethod(matrix, 3);
// 	// printf("A:\n");
// 	// printSquareMatrix(matrix, 3);
// 	// printf("Results:\n");
// 	// printByteMatrix(results, 3, 1);
// 	// printf("\nA^-1:\n");
// 	// BYTE** modular_ans = makeModularMatrix(ans, 3);
// 	// printByteSquareMatrix(modular_ans, 3);
// 	// printf("\nA*A^-1:\n");
// 	// printByteSquareMatrix(multiplyByteSquareMatrices(makeModularMatrix(ans, 3), makeModularMatrix(matrix, 3), 3), 3);
// 	// printf("COEFFICIENTS (A^-1*Results):\n");
// 	printByteMatrix(multiplyByteMatrices(matrix, results, 3, 3, 3, 1), 3, 1);
// }