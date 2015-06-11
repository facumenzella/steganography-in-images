#include <stdlib.h>
#include <stdio.h>
#include "../includes/reveal.h"

BYTE* lagrangeInterpolation(int* n_values, int n_size, int k, BYTE* shadows_pixel);
void initializeEquations(int** equations, int* n_values, int n_size, int k);
int** gaussJordanElliminationMethod(int** equations, int dimension);
BYTE* reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k);
BYTE* revealPartialImage(BYTE* partial_image, int partial_image_size);
void elliminateValuesAtColumn(int** equation, int** inverse, int dimension, int pivot);
void elliminateValues(int** equation, int** inverse, int dimension, int pivot, int direction);

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
gaussJordanElliminationMethod(int** equations, int dimension) { //AKA: Matrix inversion
	int** inverseMatrix = declareEquations(dimension);
	int** copied_equations = copySquareMatrix(equations, dimension);
	identityMatrix(inverseMatrix, dimension);
	int i;
	for (i = 0; i < dimension; i++) {
		elliminateValuesAtColumn(copied_equations, inverseMatrix, dimension, i);
	}
	return inverseMatrix;
}

void
elliminateValuesAtColumn(int** equations, int** inverse, int dimension, int pivot) {
	if (equations[pivot][pivot] != 1){
		inverse[pivot] = divideRowBy(inverse[pivot], dimension, equations[pivot][pivot]);
		equations[pivot] = divideRowBy(equations[pivot], dimension, equations[pivot][pivot]);
	}
	elliminateValues(equations, inverse, dimension, pivot, UP);
	elliminateValues(equations, inverse, dimension, pivot, DOWN);
}

void
elliminateValues(int** equations, int** inverse, int dimension, int pivot, int direction) {
	int i = pivot + direction;
	while(i >= 0 && i < dimension) {
		if (equations[i][pivot] != 0) {
			inverse[i] = addEquations(inverse[i], multiplyRowBy(inverse[pivot], dimension, equations[i][pivot]), dimension, NEGATIVE);
			equations[i] = addEquations(equations[i], multiplyRowBy(equations[pivot], dimension, equations[i][pivot]), dimension, NEGATIVE);
		}
		i += direction;
	}
}

BYTE*
revealPartialImage(BYTE* partial_image, int partial_image_size) {
	BYTE* result = calloc(partial_image_size, sizeof(BYTE));
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
	return realloc(result, result_index);
}

int
main(void) {
	// http://www.wolframalpha.com/widgets/view.jsp?id=2de311966212471dec23077dd840840d
	// http://www.gregthatcher.com/Mathematics/GaussJordan.aspx
	int** matrix = calloc(3, sizeof(int*));
	int i;
	for (i = 0; i < 3; i++) {
		matrix[i] = calloc(3, sizeof(int));
	}
	BYTE** results = calloc(3, sizeof(BYTE*));
	for (i = 0; i < 3; i++) {
		results[i] = calloc(1, sizeof(BYTE));
	}
	matrix[0] = calloc(3, sizeof(int));
	matrix[0][0] = 1;
	matrix[0][1] = 1;
	matrix[0][2] = 1;
	matrix[1][0] = 4;
	matrix[1][1] = 2;
	matrix[1][2] = 1;
	matrix[2][0] = 9;
	matrix[2][1] = 3;
	matrix[2][2] = 1;
	results[0][0] = 83;
	results[1][0] = 123;
	results[2][0] = 147;
	printSquareMatrix(matrix, 3);
	int** ans = gaussJordanElliminationMethod(matrix, 3);
	printf("A:\n");
	printSquareMatrix(matrix, 3);
	printf("Results:\n");
	printByteMatrix(results, 3, 1);
	printf("\nA^-1:\n");
	BYTE** modular_ans = makeModularMatrix(ans, 3);
	printByteSquareMatrix(modular_ans, 3);
	printf("\nA*A^-1:\n");
	printByteSquareMatrix(multiplyByteSquareMatrices(makeModularMatrix(ans, 3), makeModularMatrix(matrix, 3), 3), 3);
	printf("COEFFICIENTS (A^-1*Results):\n");
	printByteMatrix(multiplyByteMatrices(modular_ans, results, 3, 3, 3, 1), 3, 1);
}