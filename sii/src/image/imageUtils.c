#include "../../includes/imageUtils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <inttypes.h>

static const char READ_BINARY_MODE[] = "rb";
static const char WRITE_BINARY_MODE[] = "wb";
static const int FILE_SIZE_OFFSET = 2;
static const int IMAGE_OFFSET_OFFSET = 10; // Pretty cool name, a I right?
static const int IMAGE_SIZE_OFFSET = 34; // Not working, so we will use the following two
static const int IMAGE_HORIZONTAL_RESOLUTION = 18;
static const int IMAGE_VERTICAL_RESOLUTION = 22;
static const int SEED_INDEX = 6;
static const int PORTER_INDEX = 8;

char* getNameFromPath(char const *path);
void readFileSize(FILE *file, int *fileSize);
void readImageOffset(FILE *file, int *imageOffset);
void readImageSize(FILE *file, int *imageSize);
void readHeader(FILE *file, BYTE *header, int headerSize);
void readImage(FILE *file, int imageOffset, int imageSize, BYTE *image, io_error *err);
void freeWhatNeedsToBeFree(BYTE *header, BYTE *image, FILE *file);
boolean isDir(char *path);
boolean isBMP(char * path);

int
main(int argc, char * argv[]) {
    
    io_error error;
    BMPImage image = loadImage("../lena/lena512.bmp", &error);
    
    saveImage(image, "../porters/", &error);
}


BMPImage
loadImage(char *path, io_error *err) {
    printf("Trying to open:%s\n", path);
    int fileSize = 0, imageOffset = 0, imageSize = -1;
    BYTE *header = NULL, *image = NULL;
    char * imageName;
    FILE *file = NULL;
    file = fopen(path, READ_BINARY_MODE);
    if (file == NULL) {
        printf("could not open: %s\n", path);
        setError(err, COULD_NOT_OPEN_FILE_ERROR);
        freeWhatNeedsToBeFree(header, image, file);
        return NULL;
    } else {
        imageName = getNameFromPath(path);
    }
    
    readFileSize(file, &fileSize);
    readImageOffset(file, &imageOffset);
    //    printf("image offset : %d\n", imageOffset);
    readImageSize(file, &imageSize);
    
    header = calloc(imageOffset, sizeof(BYTE));
    if (header == NULL) {
        setError(err, CALLOC_ERROR);
        freeWhatNeedsToBeFree(header, image, file);
        return NULL;
    }
    readHeader(file, header, imageOffset);
    
    uint16_t seed = -1;
    memcpy(&seed, &header[SEED_INDEX], 2);
    //    printf("seed: %d\n", seed);
    
    uint16_t porter = -1;
    memcpy(&porter, &header[PORTER_INDEX], 2);
    //    printf("porter: %d\n", porter);
    
    image = calloc(imageSize, sizeof(BYTE));
    if (image == NULL) {
        setError(err, CALLOC_ERROR);
        freeWhatNeedsToBeFree(header, image, file);
        return NULL;
    }
    readImage(file, imageOffset, imageSize, image, err);
    
    fclose(file);
    return initBMPImage(imageName, fileSize, imageOffset, imageSize, header, seed, porter, image, err);
}

void
saveImage(BMPImage image, char *path, io_error *err) {
    int offset = getOffset(image);
    int fileSize = getFilesize(image);
    FILE * file;
    
    char *fullPath = calloc(strlen(path) + strlen(getFilename(image)), sizeof(char));
    strcat(fullPath, path);
    strcat(fullPath, getFilename(image));
    
    printf("Trying to save: %s\n", fullPath);
    
    file = fopen(fullPath, WRITE_BINARY_MODE);
    if(file == NULL) {
        free(fullPath);
        setError(err, COULD_NOT_OPEN_FILE_ERROR);
        return;
    }
    
    char *header_with_out_seed_and_porter = (char*)getHeader(image);
    
    //    uint16_t seed = getSeed(image);
    //    memcpy(&header_with_out_seed_and_porter[SEED_INDEX], &seed, sizeof(seed));
    //
    //    uint16_t porter = getIndex(image);
    //    memcpy(&header_with_out_seed_and_porter[PORTER_INDEX], &porter, sizeof(porter));
    
    fwrite(getHeader(image), sizeof(BYTE), offset, file);
    fwrite(getBMPImage(image), sizeof(BYTE), getImageSize(image), file);
    
    printf("we saved and image of size: %d\n", offset + getImageSize(image));
    
    fclose(file);
}

