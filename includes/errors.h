#ifndef __ERRORS_H__
#define __ERRORS_H__

// stdlib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deep shit errors
static const char MALLOC_ERROR[] = "We could not malloc memory. We are so sorry";
static const char CALLOC_ERROR[] = "We could not calloc memory. We are so sorry";

// Arguements parse errors
static const char QTY_ARGS_ERROR[] = "You have to provided the wrong amount of parameters. \nPlease run 'make arguments' in order to see the correct arguements.\n";
static const char MODE_ARG_ERROR[] = "You have to provide either discover or recover mode. \nPlease run 'make arguments' in order to see the correct arguements.\n";
static const char SECRET_ARG_ERROR[] = "You have to provide a secret image. \nPlease run 'make arguments' in order to see the correct arguements.\n";
static const char K_ARG_ERROR[] = "You have to provide a minimum number of shadows. \nPlease run 'make arguments' in order to see the correct arguements.\n";
static const char K_GREATER_THAN_N[] = "K must be lower or equal than N. \nPlease run 'make arguments' in order to see the correct arguements.\n";
static const char K_LOWER_THAN_2[] = "K must be at least 2.\n";
static const char N_LOWER_THAN_2[] = "N must be at least 2.\n";
static const char DIR_INVALID_ARGUMENT[] = "You have to provide either --directory or -dir. We will set the default directory\n";

// Arguments errors
static const char IMAGE_SIZE_NOT_DIVISIBLE_BY_K_ERROR[] = "The size of the image must be multiple of k";

// Shadow errors
static const char NOT_ENOUGH_SHADOWS_ERROR[] = "Not enough porter images.";

typedef char *arguments_error;
typedef char *distribution_error;
typedef char *image_error;
typedef char *io_error;
typedef char *main_error;

void setError(char **err, const char msg[]);

#endif
