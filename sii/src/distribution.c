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

/* step 1 - Truncate all gray values larger than 250 to 250 so that the gray
values of the secret image are in the range 0–250
*/

	BYTE *t_image = convertImageToArrayWithoutLoss(image, getImageSize(bmp));

/* step 2 - Use a key to generate a permutation sequence to permute the pixels
of the secret image.
*/
	int n = getTotalShadows(parameters);
	permutePixels(n, image);
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
