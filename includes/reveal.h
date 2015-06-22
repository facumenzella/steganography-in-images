#ifndef __REVEAL_H__
#define __REVEAL_H__

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "math.h"
#include "random.h"
#include "./bmp_image.h"
#include "./cmd.h"
#include "./imageUtils.h"

static const char* DIFFERENT_SEEDS_FOR_PORTERS = "The porter images were created with different seeds. You have been fooled!!";
static const char* STARTING_REVEAL_PROCESS = "We will get the %d porter images from: %s\n";
static const char *REVEAL_SUCCESS = "We are done revealing the secret. Please check the image located in output folder. Gamales out.\n";

void runReveal(Arguments arguments, main_error *err);

#endif