#include <stdlib.h>
#include "../includes/distribution.h"
#include "../includes/math.h"

BYTE* convertImageToArrayWithoutLoss(BYTE* image, int image_size);
void permutePixels(int n, BYTE* image);
BYTE** createLosslessShadows(unsigned char* image, int image_size, int n, int k);
void evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k);
BYTE bytePow(BYTE base, int exponent);
BYTE ** initializeShadows(int image_size, int n, int k);

void
distribute(Parameters parameters, main_error *err) {
	char *file_name = getSecret(parameters);
	BMPImage bmp = loadImage(file_name, err);
	BYTE *image = getBMPImage(bmp);
	char *directory = getDirectory(parameters);
	int image_size = getImageSize(bmp);
	int n = getTotalShadows(parameters);
	int k = getMinShadows(parameters);

/* step 1 - Use a key to generate a permutation sequence to permute the pixels
of the secret image.
*/
	permutePixels(n, image);

	/* step 2 - Sequentially read in gray values of D* and then store in E according to the rule below.
	For each read-in gray value pi of D* :
		2.1. If pi<=250; then store pi in E:
		2.2. If pi>250; then split pi into two values 250 and (pi - 250).
		Store these two values in E (first 250, then pi - 250).
	*/
	BYTE *E = convertImageToArrayWithoutLoss(image, image_size);

	BMPImage *shadowImages = loadImages(directory, n, err);
	if (*err || shadowImages == NULL) {
		d_printf("%s\n", *err);
		return; // we fucked up.
	}
	// we are cool, so we continue
	BYTE **shadows = createLosslessShadows(E, image_size, n, k);
	// TODO save shadows
}

BYTE*
convertImageToArrayWithoutLoss(BYTE* image, int image_size) {
	BYTE* converted_image = calloc(image_size, sizeof(BYTE));
	int i, j = 0;
	for (i = 0; i < image_size; i++) {
		if (image[i] >= 250) {
			converted_image[j++] = 250;
			converted_image[j++] = image[i] - 250;
		} else {
			converted_image[j++] = image[i];
		}
	}
	return converted_image;
}

void
permutePixels(int n, BYTE* image) {
	int i;
	for (i = n - 1; i > 0; i--) {
		long int random = getRandom(i);
		BYTE pivot = image[random];
		image[random] = image[i];
		image[i] = pivot;
	}
}

BYTE**
createLosslessShadows(unsigned char* image, int image_size, int n, int k) {
	int shadow_pixel_index = 0;
	// step 3 - Sequentially, take r not-shared-yet elements of the array E to form an r-pixel section.
	BYTE* section = calloc(k, sizeof(BYTE));
	BYTE** shadows = initializeShadows(image_size, n, k);
		int i;

	// step 5 - Repeat Steps 3 and 4 until all elements of the array E are processed.
	for (i = 0; i < sizeof(image); i++) {
		if (i % k == 0) {
			// step 4 - Generate n pixels for the n shadow images
			evaluateSection(section, shadows, shadow_pixel_index, n, k);
			shadow_pixel_index++;
			memset(section, 0, k);
		}
		section[i % k] = image[i];
	}
	return shadows;
}

void
evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k) {
	int i, j;
	for (i = 1; i <= n; i++) {
		BYTE ans = 0;
		for (j = 0; j < k; j++) {
			ans += bytePow(i, j);
		}
		shadows[i-1][shadow_pixel_index] = ans%MAX_BYTE_VALUE;
	}
}

BYTE **
initializeShadows(int image_size, int n, int k) {
	BYTE** shadows = calloc(n, sizeof(BYTE *));
	int shadow_size = image_size/k;
	int i = 0;
	for (i = 0; i < n; ++i) {
		shadows[i] = calloc(shadow_size, sizeof(BYTE));
	}
	return shadows;
}
