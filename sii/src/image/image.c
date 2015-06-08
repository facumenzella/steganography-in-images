#include "../../includes/image.h"

typedef struct image_t {
	char *filename;
	int fileSize;
	int offset;
	int imageSize;
	BYTE *header;
	BYTE *image;
} image_t;

BMPImage
initBMPImage(char *filename, int fileSize, int offset, int imageSize, BYTE *header, BYTE *image, image_error *error) {
	// We calloc the hole struct
  BMPImage imageStruct = calloc(1, sizeof(struct image_t));
	if (imageStruct == NULL) {
    strcpy(*error, CALLOC_ERROR);
		return NULL;
	}

  // We reserve space for the filename
	imageStruct->filename = calloc(strlen(filename) + 1, sizeof(BYTE));
	if (imageStruct->filename == NULL) {
    strcpy(*error, CALLOC_ERROR);
		return NULL;
	}
	strcpy(imageStruct->filename, filename);

  // We set the fileSize & the offset
	imageStruct->fileSize = fileSize;
	imageStruct->offset = offset;
	imageStruct->imageSize = imageSize;

  // We reserve space for the header
	imageStruct->header = calloc(offset + 1, sizeof(BYTE));
	if (imageStruct->header == NULL) {
    strcpy(*error, CALLOC_ERROR);
		return NULL;
	}
	memcpy(imageStruct->header, header, offset);

	imageStruct->image = calloc(imageSize + 1, sizeof(BYTE));
	if (imageStruct->image == NULL) {
    strcpy(*error, CALLOC_ERROR);
		return NULL;
	}
	memcpy(imageStruct->image, image, imageSize);

	return imageStruct;
}

void
freeBMPImage(BMPImage image) {
	if (image != NULL) {
		if (image->header != NULL) {
			free(image->header);
		}
		if (image->filename != NULL) {
			free(image->filename);
		}
		if (image->image != NULL) {
			free(image->image);
		}
		free(image);
	}
}

int
getFilesize(BMPImage image) {
	return image->fileSize;
}

int
getOffset(BMPImage image) {
	return image->offset;
}

int
getImageSize(BMPImage image) {
	return image->imageSize;
}

BYTE *
getHeader(BMPImage image) {
	return image->header;
}

BYTE *
getBMPImage(BMPImage image) {
	return image->image;
}

char *
getFilename(BMPImage image) {
	return image->filename;
}

void
setBMPImageInIndex(BMPImage image, char value, int index) {
	image->image[index] = value;
}