BMPImage*
loadImages(char *dir, int n, io_error *err) {
    printf("Fetching images from %s\n", dir);
    DIR *pwd = NULL;
    NEXT_DIR curr = NULL;
    int imagesRead = 0;
    BMPImage *shadows = calloc(n, sizeof(BMPImage*));
    if((pwd = opendir(dir)) == NULL) {
        setError(err, COULD_NOT_OPEN_DIR_ERROR);
        return NULL;
    }
    
    while((curr = readdir(pwd)) != NULL && imagesRead < n) {
        char *fullPath = calloc(strlen(curr->d_name) + strlen(dir) + 2, sizeof(char));
        if (fullPath == NULL) {
            setError(err, CALLOC_ERROR);
            return NULL;
        }
        // we initialize the fullpath with the directory path
        strncat(fullPath, dir, strlen(dir));
        // we append '/' to the end of the path if needed
        if(dir[strlen(dir) - 1] != '/') {
            strncat(fullPath, "/", 1);
        }
        // we append the file name to the path
        strncat(fullPath, curr->d_name, strlen(curr->d_name));
        
        // now we want to check that we only open files
        if(isDir(fullPath) == FALSE) {
            // its a file not a directory
            if (isBMP(fullPath)) {
                BMPImage shadowImage = loadImage(fullPath, err);
                //                printf("\topening %s \n", getFilename(shadowImage));
                if (*err != NULL) {
                    closedir(pwd);
                    free(fullPath);
                    return NULL;
                }
                BMPImage i = clone(shadowImage, err);
                if (*err != NULL || i == NULL) {
                    closedir(pwd);
                    free(fullPath);
                    return NULL;
                }
                shadows[imagesRead++] = i;
            }
        }
    }
    if (imagesRead < n) {
        setError(err, NOT_ENOUGH_SHADOWS_ERROR);
        return NULL;
    }
    return shadows;
}

int
countImagesInDirectory(char *dir, io_error *err) {
    printf("Fetching images from %s\n", dir);
    DIR *pwd = NULL;
    NEXT_DIR curr = NULL;
    int shadows = 0;
    if((pwd = opendir(dir)) == NULL) {
        setError(err, COULD_NOT_OPEN_DIR_ERROR);
        return 0;
    }
    
    while((curr = readdir(pwd)) != NULL) {
        char *fullPath = calloc(strlen(curr->d_name) + strlen(dir) + 2, sizeof(char));
        if (fullPath == NULL) {
            setError(err, CALLOC_ERROR);
            return 0;
        }
        // we initialize the fullpath with the directory path
        strncat(fullPath, dir, strlen(dir));
        // we append '/' to the end of the path if needed
        if(dir[strlen(dir) - 1] != '/') {
            strncat(fullPath, "/", 1);
        }
        // we append the file name to the path
        strncat(fullPath, curr->d_name, strlen(curr->d_name));
        // now we want to check that we only open files
        if(isDir(fullPath) == FALSE) {
            // its a file not a directory
            if (isBMP(fullPath)) {
                shadows++;
            }
        }
    }
    return shadows;
}

// Private functions

char *
getNameFromPath(char const *path) {
    const char ch = '/';
    char *ret;
    ret = strrchr(path, ch);
    return &ret[1];
}

void
readFileSize(FILE *file, int *fileSize) {
    fseek(file, FILE_SIZE_OFFSET, SEEK_SET);
    fread(fileSize, sizeof(int), 1, file);
    //        printf("\t file size: %d - read offset %#010x from the beginning of file\n", *fileSize, FILE_SIZE_OFFSET);
    rewind(file);
}

void
readImageOffset(FILE *file, int *imageOffset) {
    fseek(file, IMAGE_OFFSET_OFFSET, SEEK_SET);
    fread(imageOffset, sizeof(int), 1, file);
    //        printf("\t imageoffset: %d - read offset %#010x from the beginning of file\n", *imageOffset, IMAGE_OFFSET_OFFSET);
    rewind(file);
}

void
readImageSize(FILE *file, int *imageSize) {
    int hor, ver;
    fseek(file, IMAGE_HORIZONTAL_RESOLUTION, SEEK_SET);
    fread(&hor, sizeof(int), 1, file);
    printf("\t horizontal res: %d - read offset %#010x from the beginning of file\n", hor, IMAGE_HORIZONTAL_RESOLUTION);
    rewind(file);
    fseek(file, IMAGE_VERTICAL_RESOLUTION, SEEK_SET);
    fread(&ver, sizeof(int), 1, file);
    //    printf("\t vertical res: %d - read offset %#010x from the beginning of file\n", ver, IMAGE_VERTICAL_RESOLUTION);
    printf("\t Image size = %d\n", hor * ver);
    *imageSize = hor * ver;
    rewind(file);
}

void
readHeader(FILE *file, BYTE *header, int headerSize) {
    fseek(file, 0, SEEK_SET);
    fread(header, sizeof(BYTE), headerSize, file);
    rewind(file);
}

void
readImage(FILE *file, int imageOffset, int imageSize, BYTE *image, io_error *err) {
    fseek(file, imageOffset, SEEK_SET);
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

boolean
isBMP(char * path) {
    return strstr(path, BMP) != NULL;
}

boolean
isDir(char *path) {
    return (opendir(path) != NULL);
}

