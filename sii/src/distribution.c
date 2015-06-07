#include "../includes/distribution.h"

BYTE bytePow(BYTE base, int exponent);
BYTE ** initializeShadows(int image_size, int n, int k);
BYTE ** createLosslessShadows(unsigned char image[], int n, int k);

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
