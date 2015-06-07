#include <stdlib.h>
#include "../includes/distribution.h"

BYTE bytePow(BYTE base, int exponent);
BYTE ** initializeShadows(int image_size, int n, int k);
BYTE ** createLosslessShadows(unsigned char * image, int n, int k);
void evaluateSection(BYTE section[], BYTE** shadows, int shadow_pixel_index);

void
distribute(Parameters parameters) {
	io_error err = calloc(1024, sizeof(char));
	BMPImage image = loadImage("../img/Albert.bmp", &err);

	if (err) {
		d_printf("%s\n", "We fucked up");
	} else {
		d_printf("file name: %s\n", getFilename(image));
	}
}

void
permutePixels(int n, BYTE image[]) {
	int i, j;
	for (i = n - 1; i > 0; i--) {
		BYTE pivot = image[i];
		image[i] = image[j];
		image[j] = pivot;
	}
}

BYTE**
createLosslessShadows(unsigned char * image, int n, int k) {
	int shadow_pixel_index = 0;
	BYTE* section = calloc(k, sizeof(BYTE));
	BYTE** shadows = initializeShadows(sizeof(image), n, k);
	int i;
	for (i = 0; i < sizeof(image); i++) {
		if (i % k == 0) {
			evaluateSection(section, shadows, shadow_pixel_index);
			shadow_pixel_index++;
			memset(section, 0, k);
		}
		section[i % k] = image[i];
	}
	return shadows;
}

void
evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index) {
	int i, j;
	for (i = 1; i <= sizeof(shadows); i++) {
		BYTE ans = 0;
		for (j = 0; j < sizeof(section); j++) {
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
	int size_of_shadow = (image_size/k)*2;
	int i = 0;
	for (i = 0; i < n; ++i) {
		shadows[i] = calloc(size_of_shadow, sizeof(BYTE));
	}
	return shadows;
}
