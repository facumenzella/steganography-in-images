#ifndef __CMD_H__
#define __CMD_H__

// stdlib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "errors.h"
#include "constants.h"
#include "env.h"
#include "arguments.h"

#define MIN_REQUIRED_ARGS 5
#define MAX_ARGS 9
#define SECRET_MAX_LENGTH 30
#define K_MAX_LENGTH 2
#define N_MAX_LENGTH 1
#define DIR_MAX_LENGTH 30

#define MODE(s) (strcmp(s, "-d") == 0) ? "distribution" : (strcmp(s, "-r") == 0) ? "recover" : "invalid mode"

// console parameters
static const char DISTRIBUTE_ARG[] = "--distribute";
static const char S_DISTRIBUTE_ARG[] = "-d"; // short distribute
static const char RECOVER_ARG[] = "--recover";
static const char S_RECOVER_ARG[] = "-r"; // short recover
static const char SECRET_ARG[] = "--secret";
static const char S_SECRET_ARG[] = "-s"; // its pretty clear that its short secret
static const char K_ARG[] = "--mshadows";
static const char S_K_ARG[] = "-k";
static const char N_ARG[] = "--fshadows";
static const char S_N_ARG[] = "-n";
static const char DIR_ARG[] = "--directory";
static const char S_DIR_ARG[] = "-dir";

// default values
static const char DIRECTORY_DEFAULT_VALUE[] = "./";

// functions
Arguments validateArguments(int argc, char * argv[], arguments_error *error);

#endif
