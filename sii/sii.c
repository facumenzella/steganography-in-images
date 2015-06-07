// includes
#include "./includes/sii.h"
#include "./includes/constants.h"

int
main(int argc, char * argv[]) {

  mode_type mode;
  parameters_error error;
  validateParaemeters(argc, argv, &mode, &error);

  handleErrorIfNeeded(error);
}


int
handleErrorIfNeeded(parameters_error error) {
  printf("%s\n", error);
  // TODO print help
  return -1;
}
