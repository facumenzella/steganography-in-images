#ifndef __DISTRIBUTION_H__
#define __DISTRIBUTION_H__

#include <stdlib.h>

#include "./cmd.h"
#include "./constants.h"
#include "./bmp_image.h"
#include "./random.h"
#include "./math.h"

void runDistribution(Arguments arguments, main_error *err);
void distribute(BYTE *image,
                int image_size,
                BYTE **shadow_images,
                char* directory,
                int n,
                int k,
                int bits_to_hide,
                int seed,
                main_error *err);
BYTE* convertImageToArrayWithoutLoss(BYTE* image, int image_size, int* new_image_size);
BYTE* convertImageToArrayWithLoss(BYTE* image, int image_size);
void permutePixels(int n, BYTE* image);
BYTE** createShadows(unsigned char* image, int image_size, int n, int k);
void evaluateSection(BYTE* section, BYTE** shadows, int shadow_pixel_index, int n, int k);
BYTE ** initializeShadows(int image_size, int n, int k);

static const char *PORTERS_DIRECTORY = "../porters/";

#endif
