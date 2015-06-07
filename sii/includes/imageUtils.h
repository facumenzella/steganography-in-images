#ifndef __IMAGE_UTILS_H__
#define __IMAGE_UTILS_H__

// stdlib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./image.h"
#include "./errors.h"
#include "./env.h"
#include "./constants.h"

BMPImage loadImage(char *path, io_error *err);
void saveImage(BMPImage image, char *path, io_error *error);

#endif
