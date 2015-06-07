#include <stdlib.h>
#include <stdio.h>


void
distribute(Parameters *parameters) {
	
}

void
permutePixels(int n, BYTE[] image) {
	int i, j;
	for (i = 0; i < count; ++i) {
		BYTE pivot = image[i];
		image[i] = image[j];
		image[j] = pivot;
	}
}

BYTE[][]
createLosslessShadows(unsigned char[] image, int n, int k) {
	int size_of_shadow = (sizeof(image)/k)*2;
	int shadow_pixel_index = 0;
	BYTE[k] section = {};
	BYTE **shadows = initializeShadows(sizeof(image), n, k);
	int i;
	for (i = 0; i < sizeof(image); i++) {
		if (i % k == 0) {
			evaluateSection(section, shadows, shadow_pixel_index);
			shadow_pixel_index++;
			section = {};
		}
		section[i % k] = image[i];
	}
	return shadows;
}

void
evaluateSection(BYTE[] seciton, BYTE** shadows, int shadow_pixel_index) {
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
	BYTE **shadows = calloc(sizeof(BYTE *), n);
	int i = 0;
	for (i = 0; i < count; ++i) {
		shadows[i] = calloc(sizeof(BYTE), (sizeof(image)/k) * 2);
	}
	return shadows;
}
