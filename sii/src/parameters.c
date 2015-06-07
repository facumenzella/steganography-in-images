#include "../includes/parameters.h"
#include "../includes/errors.h"

void validateParaemeters(int argc, char * argv[], mode_type *m, parameters_error *error) {

  if(argc < MIN || argc > MAX) {
    *error = QTY_PARAMETERS_ERROR;
	}


}
