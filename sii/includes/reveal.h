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

void runReveal(Arguments arguments, main_error *err);
BYTE* revealImage(int* n_values, int n_size, int k, BYTE** shadows_pixels, int shadow_size, int seed);
void initializeEquations(int** equations, int* n_values, int n_size, int k);
int** gaussJordanEliminationMethod(int** equations, int dimension);
BYTE* reconstructImage(BYTE* partial_image, int partial_image_size, int n, int k);
void eliminateValuesAtColumn(int** equation, int** inverse, int dimension, int pivot);
void eliminateValues(int** equation, int** inverse, int dimension, int pivot, int direction);
BYTE* revealPartialImageWithoutLoss(BYTE* partial_image, int partial_image_size, int* permuted_image_size);
BYTE* revealPartialImageWithLoss(BYTE* partial_image, int partial_image_size);

#endif