#include <stdlib.h>
#include "../includes/distribution.h"

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
	int image_size = getImageSize(bmp);
	int n = getTotalShadows(parameters);
	int k = getMinShadows(parameters);

/* step 1 - Use a key to generate a permutation sequence to permute the pixels
of the secret image.
*/
	permutePixels(n, image);

	/* step 2 - Sequentially read in gray values of D* and then store in E according to the rule below.
	For each read-in gray value pi of D* :
		2.1. If pio250; then store pi in E:
		2.2. If piX250; then split pi into two values 250 and (pi - 250).
		Store these two values in E (first 250, then pi - 250).
	*/
	BYTE *E = convertImageToArrayWithoutLoss(image, image_size);

	// step 3 - Sequentially, take r not-shared-yet elements of the array E to form an r-pixel section.
	// step 4 - Generate n pixels for the n shadow images.
	// step 5 - Repeat Steps 3 and 4 until all elements of the array E are processed.
	BYTE **shadows = createLosslessShadows(E, image_size, n, k);

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
	BYTE* section = calloc(k, sizeof(BYTE));
	BYTE** shadows = initializeShadows(image_size, n, k);
		int i;
	for (i = 0; i < sizeof(image); i++) {
		if (i % k == 0) {
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
		shadows[i-1][shadow_pixel_index] = ans % MAX_BYTE_VALUE;
	}
}

BYTE
bytePow(BYTE base, int exponent) {
	BYTE ans = 1;
	int i;
	for (i = 0; i < exponent; i++) {
		ans *= base;
	}
	return ans;
}

BYTE **
initializeShadows(int image_size, int n, int k) {
	BYTE** shadows = calloc(n, sizeof(BYTE *));
	int size_of_shadow = image_size/k;
	int i = 0;
	for (i = 0; i < n; ++i) {
		shadows[i] = calloc(size_of_shadow, sizeof(BYTE));
	}
	return shadows;
}
