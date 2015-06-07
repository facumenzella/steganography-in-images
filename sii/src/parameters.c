#include "../includes/parameters.h"
#include "../includes/constants.h"
#include "../includes/env.h"

typedef struct parameters_t {
	mode_type mode;
	char *secret;
}parameters_t;

void validateModeType(char *arg, mode_type *mode, parameters_error *error);
void validateSecret(char *arg, char *value,  char **secret, parameters_error *error);

Parameters
validateParameters(int argc, char *argv[], parameters_error *error) {
  Parameters parameters = malloc(sizeof(struct parameters_t));

  if(argc < MIN_ARGS || argc > MAX_ARGS) {
    strcpy(*error, QTY_ARGS_ERROR);
    return NULL;
	}

  validateModeType(argv[1], &parameters->mode, error);
  validateSecret(argv[2], argv[3], &parameters->secret,error);
  return parameters;
}

void
validateModeType(char *arg, mode_type *mode, parameters_error *error) {
  if(strcmp(arg, S_DISTRIBUTE_ARG) == 0 || strcmp(arg, DISTRIBUTE_ARG) == 0) {
		*mode = DISTRIBUTE;
	} else if(strcmp(arg, S_RECOVER_ARG) == 0 || strcmp(arg, RECOVER_ARG) == 0) {
		*mode = RECOVER;
	} else {
    strcpy(*error, MODE_ARG_ERROR);
	}
  if (DEBUGGING) {
    printf("mode: %s\n", MODE(arg));
  }
}

void
validateSecret(char *arg, char *value,  char **secret, parameters_error *error) {

  if(strcmp(arg, S_SECRET_ARG) == 0 || strcmp(arg, SECRET_ARG) == 0) {
    char *s = calloc(SECRET_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    *secret = s;
  } else {
    strcpy(*error, SECRET_ARG_ERROR);
  }
  if (DEBUGGING) {
    printf("secret: %s\n", *secret);
  }
}
