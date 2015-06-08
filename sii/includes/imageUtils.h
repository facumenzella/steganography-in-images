#ifndef __IMAGE_UTILS_H__
#define __IMAGE_UTILS_H__

// stdlib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "./image.h"
#include "./errors.h"
#include "./env.h"
#include "./constants.h"

BMPImage loadImage(char *path, io_error *err);
BMPImage* loadImages(char *dir, int n, io_error *err);
void saveImage(BMPImage image, char *path, io_error *error);

typedef struct dirent *NEXT_DIR;
//struct dirent
//{
//    ino_t          d_ino;       // inode number
//    off_t          d_off;       // offset to the next dirent
//    unsigned short d_reclen;    // length of this record
//    unsigned char  d_type;      // type of file; not supported
//                                   by all file system types
//    char           d_name[256]; // filename
//}


#endif
