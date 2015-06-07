#ifndef __IMAGE_H__
#define __IMAGE_H__

// stdlib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./errors.h"
#include "./constants.h"

typedef struct image_t * BMPImage;

BMPImage initBMPImage(char *filename, int fileSize, int offset, BYTE *header, BYTE *image, image_error *error);
int getFilesize(BMPImage image);
int getOffset(BMPImage image);
BYTE *getHeader(BMPImage image);
BYTE *getBMPImage(BMPImage image);
char *getFilename(BMPImage image);
void freeImage(BMPImage image);
void setImageInIndex(BMPImage image, char value, int index);

#endif
