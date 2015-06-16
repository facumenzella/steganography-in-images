#ifndef __DISTRIBUTION_H__
#define __DISTRIBUTION_H__

#include <stdlib.h>

#include "./cmd.h"
#include "./constants.h"
#include "./image.h"
#include "./random.h"
#include "./math.h"

void runDistribution(Arguments arguments, main_error *err);
void distribute(char *file_name, BYTE *image, int image_size, char* directory, int n, int k, main_error *err);
BYTE* convertImageToArrayWithoutLoss(BYTE* image, int image_size, int* new_image_size);
BYTE* convertImageToArrayWithLoss(BYTE* image, int image_size);
void permutePixels(int n, BYTE* image);
BYTE** createShadows(unsigned char* image, int image_size, int n, int k);
void evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k);
BYTE ** initializeShadows(int image_size, int n, int k);
void hideInformation(BMPImage shadowImage, BYTE *toHide, int to_hide_size, main_error *err);

#endif
