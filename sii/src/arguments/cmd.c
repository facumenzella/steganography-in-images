#include "../../includes/cmd.h"
#include "../../includes/arguments.h"

boolean invalidAmountOfArgs(int args);
char* defaultDir();

mode_type validateModeType(char *arg, arguments_error *error);
char* validateSecret(char *arg, char *value, arguments_error *error);
int validateMinShadowsToRecoverSecret(char *arg, char*value, arguments_error *error);
boolean checkIfTotalAmountOfShadowsWasProvided(char *arg, char*value, arguments_error *error);
int validateTotalAmountOfShadowsToDistributeSecret(char *totalAmount, char *minShadows, arguments_error *error);
char* validateDir(char *arg, char*value, arguments_error *error);
boolean haveOptionalArguments(int argc, int lastReaded);
boolean isValidWithinRelatedArguemtents(Arguments arguments);

Arguments
validateArguments(int argc, char *argv[], arguments_error *error) {
  int ARGS = argc - 1; // we do not need the first argument
  if(invalidAmountOfArgs(ARGS)) {
      setError(error, QTY_ARGS_ERROR);
      return NULL;
  }
    Arguments arguments = newArguments();
    
    printf("\n%s\n", "Starting to read console arguments...");
    
    setMode(arguments, validateModeType(argv[1], error));
    if (*error != NULL) {
		return NULL;
	}
    setSecret(arguments , validateSecret(argv[2], argv[3], error));
	if (*error != NULL) {
		return NULL;
	}
    setMinShadowsToRecoverSecret(arguments, validateMinShadowsToRecoverSecret(argv[4], argv[5], error));
    if (*error != NULL) {
		return NULL;
	}
    if (haveOptionalArguments(ARGS, 5)) {
        d_printf("%s\n", "Starting to read optional console arguments...");
        if (getMode(arguments) == DISTRIBUTE) {
            // We need to check for n argument
            boolean nWasProvided = checkIfTotalAmountOfShadowsWasProvided(argv[6], argv[7], error);
            if (nWasProvided == TRUE) {
                // n was provided
                setTotalAmountOfShadowsToDistributeSecret(arguments,
                                                          validateTotalAmountOfShadowsToDistributeSecret(argv[6], argv[7], error));
                if (*error != NULL) {
                    return NULL;
                }
                // We need to check for dir argument
                if (haveOptionalArguments(ARGS, 7) == TRUE) {
                    setDirectory(arguments, validateDir(argv[8], argv[9], error));
                }
            // Maybe they have only provided dir
            } else if (haveOptionalArguments(ARGS, 5) == TRUE) {
                setDirectory(arguments, validateDir(argv[6], argv[7], error));
            }
        }
    }
    // no dir, so we set the default
    if (getDirectory(arguments) == NULL) {
        setDirectory(arguments, defaultDir());
    }
    if (isValidWithinRelatedArguemtents(arguments) == FALSE) {
		setError(error, K_GREATER_THAN_N);
		return NULL;
	}
	return arguments;
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
validateModeType(char *arg, arguments_error *error) {
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
validateSecret(char *arg, char *value, arguments_error *error) {
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
validateMinShadowsToRecoverSecret(char *arg, char*value, arguments_error *error) {
	char *s = NULL;
	if(strcmp(arg, S_K_ARG) == 0 || strcmp(arg, K_ARG) == 0) {
    s = calloc(K_MAX_LENGTH, sizeof(char));
    strcpy(s, value);
    d_printf("Min shadows: %s\n", s);
  } else {
		setError(error, K_ARG_ERROR);
		return -1;
  }
	int k = -1;
	if ((k = atoi(s)) < 2) {
		setError(error, K_LOWER_THAN_2);
		return -1;
	}
	return k;
}

boolean
checkIfTotalAmountOfShadowsWasProvided(char *arg, char*value, arguments_error *error) {
  if(strcmp(arg, S_N_ARG) == 0 || strcmp(arg, N_ARG) == 0) {
    return TRUE;
  }
  return FALSE;
}

int
validateTotalAmountOfShadowsToDistributeSecret(char *totalAmount, char *totalShadows, arguments_error *error) {
	// there is no validation because we have already validated
	char *s = calloc(N_MAX_LENGTH, sizeof(char));
  strcpy(s, totalShadows);
  d_printf("Total shadows: %s\n", s);
	int n = -1;
	if ( (n = atoi(s)) < 2) {
		setError(error, N_LOWER_THAN_2);
		return -1;
	}
	return n;
}

char*
defaultDir() {
	char *s = calloc(strlen(DIRECTORY_DEFAULT_VALUE), sizeof(char));
	strcpy(s, DIRECTORY_DEFAULT_VALUE);
	d_printf("Setting default directory: %s\n", s);
    return s;
}

char*
validateDir(char *arg, char*value, arguments_error *error) {
    char *s = NULL;
    if(strcmp(arg, S_DIR_ARG) == 0 || strcmp(arg, DIR_ARG) == 0) {
        s = calloc(DIR_MAX_LENGTH, sizeof(char));
        strcpy(s, value);
        d_printf("Setting directory: %s\n", s);
    } else {
        printf("%s\n", DIR_INVALID_ARGUMENT);
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

boolean
isValidWithinRelatedArguemtents(Arguments arguments) {
	// k <= n
	if ( (getTotalAmountOfShadowsToDistributeSecret(arguments) == -1) ||
        getMinShadowsToRecoverSecret(arguments) <= getTotalAmountOfShadowsToDistributeSecret(arguments)) {
		return TRUE;
	}
	return FALSE;
}
