#include "../includes/parameters.h"

typedef struct parameters_t {
	mode_type mode;
	char *secret;
  int minShadowsToRecoverSecret;
  int totalAmountOfShadowsToDistributeSecret;
  char *directory;
}parameters_t;

boolean invalidAmountOfArgs(int args);
void setDefaultDir(char **dir);

mode_type validateModeType(char *arg, parameters_error *error);
char* validateSecret(char *arg, char *value, parameters_error *error);
int validateMinShadowsToRecoverSecret(char *arg, char*value, parameters_error *error);
boolean checkIfTotalAmountOfShadowsWasProvided(char *arg, char*value, parameters_error *error);
int validateTotalAmountOfShadowsToDistributeSecret(char *totalAmount, char *minShadows, parameters_error *error);
char* validateDir(char *arg, char*value, parameters_error *error);
boolean haveOptionalArguments(int argc, int lastReaded);

Parameters
validateParameters(int argc, char *argv[], parameters_error *error) {
  int ARGS = argc - 1; // we do not need the first argument
  if(invalidAmountOfArgs(ARGS)) {
		setError(error, QTY_ARGS_ERROR);
    return NULL;
	}

	Parameters parameters = malloc(sizeof(struct parameters_t));

  d_printf("\n%s\n", "Starting to read console arguments...");

  parameters->mode = validateModeType(argv[1], error);
  parameters->secret = validateSecret(argv[2], argv[3], error);
  parameters->minShadowsToRecoverSecret = validateMinShadowsToRecoverSecret(argv[4], argv[5], error);

  if (haveOptionalArguments(ARGS, 5)) {
    d_printf("%s\n", "Starting to read optional console arguments...");
    if (parameters->mode == DISTRIBUTE) {
      // We need to check for n argument
      boolean nWasProvided = checkIfTotalAmountOfShadowsWasProvided(argv[6], argv[7], error);
      if (nWasProvided) {
				parameters->totalAmountOfShadowsToDistributeSecret = validateTotalAmountOfShadowsToDistributeSecret(argv[6], argv[7], error);
        if (haveOptionalArguments(ARGS, 7)) {
					parameters->directory = validateDir(argv[8], argv[9], error);
        }
      } else if (haveOptionalArguments(ARGS, 5)) {
        parameters->directory = validateDir(argv[6], argv[7], error);
				if (parameters->directory == NULL) {
					setDefaultDir(&parameters->directory);
				}
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


mode_type
validateModeType(char *arg, parameters_error *error) {
  mode_type mode;
	if(strcmp(arg, S_DISTRIBUTE_ARG) == 0 || strcmp(arg, DISTRIBUTE_ARG) == 0) {
		mode = DISTRIBUTE;
	} else if(strcmp(arg, S_RECOVER_ARG) == 0 || strcmp(arg, RECOVER_ARG) == 0) {
		mode = RECOVER;
	} else {
		setError(error, MODE_ARG_ERROR);
	}
  d_printf("Mode: %s\n", MODE(arg));
	return mode;
}

char *
validateSecret(char *arg, char *value, parameters_error *error) {
	char *s = NULL;
  if(strcmp(arg, S_SECRET_ARG) == 0 || strcmp(arg, SECRET_ARG) == 0) {
    s = calloc(SECRET_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    d_printf("Secret: %s\n", s);
  } else {
		setError(error, SECRET_ARG_ERROR);
  }
	return s;
}

int
validateMinShadowsToRecoverSecret(char *arg, char*value, parameters_error *error) {
	char *s = NULL;
	if(strcmp(arg, S_K_ARG) == 0 || strcmp(arg, K_ARG) == 0) {
    s = calloc(K_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    d_printf("Min shadows: %s\n", s);
  } else {
		setError(error, K_ARG_ERROR);
  }
	int k = -1;
	if (s != NULL && (k = atoi(s)) >= 2) {
		return k;
	}
	return -1;
}

boolean
checkIfTotalAmountOfShadowsWasProvided(char *arg, char*value, parameters_error *error) {
  if(strcmp(arg, S_N_ARG) == 0 || strcmp(arg, N_ARG) == 0) {
    return TRUE;
  }
  return FALSE;
}

int
validateTotalAmountOfShadowsToDistributeSecret(char *totalAmount, char *minShadows, parameters_error *error) {
	// there is no validation because we have already validated
	char *s = calloc(N_MAX_LENGTH, sizeof(char));
  strcpy(s, minShadows);
  d_printf("Total shadows: %s\n", s);
	int n = -1;
	if ( (n = atoi(s) >= 2)) {
		return n;
	}
	return -1;
}

void
setDefaultDir(char **dir) {
	char *s = calloc(strlen(DIRECTORY_DEFAULT_VALUE), sizeof(char));
	strcpy(s, DIRECTORY_DEFAULT_VALUE);
	*dir = s;
	d_printf("Setting default directory: %s\n", *dir);
}

char*
validateDir(char *arg, char*value, parameters_error *error) {
	char *s = NULL;
	if(strcmp(arg, S_DIR_ARG) == 0 || strcmp(arg, DIR_ARG) == 0) {
    s = calloc(DIR_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    d_printf("Directory: %s\n", s);
  }
	return s;
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
int getMinShadowsToRecoverSecret(Parameters p) { return p->minShadowsToRecoverSecret; }
int getTotalAmountOfShadowsToDistributeSecret(Parameters p) { return p->totalAmountOfShadowsToDistributeSecret; }
char *getDirectory(Parameters p) { return p->directory; }
