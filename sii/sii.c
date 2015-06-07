// includes
#include "./includes/sii.h"
#include "./includes/constants.h"

int
main(int argc, char * argv[]) {

  mode_type mode;
  parameters_error error = calloc(1024, sizeof(char));
  validateParameters(argc, argv, &mode, &error);

  handleErrorIfNeeded(error);


}


int
handleErrorIfNeeded(parameters_error error) {
  handleError(error); // it prints if we are debugging
  if (error) {
    return -1;
  }
  return 0;
}
