#include "../../includes/imageUtils.h"

static const char READ_BINARY_MODE[] = "rb";
static const int FILE_SIZE_OFFSET = 2;
static const int IMAGE_OFFSET_OFFSET = 10; // Pretty cool name, a I right?
static const int IMAGE_SIZE_OFFSET = 34;

void readFileSize(FILE *file, int *fileSize);
void readImageOffset(FILE *file, int *imageOffset);
void readImageSize(FILE *file, int *imageSize);
void readHeader(FILE *file, BYTE *header, int headerSize);
void readImage(FILE *file, int imageOffset, int imageSize, BYTE *image, io_error *err);

BMPImage
loadImage(char *path, io_error *err) {
  printf("Trying to open:%s\n", path);
  int fileSize = 0, imageOffset = 0, imageSize = 0;
  FILE * file = fopen(path, READ_BINARY_MODE);
	if (file == NULL) {
    d_printf("could not open: %s\n", path);
		strcpy(*err, COULD_NOT_OPEN_FILE_ERROR);
		return NULL;
	}

  readFileSize(file, &fileSize);
  d_printf("\tfile size: %d\n", fileSize);
  readImageOffset(file, &imageOffset);
  d_printf("\timage offset: %d\n", imageOffset);
  readImageSize(file, &imageSize);
  d_printf("\timage size: %d\n", imageSize);

  BYTE *header = calloc(imageOffset + 1, sizeof(BYTE));
  if (header == NULL) {
		strcpy(*err, CALLOC_ERROR);
		return NULL;
	}
  readHeader(file, header, imageOffset);

  BYTE *image = calloc(imageSize + 1, sizeof(BYTE));
  if (image == NULL) {
		strcpy(*err, CALLOC_ERROR);
		return NULL;
	}
  readImage(file, imageOffset, imageSize, image, err);
  BMPImage i = initBMPImage(path, fileSize, imageOffset, header, image, err);
  return i;
}

void
readFileSize(FILE *file, int *fileSize) {
  fseek(file, FILE_SIZE_OFFSET, SEEK_SET);
	fread(fileSize, sizeof(int), 1, file);
  rewind(file);
}

void
readImageOffset(FILE *file, int *imageOffset) {
  fseek(file, IMAGE_OFFSET_OFFSET, SEEK_SET);
	fread(imageOffset, sizeof(int), 1, file);
  rewind(file);
}

void
readImageSize(FILE *file, int *imageSize) {
  fseek(file, IMAGE_SIZE_OFFSET, SEEK_SET);
	fread(imageSize, sizeof(int), 1, file);
  rewind(file);
}

void
readHeader(FILE *file, BYTE *header, int headerSize) {
  fseek(file, headerSize, SEEK_SET);
  fread(header, sizeof(BYTE), headerSize, file);
  rewind(file);
}

void
readImage(FILE *file, int imageOffset, int imageSize, BYTE *image, io_error *err) {
  fseek(file, imageOffset + 1, SEEK_SET);
  fread(image, sizeof(BYTE), imageSize, file);
  rewind(file);
}
