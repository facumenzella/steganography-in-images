#include "../includes/distribution.h"
#include "../includes/imageUtils.h"

BYTE* convertImageToArrayWithoutLoss(BYTE* image, int image_size, int* new_image_size);
BYTE* convertImageToArrayWithLoss(BYTE* image, int image_size);
void permutePixels(int n, BYTE* image);
BYTE** createShadows(unsigned char* image, int image_size, int n, int k);
void evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k);
BYTE ** initializeShadows(int image_size, int n, int k);
void hideInformation(BMPImage shadowImage, BYTE *toHide, int to_hide_size, main_error *err);

void
distribute(Arguments arguments, main_error *err) {
    
	char *file_name = getSecret(arguments);
	BMPImage bmp = loadImage(file_name, err);
    printf("Secret image %s was succesfully loaded\n", file_name);
	BYTE *image = getBMPImage(bmp);
	char *directory = getDirectory(arguments);
	int image_size = getImageSize(bmp);
	int n = getTotalAmountOfShadowsToDistributeSecret(arguments);
	int k = getMinShadowsToRecoverSecret(arguments);

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
	BYTE *E = convertImageToArrayWithLoss(image, image_size);

	BMPImage *shadowImages = loadImages(directory, n, err);
	if (shadowImages == NULL) {
		d_printf("%s\n", *err);
		return; // we fucked up.
	}
    printf("We have loaded the %d shadows\n", n);
	// we are cool, so we continue
	BYTE **shadows = createShadows(E, image_size, n, k);

	for (int i = 0; i < n; i++) {
		hideInformation(shadowImages[i], shadows[i], image_size/k, err);
	}
	printf("We are done here\nWe now save the images with the hidden data\n");
    for (int i = 0; i < n; i++) {
        io_error *err;
        BMPImage image = shadowImages[i];
        saveImage(image, directory, err);
        if (err != NULL) {
            printf("error: %s\n", *err);
        }
    }
}

BYTE*
convertImageToArrayWithLoss(BYTE* image, int image_size) {
	BYTE* converted_image = calloc(image_size, sizeof(BYTE));
	int i, j = 0;
	for (i = 0; i < image_size; i++) {
		if (image[i] >= 250) {
			converted_image[j++] = 250;
		} else {
			converted_image[j++] = image[i];
		}
	}
	return converted_image;
}

BYTE*
convertImageToArrayWithoutLoss(BYTE* image, int image_size, int* new_image_size) {
	BYTE* converted_image = calloc(image_size*2, sizeof(BYTE));
	int i, j = 0;
	for (i = 0; i < image_size; i++) {
		if (image[i] >= 250) {
			converted_image[j++] = 250;
			converted_image[j++] = image[i] - 250;
		} else {
			converted_image[j++] = image[i];
		}
	}
	*new_image_size = j;
	realloc(new_image_size, *converted_image);
	return converted_image;
}

BYTE**
createShadows(BYTE* image, int image_size, int n, int k) {
	int shadow_pixel_index = 0;
	// step 3 - Sequentially, take r not-shared-yet elements of the array E to form an r-pixel section.
	BYTE* section = calloc(k, sizeof(BYTE));
	BYTE** shadows = initializeShadows(image_size, n, k);
	int i;

	// step 5 - Repeat Steps 3 and 4 until all elements of the array E are processed.
	for (i = 1; i <= image_size; i++) {
		section[(i % k) - 1] = image[i-1];
		if (i % k == 0) {
			// step 4 - Generate n pixels for the n shadow images
			evaluateSection(section, shadows, shadow_pixel_index, n, k);
			shadow_pixel_index++;
			memset(section, 0, k);
		}
	}
	return shadows;
}

void
evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k) {
	int i, j, ans;
	for (i = 1; i <= n; i++) {
		ans = 0;
		for (j = 0; j < k; j++) {
			ans += section[j] * intPow(i, j);
		}
		shadows[i-1][shadow_pixel_index] = ans % MAX_BYTE_VALUE;
	}
}

/*
 * This method assumes that image_size/k is an integer
 */

BYTE **
initializeShadows(int image_size, int n, int k) {
	BYTE** shadows = calloc(n, sizeof(BYTE *)); // aka unsigned char*
	int shadow_size = image_size/k;
	int i;
	for (i = 0; i < n; ++i) {
		shadows[i] = calloc(shadow_size, sizeof(BYTE));
	}
	return shadows;
}

void
hideInformation(BMPImage shadowImage, BYTE *toHide, int size_to_hide, main_error *err) {
	BYTE *shadowImage_bytes = getBMPImage(shadowImage);
    int shadow_size = getImageSize(shadowImage);
	int bi = 0; // for iterating over shadowImage_bytes
	for (int i = 0; i < size_to_hide; i++) {
		// we iterate over the bytes to hide
		BYTE byte_toHide = toHide[i];
		for (int j = 0; j < 8; j++) {
			// we iterate over the bits of the byte to hide
			int bit = getBit(byte_toHide, j);
			BYTE shadowImage_byte = shadowImage_bytes[bi];
			shadowImage_bytes[bi++] = overrideLessSignificantBit(shadowImage_byte, bit);
		}
	}
}
