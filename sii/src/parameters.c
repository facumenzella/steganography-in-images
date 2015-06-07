#include "../includes/parameters.h"
#include "../includes/constants.h"
#include "../includes/env.h"

#define MODE(s) (strcmp(s, "-d") == 0) ? "distribution" : (strcmp(s, "-r") == 0) ? "recover" : "invalid mode"

void validateModeType(char* arg, mode_type* mode, parameters_error *error);

void
validateParameters(int argc, char * argv[], mode_type *m, parameters_error *error) {

  // if(argc < MIN || argc > MAX) {
  //   strcpy(*error, QTY_ARGS_ERROR);
  //   return;
	// }

  validateModeType(argv[1], m, error);
}

void
validateModeType(char* arg, mode_type* mode, parameters_error *error) {

  if (DEBUGGING) {
    printf("mode: %s\n", MODE(arg));
  }

  if(strcmp(arg, S_DISTRIBUTE_ARG) == 0 || strcmp(arg, DISTRIBUTE_ARG) == 0) {
		*mode = DISTRIBUTE;
	} else if(strcmp(arg, S_RECOVER_ARG) == 0 || strcmp(arg, RECOVER_ARG) == 0) {
		*mode = RECOVER;
	} else {
    strcpy(*error, MODE_ARG_ERROR);
	}

}
