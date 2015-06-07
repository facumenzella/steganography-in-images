#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

// stdlib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../includes/errors.h"

#define MIN_ARGS 5
#define MAX_ARGS 9
#define SECRET_MAX_LENGTH 30
#define K_MAX_LENGTH 2

#define MODE(s) (strcmp(s, "-d") == 0) ? "distribution" : (strcmp(s, "-r") == 0) ? "recover" : "invalid mode"

typedef struct parameters_t *Parameters;

typedef enum {
  DISTRIBUTE, RECOVER
} mode_type;

// console parameters
static const char DISTRIBUTE_ARG[] = "--distribute";
static const char S_DISTRIBUTE_ARG[] = "-d"; // short distribute
static const char RECOVER_ARG[] = "--recover";
static const char S_RECOVER_ARG[] = "-r"; // short recover
static const char SECRET_ARG[] = "--secret";
static const char S_SECRET_ARG[] = "-s"; // its pretty clear that its short secret
static const char K_ARG[] = "-minShadows";
static const char S_K_ARG[] = "-k";


// functions
Parameters validateParameters(int argc, char * argv[], parameters_error *error);

#endif
