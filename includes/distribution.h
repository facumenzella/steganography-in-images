#ifndef __DISTRIBUTION_H__
#define __DISTRIBUTION_H__

#include <stdlib.h>

#include "./cmd.h"
#include "./constants.h"
#include "./bmp_image.h"
#include "./random.h"
#include "./math.h"

void runDistribution(Arguments arguments, main_error *err);

// Debugging strings
static const char *SECRET_IMAGE_SUCCESS = "The secret image %s was succesfully loaded\n";
static const char *PORTER_IMAGES_SUCCESS = "We have loaded the %d full porter images\n";
static const char *STEGANOGRAPHY_SUCCESS = "We succesffully performed the hiding\n";
static const char *DISTRIBUTION_SUCCESS = "We are done distributing. Gamales out.\n";

// Errors
static const char *NO_SECRET_IMAGE = "We were not able to open the secret image. Either it does not exist or the path its wrong.";
static const char *NO_PORTER_IMAGES = "We were not able to open all the porter images. Either it one of them does not exist or the path its wrong.";
static const char *INVALID_PORTER_IMAGE_SIZE = "Invalid size for porter image. Remember it must be able to store 1 bit per byte so make the math.";

static const char *PORTERS_DIRECTORY = "./porters/";

#endif
