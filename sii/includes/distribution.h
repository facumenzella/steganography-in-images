#ifndef __DISTRIBUTION_H__
#define __DISTRIBUTION_H__

#include <stdlib.h>

#include "./cmd.h"
#include "./constants.h"
#include "./bmp_image.h"
#include "./random.h"
#include "./math.h"

void runDistribution(Arguments arguments, main_error *err);

static const char *PORTERS_DIRECTORY = "../porters/";

#endif
