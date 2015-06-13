#ifndef __REVEAL_H__
#define __REVEAL_H__

#include "constants.h"
#include "math.h"
#include "random.h"

BYTE* revealImage(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size, int seed);

#endif