#include <stdlib.h>
#include <stdio.h>
#include "../includes/reveal.h"
#include "../includes/distribution.h"
#include "../includes/math.h"
#include "../includes/random.h"

void printBytes(BYTE* bytes, int size);

int
main(int argc, char const *argv[])
{
	int imageSize = 100;
	int n = 5;
	int k = 4;

	BYTE* image = calloc(imageSize, sizeof(BYTE));

	int i;
	for (i = 1; i <= imageSize; i++) {
		image[i-1] = i;
	}

	// randomize(1);

	// permutePixels(imageSize, image);

	printBytes(image, imageSize);

	BYTE* E = convertImageToArrayWithLoss(image, imageSize);

	BYTE** shadows = createShadows(E, imageSize, n, k);

	int* n_values = calloc(k, sizeof(int));
	n_values[0] = 1;
	n_values[1] = 3;
	n_values[2] = 4;
	n_values[3] = 5;

	BYTE** selectedShadows = calloc(k, sizeof(BYTE*));
	selectedShadows[0] = shadows[0];
	selectedShadows[1] = shadows[2];
	selectedShadows[2] = shadows[3];
	selectedShadows[3] = shadows[4];
	// selectedShadows[3] = shadows[4];

	// BYTE* revealImage(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size, int seed)

	BYTE* result = revealImage(n_values, k, k, selectedShadows, imageSize/k, 1);

	// permutePixels(imageSize, result);

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