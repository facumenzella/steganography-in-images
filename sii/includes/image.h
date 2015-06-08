#ifndef __IMAGE_H__
#define __IMAGE_H__

// stdlib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./errors.h"
#include "./constants.h"

typedef struct image_t * BMPImage;

static const char BMP[] = "bmp";

BMPImage initBMPImage(char *filename, int fileSize, int offset, int imageSize, BYTE *header, BYTE *image, image_error *error);
int getFilesize(BMPImage image);
int getOffset(BMPImage image);
int getImageSize(BMPImage size);
BYTE *getHeader(BMPImage image);
BYTE *getBMPImage(BMPImage image);
char *getFilename(BMPImage image);
void freeImage(BMPImage image);
void setImageInIndex(BMPImage image, char value, int index);
BMPImage clone(BMPImage image, io_error *err);

#endif
