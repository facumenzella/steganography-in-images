#ifndef __ERRORS_H__
#define __ERRORS_H__

// stdlib includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deep shit errors
static const char MALLOC_ERROR[] = "We could not malloc memory. We are so sorry";
static const char CALLOC_ERROR[] = "We could not calloc memory. We are so sorry";

// Parameters parse errors
static const char QTY_ARGS_ERROR[] = "You have to provided the wrong amount of parameters";
static const char MODE_ARG_ERROR[] = "You have to provide either discover or recover mode";
static const char SECRET_ARG_ERROR[] = "You have to provide a secret image";
static const char K_ARG_ERROR[] = "You have to provide a minimum number of shadows";

// IO errors
static const char COULD_NOT_OPEN_FILE_ERROR[] = "We could not open the file you provided";


typedef char *parameters_error;
typedef char *distribution_error;
typedef char *image_error;
typedef char *io_error;
typedef char *main_error;

void setError(char **err, const char msg[]);

#endif
