#include <stdlib.h>
#include <stdio.h>
#include "../includes/reveal.h"
#include "../includes/distribution.h"
#include "../includes/math.h"
#include "../includes/random.h"

void printBytes(BYTE* bytes, int size);
BYTE** distribute2(BYTE *image, int image_size, int n, int k);
BYTE* revealImage2(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size);

BYTE**
distribute2(BYTE *image, int image_size, int n, int k) {
    BYTE *E = convertImageToArrayWithLoss(image, image_size);
    BYTE **shadows = createShadows(E, image_size, n, k);
    return shadows;
}

BYTE*
revealImage2(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size) {
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
    return partial_image;
}

int
main(int argc, char const *argv[])
{
	// int imageSize = 262144;
	int imageSize = 1024;
	int n = 8;
	int k = 8;

	BYTE* image = calloc(imageSize, sizeof(BYTE));

	int i;
	for (i = 1; i <= imageSize; i++) {
		image[i-1] = i % 251;
	}

	// randomize(1);

	// printf("PERMUTANDO...\n");
	//shufflePixels(imageSize, image);

	printf("Imagen original:");
	printBytes(image, imageSize);

	BYTE** shadows = distribute2(image, imageSize, n, k);

	int* n_values = calloc(k, sizeof(int));
	n_values[0] = 1;
	n_values[1] = 2;
	n_values[2] = 3;
	n_values[3] = 4;
	n_values[4] = 5;
	n_values[5] = 6;
	n_values[6] = 7;
	n_values[7] = 8;
	
	BYTE** selectedShadows = calloc(k, sizeof(BYTE*));
	selectedShadows[0] = shadows[0];
	selectedShadows[1] = shadows[1];
	selectedShadows[2] = shadows[2];
	selectedShadows[3] = shadows[3];
	selectedShadows[4] = shadows[4];
	selectedShadows[5] = shadows[5];
	selectedShadows[6] = shadows[6];
	selectedShadows[7] = shadows[7];

	BYTE* result = revealImage2(n_values, n, k, selectedShadows, imageSize/k);

	printBytes(result, imageSize);

	return 0;
}

void
printBytes(BYTE* bytes, int size) {
	int i;
	printf("\n");
	for (i = 0; i < size; i++) {
		printf("%d ", bytes[i]);;
	}
	printf("\n");
}