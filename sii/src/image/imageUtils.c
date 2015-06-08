#include "../../includes/imageUtils.h"

static const char READ_BINARY_MODE[] = "rb";
static const char WRITE_BINARY_MODE[] = "wb";
static const int FILE_SIZE_OFFSET = 2;
static const int IMAGE_OFFSET_OFFSET = 10; // Pretty cool name, a I right?
static const int IMAGE_SIZE_OFFSET = 34;

void readFileSize(FILE *file, int *fileSize);
void readImageOffset(FILE *file, int *imageOffset);
void readImageSize(FILE *file, int *imageSize);
void readHeader(FILE *file, BYTE *header, int headerSize);
void readImage(FILE *file, int imageOffset, int imageSize, BYTE *image, io_error *err);
void freeWhatNeedsToBeFree(BYTE *header, BYTE *image, FILE *file);

BMPImage
loadImage(char *path, io_error *err) {
  printf("Trying to open:%s\n", path);
  int fileSize = 0, imageOffset = 0, imageSize = 0;
  BYTE *header = NULL, *image = NULL;
  FILE *file = NULL;
  file = fopen(path, READ_BINARY_MODE);
	if (file == NULL) {
    d_printf("could not open: %s\n", path);
		strcpy(*err, COULD_NOT_OPEN_FILE_ERROR);
    freeWhatNeedsToBeFree(header, image, file);
    return NULL;
	}

  readFileSize(file, &fileSize);
  d_printf("\tfile size: %d\n", fileSize);
  readImageOffset(file, &imageOffset);
  d_printf("\timage offset: %d\n", imageOffset);
  readImageSize(file, &imageSize);
  d_printf("\timage size: %d\n", imageSize);

  header = calloc(imageOffset, sizeof(BYTE));
  if (header == NULL) {
		strcpy(*err, CALLOC_ERROR);
    freeWhatNeedsToBeFree(header, image, file);
		return NULL;
	}
  readHeader(file, header, imageOffset);

  image = calloc(imageSize, sizeof(BYTE));
  if (image == NULL) {
		strcpy(*err, CALLOC_ERROR);
    freeWhatNeedsToBeFree(header, image, file);
		return NULL;
	}
  readImage(file, imageOffset, imageSize, image, err);
  return initBMPImage(path, fileSize, imageOffset, imageSize, header, image, err);
}

void
saveImage(BMPImage image, char *path, io_error *err) {
  int offset = getOffset(image);
	int fileSize = getFilesize(image);
	FILE * file;

	file = fopen(path, WRITE_BINARY_MODE);
	if(file == NULL) {
		strcpy(*err, COULD_NOT_OPEN_FILE_ERROR);
    return;
	}

	fwrite(getHeader(image), sizeof(BYTE), offset, file);
	fwrite(getBMPImage(image), sizeof(BYTE), getImageSize(image), file);

	fclose(file);
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
  rewind(file);
  fread(header, sizeof(BYTE), headerSize, file);
  rewind(file);
}

void
readImage(FILE *file, int imageOffset, int imageSize, BYTE *image, io_error *err) {
  fseek(file, imageOffset + 1, SEEK_SET);
  fread(image, sizeof(BYTE), imageSize, file);
  rewind(file);
}

void
freeWhatNeedsToBeFree(BYTE *header, BYTE *image, FILE *file) {
  if (file != NULL) {
    fclose(file);
  }
  if (header != NULL) {
    free(header);
  }
  if (image != NULL) {
    free(image);
  }
}
