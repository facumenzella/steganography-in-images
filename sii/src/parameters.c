#include "../includes/parameters.h"

typedef struct parameters_t {
	mode_type mode;
	char *secret;
  char *minShadows;
  char *totalShadows;
  char *directory;
}parameters_t;

boolean invalidAmountOfArgs(int args);
void validateModeType(char *arg, mode_type *mode, parameters_error *error);
void validateSecret(char *arg, char *value,  char **secret, parameters_error *error);
void validateMinShadows(char *arg, char*value, char **number, parameters_error *error);
boolean validateTotalAmountOfShadows(char *arg, char*value, char **number, parameters_error *error);
void validateDir(char *arg, char*value, char **number, parameters_error *error);
boolean haveOptionalArguments(int argc, int lastReaded);

Parameters
validateParameters(int argc, char *argv[], parameters_error *error) {
  Parameters parameters = malloc(sizeof(struct parameters_t));
  int ARGS = argc - 1; // we do not need the first argument
  if(invalidAmountOfArgs(ARGS)) {
		setError(error, QTY_ARGS_ERROR);
    return NULL;
	}

  if (DEBUGGING) {
    printf("\n%s\n", "Starting to read console arguments...");
  }

  validateModeType(argv[1], &parameters->mode, error);
  validateSecret(argv[2], argv[3], &parameters->secret, error);
  validateMinShadows(argv[4], argv[5], &parameters->minShadows, error);

  if (haveOptionalArguments(ARGS, 5)) {
    d_printf("%s\n", "Starting to read optional console arguments...");
    if (parameters->mode == DISTRIBUTE) {
      // We need to check for n argument
      boolean nWasProvided = validateTotalAmountOfShadows(argv[6], argv[7], &parameters->totalShadows, error);
      if (nWasProvided && haveOptionalArguments(ARGS, 7)) {
        validateDir(argv[8], argv[9], &parameters->directory, error);
      } else {
        validateDir(argv[6], argv[7], &parameters->directory, error);
      }
    }
  }


  return parameters;
}

boolean
invalidAmountOfArgs(int args) {
  boolean even = (args % 2 == 0) ? TRUE : FALSE;
  if (args < MIN_REQUIRED_ARGS || args > MAX_ARGS || even) {
    return TRUE;
  }
  return FALSE;
}


void
validateModeType(char *arg, mode_type *mode, parameters_error *error) {
  if(strcmp(arg, S_DISTRIBUTE_ARG) == 0 || strcmp(arg, DISTRIBUTE_ARG) == 0) {
		*mode = DISTRIBUTE;
	} else if(strcmp(arg, S_RECOVER_ARG) == 0 || strcmp(arg, RECOVER_ARG) == 0) {
		*mode = RECOVER;
	} else {
		setError(error, MODE_ARG_ERROR);
	}
  d_printf("Mode: %s\n", MODE(arg));
}

void
validateSecret(char *arg, char *value,  char **secret, parameters_error *error) {

  if(strcmp(arg, S_SECRET_ARG) == 0 || strcmp(arg, SECRET_ARG) == 0) {
    char *s = calloc(SECRET_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    *secret = s;
    d_printf("Secret: %s\n", *secret);
  } else {
		setError(error, SECRET_ARG_ERROR);
  }
}

void
validateMinShadows(char *arg, char*value, char **number, parameters_error *error) {
  if(strcmp(arg, S_K_ARG) == 0 || strcmp(arg, K_ARG) == 0) {
    char *s = calloc(K_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    *number = s;
    d_printf("Min shadows: %s\n", *number);
  } else {
		setError(error, K_ARG_ERROR);
  }
}

boolean
validateTotalAmountOfShadows(char *arg, char*value, char **number, parameters_error *error) {
  if(strcmp(arg, S_N_ARG) == 0 || strcmp(arg, N_ARG) == 0) {
    char *s = calloc(N_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    *number = s;
    d_printf("Total shadows: %s\n", *number);
    return TRUE;
  }
  return FALSE;
}

void
validateDir(char *arg, char*value, char **number, parameters_error *error) {
  if(strcmp(arg, S_DIR_ARG) == 0 || strcmp(arg, DIR_ARG) == 0) {
    char *s = calloc(DIR_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    *number = s;
    d_printf("Directory: %s\n", *number);
  }
}

boolean
haveOptionalArguments(int argc, int lastReaded) {
  if (argc > lastReaded) {
    return TRUE;
  }
  return FALSE;
}

// Parameters structure functions
mode_type getMode(Parameters p) { return p->mode; }
char *getSecret(Parameters p) { return p->secret; }
int getMinShadows(Parameters p) { return atoi(p->minShadows); }
int getTotalShadows(Parameters p) { return atoi(p->totalShadows); }
char *getDirectory(Parameters p) { return p->directory; }
