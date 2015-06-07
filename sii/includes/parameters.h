#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

// stdlib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/errors.h"

#define MIN 3
#define MAX 5

typedef enum {
  DISTRIBUTE, RECOVER
} mode_type;

// console parameters
static const char DISTRIBUTE_ARG[] = "--distribute";
static const char S_DISTRIBUTE_ARG[] = "-d"; // short distribute
static const char RECOVER_ARG[] = "--recover";
static const char S_RECOVER_ARG[] = "-r";

// functions
void validateParameters(int argc, char * argv[], mode_type *m, parameters_error *error);

#endif
